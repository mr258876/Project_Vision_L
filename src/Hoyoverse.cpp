/*

FileName: Hoyoverse.cpp
Author: mr258876
Note: Hoyolab API client for ESP32

Copyright (c) 2022, mr258876

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

*/

#include "Hoyoverse.h"
#include "Hoyoverse_const.h"

#define MAX_HTTP_RECV_BUFFER 2048
static const PROGMEM char *HTTP_TAG = "HTTP_CLIENT";

HoyoverseClient::HoyoverseClient()
{
}

HoyoverseClient::~HoyoverseClient()
{
}

/*
    @brief  Initialize HoyoverseClient
    @param[0]  cookie: cookie to login Hoyolab
    @param[1]  uid: game character id
*/
void HoyoverseClient::begin(const char *cookie, const char *uid)
{
    _uid = String(uid);
    _cookie = String(cookie);
}

/*
    @brief  Set cookie for Hoyolab.
    @param  cookie: cookie to set
*/
void HoyoverseClient::setCookie(const char *cookie)
{
    _cookie = String(cookie);
}

/*
    @brief  Get Hoyolab cookie.
    @return Cookie in String
*/
String HoyoverseClient::getCookie()
{
    return _cookie;
}

/*
    @brief  Set character UID.
    @param  uid: UID to set
*/
void HoyoverseClient::setUid(const char *uid)
{
    _uid = String(uid);
}

/*
    @brief  Get character UID.
    @return Uid in String
*/
String HoyoverseClient::getUid()
{
    return _uid;
}

/*
    @brief  Set GUID for API requests. It should be fine if left this blank.
    @param  guid: GUID to set
*/
void HoyoverseClient::setDeviceGuid(const char *guid)
{
    _device_guid = String(guid);
}

/*
    @brief  Get current GUID.
    @return guid in String
*/
String HoyoverseClient::getDeviceGuid()
{
    return _device_guid;
}

/*
    @brief  Get forum type.
    @return 0 for 米游社, 1 for Hoyolab
*/
uint8_t HoyoverseClient::getForumType(const char *uid)
{
    switch (uid[0])
    {
    case '1':
    case '2':
        return 0; // Miyoushe
    default:
        return 1; // Hoyolab
    }
}

/*
    @brief  Get server for one uid.
    @return server name in const char*
*/
const char *HoyoverseClient::getServer(const char *uid)
{
    switch (uid[0])
    {
    case '1':
    case '2':
        return "cn_gf01"; // Official server CN (Simplified Chinese)
    case '5':
        return "cn_qd01"; // Channel server CN (Simplified Chinese)
    case '6':
        return "os_usa"; // Official server NA
    case '7':
        return "os_euro"; // Official server EU
    case '8':
        return "os_asia"; // Official server AP
    case '9':
        return "os_cht"; // Official server Traditional Chinese
    }
    return "cn_gf01";
}

/*
    @brief  Get dynamic salt for request.
    @param[0] body: request body (HTTP POST only)
    @param[1] param: request parameters
    @return Dynamic salt in String
*/
String HoyoverseClient::getDynamicSalt(const char *body, const char *param)
{
    MD5Builder md5;
    md5.begin();

    time_t t = time(NULL);
    int r = random(100001, 200000);

    md5.add("salt=");
    md5.add(Hoyoverse_salt[getForumType(_uid.c_str())]);

    md5.add("&t=");
    md5.add(String(t));

    md5.add("&r=");
    md5.add(String(r));

    md5.add("&b=");
    if (strlen(body) > 0)
    {
        md5.add(body);
    }

    md5.add("&q=");
    if (strlen(param) > 0)
    {
        md5.add(param);
    }

    md5.calculate();

    String result = String(t);
    result.concat(',');
    result.concat(String(r));
    result.concat(',');
    result.concat(md5.toString());

    // ESP_LOGI("HoyoverseClient::getDynamicSalt()", "Time:%s", String(t).c_str());
    // ESP_LOGI("HoyoverseClient::getDynamicSalt()", "Rand:%s", String(r).c_str());
    // ESP_LOGI("HoyoverseClient::getDynamicSalt()", "DS:%s", result.c_str());

    return result;
}

