#include "system/FileCheck.h"

//////////////////////////////
//
//  Function declaraions
//
//////////////////////////////
static uint loadPlayList();
static uint loadHoyolabConfig();
static uint loadWeatherConfig();
static uint loadConfig();

static Vision_FileCheck_result_t cb_general_sys_file(bool filePassedCheck);
static Vision_FileCheck_result_t cb_ui_font_HanyiWenhei20(bool filePassedCheck);

//////////////////////////////
//
//  Variables
//
//////////////////////////////
const char *fileDownloadPrefix[] = {
    "https://mr258876.github.io/Project_Vision_L/resources/0.2.1",
};

const char *updateConfPath = "update.json";

static const Vision_FileCheck_t fileCheckFiles[] = {
    {"/s/The Vision L/fonts/ui_font_HanyiWenhei20.bin", "/fonts/ui_font_HanyiWenhei20.bin", cb_ui_font_HanyiWenhei20},
    {"/s/The Vision L/utility/index.html", "/utility/index.html", cb_general_sys_file},
    {"/s/The Vision L/utility/css/mdui.min.css", "/utility/css/mdui.min.css", cb_general_sys_file},
    {"/s/The Vision L/utility/js/mdui.min.js", "/utility/js/mdui.min.js", cb_general_sys_file},
    {"/s/The Vision L/utility/js/jquery-3.6.3.min.js", "/utility/js/jquery-3.6.3.min.js", cb_general_sys_file},
    {"/s/The Vision L/utility/icons/material-icons/MaterialIcons-Regular.ijmap", "/utility/icons/material-icons/MaterialIcons-Regular.ijmap", cb_general_sys_file},
    {"/s/The Vision L/utility/icons/material-icons/MaterialIcons-Regular.woff2", "/utility/icons/material-icons/MaterialIcons-Regular.woff2", cb_general_sys_file},
    {"/s/The Vision L/utility/images/Liyue.png", "/utility/images/Liyue.png", cb_general_sys_file},
    {"/s/The Vision L/utility/images/Liyue_Extended.png", "/utility/images/Liyue_Extended.png", cb_general_sys_file},
    {"/s/The Vision L/utility/images/Mondstadt.png", "/utility/images/Mondstadt.png", cb_general_sys_file},
};

Vision_FileCheck_result_t fileCheckResults[10];

//////////////////////////////
//
//  Helper fcuntions
//
//////////////////////////////
static SemaphoreHandle_t *get_FS_mutex(char drv_letter)
{
  switch (drv_letter)
  {
  case 's':
    return &SDMutex;
  case 'f':
    return &FlashMutex;
  default:
    return nullptr;
  }
}

static bool is_file_ext(const char *filename, const char *ext)
{
  return (strcasecmp(&filename[strlen(filename) - sizeof(ext) + 1], ext) == 0);
}

//////////////////////////////
//
//  File check callbacks
//
//////////////////////////////
Vision_FileCheck_result_t cb_general_sys_file(bool filePassedCheck)
{
  if (filePassedCheck)
    return VISION_FILE_OK;
  return VISION_FILE_SYS_FILE_ERR;
}

Vision_FileCheck_result_t cb_ui_font_HanyiWenhei20(bool filePassedCheck)
{
  if (filePassedCheck)
  {
    flag_ui_font_HanyiWenhei20 = true;
    return VISION_FILE_OK;
  }
  else
  {
    return VISION_FILE_SYS_FILE_ERR;
  }
}

//////////////////////////////
//
//  Check Files & Load Config
//
//////////////////////////////
uint checkSDFiles()
{
  int err = VISION_FILE_OK;

  err = err | loadPlayList();
  err = err | loadHoyolabConfig();
  err = err | loadWeatherConfig();
  // err = err | loadConfig();

  SemaphoreHandle_t *FSMutex;
  FILE *f;
  Vision_FileCheck_result_t fileResult;
  for (size_t i = 0; i < (sizeof(fileCheckResults) / sizeof(Vision_FileCheck_result_t)); i++)
  {
    FSMutex = get_FS_mutex(fileCheckFiles[i].localPath[1]);
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
      f = fopen(fileCheckFiles[i].localPath, "r");
      fileResult = fileCheckFiles[i].file_cb(f ? true : false);
      if (f)
        fclose(f);
      fileCheckResults[i] = fileResult;
      err = err | fileResult;
    }
    xSemaphoreGive(*FSMutex);
  }

  return err;
}

