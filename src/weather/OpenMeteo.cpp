#include "weather/OpenMeteo.h"

OpenMeteoWeather OpenMeteo = OpenMeteoWeather();

const char HTTP_TAG[] = "OpenMeteoWeather::getCurrentWeather";

Weather_weather_t OpenMeteoWeather::weatherCodeConvert(int weatherId)
{
    for (size_t i = 0; i < 18; i++)
    {
        if (weatherId <= weatherTable[i][0])
        {
            return (Weather_weather_t)weatherTable[i][1];
        }
    }
    return WEATHER_CLEAR_SKY;
}

Weather_result_t OpenMeteoWeather::getCurrentWeather(float latitude, float longitude, Weather_current_t *weather)
{
    /* Current Weather */

    String url = "https://api.open-meteo.com/v1/forecast?current_weather=true&latitude=";
    url.concat(latitude);
    url.concat("&longitude=");
    url.concat(longitude);

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

    StaticJsonDocument<16> filter;
    filter["current_weather"] = true;
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, buffer, WEATHER_HTTP_RECV_BUFFER_SIZE, DeserializationOption::Filter(filter));

    if (error)
    {
        ESP_LOGE(HTTP_TAG, "deserializeJson() failed: %s", error.c_str());
        free(buffer);
        doc.clear();
        return WEATHER_RESULT_JSON_DESER_FAIL;
    }

    JsonObject current_weather = doc["current_weather"];
    float current_weather_temperature = current_weather["temperature"];   // 6.6
    float current_weather_windspeed = current_weather["windspeed"];       // 18.4
    int current_weather_winddirection = current_weather["winddirection"]; // 219
    int current_weather_weathercode = current_weather["weathercode"];     // 3
    const char *current_weather_time = current_weather["time"];           // "2023-01-15T14:00" <- Note: GMT time

    char current_weather_date[11];
    strncpy(current_weather_date, current_weather_time, 10);

    weather->temp = current_weather_temperature;
    weather->weather = weatherCodeConvert(current_weather_weathercode);

    filter.clear();
    doc.clear();

    /* Air Quality */

    url = "https://air-quality-api.open-meteo.com/v1/air-quality?hourly=us_aqi&timezone=auto&latitude=";
    url.concat(latitude);
    url.concat("&longitude=");
    url.concat(longitude);
    url.concat("&start_date=");
    url.concat(current_weather_date);
    url.concat("&end_date=");
    url.concat(current_weather_date);

    conf.url = url.c_str();

    client = esp_http_client_init(&conf);
    if (!client)
    {
        ESP_LOGE(HTTP_TAG, "HTTP client init failed!");
        free(buffer);
        return WEATHER_RESULT_HTTP_OPEN_FAIL;
    }

    /* Execute query */
    if ((http_err = esp_http_client_open(client, 0)) != ESP_OK)
    {
        ESP_LOGE(HTTP_TAG, "Failed to open HTTP connection: %s", esp_err_to_name(http_err));
        free(buffer);
        return WEATHER_RESULT_HTTP_OPEN_FAIL;
    }

    content_length = esp_http_client_fetch_headers(client);
    // ESP_LOGI(HTTP_TAG, "Content Length:%d", content_length);
    total_read_len = 0;
    read_len = 0;
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

    filter["hourly"] = true;
    error = deserializeJson(doc, buffer, WEATHER_HTTP_RECV_BUFFER_SIZE, DeserializationOption::Filter(filter));

    if (error)
    {
        ESP_LOGE(HTTP_TAG, "deserializeJson() failed: %s", error.c_str());
        free(buffer);
        doc.clear();
        return WEATHER_RESULT_JSON_DESER_FAIL;
    }

    JsonArray hourly_time = doc["hourly"]["time"]; // Note: GMT time
    JsonArray hourly_us_aqi = doc["hourly"]["us_aqi"];

    /* Get GMT time offset */
    char *TZ = getenv("TZ");
    int gmt_hour_offset = 0;
    int gmt_minute_offset = 0;
    sscanf(TZ, "GMT%d:%d", &gmt_hour_offset, &gmt_minute_offset);
    int gmt_offset = -(gmt_hour_offset * 3600 + gmt_minute_offset * 60);

    int aqi = 0;
    for (int i = 23; i >= 0; i--)
    {
        long hour_time = hourly_time[i];
        if (hour_time)
            hour_time += gmt_offset;
        else
            continue;
        
        if (time(NULL) > hour_time || i == 0)
        {
            aqi = hourly_us_aqi[i];
        }
    }

    weather->aqi = aqi;
    weather->aqiStandard = AIR_QUALITY_STANDARD_US;

    filter.clear();
    doc.clear();

    free(buffer);

    return WEATHER_RESULT_OK;
}

Weather_result_t OpenMeteoWeather::getCurrentWeather(Weather_current_t *weather)
{
    if (getLatitude() && getLongitude())
    {
        return getCurrentWeather(getLatitude(), getLongitude(), weather);
    }
    return WEATHER_RESULT_NO_CITY;
}