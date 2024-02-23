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

static uint checkStaticResources();

static int getDownloadSource(const char *filename);

static Vision_FileCheck_result_t cb_general_sys_file(bool filePassedCheck);
static Vision_FileCheck_result_t cb_static_resources_json(bool filePassedCheck);
static Vision_FileCheck_result_t cb_static_resources_file(bool filePassedCheck);
static Vision_FileCheck_result_t cb_reboot_after_finish(bool filePassedCheck);

//////////////////////////////
//
//  Variables
//
//////////////////////////////
const char *fileDownloadPrefix[] = {
    "https://mr258876.github.io/Project_Vision_L/resources/0.3.0",
    "https://gitee.com/mr258876/Project_Vision_L/raw/static_resources/resources/0.3.0",
};

static const char *static_res_json_down_path = "/static_resources.json";
static const char *static_res_beta_down_path = "/static_resources_beta.json";
static const char *static_res_json_local_path = "/s/The Vision L/static_resources.json";

static Vision_FileCheck_file_t constFileCheckList[] = {
  {static_res_json_local_path, static_res_json_down_path, cb_static_resources_json}
};

Vision_FileCheck_result_t fileCheckResults[1];

LinkedList<Vision_FileCheck_file_t> staticFileDownloadList;

uint static_resources_err = 0;

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
  return (strcasecmp(&filename[strlen(filename) - strlen(ext)], ext) == 0);
}

