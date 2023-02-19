#ifndef _UI_SUPPLY_FUNCTIONS_H_
#define _UI_SUPPLY_FUNCTIONS_H_

#include "lvgl.h"

void cleanObj(lv_obj_t *obj);
void delScr(void *scr);
void refreshScr(void *scr);

uint16_t cb_readProx();

#endif