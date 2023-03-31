#ifndef _MOJITIANQI_H_
#define _MOJITIANQI_H_

#include "Weather.h"
#include <esp_http_client.h>
#include <esp_crt_bundle.h>
#include <Arduino.h>
#include <ArduinoJson.h>

class MojiTianqiWeather : public WeatherProvider
{
public:
    MojiTianqiWeather(){};
    ~MojiTianqiWeather(){};

    Weather_result_t getCurrentWeather(Weather_current_t *weather);
private:
    Weather_weather_t weatherCodeConvert(int weatherId);

    Weather_result_t performCurrentWeatherQuery(const char* url, Weather_current_t *weather);
    Weather_result_t getCurrentWeather(const char* cityName, Weather_current_t *weather);
    Weather_result_t getCurrentWeather(float latitude, float longitude, Weather_current_t *weather);

    const uint8_t weatherTable[42][2] = {
    /* Reference:
        墨迹天气第三方天气数据接口说明
        https://share.weiyun.com/SqNmcgP5
     */
    {7, WEATHER_CLEAR_SKY},
    {12, WEATHER_PARTLY_CLOUDY},
    {14, WEATHER_OVERCAST},
    {23, WEATHER_RAIN_SHOWERS},
    {25, WEATHER_SNOW_SHOWERS},
    {28, WEATHER_FOG},
    {29, WEATHER_SANDSTORM},
    {32, WEATHER_SAND},
    {33, WEATHER_SANDSTORM},
    {35, WEATHER_HAZE},
    {36, WEATHER_OVERCAST},
    {43, WEATHER_THUNDERSTORM},
    {48, WEATHER_HAIL},
    {50, WEATHER_SLEET},
    {52, WEATHER_SLIGHT_RAIN},
    {53, WEATHER_MODERATE_RAIN},
    {54, WEATHER_HEAVY_RAIN},
    {57, WEATHER_RAINSTORM},
    {59, WEATHER_SLIGHT_SNOW_FALL},
    {61, WEATHER_MODERATE_SNOW_FALL},
    {62, WEATHER_HEAVY_SNOW_FALL},
    {63, WEATHER_SNOWSTORM},
    {65, WEATHER_FREEZING_DRIZZLE},
    {66, WEATHER_SLIGHT_RAIN},
    {67, WEATHER_MODERATE_RAIN},
    {68, WEATHER_HEAVY_RAIN},
    {70, WEATHER_RAINSTORM},
    {73, WEATHER_SLIGHT_SNOW_FALL},
    {75, WEATHER_HEAVY_SNOW_FALL},
    {76, WEATHER_SNOWSTORM},
    {77, WEATHER_HEAVY_SNOW_FALL},
    {78, WEATHER_MODERATE_RAIN},
    {79, WEATHER_HAZE},
    {82, WEATHER_PARTLY_CLOUDY},
    {84, WEATHER_FOG},
    {85, WEATHER_OVERCAST},
    {86, WEATHER_RAIN_SHOWERS},
    {90, WEATHER_THUNDERSTORM},
    {91, WEATHER_SLIGHT_RAIN},
    {92, WEATHER_HEAVY_RAIN},
    {93, WEATHER_RAINSTORM},
    {94, WEATHER_MODERATE_SNOW_FALL}};
};

extern MojiTianqiWeather MojiTianqi;

#endif