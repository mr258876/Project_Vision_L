#include "APIServer.h"

//////////////////////////////
//
//  局部变量
//
//////////////////////////////

httpd_handle_t s;

//////////////////////////////
//
//  函数声明
//
//////////////////////////////

static esp_err_t root_handler(httpd_req_t *req);
static esp_err_t info_handler(httpd_req_t *req);

static esp_err_t playlist_get_handler(httpd_req_t *req);
static esp_err_t playlist_post_handler(httpd_req_t *req);

static esp_err_t file_listdir_handler(httpd_req_t *req);
static esp_err_t file_get_handler(httpd_req_t *req);
static esp_err_t file_post_handler(httpd_req_t *req);
static esp_err_t file_delete_handler(httpd_req_t *req);
static esp_err_t file_makedir_handler(httpd_req_t *req);

static esp_err_t hoyolab_conf_get_handler(httpd_req_t *req);
static esp_err_t hoyolab_conf_post_handler(httpd_req_t *req);

static esp_err_t setting_auto_bright_get_handler(httpd_req_t *req);
static esp_err_t setting_auto_rotate_get_handler(httpd_req_t *req);
static esp_err_t setting_brightness_get_handler(httpd_req_t *req);
static esp_err_t setting_volume_get_handler(httpd_req_t *req);
static esp_err_t setting_language_get_handler(httpd_req_t *req);
static esp_err_t setting_timezone_get_handler(httpd_req_t *req);

static esp_err_t weather_city_get_handler(httpd_req_t *req);

//////////////////////////////
//
//  URI结构体
//
//////////////////////////////

/* GET / 的 URI 处理结构 */
httpd_uri_t uri_root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = root_handler,
    .user_ctx = NULL};

/* GET /info 的 URI 处理结构 */
httpd_uri_t uri_info = {
    .uri = "/api/v1/info",
    .method = HTTP_GET,
    .handler = info_handler,
    .user_ctx = NULL};

/* GET /playlist 的 URI 处理结构 */
httpd_uri_t uri_playlist_get = {
    .uri = "/api/v1/playlist",
    .method = HTTP_GET,
    .handler = playlist_get_handler,
    .user_ctx = NULL};

/* POST /playlist 的 URI 处理结构 */
httpd_uri_t uri_playlist_post = {
    .uri = "/api/v1/playlist",
    .method = HTTP_POST,
    .handler = playlist_post_handler,
    .user_ctx = NULL};

/* GET /file/listdir 的 URI 处理结构 */
httpd_uri_t uri_file_listdir = {
    .uri = "/api/v1/file/listdir",
    .method = HTTP_GET,
    .handler = file_listdir_handler,
    .user_ctx = NULL};

/* GET /file/file 的 URI 处理结构 */
httpd_uri_t uri_file_get = {
    .uri = "/api/v1/file",
    .method = HTTP_GET,
    .handler = file_get_handler,
    .user_ctx = NULL};

/* POST /file/file 的 URI 处理结构 */
httpd_uri_t uri_file_post = {
    .uri = "/api/v1/file",
    .method = HTTP_POST,
    .handler = file_post_handler,
    .user_ctx = NULL};

/* DELETE /file/file 的 URI 处理结构 */
httpd_uri_t uri_file_delete = {
    .uri = "/api/v1/file",
    .method = HTTP_DELETE,
    .handler = file_delete_handler,
    .user_ctx = NULL};

/* POST /file/makedir 的 URI 处理结构 */
httpd_uri_t uri_file_makedir = {
    .uri = "/api/v1/file/makedir",
    .method = HTTP_POST,
    .handler = file_makedir_handler,
    .user_ctx = NULL};

/* GET /hoyolab/conf 的 URI 处理结构 */
httpd_uri_t uri_hoyolab_conf_get = {
    .uri = "/api/v1/hoyolab/conf",
    .method = HTTP_GET,
    .handler = hoyolab_conf_get_handler,
    .user_ctx = NULL};

/* POST /hoyolab/conf 的 URI 处理结构 */
httpd_uri_t uri_hoyolab_conf_post = {
    .uri = "/api/v1/hoyolab/conf",
    .method = HTTP_POST,
    .handler = hoyolab_conf_post_handler,
    .user_ctx = NULL};

/* GET /setting/auto_bright 的 URI 处理结构 */
httpd_uri_t uri_setting_auto_bright_get = {
    .uri = "/api/v1/setting/auto_bright",
    .method = HTTP_GET,
    .handler = setting_auto_bright_get_handler,
    .user_ctx = NULL};

/* GET /setting/auto_rotate 的 URI 处理结构 */
httpd_uri_t uri_setting_auto_rotate_get = {
    .uri = "/api/v1/setting/auto_rotate",
    .method = HTTP_GET,
    .handler = setting_auto_rotate_get_handler,
    .user_ctx = NULL};

