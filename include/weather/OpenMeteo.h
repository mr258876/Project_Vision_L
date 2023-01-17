#ifndef _OPENMETEO_H_
#define _OPENMETEO_H_

#include "Weather.h"
#include <esp_http_client.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "TLScert.h"

class OpenMeteoWeather : public WeatherProvider
{
public:
    OpenMeteoWeather(){};
    ~OpenMeteoWeather(){};

    Weather_result_t getCurrentWeather(Weather_current_t *weather);
private:
    Weather_weather_t weatherCodeConvert(int weatherId);

    Weather_result_t getCurrentWeather(float latitude, float longitude, Weather_current_t *weather);

    const uint8_t weatherTable[18][2] = {
    /* Reference:
        Weather Forecast API
        https://open-meteo.com/en/docs
     */
    {0, WEATHER_CLEAR_SKY},
    {2, WEATHER_PARTLY_CLOUDY},
    {3, WEATHER_OVERCAST},
    {45, WEATHER_FOG},
    {48, WEATHER_FOG},
    {55, WEATHER_RAIN_SHOWERS},
    {57, WEATHER_FREEZING_DRIZZLE},
    {61, WEATHER_SLIGHT_RAIN},
    {63, WEATHER_MODERATE_RAIN},
    {65, WEATHER_HEAVY_RAIN},
    {67, WEATHER_FREEZING_DRIZZLE},
    {71, WEATHER_SLIGHT_SNOW_FALL},
    {73, WEATHER_MODERATE_SNOW_FALL},
    {75, WEATHER_HEAVY_SNOW_FALL},
    {82, WEATHER_RAIN_SHOWERS},
    {86, WEATHER_SNOW_SHOWERS},
    {95, WEATHER_THUNDERSTORM},
    {99, WEATHER_HAIL}};
};

extern OpenMeteoWeather OpenMeteo;

#endif