static uint loadPlayList()
{
  int err = VISION_FILE_OK;
  FILE *f;
  StaticJsonDocument<PLAY_LIST_JSON_SIZE> doc;
  DeserializationError error;
  char buf[PLAY_LIST_CONF_DEFAULT_LENGTH];

  xSemaphoreTake(SDMutex, portMAX_DELAY);
  {
    /* 读取播放文件列表 */
    f = fopen("/s" PLAY_LIST_CONF_PATH, "r");
    if (!f)
    {
      /* 若返回空指针则说明文件不存在，新建文件并写入默认配置，随后重新打开 */
      fclose(f);
      f = fopen("/s" PLAY_LIST_CONF_PATH, "w");
      fwrite(PLAY_LIST_DEFAULT_CONF, sizeof(PLAY_LIST_DEFAULT_CONF), 1, f);
      fclose(f);
      f = fopen("/s" PLAY_LIST_CONF_PATH, "r");
    }
    /* 将文件内容读入缓存 */
    fread(buf, PLAY_LIST_CONF_DEFAULT_LENGTH, 1, f);
    fclose(f);
  }
  xSemaphoreGive(SDMutex);

  error = deserializeJson(doc, buf, PLAY_LIST_CONF_DEFAULT_LENGTH);

  if (error)
  {
    err = err | VISION_FILE_PLAYLIST_CRITICAL;
    return err;
  }

  JsonArray files = doc["files"];

  filePaths.clear();
  for (const char *fp : files)
  {
    if ((!is_file_ext(fp, ".mjpeg")) && (!is_file_ext(fp, ".jpg")) && (!is_file_ext(fp, ".jpeg")))
    {
      continue;
    }

    lv_fs_res_t _input_op_result;
    lv_fs_file_t _input;
    _input_op_result = lv_fs_open(&_input, fp, LV_FS_MODE_RD);
    if (_input_op_result == LV_FS_RES_OK)
    {
      filePaths.add(String(fp));
    }
    lv_fs_close(&_input);
  }

  if (filePaths.size() < 1)
    err = err | VISION_FILE_PLAYLIST_ERR;

  files.clear();
  doc.clear();

  return err;
}

static uint loadHoyolabConfig()
{
  int err = VISION_FILE_OK;
  FILE *f;
  StaticJsonDocument<HOYOLAB_CONF_JSON_SIZE> doc;
  DeserializationError error;
  char buf[HOYOLAB_CONF_DEFAULT_LENGTH];

  xSemaphoreTake(SDMutex, portMAX_DELAY);
  {
    /* 打开米游社配置文件 */
    f = fopen("/s" HOYOLAB_CONF_PATH, "r");
    if (!f)
    {
      /* 若不存在则直接返回 */
      fclose(f);
      xSemaphoreGive(SDMutex);
      return err;
    }
    fread(buf, HOYOLAB_CONF_DEFAULT_LENGTH, 1, f);
    fclose(f);
  }
  xSemaphoreGive(SDMutex);

  error = deserializeJson(doc, buf, HOYOLAB_CONF_DEFAULT_LENGTH);

  if (error)
  {
    err = err | VISION_FILE_CONF_CRITICAL;
    return err;
  }

  const char *uid = doc["uid"];
  const char *cookie = doc["cookie"];
  const char *guid = doc["device_guid"];

  // not making any check for in case to remove uid and cookie
  prefs.putString("hoyolabUID", uid);
  prefs.putString("hoyolabCookie", cookie);
  hyc.begin(cookie, uid);

  if (guid && strlen(guid) == 32) // 手动指定guid
  {
    if (!info_deviceGuid.equals(guid))
    {
      info_deviceGuid = String(guid);
      prefs.putString("deviceGuid", info_deviceGuid);
    }
    hyc.setDeviceGuid(info_deviceGuid.c_str());
  }
  else if (info_deviceGuid.length() != 32) // 未手动指定guid且guid不存在则生成一个guid并保存
  {
    info_deviceGuid = HoyoverseClient::generateGuid();
    prefs.putString("deviceGuid", info_deviceGuid);
    hyc.setDeviceGuid(info_deviceGuid.c_str());
  }
  else // 未手动指定guid但已生成则使用已有guid
  {
    hyc.setDeviceGuid(info_deviceGuid.c_str());
  }

  xSemaphoreTake(SDMutex, portMAX_DELAY);
  {
    remove("/s" HOYOLAB_CONF_PATH); // delete the file after conf imported
  }
  xSemaphoreGive(SDMutex);

  doc.clear();

  return err;
}