/* GET /setting/brightness 的 URI 处理结构 */
httpd_uri_t uri_setting_brightness_get = {
    .uri = "/api/v1/setting/brightness",
    .method = HTTP_GET,
    .handler = setting_brightness_get_handler,
    .user_ctx = NULL};

/* GET /setting/volume 的 URI 处理结构 */
httpd_uri_t uri_setting_volume_get = {
    .uri = "/api/v1/setting/volume",
    .method = HTTP_GET,
    .handler = setting_volume_get_handler,
    .user_ctx = NULL};

/* GET /setting/language 的 URI 处理结构 */
httpd_uri_t uri_setting_language_get = {
    .uri = "/api/v1/setting/language",
    .method = HTTP_GET,
    .handler = setting_language_get_handler,
    .user_ctx = NULL};

/* GET /setting/timezone 的 URI 处理结构 */
httpd_uri_t uri_setting_timezone_get = {
    .uri = "/api/v1/setting/timezone",
    .method = HTTP_GET,
    .handler = setting_timezone_get_handler,
    .user_ctx = NULL};

/* GET /weather/city 的 URI 处理结构 */
httpd_uri_t uri_weather_city_get = {
    .uri = "/api/v1/weather/city",
    .method = HTTP_GET,
    .handler = weather_city_get_handler,
    .user_ctx = NULL};

//////////////////////////////
//
//  helper 函数
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

int remove_files(const char *path)
{
    /* 根据驱动器号获取互斥量 */
    SemaphoreHandle_t *FSMutex = get_FS_mutex(path[1]);
    if (!FSMutex)
        return -1;

    struct stat file_stat;
    int res;
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        res = stat(path, &file_stat);
    }
    xSemaphoreGive(*FSMutex);
    if (res == -1)
        return -1;

    if (S_ISDIR(file_stat.st_mode))
    {
        // Is directory
        DIR *dir;
        dirent *f_dirent;
        xSemaphoreTake(*FSMutex, portMAX_DELAY);
        {
            dir = opendir(path);
        }
        xSemaphoreGive(*FSMutex);
        while (1)
        {
            xSemaphoreTake(*FSMutex, portMAX_DELAY);
            {
                f_dirent = readdir(dir);
            }
            xSemaphoreGive(*FSMutex);

            if (f_dirent)
            {
                char p[strlen(path) + strlen(f_dirent->d_name) + 2];
                sprintf(p, "%s/%s", path, f_dirent->d_name);
                if (f_dirent->d_type == DT_DIR)
                {
                    res = remove_files(p);
                    if (res == -1)
                        return -1;
                }
                else
                {
                    xSemaphoreTake(*FSMutex, portMAX_DELAY);
                    {
                        res = remove(p);
                    }
                    xSemaphoreGive(*FSMutex);
                    if (res == -1)
                        return -1;
                }
            }
            else
                break;
        }
        xSemaphoreTake(*FSMutex, portMAX_DELAY);
        {
            res = rmdir(path);
        }
        xSemaphoreGive(*FSMutex);
    }
    else
    {
        // Regular file
        xSemaphoreTake(*FSMutex, portMAX_DELAY);
        {
            res = remove(path);
        }
        xSemaphoreGive(*FSMutex);
    }

    return res;
}

#define IS_FILE_EXT(filename, ext) \
    (strcasecmp(&filename[strlen(filename) - sizeof(ext) + 1], ext) == 0)

/* 设置header中的content-type */
static esp_err_t set_content_type_from_file(httpd_req_t *req, const char *filename)
{
    if (IS_FILE_EXT(filename, ".pdf"))
    {
        return httpd_resp_set_type(req, "application/pdf");
    }
    else if (IS_FILE_EXT(filename, ".json"))
    {
        return httpd_resp_set_type(req, "application/json");
    }
    else if (IS_FILE_EXT(filename, ".html"))
    {
        return httpd_resp_set_type(req, "text/html");
    }
    else if (IS_FILE_EXT(filename, ".jpeg"))
    {
        return httpd_resp_set_type(req, "image/jpeg");
    }
    else if (IS_FILE_EXT(filename, ".ico"))
    {
        return httpd_resp_set_type(req, "image/x-icon");
    }
    else if (IS_FILE_EXT(filename, ".wav"))
    {
        return httpd_resp_set_type(req, "audio/wav");
    }
    /* This is a limited set only */
    /* For any other type always set as binary data */
    return httpd_resp_set_type(req, "application/octet-stream");
}