static int getDownloadSource(const char *filename)
{
  if (IS_FILE_EXT(filename, ".bin"))
  {
    return 0;
  }
  return curr_lang;
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

static Vision_FileCheck_result_t cb_static_resources_json(bool filePassedCheck)
{
  if (filePassedCheck)
  {
    // 清除上一次检查添加的下载任务
    for (size_t i = 0; i < staticFileDownloadList.size(); i++)
    {
      if (staticFileDownloadList.get(i).file_cb == cb_static_resources_file)
      {
        staticFileDownloadList.remove(i);
        i -= 1;
      }
    }

    // 检查资源文件
    static_resources_err = checkStaticResources();

    // 此处为json文件的状态
    return VISION_FILE_OK;
  }
  return VISION_FILE_SYS_FILE_ERR;
}

static Vision_FileCheck_result_t cb_static_resources_file(bool filePassedCheck)
{
  return cb_general_sys_file(filePassedCheck);
}

static Vision_FileCheck_result_t cb_reboot_after_finish(bool filePassedCheck)
{
  if (filePassedCheck)
  {
    esp_restart();
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

  // 加载配置文件
  err = err | loadPlayList();
  err = err | loadHoyolabConfig();
  err = err | loadWeatherConfig();
  // err = err | loadConfig();

  if (setting_updateChannel == OTA_BETA_CHANNEL)
  {
    constFileCheckList[0].downloadPath = static_res_beta_down_path;
  }

  // 此处检查写在 constFileCheckList 变量中的文件
  SemaphoreHandle_t *FSMutex;
  struct stat stat_buf;
  int stat_res = 0;
  Vision_FileCheck_result_t fileResult;
  for (size_t i = 0; i < (sizeof(fileCheckResults) / sizeof(Vision_FileCheck_result_t)); i++)
  {
    FSMutex = get_FS_mutex(constFileCheckList[i].localPath[1]);
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    stat_res = stat(constFileCheckList[i].localPath.c_str(), &stat_buf);
    xSemaphoreGive(*FSMutex);

    fileResult = constFileCheckList[i].file_cb((stat_res == 0) && (stat_buf.st_size > 0) && (S_ISREG(stat_buf.st_mode)));
    fileCheckResults[i] = fileResult;
    err = err | fileResult;
  }

  err = err | static_resources_err;

  return err;
}

uint checkFileStatus()
{
  uint err = 0;
  for (size_t i = 0; i < sizeof(fileCheckResults) / sizeof(Vision_FileCheck_result_t); i++)
  {
    err = err | fileCheckResults[i];
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
    if (is_file_ext(fp, ".mjpeg") || is_file_ext(fp, ".jpg") || is_file_ext(fp, ".jpeg"))
    {
      lv_fs_res_t _input_op_result;
      lv_fs_file_t _input;
      _input_op_result = lv_fs_open(&_input, fp, LV_FS_MODE_RD);
      if (_input_op_result == LV_FS_RES_OK)
      {
        filePaths.add(String(fp));
      }
      lv_fs_close(&_input);
    }
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

    if (wp) delete wp;
    switch (provider)
    {
    case 0:
      wp = new OpenMeteoWeather();
      break;
    default:
      wp = new OpenMeteoWeather();
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
uint downloadFile(const char *url, const char *path_to_save, Vision_download_info_t *info)
{
  const char *HTTP_TAG = "downloadFile";
  String path0 = "";
  String path1 = path_to_save;

  ESP_LOGI(HTTP_TAG, "start download: %s", path_to_save);

  FILE *f;
  /* 根据驱动器号获取互斥量 */
  SemaphoreHandle_t *FSMutex = get_FS_mutex(path_to_save[1]);
  if (!FSMutex)
  {
    ESP_LOGE(HTTP_TAG, "could not get mutex!");
    return -1;
  }

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

  ESP_LOGI(HTTP_TAG, "from url: %s", url);

  esp_http_client_config_t conf = {
      .url = url,
      .method = HTTP_METHOD_GET,
      .crt_bundle_attach = esp_crt_bundle_attach,
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

  int content_length = esp_http_client_fetch_headers(client);

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

  /* 写入文件 */
  int read_len, write_len;
  if (info)
  {
    info->totalBytes = content_length;
    info->writtenBytes = 0;
  }
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

    if (info)
      info->writtenBytes += write_len;
  }

  xSemaphoreTake(*FSMutex, portMAX_DELAY);
  fclose(f);
  xSemaphoreGive(*FSMutex);

  esp_http_client_close(client);
  esp_http_client_cleanup(client);

  free(buffer);

  return DOWNLOAD_RES_OK;
}

void tsk_fixMissingFiles(void *parameter)
{
  Vision_download_info_t *info = (Vision_download_info_t *)parameter;
  info->result = DOWNLOAD_RES_DOWNLOADING;
  // 统计要下载的文件个数
  int listedFileCount = 0;
  info->total_file_count = 0;
  for (size_t i = 0; i < (sizeof(fileCheckResults) / sizeof(Vision_FileCheck_result_t)); i++)
  {
    if (fileCheckResults[i])
    {
      info->total_file_count += 1;
    }
  }
  listedFileCount = info->total_file_count;
  info->total_file_count += staticFileDownloadList.size();

  // 下载文件
  info->current_file_no = 0;
  for (size_t i = 0; i < (sizeof(fileCheckResults) / sizeof(Vision_FileCheck_result_t)); i++)
  {
    if (fileCheckResults[i] & VISION_FILE_SYS_FILE_ERR || fileCheckResults[i] & VISION_FILE_SYS_FILE_CRITICAL)
    {
      info->current_file_no += 1;

      /* 拼接url */
      /* 国内平台下载.bin需登录故指定从github下载 */
      char url[strlen(getFileDownloadPrefix(getDownloadSource(constFileCheckList[i].downloadPath.c_str()))) + strlen(constFileCheckList[i].downloadPath.c_str()) + 1];
      sprintf(url, "%s%s", getFileDownloadPrefix(getDownloadSource(constFileCheckList[i].downloadPath.c_str())), constFileCheckList[i].downloadPath.c_str());

      if (!downloadFile(url, constFileCheckList[i].localPath.c_str(), info)) // <- DOWNLOAD_RES_OK=0
      {
        fileCheckResults[i] = constFileCheckList[i].file_cb(true);
      }
    }

    info->total_file_count = listedFileCount + staticFileDownloadList.size(); // 重新计算需要下载的文件个数
  }

  Vision_FileCheck_file_t static_file;
  while (staticFileDownloadList.size() > 0)
  {
    static_file = staticFileDownloadList.pop();
    info->current_file_no += 1;

    /* 拼接url */
    /* 国内平台下载.bin需登录故指定从github下载 */
    char url[strlen(getFileDownloadPrefix(getDownloadSource(static_file.downloadPath.c_str()))) + strlen(static_file.downloadPath.c_str()) + 1];
    sprintf(url, "%s%s", getFileDownloadPrefix(getDownloadSource(static_file.downloadPath.c_str())), static_file.downloadPath.c_str());

    if (!downloadFile(url, static_file.localPath.c_str(), info)) // <- DOWNLOAD_RES_OK=0
    {
      static_file.file_cb(true);
    }
  }

  info->result = DOWNLOAD_RES_OK;
  vTaskDelete(NULL);
}

const char *getFileDownloadPrefix(int source)
{
  if (source == 1)
  {
    return fileDownloadPrefix[1];
  }
  return fileDownloadPrefix[0];
}

void updateFileDownload(const char *lp, const char *dp, bool reboot_when_finish)
{
  staticFileDownloadList.add({String(lp), String(dp), reboot_when_finish ? cb_reboot_after_finish : cb_general_sys_file});
}

//////////////////////////////
//
//  Check Static Resources
//
//////////////////////////////
static uint checkStaticResources()
{
  int err = VISION_FILE_OK;
  FILE *f;
  DynamicJsonDocument doc(STATIC_FILE_CONF_JSON_SIZE);
  DeserializationError error;
  char *buf = (char *)malloc(STATIC_FILE_CONF_DEFAULT_LENGTH);

  if (!buf)
  {
    return VISION_FILE_NOT_CHECK;
  }

  xSemaphoreTake(SDMutex, portMAX_DELAY);
  {
    /* 读取文件列表 */
    f = fopen("/s" STATIC_FILE_CONF_PATH, "r");
    if (!f)
    {
      /* 若返回空指针则说明文件不存在，返回错误 */
      fileCheckResults[0] = VISION_FILE_SYS_FILE_CRITICAL;
      fclose(f);
      xSemaphoreGive(SDMutex);
      free(buf);
      return VISION_FILE_SYS_FILE_CRITICAL;
    }
    /* 将文件内容读入缓存 */
    fread(buf, STATIC_FILE_CONF_DEFAULT_LENGTH, 1, f);
    fclose(f);
  }
  xSemaphoreGive(SDMutex);

  error = deserializeJson(doc, buf, STATIC_FILE_CONF_DEFAULT_LENGTH);

  if (error)
  {
    err = err | VISION_FILE_SYS_FILE_CRITICAL;
    doc.clear();
    free(buf);
    return err;
  }

  long static_resources_version = doc["static_resources_version"];
  if (static_resources_version)
  {
    info_static_resources_ver = static_resources_version;
  }

  JsonArray local_path = doc["local_path"];
  JsonArray download_path = doc["download_path"];
  JsonArray file_size = doc["file_size"];

  if (local_path.size() != download_path.size() || download_path.size() != file_size.size())
  {
    // 文件格式错误
    err = err | VISION_FILE_SYS_FILE_CRITICAL;
    doc.clear();
    free(buf);
    return err;
  }

  struct stat stat_buf;
  int stat_res = 0;
  for (size_t i = 0; i < local_path.size(); i++)
  {
    const char *lp = local_path[i];
    const char *dp = download_path[i];
    size_t sz = file_size[i];

    xSemaphoreTake(SDMutex, portMAX_DELAY);
    stat_res = stat(lp, &stat_buf);
    xSemaphoreGive(SDMutex);

    // 文件缺失
    if (stat_res == -1)
    {
      ESP_LOGE("checkStaticResources", "File missing: %s", lp);

      staticFileDownloadList.add({String(lp), String(dp), cb_static_resources_file});
      err = err | VISION_FILE_STATIC_FILE_ERR;
      continue;
    }

    // 文件不同相同将文件添加至下载列表
    if (!S_ISREG(stat_buf.st_mode) || stat_buf.st_size != sz)
    {
      ESP_LOGE("checkStaticResources", "File invalid: %s", lp);

      xSemaphoreTake(SDMutex, portMAX_DELAY);
      remove(lp);
      xSemaphoreGive(SDMutex);

      staticFileDownloadList.add({String(lp), String(dp), cb_static_resources_file});
      err = err | VISION_FILE_STATIC_FILE_ERR;
    }
  }

  doc.clear();
  free(buf);
  return err;
}