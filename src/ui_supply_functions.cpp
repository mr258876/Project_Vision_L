#include <Arduino.h>
#include "ui.h"
#include "rtos_externs.h"
#include "The_Vision_L_globals.h"

void removeStyles(lv_obj_t *obj)
{
  lv_obj_remove_style_all(obj);
  for (int i = 0; i < lv_obj_get_child_cnt(obj); i++)
  {
    removeStyles(lv_obj_get_child(obj, i));
  }
}

void delScr(void *scr)
{
  removeStyles((lv_obj_t *)scr);
  lv_obj_del_async((lv_obj_t *)scr);
}

void refreshScr(void *scr)
{
  lv_obj_invalidate((lv_obj_t *)scr);
}

void cb_leaveResinScreen(lv_event_t *e)
{
  lv_timer_del(ui_timer_ResinDispTimer);                              // 删除树脂显示刷新定时器
  lv_group_remove_all_objs(ui_group);                                 // 删除控制组内对象
  removeStyles(ui_ResinScreen);                                       // 删除样式
  ui_MenuScreen_screen_init();                                        // 初始化下个要显示的屏幕
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true); // 切换屏幕
}

void cb_leaveClockScreen(lv_event_t *e)
{
  lv_anim_del_all();                                                   // 删除时钟背景动画
  lv_timer_del(ui_timer_ClockTimer);                                   // 删除树脂显示刷新定时器
  lv_group_remove_all_objs(ui_group);                                  // 删除控制组内对象
  ui_MenuScreen_screen_init();                                         // 初始化下个要显示的屏幕
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false); // 切换屏幕
  lv_async_call(delScr, ui_ClockScreen);                               // 屏幕切换后异步释放资源

  lv_async_call(refreshScr, ui_MenuScreen); // 刷新屏幕消除切换回菜单后的残留部分
}

void cb_leaveSettingScreen(lv_event_t *e)
{
  lv_group_remove_all_objs(ui_group);                                  // 删除控制组内对象
  ui_MenuScreen_screen_init();                                         // 初始化下个要显示的屏幕
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false); // 切换屏幕
  lv_async_call(delScr, ui_SettingScreen);                             // 屏幕切换后异步释放资源
}

void cb_loadResinScreen(lv_event_t *e)
{
  lv_group_remove_all_objs(ui_group);
  ui_ResinScreen_screen_init();
  lv_scr_load_anim(ui_ResinScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
  lv_async_call(delScr, ui_MenuScreen);
}

void cb_loadClockScreen(lv_event_t *e)
{
  lv_group_remove_all_objs(ui_group);
  ui_ClockScreen_screen_init();
  lv_scr_load_anim(ui_ClockScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
  lv_async_call(delScr, ui_MenuScreen);
}

void cb_loadSettingScreen(lv_event_t *e)
{
  lv_group_remove_all_objs(ui_group);
  ui_SettingScreen_screen_init();
  lv_scr_load_anim(ui_SettingScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
  lv_async_call(delScr, ui_MenuScreen);
}