#include "weather/MojiTianqi.h"

MojiTianqiWeather MojiTianqi = MojiTianqiWeather();

const char HTTP_TAG[] = "MojiTianqiWeather::getCurrentWeather";

Weather_weather_t MojiTianqiWeather::weatherCodeConvert(int weatherId)
{
    for (size_t i = 0; i < 42; i++)
    {
        if (weatherId <= weatherTable[i][0])
        {
            return (Weather_weather_t)weatherTable[i][1];
        }
    }
    return WEATHER_CLEAR_SKY;
}

Weather_result_t MojiTianqiWeather::performCurrentWeatherQuery(const char *url, Weather_current_t *weather)
{
    esp_http_client_config_t conf = {
        .url = url,
        .cert_pem = GlobalSign_Root_CA2,
        .method = HTTP_METHOD_GET,
        .keep_alive_enable = false,
    };

    esp_http_client_handle_t client = esp_http_client_init(&conf);
    if (!client)
    {
        ESP_LOGE(HTTP_TAG, "HTTP client init failed!");
        return WEATHER_RESULT_HTTP_OPEN_FAIL;
    }

    /* Execute query */
    esp_err_t http_err;
    if ((http_err = esp_http_client_open(client, 0)) != ESP_OK)
    {
        ESP_LOGE(HTTP_TAG, "Failed to open HTTP connection: %s", esp_err_to_name(http_err));
        return WEATHER_RESULT_HTTP_OPEN_FAIL;
    }

    int status_code = esp_http_client_get_status_code(client);
    if (status_code >= 400)
    {
        ESP_LOGE(HTTP_TAG, "HTTP abnormal status code: %d", status_code);
        return WEATHER_RESULT_HTTP_READ_FAIL;
    }

    char *buffer = (char *)malloc(WEATHER_HTTP_RECV_BUFFER_SIZE + 1);
    if (buffer == NULL)
    {
        ESP_LOGE(HTTP_TAG, "Cannot malloc http receive buffer");
        return WEATHER_RESULT_OUT_OF_MEM;
    }

    int content_length = esp_http_client_fetch_headers(client);
    // ESP_LOGI(HTTP_TAG, "Content Length:%d", content_length);
    if (esp_http_client_is_chunked_response(client)) // <- This api uses chunked encoding
    {
        int read_len;
        while (1)
        {
            read_len = esp_http_client_read(client, buffer, WEATHER_HTTP_RECV_BUFFER_SIZE);
            if (read_len <= 0)
            {
                if (esp_http_client_is_complete_data_received(client))
                {
                    break;
                }
                ESP_LOGE(HTTP_TAG, "Error reading data");
                free(buffer);
                return WEATHER_RESULT_HTTP_READ_FAIL;
            }
        }
    }
    else
    {
        /* Just in case */
        int read_len = 0;
        if (0 < content_length && content_length <= WEATHER_HTTP_RECV_BUFFER_SIZE)
        {
            read_len = esp_http_client_read(client, buffer, content_length);
            if (read_len <= 0)
            {
                ESP_LOGE(HTTP_TAG, "Error read data");
                free(buffer);
                return WEATHER_RESULT_HTTP_READ_FAIL;
            }
            buffer[read_len] = 0;
            // ESP_LOGD(HTTP_TAG, "read_len = %d", read_len);
        }
    }

    esp_http_client_close(client);
    esp_http_client_cleanup(client);

    // ESP_LOGI(HTTP_TAG, "Body Received:%s", buffer);

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, buffer, WEATHER_HTTP_RECV_BUFFER_SIZE);

    if (error)
    {
        ESP_LOGE(HTTP_TAG, "deserializeJson() failed: %s", error.c_str());
        free(buffer);
        doc.clear();
        return WEATHER_RESULT_JSON_DESER_FAIL;
    }

    int code = doc["code"];       // 0
    const char *msg = doc["msg"]; // "操作成功"
    weather->respCode = code;
    weather->respMsg = msg;

    if (code != 0)
    {
        ESP_LOGE(HTTP_TAG, "Get data failed! Server response code: %d", code);
        free(buffer);
        doc.clear();
        return WEATHER_RESULT_RESP_ERR;
    }

    JsonObject data_list_0 = doc["data"]["list"][0];
    const char *data_list_0_city = data_list_0["city"];       // "深圳"
    int data_list_0_temp = data_list_0["temp"];               // 13
    const char *data_list_0_airData = data_list_0["airData"]; // "10"
    int data_list_0_weatherType = data_list_0["weatherType"]; // 2

    weather->temp = data_list_0_temp;
    weather->aqi = atoi(data_list_0_airData);
    weather->weather = weatherCodeConvert(data_list_0_weatherType);
    weather->aqiStandard = AIR_QUALITY_STANDARD_CHINA;

    /* 更新城市名 */
    setCity(data_list_0_city);

    doc.clear();
    free(buffer);

    return WEATHER_RESULT_OK;
}

Weather_result_t MojiTianqiWeather::getCurrentWeather(float latitude, float longitude, Weather_current_t *weather)
{
    String url = "https://autodev.openspeech.cn/csp/api/v2.1/weather?openId=aiuicus&clientType=android&sign=android&latitude=";
    url.concat(latitude);
    url.concat("&longitude=");
    url.concat(longitude);
    url.concat("&needMoreData=false&pageNo=1&pageSize=1");

    return performCurrentWeatherQuery(url.c_str(), weather);
}

String urlEncode(const char *msg)
{
    const char *hex = "0123456789ABCDEF";
    String encodedMsg = "";
    while (*msg != '\0')
    {
        if (('a' <= *msg && *msg <= 'z') || ('A' <= *msg && *msg <= 'Z') || ('0' <= *msg && *msg <= '9') || *msg == '-' || *msg == '_' || *msg == '.' || *msg == '~')
        {
            encodedMsg += *msg;
        }
        else
        {
            encodedMsg += '%';
            encodedMsg += hex[*msg >> 4];
            encodedMsg += hex[*msg & 0xf];
        }
        msg++;
    }
    return encodedMsg;
}

Weather_result_t MojiTianqiWeather::getCurrentWeather(const char *cityName, Weather_current_t *weather)
{
    String url = "https://autodev.openspeech.cn/csp/api/v2.1/weather?openId=aiuicus&clientType=android&sign=android&city=";
    url.concat(urlEncode(cityName));
    url.concat("&needMoreData=false&pageNo=1&pageSize=1");

    return performCurrentWeatherQuery(url.c_str(), weather);
}

Weather_result_t MojiTianqiWeather::getCurrentWeather(Weather_current_t *weather)
{
    if (getLatitude() && getLongitude())
    {
        return getCurrentWeather(getLatitude(), getLongitude(), weather);
    }
    if (!getCity().isEmpty())
    {
        return getCurrentWeather(getCity().c_str(), weather);
    }
    return WEATHER_RESULT_NO_CITY;
}