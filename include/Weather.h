#ifndef _WEATHER_H_
#define _WEATHER_H_

#define WEATHER_HTTP_RECV_BUFFER_SIZE 1024

#include <Arduino.h>

enum Weather_weather_t
{
    WEATHER_CLEAR_SKY = 0,      // 晴
    WEATHER_PARTLY_CLOUDY,      // 多云(少云)
    WEATHER_OVERCAST,           // 阴
    WEATHER_RAIN_SHOWERS,       // 阵雨
    WEATHER_THUNDERSTORM,       // 雷电/雷阵雨
    WEATHER_HAIL,               // 冰雹/雷阵雨伴冰雹
    WEATHER_SLEET,              // 雨夹雪
    WEATHER_SLIGHT_RAIN,        // 小雨
    WEATHER_MODERATE_RAIN,      // 中雨
    WEATHER_HEAVY_RAIN,         // 大雨
    WEATHER_RAINSTORM,          // 暴雨
    WEATHER_SNOW_SHOWERS,       // 阵雪
    WEATHER_SLIGHT_SNOW_FALL,   // 小雪
    WEATHER_MODERATE_SNOW_FALL, // 中雪
    WEATHER_HEAVY_SNOW_FALL,    // 大雪
    WEATHER_SNOWSTORM,          // 暴雪
    WEATHER_FOG,                // 雾
    WEATHER_FREEZING_DRIZZLE,   // 冻雨
    WEATHER_SANDSTORM,          // 沙尘暴
    WEATHER_SAND,               // 扬沙
    WEATHER_HAZE                // 霾
};

enum Weather_airQuality_t
{
    AIR_QUALITY_GOOD = 0,        // 优
    AIR_QUALITY_MODERATE,        // 良
    AIR_QUALITY_LIGHT_UNHEALTHY, // 轻度
    AIR_QUALITY_UNHEALTHY,       // 中度
    AIR_QUALITY_VERY_UNHEALTHY,  // 重度
    AIR_QUALITY_HAZARDOUS        // 严重
};

enum Weather_airQuality_standard_t
{
    AIR_QUALITY_STANDARD_US = 0, // 美标
    AIR_QUALITY_STANDARD_EUROPE, // 欧标
    AIR_QUALITY_STANDARD_CHINA   // 国标
};

enum Weather_result_t
{
    WEATHER_RESULT_NO_CITY = -1,
    WEATHER_RESULT_OK = 0,
    WEATHER_RESULT_OUT_OF_MEM,
    WEATHER_RESULT_HTTP_OPEN_FAIL,
    WEATHER_RESULT_HTTP_READ_FAIL,
    WEATHER_RESULT_JSON_DESER_FAIL,
    WEATHER_RESULT_RESP_ERR,
};

struct Weather_current_t
{
    Weather_weather_t weather = WEATHER_CLEAR_SKY;                       // 天气类型
    int temp = 0;                                                        // 气温
    int aqi = 0;                                                         // 空气污染指数
    Weather_airQuality_standard_t aqiStandard = AIR_QUALITY_STANDARD_US; // 空气污染指数标准
    time_t lastUpdate = 0;                                               // 上次更新时间
    int respCode = 0;                                                    // 服务器返回码
    String respMsg = "";                                                 // 服务器返回信息
};

class WeatherProvider
{
private:
    String cityName;
    float latitude;
    float longitude;

public:
    virtual ~WeatherProvider(){};
    virtual Weather_result_t getCurrentWeather(Weather_current_t *weather) = 0;

    void setCity(const char *city) { cityName = city; };
    void setCoordinate(float lat, float lon)
    {
        latitude = lat;
        longitude = lon;
    };

    String getCity() { return cityName; };
    float getLatitude() { return latitude; };
    float getLongitude() { return longitude; };

    /* Returns air quality level from aqi */
    Weather_airQuality_t airQuality_AQI(Weather_airQuality_standard_t standard, int aqi)
    {
        switch (standard)
        {
        case AIR_QUALITY_STANDARD_EUROPE:
            if (aqi < 26)
            {
                return AIR_QUALITY_GOOD;
            }
            else if (aqi < 51)
            {
                return AIR_QUALITY_MODERATE;
            }
            else if (aqi < 76)
            {
                return AIR_QUALITY_LIGHT_UNHEALTHY;
            }
            else if (aqi < 101)
            {
                return AIR_QUALITY_UNHEALTHY;
            }
            else
            {
                return AIR_QUALITY_HAZARDOUS;
            }
            break;
        default:
            if (aqi < 51)
            {
                return AIR_QUALITY_GOOD;
            }
            else if (aqi < 101)
            {
                return AIR_QUALITY_MODERATE;
            }
            else if (aqi < 151)
            {
                return AIR_QUALITY_LIGHT_UNHEALTHY;
            }
            else if (aqi < 201)
            {
                return AIR_QUALITY_UNHEALTHY;
            }
            else if (aqi < 301)
            {
                return AIR_QUALITY_VERY_UNHEALTHY;
            }
            else
            {
                return AIR_QUALITY_HAZARDOUS;
            }
            break;
        }
        return AIR_QUALITY_MODERATE;
    };
};

#endif