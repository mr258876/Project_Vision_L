#ifndef _UI_SUPPLY_FUNCTIONS_H_
#define _UI_SUPPLY_FUNCTIONS_H_

#include "lvgl.h"

void cleanObj(lv_obj_t *obj);
void delScr(void *scr);
void refreshScr(void *scr);

void mboxCreate(lv_obj_t *parent, const char *title, const char *content, const char **btn_txts, bool add_close_btn, uint32_t timeout = 5000);

uint16_t cb_readProx();

#endif