/*

FileName: BrightnessController.cpp
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

#include "BrightnessController.h"

BrightnessController::BrightnessController(int maxScreenNit)
{
    this->maxScreenBrightnessNit = maxScreenNit;
}

BrightnessController::~BrightnessController()
{
}

float BrightnessController::getTargetNit(float lux)
{
    return (9.9323 * logf(lux) + 27.059) * (this->maxScreenBrightnessNit / 100.0);  // Screen beightness curve in Windows 10 and below
}

int BrightnessController::getBrightnessVal(float lux)
{
    float lev = lux / 1.1764705882352941;
    int res = round(lev);
    res = (res < 1 ? 1 : res);
    res = (res > 255 ? 255 : res);
    return res;
}

int BrightnessController::updateBrightness(float lux, float userAdj)
{
    userAdj = (userAdj > 1 ? 1 : userAdj);
    userAdj = (userAdj < -1 ? -1 : userAdj);

    float brightness = getBrightnessVal(getTargetNit(lux)) * 1.0 / maxBrightnessLevel;
    brightness = (brightness > 1 ? 1 : brightness);
    brightness = (brightness < 0 ? 0 : brightness);
    float lev = pow(brightness, (3 - userAdj)) * maxBrightnessLevel;

    int res = round(lev);
    res = (res < 1 ? 1 : res);
    res = (res > 255 ? 255 : res);
    return res;
}

void BrightnessController::setDisplayNit_BrightnessLevelFunction(displayNit_brightnessLevel_fun_t fun)
{
    this->nit_lev_fun = fun;
    this->maxBrightnessLevel = this->nit_lev_fun(9999);
}

void BrightnessController::setMaxScreenNit(int maxScreenNit)
{
    this->maxScreenBrightnessNit = maxScreenNit;
}