/* url字符转16进制 */
static unsigned char h2int(char c)
{
    if (c >= '0' && c <= '9')
    {
        return ((unsigned char)c - '0');
    }
    if (c >= 'a' && c <= 'f')
    {
        return ((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <= 'F')
    {
        return ((unsigned char)c - 'A' + 10);
    }
    return (0);
}

/* url解码 */
static String urldecode(String str)
{

    String encodedString = "";
    char c;
    char code0;
    char code1;
    for (int i = 0; i < str.length(); i++)
    {
        c = str.charAt(i);
        if (c == '+')
        {
            encodedString += ' ';
        }
        else if (c == '%')
        {
            i++;
            code0 = str.charAt(i);
            i++;
            code1 = str.charAt(i);
            c = (h2int(code0) << 4) | h2int(code1);
            encodedString += c;
        }
        else
        {

            encodedString += c;
        }
    }

    // 移除最后一个斜杠 <- 似乎打开目录的时候有些bug
    if (encodedString.endsWith("/"))
    {
        encodedString.remove(encodedString.length() - 1);
    }

    return encodedString;
}

//////////////////////////////
//
//  函数实现
//
//////////////////////////////

/* 根目录跳转 */
static esp_err_t root_handler(httpd_req_t *req)
{
    httpd_resp_set_status(req, "302	Found");
    httpd_resp_set_type(req, HTTPD_TYPE_TEXT);
    httpd_resp_set_hdr(req, "Location", "https://mr258876.github.io/Project_Vision_L/"); // Redirect to page on github
    httpd_resp_send(req, "<html><h2>Please visit the management page here:</h2><br><a href=\"https://mr258876.github.io/Project_Vision_L/\">Project_Vision_L</a></html>", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取神之眼基本信息 */
static esp_err_t info_handler(httpd_req_t *req)
{
    // 获取app版本
    const esp_app_desc_t *running_app_info = esp_ota_get_app_description();

    String json = "";
    StaticJsonDocument<256> doc;
    doc["device_name"] = setting_deviceName;
    doc["app_version"] = running_app_info->version;
    doc["hw_version"] = info_hwType;
    doc["mac_address"] = info_macAddress;

    serializeJson(doc, json);
    doc.clear();

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, json.c_str(), HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取播放列表 */
static esp_err_t playlist_get_handler(httpd_req_t *req)
{
    String json = "";
    StaticJsonDocument<1024> doc;
    JsonArray files = doc.createNestedArray("files");

    if (filePaths.size() > 0)
    {
        ListNode<String> *fp = filePaths.getRoot();
        do
        {
            files.add(fp->data);
            fp = fp->next;
        } while (fp);
    }

    serializeJson(doc, json);
    doc.clear();

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, json.c_str(), HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 设置播放列表 */
static esp_err_t playlist_post_handler(httpd_req_t *req)
{
    char post_ctx[1024];

    /* 如果内容长度大于缓冲区则截断 */
    size_t recv_size = min(req->content_len, sizeof(post_ctx));

    int ret = httpd_req_recv(req, post_ctx, recv_size);
    if (ret <= 0)
    { /* 返回 0 表示连接已关闭 */
        /* 检查是否超时 */
        if (ret == HTTPD_SOCK_ERR_TIMEOUT)
        {
            /* 如果是超时，可以调用 httpd_req_recv() 重试
             * 简单起见，这里我们直接
             * 响应 HTTP 408（请求超时）错误给客户端 */
            httpd_resp_send_408(req);
        }
        /* 如果发生了错误，返回 ESP_FAIL 确保底层套接字被关闭 */
        return ESP_FAIL;
    }

    StaticJsonDocument<1024> doc;
    DeserializationError error;

    error = deserializeJson(doc, (const char *)post_ctx, recv_size);
    if (error)
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Error when deserializing json\",\"code\":-1}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    JsonArray files = doc["files"];

    if (files.isNull() || files[0].isNull())
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid JSON\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    int error_count = 0;

    filePaths.clear();

    for (const char *fp : files)
    {
        lv_fs_res_t _input_op_result;
        lv_fs_file_t _input;
        _input_op_result = lv_fs_open(&_input, fp, LV_FS_MODE_RD);
        if (_input_op_result == LV_FS_RES_OK)
            filePaths.add(String(fp));
        else
            error_count += 1;
        lv_fs_close(&_input);
    }

    // 返回新的播放列表
    String json = "";
    files.clear();

    if (filePaths.size() > 0)
    {
        ListNode<String> *fp = filePaths.getRoot();
        do
        {
            files.add(fp->data);
            fp = fp->next;
        } while (fp);
    }

    serializeJson(doc, json);
    doc.clear();

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, json.c_str(), HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取目录下文件列表 */
/* @param path: 文件夹路径，通过url传参 */
static esp_err_t file_listdir_handler(httpd_req_t *req)
{
    char str[512];
    char path[512];

    /* 获取url中参数 */
    if (httpd_req_get_url_query_str(req, str, 512)) // <-- ESP_OK = 0
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid query\",\"code\":-1}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }
    /* 提取路径 */
    if (httpd_query_key_value(str, "path", path, 512)) // <-- ESP_OK = 0
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid path\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    /* 根据驱动器号获取互斥量 */
    SemaphoreHandle_t *FSMutex = get_FS_mutex(path[1]);
    if (!FSMutex)
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"No such volume\",\"code\":-5}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    /* 尝试打开文件夹(检测路径是否存在) */
    strcpy(path, urldecode(path).c_str());
    DIR *dir;
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        dir = opendir(path);
    }
    xSemaphoreGive(*FSMutex);
    if (!dir)
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Unable to open path\",\"code\":-3}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    DynamicJsonDocument doc(4096);
    JsonArray files = doc.createNestedArray("files");
    dirent *f_dirent;
    /* 将文件名添加至列表 */
    while (1)
    {
        strcpy(str, "");
        xSemaphoreTake(*FSMutex, portMAX_DELAY);
        {
            f_dirent = readdir(dir);
        }
        xSemaphoreGive(*FSMutex);
        if (!f_dirent)
        {
            break;
        }

        if (f_dirent->d_type == DT_REG)
        {
            files.add(f_dirent->d_name);
        }
        else if (f_dirent->d_type == DT_DIR)
        {
            // Is directiory
            String fn = String("/") + f_dirent->d_name;
            files.add(fn);
        }
    }
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        closedir(dir);
    }
    xSemaphoreGive(*FSMutex);

    String json = "";
    serializeJson(doc, json);
    doc.clear();

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, json.c_str(), HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 下载文件 */
/* @param path: 文件路径，通过url传参 */
static esp_err_t file_get_handler(httpd_req_t *req)
{
    char str[512];
    char path[512];

    /* 获取url中参数 */
    if (httpd_req_get_url_query_str(req, str, 512)) // <-- ESP_OK = 0
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid query\",\"code\":-1}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }
    /* 提取路径 */
    if (httpd_query_key_value(str, "path", path, 512)) // <-- ESP_OK = 0
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid path\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    /* 根据驱动器号获取互斥量 */
    SemaphoreHandle_t *FSMutex = get_FS_mutex(path[1]);
    if (!FSMutex)
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"No such volume\",\"code\":-5}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    /* 尝试打开文件(检测路径是否存在) */
    strcpy(path, urldecode(path).c_str());
    struct stat file_stat;
    int stat_res;
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        stat_res = stat(path, &file_stat);
    }
    xSemaphoreGive(*FSMutex);
    if (stat_res == -1)
    {
        ESP_LOGE("file_get_handler", "Open file fail!\"code\":%d", errno);
        httpd_resp_set_status(req, HTTPD_404);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"File not exist\",\"code\":-6}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    FILE *fd = nullptr;
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        fd = fopen(path, "r");
    }
    xSemaphoreGive(*FSMutex);

    if (!fd)
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Unable to open file\",\"code\":-3}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    /* 设置header中的Content-type */
    set_content_type_from_file(req, path);

    /* 设置header中的Content-disposition */
    /* 用于设置下载时的文件名 */
    String fn = String(path);
    int index = fn.lastIndexOf("/");
    if (index < 0)
    {
        index = fn.lastIndexOf(":");
    }
    fn = "inline; filename=\"" + fn.substring(index + 1) + "\"";
    httpd_resp_set_hdr(req, "Content-Disposition", fn.c_str()); // <- make sure the value is still valid until send function

    /* Retrieve the pointer to scratch buffer for temporary storage */
    char *chunk = (char *)malloc(FILE_SCRATCH_BUFSIZE);
    size_t chunksize = FILE_SCRATCH_BUFSIZE;
    if (!chunk)
    {
        ESP_LOGI("file_get_handler", "Create scratch buffer failed. Falling back to smaller size.");
        chunk = (char *)malloc(FILE_SCRATCH_FALLBACK_BUFSIZE);
        chunksize = FILE_SCRATCH_FALLBACK_BUFSIZE;
    }
    if (!chunk)
    {
        ESP_LOGE("file_get_handler", "No enough memory to create scratch buffer!");
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"No enough ram\",\"code\":-20}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    size_t bytesread;
    do
    {
        xSemaphoreTake(*FSMutex, portMAX_DELAY);
        {
            /* Read file in chunks into the scratch buffer */
            bytesread = fread(chunk, 1, chunksize, fd);
        }
        xSemaphoreGive(*FSMutex);

        if (bytesread > 0)
        {
            /* Send the buffer contents as HTTP response chunk */
            if (httpd_resp_send_chunk(req, chunk, bytesread) != ESP_OK)
            {
                free(chunk);
                xSemaphoreTake(*FSMutex, portMAX_DELAY);
                {
                    fclose(fd);
                }
                xSemaphoreGive(*FSMutex);
                ESP_LOGE("file_get_handler", "File sending failed!");
                /* Abort sending file */
                httpd_resp_sendstr_chunk(req, NULL);
                /* Respond with 500 Internal Server Error */
                httpd_resp_set_status(req, HTTPD_500);
                httpd_resp_set_type(req, HTTPD_TYPE_JSON);
                httpd_resp_send(req, "{\"response\":\"Failed on sending file\",\"code\":-11}", HTTPD_RESP_USE_STRLEN);
                return ESP_FAIL;
            }
        }

        /* Keep looping till the whole file is sent */
    } while (bytesread > 0);

    /* To finish the transfer */
    httpd_resp_send_chunk(req, NULL, 0);
    free(chunk);

    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        fclose(fd);
    }
    xSemaphoreGive(*FSMutex);

    return ESP_OK;
}

/* 上传文件 */
/* @param path: 文件路径，通过url传参 */
static esp_err_t file_post_handler(httpd_req_t *req)
{
    char str[512];
    char path[512];

    /* 获取url中参数 */
    if (httpd_req_get_url_query_str(req, str, 512)) // <-- ESP_OK = 0
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid query\",\"code\":-1}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }
    /* 提取路径 */
    if (httpd_query_key_value(str, "path", path, 512)) // <-- ESP_OK = 0
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid path\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    strcpy(path, urldecode(path).c_str());
    if (path[strlen(path) - 1] == '/')
    {
        ESP_LOGE("file_post_handler", "Invalid filename : %s", path);
        httpd_resp_set_status(req, HTTPD_200);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid path\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    /* 根据驱动器号获取互斥量 */
    SemaphoreHandle_t *FSMutex = get_FS_mutex(path[1]);
    if (!FSMutex)
    {
        httpd_resp_set_status(req, HTTPD_200);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"No such volume\",\"code\":-5}", HTTPD_RESP_USE_STRLEN);
        return ESP_OK;
    }

    FILE *fd = nullptr;
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        fd = fopen(path, "wb");
    }
    xSemaphoreGive(*FSMutex);

    if (!fd)
    {
        httpd_resp_set_status(req, HTTPD_200);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Unable to open (create) file\",\"code\":-8}", HTTPD_RESP_USE_STRLEN);
        return ESP_OK;
    }

    /* Retrieve the pointer to scratch buffer for temporary storage */
    char *chunk = (char *)malloc(FILE_SCRATCH_BUFSIZE);
    size_t chunksize = FILE_SCRATCH_BUFSIZE;
    if (!chunk)
    {
        ESP_LOGI("file_get_handler", "Create scratch buffer failed. Falling back to smaller size.");
        chunk = (char *)malloc(FILE_SCRATCH_FALLBACK_BUFSIZE);
        chunksize = FILE_SCRATCH_FALLBACK_BUFSIZE;
    }
    if (!chunk)
    {
        ESP_LOGE("file_get_handler", "No enough memory to create scratch buffer!");
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"No enough ram\",\"code\":-20}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    size_t remaining = req->content_len;
    size_t received;
    size_t written;
    while (remaining > 0)
    {
        /* Receive the file part by part into a buffer */
        if ((received = httpd_req_recv(req, chunk, min(remaining, chunksize))) <= 0)
        {
            if (received == HTTPD_SOCK_ERR_TIMEOUT)
            {
                /* Retry if timeout occurred */
                continue;
            }

            /* In case of unrecoverable error,
             * close and delete the unfinished file*/
            free(chunk);

            xSemaphoreTake(*FSMutex, portMAX_DELAY);
            {
                fclose(fd);
                remove(path);
            }
            xSemaphoreGive(*FSMutex);

            ESP_LOGE("file_post_handler", "File reception failed!");
            /* Respond with 500 Internal Server Error */
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Failed on receiving file\",\"code\":-9}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }

        /* Write buffer content to file on storage */
        if (received)
        {
            xSemaphoreTake(*FSMutex, portMAX_DELAY);
            {
                written = fwrite(chunk, 1, received, fd);
            }
            xSemaphoreGive(*FSMutex);

            if (received != written)
            {
                /* Couldn't write everything to file!
                 * Storage may be full? */
                free(chunk);

                xSemaphoreTake(*FSMutex, portMAX_DELAY);
                {
                    fclose(fd);
                    remove(path);
                }
                xSemaphoreGive(*FSMutex);

                ESP_LOGE("file_post_handler", "File write failed!");
                /* Respond with 500 Internal Server Error */
                httpd_resp_set_status(req, HTTPD_500);
                httpd_resp_set_type(req, HTTPD_TYPE_JSON);
                httpd_resp_send(req, "{\"response\":\"Failed on writing file\",\"code\":-10}", HTTPD_RESP_USE_STRLEN);
                return ESP_FAIL;
            }
        }

        /* Keep track of remaining size of
         * the file left to be uploaded */
        remaining -= received;
    }
    /* Free the buffer */
    free(chunk);

    /* Close file upon upload completion */
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        fclose(fd);
    }
    xSemaphoreGive(*FSMutex);

    /* Redirect onto root to see the updated file list */
    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, "{\"response\":\"success\",\"code\":0}", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 删除文件 */
/* @param path: 文件路径，通过url传参 */
static esp_err_t file_delete_handler(httpd_req_t *req)
{
    char str[512];
    char path[512];

    /* 获取url中参数 */
    if (httpd_req_get_url_query_str(req, str, 512)) // <-- ESP_OK = 0
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid query\",\"code\":-1}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }
    /* 提取路径 */
    if (httpd_query_key_value(str, "path", path, 512)) // <-- ESP_OK = 0
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid path\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    /* 根据驱动器号获取互斥量 */
    SemaphoreHandle_t *FSMutex = get_FS_mutex(path[1]);
    if (!FSMutex)
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"No such volume\",\"code\":-5}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    /* 检测文件状态 */
    strcpy(path, urldecode(path).c_str());
    struct stat file_stat;
    int stat_res;
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        stat_res = stat(path, &file_stat);
    }
    xSemaphoreGive(*FSMutex);
    if (stat_res == -1)
    {
        httpd_resp_set_status(req, HTTPD_404);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"File not exist\",\"code\":-6}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    int res = remove_files(path);

    if (res == -1)
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Error occured deleting files\",\"code\":-4}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, "{\"response\":\"success\",\"code\":0}", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 新建文件夹 */
/* @param path: 文件路径，通过url传参 */
static esp_err_t file_makedir_handler(httpd_req_t *req)
{
    char str[512];
    char path[512];

    /* 获取url中参数 */
    if (httpd_req_get_url_query_str(req, str, 512)) // <-- ESP_OK = 0
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid query\",\"code\":-1}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }
    /* 提取路径 */
    if (httpd_query_key_value(str, "path", path, 512)) // <-- ESP_OK = 0
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid path\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    /* 根据驱动器号获取互斥量 */
    SemaphoreHandle_t *FSMutex = get_FS_mutex(path[1]);
    if (!FSMutex)
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"No such volume\",\"code\":-5}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    /* 尝试打开文件(检测路径是否存在) */
    strcpy(path, urldecode(path).c_str());
    int res;
    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        res = access(path, F_OK);
    }
    xSemaphoreGive(*FSMutex);
    if (res == 0)
    {
        ESP_LOGE("file_makedir_handler", "File (dir) already exists!");
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"File already exist\",\"code\":-7}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    xSemaphoreTake(*FSMutex, portMAX_DELAY);
    {
        res = mkdir(path, 0777);
    }
    xSemaphoreGive(*FSMutex);
    if (res == 0)
    {
        ESP_LOGE("file_makedir_handler", "Unable to create folder!");
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Error create folder!\",\"code\":-8}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, "{\"response\":\"success\",\"code\":0}", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取米游社配置 */
static esp_err_t hoyolab_conf_get_handler(httpd_req_t *req)
{
    String json = "";
    StaticJsonDocument<1024> doc;
    doc["uid"] = hyc.getUid();
    doc["cookie"] = hyc.getCookie();
    doc["device_guid"] = hyc.getDeviceGuid();

    serializeJson(doc, json);
    doc.clear();

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, json.c_str(), HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 更新米游社配置 */
static esp_err_t hoyolab_conf_post_handler(httpd_req_t *req)
{
    char post_ctx[1024];

    /* 如果内容长度大于缓冲区则截断 */
    size_t recv_size = min(req->content_len, sizeof(post_ctx));

    int ret = httpd_req_recv(req, post_ctx, recv_size);
    if (ret <= 0)
    { /* 返回 0 表示连接已关闭 */
        /* 检查是否超时 */
        if (ret == HTTPD_SOCK_ERR_TIMEOUT)
        {
            /* 如果是超时，可以调用 httpd_req_recv() 重试
             * 简单起见，这里我们直接
             * 响应 HTTP 408（请求超时）错误给客户端 */
            httpd_resp_send_408(req);
        }
        /* 如果发生了错误，返回 ESP_FAIL 确保底层套接字被关闭 */
        return ESP_FAIL;
    }

    StaticJsonDocument<1024> doc;
    DeserializationError error;

    error = deserializeJson(doc, post_ctx, recv_size);
    if (error)
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Error when deserializing json\",\"code\":-1}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    const char *uid = doc["uid"];
    const char *cookie = doc["cookie"];
    const char *guid = doc["device_guid"];

    if (!uid || !cookie || !guid)
    {
        httpd_resp_set_status(req, HTTPD_500);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid JSON\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
        return ESP_FAIL;
    }

    prefs.putString("hoyolabUID", uid);
    prefs.putString("hoyolabCookie", cookie);
    prefs.putString("deviceGuid", guid);
    hyc.setUid(uid);
    hyc.setCookie(cookie);
    hyc.setDeviceGuid(guid);

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, "{\"response\":\"success\",\"code\":0}", HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

/* 获取/设置自动亮度开关 */
/* @param value: 要设置的值，通过url传参(true, false) */
static esp_err_t setting_auto_bright_get_handler(httpd_req_t *req)
{
    char str[64];
    char value[64];

    /* 获取url中参数 */
    if (!httpd_req_get_url_query_str(req, str, 64)) // <-- ESP_OK = 0
    {
        /* 提取输入值 */
        if (httpd_query_key_value(str, "value", value, 64)) // <-- ESP_OK = 0
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }

        /* 检查输入值 */
        if (strcmp(value, "true") == 0)
        {
            setting_autoBright = true;
            prefs.putBool("useAutoBright", true);
        }
        else if (strcmp(value, "false") == 0)
        {
            setting_autoBright = false;
            prefs.putBool("useAutoBright", false);
        }
        else
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }
    }

    if (setting_autoBright)
    {
        sprintf(str, "{\"setting_autoBright\":%s}", "true");
    }
    else
    {
        sprintf(str, "{\"setting_autoBright\":%s}", "false");
    }
    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, str, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取/设置自动旋转开关 */
/* @param value: 要设置的值，通过url传参(true, false) */
static esp_err_t setting_auto_rotate_get_handler(httpd_req_t *req)
{
    char str[64];
    char value[64];

    /* 获取url中参数 */
    if (!httpd_req_get_url_query_str(req, str, 64)) // <-- ESP_OK = 0
    {
        /* 提取输入值 */
        if (httpd_query_key_value(str, "value", value, 64)) // <-- ESP_OK = 0
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }

        /* 检查输入值 */
        if (strcmp(value, "true") == 0)
        {
            setting_useAccel = true;
            prefs.putBool("useAccelMeter", true);
        }
        else if (strcmp(value, "false") == 0)
        {
            setting_useAccel = false;
            prefs.putBool("useAccelMeter", false);
        }
        else
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }
    }

    if (setting_useAccel)
    {
        sprintf(str, "{\"setting_useAccel\":%s}", "true");
    }
    else
    {
        sprintf(str, "{\"setting_useAccel\":%s}", "false");
    }
    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, str, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取/设置屏幕亮度 */
/* @param value: 要设置的值，通过url传参(0-255) */
static esp_err_t setting_brightness_get_handler(httpd_req_t *req)
{
    char str[64];
    char value[64];
    int brightness = setting_screenBrightness;

    /* 获取url中参数 */
    if (!httpd_req_get_url_query_str(req, str, 64)) // <-- ESP_OK = 0
    {
        /* 提取输入值 */
        if (httpd_query_key_value(str, "value", value, 64)) // <-- ESP_OK = 0
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }

        /* 检查输入值 */
        if (sscanf(value, "%d", &brightness) == 1 && brightness >= 0 && brightness < 256)
        {
            setting_screenBrightness = brightness;
            prefs.putUInt("screenBrightness", setting_screenBrightness);
        }
        else
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }
    }

    sprintf(str, "{\"setting_screenBrightness\":%d}", setting_screenBrightness);
    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, str, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static esp_err_t setting_volume_get_handler(httpd_req_t *req)
{
    return ESP_OK;
}

/* 获取/设置语言 */
/* @param value: 要设置的值，通过url传参(0-1) */
static esp_err_t setting_language_get_handler(httpd_req_t *req)
{
    char str[64];
    char value[64];
    int language = curr_lang;

    /* 获取url中参数 */
    if (!httpd_req_get_url_query_str(req, str, 64)) // <-- ESP_OK = 0
    {
        /* 提取输入值 */
        if (httpd_query_key_value(str, "value", value, 64)) // <-- ESP_OK = 0
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }

        /* 检查输入值 */
        if (sscanf(value, "%d", &language) == 1 && language >= 0 && language < 2)
        {
            curr_lang = language;
            prefs.putBool("language", curr_lang);
        }
        else
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }
    }

    sprintf(str, "{\"curr_lang\":%d}", curr_lang);
    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, str, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取/设置时区 */
/* @param val: 要设置的值，通过url传参 */
static esp_err_t setting_timezone_get_handler(httpd_req_t *req)
{
    char str[64];
    char value[64];

    /* 获取url中参数 */
    if (!httpd_req_get_url_query_str(req, str, 64)) // <-- ESP_OK = 0
    {
        /* 提取输入值 */
        if (httpd_query_key_value(str, "val", value, 64)) // <-- ESP_OK = 0
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }

        setting_timeZone = urldecode(value);
        setenv("TZ", setting_timeZone.c_str(), 1);
        tzset();
        prefs.putString("timeZone", setting_timeZone);
    }

    sprintf(str, "{\"setting_timeZone\":\"%s\"}", setting_timeZone.c_str());
    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, str, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取/设置城市 */
/* @param city: 要设置的城市名称，通过url传参 */
/* @param latitude: 要设置的城市纬度，通过url传参 */
/* @param longitude: 要设置的城市经度，通过url传参 */
static esp_err_t weather_city_get_handler(httpd_req_t *req)
{
    char str[128];
    char value1[64];
    char value2[64];
    char value3[64];
    float lat, lon;

    /* 获取url中参数 */
    if (!httpd_req_get_url_query_str(req, str, 128)) // <-- ESP_OK = 0
    {
        /* 提取输入值 */
        if (httpd_query_key_value(str, "city", value1, 64) || httpd_query_key_value(str, "latitude", value2, 64) || httpd_query_key_value(str, "longitude", value3, 64)) // <-- ESP_OK = 0
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }

        /* 检查输入值 */
        if ((sscanf(value2, "%f", &lat) == 1 && lat >= -90 && lat <= 90) && (sscanf(value3, "%f", &lon) == 1 && lon >= -180 && lon <= 180))
        {
            wp->setCoordinate(lat, lon);
            wp->setCity(urldecode(value1).c_str());
            prefs.putString("weatherCity", wp->getCity());
            prefs.putFloat("weatherLat", lat);
            prefs.putFloat("weatherLon", lon);
        }
        else
        {
            httpd_resp_set_status(req, HTTPD_500);
            httpd_resp_set_type(req, HTTPD_TYPE_JSON);
            httpd_resp_send(req, "{\"response\":\"Invalid value\",\"code\":-2}", HTTPD_RESP_USE_STRLEN);
            return ESP_FAIL;
        }
    }

    sprintf(str, "{\"city\":\"%s\",\"latitude\":%f,\"longitude\":%f}", wp->getCity().c_str(), wp->getLatitude(), wp->getLongitude());
    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, str, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

//////////////////////////////
//
//  全局函数实现
//
//////////////////////////////

/* 启动 Web 服务器的函数 */
void startAPIServer()
{
    if (s)
    {
        return;
    }

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 24;
    config.stack_size = 6144;

    /* 置空 esp_http_server 的实例句柄 */
    httpd_handle_t server = NULL;

    /* 启动 httpd server */
    if (httpd_start(&server, &config) == ESP_OK)
    {
        /* 注册 URI 处理程序 */
        httpd_register_uri_handler(server, &uri_root);
        httpd_register_uri_handler(server, &uri_info);

        httpd_register_uri_handler(server, &uri_playlist_get);
        httpd_register_uri_handler(server, &uri_playlist_post);

        httpd_register_uri_handler(server, &uri_file_listdir);
        httpd_register_uri_handler(server, &uri_file_get);
        httpd_register_uri_handler(server, &uri_file_post);
        httpd_register_uri_handler(server, &uri_file_delete);
        httpd_register_uri_handler(server, &uri_file_makedir);

        httpd_register_uri_handler(server, &uri_hoyolab_conf_get);
        httpd_register_uri_handler(server, &uri_hoyolab_conf_post);

        httpd_register_uri_handler(server, &uri_setting_auto_bright_get);
        httpd_register_uri_handler(server, &uri_setting_auto_rotate_get);
        httpd_register_uri_handler(server, &uri_setting_brightness_get);
        // httpd_register_uri_handler(server, &uri_setting_volume_get);
        httpd_register_uri_handler(server, &uri_setting_language_get);
        httpd_register_uri_handler(server, &uri_setting_timezone_get);

        httpd_register_uri_handler(server, &uri_weather_city_get);
    }
    /* 如果服务器启动失败，返回的句柄是 NULL */
    s = server;
}

/* 停止 Web 服务器的函数 */
void endAPIServer()
{
    if (s)
    {
        /* 停止 httpd server */
        httpd_stop(s);
    }
}