/*
    @brief  Get resin data from Hoyolab.
    @param[0] nd: Pointer to NoteData object to save resin data
    @return operation result in HoyoverseClient_result_t
*/
HoyoverseClient_result_t HoyoverseClient::syncDailyNote(Notedata *nd)
{
    if (_uid.length() < 1 || _cookie.length() < 1)
    {
        return HOYO_CLI_CONFIG_ERR;
    }

    /* Request Param */
    String p = "role_id=";
    p.concat(_uid);
    p.concat("&server=");
    p.concat(getServer(_uid.c_str()));

    int forumtype = getForumType(_uid.c_str());
    String url = Hoyoverse_hosts_record[forumtype];
    url.concat("game_record/app/genshin/api/dailyNote?");
    url.concat(p);

    esp_http_client_config_t conf = {
        .url = url.c_str(),
        .cert_pem = Hoyoverse_SSL_root_cert,
        .user_agent = Hoyoverse_App_UA[forumtype],
        .method = HTTP_METHOD_GET,
        .buffer_size_tx = 1536,
        .keep_alive_enable = false,
    };
    // ESP_LOGI(HTTP_TAG, "URL:%s", url.c_str());

    char *buffer = (char *)malloc(MAX_HTTP_RECV_BUFFER + 1);
    if (buffer == NULL)
    {
        ESP_LOGE(HTTP_TAG, "Cannot malloc http receive buffer");
        return HOYO_CLI_OUT_OF_MEM;
    }

    esp_http_client_handle_t client = esp_http_client_init(&conf);
    if (!client)
    {
        ESP_LOGE(HTTP_TAG, "HTTP client init failed!");
        free(buffer);
        return HOYO_CLI_HTTP_OPEN_FAIL;
    }

    /* Set headers */
    esp_http_client_set_header(client, "Accept", "application/json, text/plain, */*");
    esp_http_client_set_header(client, "Accept-Language", "en-US,zh-CN,ja-JP,ko-KR;q=0.8");
    esp_http_client_set_header(client, "cookie", _cookie.c_str());
    esp_http_client_set_header(client, "DS", getDynamicSalt("", p.c_str()).c_str());
    esp_http_client_set_header(client, "Origin", Hoyoverse_App_origin[forumtype]);
    esp_http_client_set_header(client, "Referer", Hoyoverse_App_referer[forumtype]);
    // esp_http_client_set_header(client, "User-Agent", Hoyoverse_App_UA[forumtype]);
    esp_http_client_set_header(client, "X_Requested_With", Hoyoverse_App_x_requested_with[forumtype]);
    esp_http_client_set_header(client, "x-rpc-app_version", Hoyoverse_App_version[forumtype]);
    esp_http_client_set_header(client, "x-rpc-client_type", Hoyoverse_App_client_type[forumtype]);
    if (_device_guid.length() == 32)
    {
        esp_http_client_set_header(client, "x-rpc-device_id", _device_guid.c_str());
    }

    /* Execute query */
    esp_err_t http_err;
    if ((http_err = esp_http_client_open(client, 0)) != ESP_OK)
    {
        ESP_LOGE(HTTP_TAG, "Failed to open HTTP connection: %s", esp_err_to_name(http_err));
        free(buffer);
        return HOYO_CLI_HTTP_OPEN_FAIL;
    }

    int content_length = esp_http_client_fetch_headers(client);
    // ESP_LOGI(HTTP_TAG, "Content Length:%d", content_length);
    int total_read_len = 0, read_len;
    if (total_read_len < content_length && content_length <= MAX_HTTP_RECV_BUFFER)
    {
        read_len = esp_http_client_read(client, buffer, content_length);
        if (read_len <= 0)
        {
            ESP_LOGE(HTTP_TAG, "Error read data");
            free(buffer);
            return HOYO_CLI_HTTP_READ_FAIL;
        }
        buffer[read_len] = 0;
        ESP_LOGD(HTTP_TAG, "read_len = %d", read_len);
    }

    esp_http_client_close(client);
    esp_http_client_cleanup(client);

    // printf("\nResponse:%s\n\n", buffer);

    /* JSON deserializing */
    StaticJsonDocument<0> filter;
    filter.set(true);

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, buffer, content_length, DeserializationOption::Filter(filter));

    if (error)
    {
        ESP_LOGE("Arduino JSON", "deserializeJson() failed: %s", error.c_str());
        free(buffer);
        doc.clear();
        return HOYO_CLI_JSON_DESER_FAIL;
    }

    int retcode = doc["retcode"]; // 0
    nd->respCode = retcode;
    nd->respMsg = (const char *)doc["message"]; // "OK"
    if (retcode != 0)
    {
        ESP_LOGE("HoyoverseClient::getDailyNote()", "Get data failed! Server response code: %d", (int)doc["retcode"]);
        free(buffer);
        doc.clear();
        return HOYO_CLI_RESP_ERR;
    }

    JsonObject data = doc["data"];
    nd->resinRemain = data["current_resin"];                  // 120
    nd->resinMax = data["max_resin"];                         // 160
    nd->resinRecoverTime = atol(data["resin_recovery_time"]); // "19104"

    nd->homecoinRemain = data["current_home_coin"];                  // 750
    nd->homecoinMax = data["max_home_coin"];                         // 2400
    nd->homecoinRecoverTime = atol(data["home_coin_recovery_time"]); // "195774"

    nd->expeditionOngoing = data["current_expedition_num"]; // 5
    nd->expeditionMax = data["max_expedition_num"];         // 5
    nd->expeditionFinished = 0;
    memset(nd->expeditionRecoverTime, 0, sizeof(nd->expeditionRecoverTime));
    int i = 0;
    for (JsonObject data_expedition : data["expeditions"].as<JsonArray>())
    {
        nd->expeditionRecoverTime[i] = atol(data_expedition["remained_time"]); // "0", "0", "0", "0", "0"
        nd->expeditionFinished += nd->expeditionRecoverTime[i] > 0 ? 0 : 1;
        i++;
    }

    JsonObject data_transformer = data["transformer"];
    bool data_transformer_obtained = data_transformer["obtained"]; // true
    nd->hasTransformer = data_transformer_obtained;
    if (data_transformer_obtained)
    {
        JsonObject data_transformer_recovery_time = data_transformer["recovery_time"];
        nd->transformerRecoverTime = ((int)data_transformer_recovery_time["Day"]) * 86400 + ((int)data_transformer_recovery_time["Hour"]) * 3600 + ((int)data_transformer_recovery_time["Minute"]) * 60;

        if ((int)data_transformer_recovery_time["Day"] > 0)
        {
            nd->transformerRecoverTime += 43200; // 1天23小时也只会返回1天，因此当剩余时间>1天时再添加12小时时间
        }
    }

    time_t update_time = time(NULL);
    nd->_last_update_time = update_time;
    nd->_last_calc_time = update_time;

    free(buffer);
    doc.clear();
    return HOYO_CLI_OK;
}

