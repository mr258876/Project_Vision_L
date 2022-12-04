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

esp_err_t root_handler(httpd_req_t *req);
esp_err_t info_handler(httpd_req_t *req);

esp_err_t playlist_get_handler(httpd_req_t *req);
esp_err_t playlist_post_handler(httpd_req_t *req);

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
    .uri = "/info",
    .method = HTTP_GET,
    .handler = info_handler,
    .user_ctx = NULL};

/* GET /playlist 的 URI 处理结构 */
httpd_uri_t uri_playlist_get = {
    .uri = "/playlist",
    .method = HTTP_GET,
    .handler = playlist_get_handler,
    .user_ctx = NULL};

/* POST /playlist 的 URI 处理结构 */
httpd_uri_t uri_playlist_post = {
    .uri = "/playlist",
    .method = HTTP_POST,
    .handler = playlist_post_handler,
    .user_ctx = NULL};

//////////////////////////////
//
//  函数实现
//
//////////////////////////////

/* 根目录跳转 */
esp_err_t root_handler(httpd_req_t *req)
{
    httpd_resp_set_status(req, "302	Found");
    httpd_resp_set_type(req, HTTPD_TYPE_TEXT);
    httpd_resp_set_hdr(req, "Location", "https://mr258876.github.io/Project_Vision_L/"); // Redirect to page on github
    httpd_resp_send(req, "<html><h2>Please visit the management page here:</h2><br><a href=\"https://mr258876.github.io/Project_Vision_L/\">Project_Vision_L</a></html>", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取神之眼基本信息 */
esp_err_t info_handler(httpd_req_t *req)
{
    // 获取app版本
    const esp_app_desc_t *running_app_info = esp_ota_get_app_description();

    String json = "";
    StaticJsonDocument<256> doc;
    doc["device_name"] = setting_deviceName;
    doc["app_version"] = running_app_info->version;
    doc["hw_version"] = info_hwType;

    serializeJson(doc, json);
    doc.clear();

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, json.c_str(), HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取目录下文件列表 */
esp_err_t filelist_handler(httpd_req_t *req)
{
    StaticJsonDocument<1024> doc;

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, "{}", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* 获取播放列表 */
esp_err_t playlist_get_handler(httpd_req_t *req)
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
esp_err_t playlist_post_handler(httpd_req_t *req)
{
    char post_cxt[1024];
    char response[256];

    /* 如果内容长度大于缓冲区则截断 */
    size_t recv_size = min(req->content_len, sizeof(post_cxt));

    int ret = httpd_req_recv(req, post_cxt, recv_size);
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
    StaticJsonDocument<0> filter;
    DeserializationError error;

    error = deserializeJson(doc, post_cxt, DeserializationOption::Filter(filter));
    if (error)
    {
        sprintf(response, "{\"response\":\"%s\",code:-1}", error);
        httpd_resp_set_status(req, HTTPD_200);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
        return ESP_OK;
    }

    if (!doc.containsKey("files") || !doc["files"].is<JsonArray>() || doc["files"].isNull() || !doc["files"][0].is<const char*>())
    {
        httpd_resp_set_status(req, HTTPD_200);
        httpd_resp_set_type(req, HTTPD_TYPE_JSON);
        httpd_resp_send(req, "{\"response\":\"Invalid JSON\",code:-2}", HTTPD_RESP_USE_STRLEN);
        return ESP_OK;
    }

    JsonArray files = doc["files"];
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

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    if (error_count)
        httpd_resp_send(req, "{\"response\":\"success with error\",code:1}", HTTPD_RESP_USE_STRLEN);
    else
        httpd_resp_send(req, "{\"response\":\"success\",code:0}", HTTPD_RESP_USE_STRLEN);

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