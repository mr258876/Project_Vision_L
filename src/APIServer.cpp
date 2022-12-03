#include "APIServer.h"

httpd_handle_t s;

esp_err_t root_handler(httpd_req_t *req);
esp_err_t info_handler(httpd_req_t *req);

/* GET / 的 URI 处理结构 */
httpd_uri_t uri_root = {
    .uri      = "/",
    .method   = HTTP_GET,
    .handler  = root_handler,
    .user_ctx = NULL
};

/* GET /info 的 URI 处理结构 */
httpd_uri_t uri_info = {
    .uri      = "/info",
    .method   = HTTP_GET,
    .handler  = info_handler,
    .user_ctx = NULL
};

/* 根目录跳转 */
esp_err_t root_handler(httpd_req_t *req)
{
    httpd_resp_set_status(req, "302	Found");
    httpd_resp_set_type(req, HTTPD_TYPE_TEXT);
    httpd_resp_set_hdr(req, "Location", "https://mr258876.github.io/Project_Vision_L/");    // Redirect to page on github
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

    httpd_resp_set_status(req, HTTPD_200);
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, json.c_str(), HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}


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
    if (httpd_start(&server, &config) == ESP_OK) {
        /* 注册 URI 处理程序 */
        httpd_register_uri_handler(server, &uri_root);
        httpd_register_uri_handler(server, &uri_info);
    }
    /* 如果服务器启动失败，返回的句柄是 NULL */
    s = server;
}


/* 停止 Web 服务器的函数 */
void endAPIServer()
{
    if (s) {
        /* 停止 httpd server */
        httpd_stop(s);
    }
}