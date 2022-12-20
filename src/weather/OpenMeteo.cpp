#include "weather/OpenMeteo.h"

const char HTTP_TAG[] = "OpenMeteoWeather::getCurrentWeather";

Weather_result_t OpenMeteoWeather::getCurrentWeather(float latitude, float longitude, Weather_current_t *weather)
{
    String url = "https://api.open-meteo.com/v1/forecast?latitude=";
    url.concat(latitude);
    url.concat("&longitude=");
    url.concat(longitude);
    url.concat("&current_weather=true");

    esp_http_client_config_t conf = {
        .url = url.c_str(),
        .cert_pem = ISRG_Root_X1,
        .method = HTTP_METHOD_GET,
        .buffer_size_tx = 64,
        .keep_alive_enable = false,
    };

    char *buffer = (char *)malloc(WEATHER_HTTP_RECV_BUFFER_SIZE + 1);
    if (buffer == NULL)
    {
        ESP_LOGE(HTTP_TAG, "Cannot malloc http receive buffer");
        return WEATHER_RESULT_OUT_OF_MEM;
    }

    esp_http_client_handle_t client = esp_http_client_init(&conf);
    if (!client)
    {
        ESP_LOGE(HTTP_TAG, "HTTP client init failed!");
        free(buffer);
        return WEATHER_RESULT_HTTP_OPEN_FAIL;
    }

    /* Execute query */
    esp_err_t http_err;
    if ((http_err = esp_http_client_open(client, 0)) != ESP_OK)
    {
        ESP_LOGE(HTTP_TAG, "Failed to open HTTP connection: %s", esp_err_to_name(http_err));
        free(buffer);
        return WEATHER_RESULT_HTTP_OPEN_FAIL;
    }

    int content_length = esp_http_client_fetch_headers(client);
    // ESP_LOGI(HTTP_TAG, "Content Length:%d", content_length);
    int total_read_len = 0, read_len;
    if (total_read_len < content_length && content_length <= WEATHER_HTTP_RECV_BUFFER_SIZE)
    {
        read_len = esp_http_client_read(client, buffer, content_length);
        if (read_len <= 0)
        {
            ESP_LOGE(HTTP_TAG, "Error read data");
            free(buffer);
            return WEATHER_RESULT_HTTP_READ_FAIL;
        }
        buffer[read_len] = 0;
        ESP_LOGD(HTTP_TAG, "read_len = %d", read_len);
    }

    esp_http_client_close(client);

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, buffer, WEATHER_HTTP_RECV_BUFFER_SIZE);

    if (error)
    {
        ESP_LOGE(HTTP_TAG, "deserializeJson() failed: %s", error.c_str());
        free(buffer);
        doc.clear();
        return WEATHER_RESULT_JSON_DESER_FAIL;
    }

    return WEATHER_RESULT_OK;
}