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
    Weather_result_t getCurrentWeather(const char *cityName, Weather_current_t *weather);
    Weather_result_t getCurrentWeather(float latitude, float longitude, Weather_current_t *weather);
};

// OpenMeteoWeather OpenMeteo = OpenMeteoWeather();

#endif