/*
    @brief  Calculate resin data locally.
    @param[0] nd: Pointer to NoteData object which contains resin data
*/
void HoyoverseClient::updateDailyNote(Notedata *nd)
{
    time_t t = time(NULL);
    /* Resin 树脂 */
    if (nd->resinRecoverTime > 0)
    {
        nd->resinRecoverTime -= t - nd->_last_calc_time;

        if (nd->resinRecoverTime < 0)
        {
            nd->resinRecoverTime = 0;
        }

        nd->resinRemain = floor(nd->resinMax - nd->resinRecoverTime / 480);
    }
    else
    {
        nd->resinRemain = nd->resinMax;
    }

    /* Resin 洞天宝钱 */
    if (nd->homecoinRecoverTime > 0)
    {
        int hcRecSecs; // Time interval to recovery 1 homecoin
        switch (nd->homecoinMax)
        {
        case 300: // Trust Rank 1
            hcRecSecs = 900;
            break;
        case 600: // Trust Rank 2
            hcRecSecs = 450;
            break;
        case 900: // Trust Rank 3
            hcRecSecs = 300;
            break;
        case 1200: // Trust Rank 4
            hcRecSecs = 225;
            break;
        case 1400: // Trust Rank 5
            hcRecSecs = 180;
            break;
        case 1600: // Trust Rank 6
            hcRecSecs = 164;
            break;
        case 1800: // Trust Rank 7
            hcRecSecs = 150;
            break;
        case 2000: // Trust Rank 8
            hcRecSecs = 138;
            break;
        case 2200: // Trust Rank 9
            hcRecSecs = 129;
            break;
        default: // Trust Rank 10
            hcRecSecs = 120;
            break;
        }

        nd->homecoinRemain += ceil(nd->homecoinRecoverTime / hcRecSecs);
        nd->homecoinRecoverTime -= t - nd->_last_calc_time;

        if (nd->homecoinRecoverTime < 0)
        {
            nd->homecoinRecoverTime = 0;
        }

        nd->homecoinRemain -= ceil(nd->homecoinRecoverTime / hcRecSecs);
    }
    else
    {
        nd->homecoinRemain = nd->homecoinMax;
    }

    /* Expedition 探索任务 */
    for (size_t i = 0; i < 5; i++)
    {
        if (nd->expeditionRecoverTime[i] > 0)
        {
            nd->expeditionRecoverTime[i] -= t - nd->_last_calc_time;
            if (nd->expeditionRecoverTime[i] < 1)
            {
                nd->expeditionFinished += 1;
                nd->expeditionRecoverTime[i] = 0;
            }
        }
    }

    /* Transformer 质量参变仪 */
    if (nd->hasTransformer && nd->transformerRecoverTime > 0)
    {
        nd->transformerRecoverTime -= t - nd->_last_calc_time;
        if (nd->transformerRecoverTime < 1)
        {
            nd->transformerRecoverTime = 0;
        }
    }

    nd->_last_calc_time = t;
}

/*
    @brief  Generate a GUID.
    @return GUID in String
*/
String HoyoverseClient::generateGuid()
{
    String guid = "";
    for (size_t i = 0; i < 8; i++)
    {
        guid.concat(genGuid4Byte());
    }
    return guid;
}

/*
    @brief  Generate one part of GUID.
    @return 4 byte random HEX in String
*/
String HoyoverseClient::genGuid4Byte()
{
    return String(random(65536, 131071), HEX).substring(1);
}