static uint loadWeatherConfig()
{
  int err = VISION_FILE_OK;
  FILE *f;
  StaticJsonDocument<WEATHER_CONF_JSON_SIZE> doc;
  DeserializationError error;
  char buf[WEATHER_CONF_DEFAULT_LENGTH];

  xSemaphoreTake(SDMutex, portMAX_DELAY);
  {
    /* 打开米游社配置文件 */
    f = fopen("/s" WEATHER_CONF_PATH, "r");
    if (!f)
    {
      /* 若不存在则直接返回 */
      fclose(f);
      xSemaphoreGive(SDMutex);
      return err;
    }
    fread(buf, WEATHER_CONF_DEFAULT_LENGTH, 1, f);
    fclose(f);
  }
  xSemaphoreGive(SDMutex);

  error = deserializeJson(doc, buf, WEATHER_CONF_DEFAULT_LENGTH);

  if (error)
  {
    err = err | VISION_FILE_CONF_CRITICAL;
    return err;
  }

  const char *city = doc["city"];     // "深圳"
  float latitude = doc["latitude"];   // 12.7
  float longitude = doc["longitude"]; // 3.5
  int provider = doc["provider"];     // 0

  // if (provider >= 0 && provider <= 1)
  if (provider == 1)
  {
    prefs.putString("weatherCity", city);
    prefs.putFloat("weatherLat", latitude);
    prefs.putFloat("weatherLong", longitude);
    prefs.putInt("weatherProvider", provider);

    switch (provider)
    {
    case 0:
      // wp = &OpenMeteo;
      break;
    default:
      wp = &MojiTianqi;
      break;
    }
    wp->setCity(city);
    wp->setCoordinate(latitude, longitude);
  }

  xSemaphoreTake(SDMutex, portMAX_DELAY);
  {
    remove("/s" WEATHER_CONF_PATH); // delete the file after conf imported
  }
  xSemaphoreGive(SDMutex);

  doc.clear();

  return err;
}

