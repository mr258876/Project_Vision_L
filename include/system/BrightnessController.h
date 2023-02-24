/*

FileName: BrightnessController.h
Author: mr258876
Note: Screen brightness controller

Copyright (c) 2023, mr258876

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

*/

#include "math.h"

typedef float (*ambient_displayNit_fun_t)(float);
typedef int (*displayNit_brightnessLevel_fun_t)(float);

class BrightnessController
{
private:
    ambient_displayNit_fun_t lux_nit_fun = nullptr;
    displayNit_brightnessLevel_fun_t nit_lev_fun = nullptr;

    int maxScreenBrightnessNit = 300;
    int maxBrightnessLevel = 255;

    /*
        @brief Caluate screen brightness(nit) from ambient light
        @param lux float, ambient light in nit (cd/m2)
        @return float - target screen brightness in nit (cd/m2)
     */
    float getTargetNit(float lux);
    /*
        @brief Caluate screen brightness level from nit
        @param lux float, screen brightness light in nit (cd/m2)
        @note 255 level with 300 nit max brightness as default
        @return int - screen brightness level
     */
    int getBrightnessVal(float lux);

public:
    BrightnessController(int maxScreenNit = 300);
    ~BrightnessController();

    /*
        @brief Function to calculate screen brightness
        @param lux float, screen brightness light in nit (cd/m2)
        @param userAdj float, brightness user adjust level (-1.0 ~ 1.0)
        @return int - screen brightness level
     */
    int updateBrightness(float lux, float userAdj);
    
    void setAmbient_DisplayNitFunction(ambient_displayNit_fun_t fun);
    void setDisplayNit_BrightnessLevelFunction(displayNit_brightnessLevel_fun_t fun);
    void setMaxScreenNit(int maxScreenNit);
};