//////////////////////////////
//
//  File downloader
//
//////////////////////////////
uint downloadFile(const char *url, const char *path_to_save, const char *TLScert)
{
  const char *HTTP_TAG = "downloadFile";
  String path0 = "";
  String path1 = path_to_save;

  FILE *f;
  /* 根据驱动器号获取互斥量 */
  SemaphoreHandle_t *FSMutex = get_FS_mutex(path_to_save[1]);
  if (!FSMutex)
    return -1;

  /* 创建多层文件夹 */
  path0 = path1.substring(0, 3);
  path1 = path1.substring(3);
  while (path1.indexOf("/") >= 0)
  {
    path0.concat(path1.substring(0, path1.indexOf("/")));
    path1 = path1.substring(path1.indexOf("/") + 1);
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    if (access(path0.c_str(), F_OK) == -1)
    {
      mkdir(path0.c_str(), 0777);
    }
    xSemaphoreGive(*FSMutex);
    path0.concat('/');
  }

  esp_http_client_config_t conf = {
      .url = url,
      .cert_pem = TLScert,
      .method = HTTP_METHOD_GET,
      .keep_alive_enable = false,
  };

  esp_http_client_handle_t client = esp_http_client_init(&conf);
  if (!client)
  {
    ESP_LOGE(HTTP_TAG, "HTTP client init failed!");
    return DOWNLOAD_RES_HTTP_OPEN_FAIL;
  }

  /* Execute query */
  esp_err_t http_err;
  if ((http_err = esp_http_client_open(client, 0)) != ESP_OK)
  {
    ESP_LOGE(HTTP_TAG, "Failed to open HTTP connection: %s", esp_err_to_name(http_err));
    return DOWNLOAD_RES_HTTP_OPEN_FAIL;
  }

  int status_code = esp_http_client_get_status_code(client);
  if (status_code >= 400)
  {
    ESP_LOGE(HTTP_TAG, "HTTP abnormal status code: %d", status_code);
    return DOWNLOAD_RES_HTTP_READ_FAIL;
  }

  /* 打开文件 */
  xSemaphoreTake(*FSMutex, portMAX_DELAY);
  f = fopen(path_to_save, "w");
  xSemaphoreGive(*FSMutex);
  if (!f)
  {
    ESP_LOGE(HTTP_TAG, "Could not open file! Path=%s", path_to_save);
    return DOWNLOAD_RES_FILE_OPEN_FAIL;
  }

  char *buffer = (char *)malloc(FILE_DOWNLOAD_RECV_BUFFER_SIZE);
  if (buffer == NULL)
  {
    ESP_LOGE(HTTP_TAG, "Cannot malloc http receive buffer");
    return DOWNLOAD_RES_OUT_OF_MEM;
  }

  int content_length = esp_http_client_fetch_headers(client);
  int read_len, write_len;
  while (1)
  {
    read_len = esp_http_client_read(client, buffer, FILE_DOWNLOAD_RECV_BUFFER_SIZE);
    if (read_len <= 0)
    {
      if (esp_http_client_is_complete_data_received(client))
      {
        break;
      }
      xSemaphoreTake(*FSMutex, portMAX_DELAY);
      fclose(f);
      remove(path_to_save);
      xSemaphoreGive(*FSMutex);

      ESP_LOGE(HTTP_TAG, "Error reading data");
      free(buffer);
      return DOWNLOAD_RES_HTTP_READ_FAIL;
    }
    else
    {
      xSemaphoreTake(*FSMutex, portMAX_DELAY);
      write_len = fwrite(buffer, read_len, 1, f);
      xSemaphoreGive(*FSMutex);

      if (write_len != 1)
      {
        xSemaphoreTake(*FSMutex, portMAX_DELAY);
        fclose(f);
        remove(path_to_save);
        xSemaphoreGive(*FSMutex);

        ESP_LOGE(HTTP_TAG, "Error writing data, path=%s", path_to_save);
        free(buffer);
        return DOWNLOAD_RES_FILE_WRITE_FAIL;
      }
    }
  }

  xSemaphoreTake(*FSMutex, portMAX_DELAY);
  fclose(f);
  xSemaphoreGive(*FSMutex);

  esp_http_client_close(client);
  esp_http_client_cleanup(client);

  return DOWNLOAD_RES_OK;
}

uint fixMissingFiles()
{
  uint res = 0;
  for (size_t i = 0; i < (sizeof(fileCheckResults) / sizeof(Vision_FileCheck_result_t)); i++)
  {
    if (fileCheckResults[i])
    {
      /* 拼接url */
      char url[strlen(getFileDownloadPrefix()) + strlen(fileCheckFiles[i].downloadPath) + 1];
      sprintf(url, "%s%s", getFileDownloadPrefix(), fileCheckFiles[i].downloadPath);

      if (downloadGithubFile(url, fileCheckFiles[i].localPath)) // <- DOWNLOAD_RES_OK=0
      {
        res = res | fileCheckResults[i];
      }
      else
      {
        fileCheckFiles[i].file_cb(true);
      }
    }
  }
  return res;
}

uint downloadGithubFile(const char *url, const char *path_to_save)
{
  return downloadFile(url, path_to_save, GlobalSign_Root_CA);
}

const char *getFileDownloadPrefix()
{
  // if (curr_lang == 1)
  // {
  //   return fileDownloadPrefix[1];
  // }
  return fileDownloadPrefix[0];
}