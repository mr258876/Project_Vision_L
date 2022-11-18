#include <Arduino.h>
#include <Preferences.h>
#include "ui.h"
#include "rtos_externs.h"
#include "The_Vision_L_globals.h"
#include "ui_multiLanguage.h"

void removeStyles(lv_obj_t *obj)
{
  for (int i = 0; i < lv_obj_get_child_cnt(obj); i++)
  {
    removeStyles(lv_obj_get_child(obj, i));
  }
  lv_obj_remove_style_all(obj);
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

void cb_timer_ScrDelTimer(lv_timer_t *timer)
{
  lv_obj_t *scr = (lv_obj_t *)(timer->user_data);
  lv_async_call(delScr, scr);
}

void cb_leaveResinScreen_async(void *parameter)
{
  lv_group_remove_all_objs(ui_group);                                  // 删除控制组内对象
  ui_MenuScreen_screen_init();                                         // 初始化下个要显示的屏幕
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false); // 切换屏幕
  lv_async_call(delScr, ui_ResinScreen);                               // 异步删除屏幕
}
void cb_leaveResinScreen(lv_event_t *e)
{
  lv_timer_del(ui_timer_ResinDispTimer);          // 删除树脂显示刷新定时器
  lv_async_call(cb_leaveResinScreen_async, NULL); // 异步调用屏幕切换函数
}

void cb_leaveClockScreen_async(void *parameter)
{
  lv_group_remove_all_objs(ui_group);                                  // 删除控制组内对象
  ui_MenuScreen_screen_init();                                         // 初始化下个要显示的屏幕
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false); // 切换屏幕
  lv_async_call(delScr, ui_ClockScreen);                               // 屏幕切换后异步释放资源
  lv_async_call(refreshScr, ui_MenuScreen);                            // 刷新屏幕消除切换回菜单后的残留部分
}
void cb_leaveClockScreen(lv_event_t *e)
{
  lv_anim_del_all();                              // 删除时钟背景动画
  lv_timer_del(ui_timer_ClockTimerSecond);              // 删除树脂显示刷新定时器
  lv_timer_del(ui_timer_ClockTimerMinute);              // 删除树脂显示刷新定时器
  lv_timer_del(ui_timer_ClockTimerHour);              // 删除树脂显示刷新定时器
  lv_async_call(cb_leaveClockScreen_async, NULL); // 异步调用屏幕切换函数
}

void cb_leaveSettingScreen(lv_event_t *e)
{
  lv_group_remove_all_objs(ui_group);                                  // 删除控制组内对象
  ui_MenuScreen_screen_init();                                         // 初始化下个要显示的屏幕
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false); // 切换屏幕
  lv_async_call(delScr, ui_SettingScreen);                             // 异步删除屏幕
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
  // Check whether time is avaliable
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    // if not, pop out error message
    lv_obj_t *mbox = lv_msgbox_create(ui_MenuScreen, lang[curr_lang][54], lang[curr_lang][55], {}, false); // LV_SYMBOL_WARNING "错误：" "未同步时间\n"
    lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(mbox);
    ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 5000, mbox);
    lv_timer_set_repeat_count(ui_timer_ScrDelTimer, 1);
    return;
  }

  // Remove menu screen, Load clock screen
  lv_group_remove_all_objs(ui_group);
  ui_ClockScreen_screen_init();
  lv_scr_load_anim(ui_ClockScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
  lv_async_call(delScr, ui_MenuScreen);

  // Rotate clock dial 45 degrees if using round LCD
  if (!info_isSquareLCD)
  {
    lv_img_set_angle(ui_ClockDial, 3150);
  }
}

void cb_loadSettingScreen(lv_event_t *e)
{
  lv_group_remove_all_objs(ui_group);
  ui_SettingScreen_screen_init();
  lv_scr_load_anim(ui_SettingScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
  lv_async_call(delScr, ui_MenuScreen);
  // ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 100, ui_MenuScreen);
  // lv_timer_set_repeat_count(ui_timer_ScrDelTimer, 1);
}

void cb_dispSettings(lv_event_t *e)
{
  if (info_hasProx)
  {
    if (setting_autoBright)
      lv_obj_add_state(ui_SettingPanel2SW1Switch1, LV_STATE_CHECKED);
  }
  else
  {
    lv_obj_add_state(ui_SettingPanel2SW1Switch1, LV_STATE_DISABLED);
  }

  if (info_hasAccel)
  {
    if (setting_useAccel)
      lv_obj_add_state(ui_SettingPanel2SW2Switch1, LV_STATE_CHECKED);
  }
  else
  {
    lv_obj_add_state(ui_SettingPanel2SW2Switch1, LV_STATE_DISABLED);
  }

  lv_dropdown_set_selected(ui_SettingPanel2DP1Dropdown1, curr_lang);
}

void cb_setAutoBright(bool val)
{
  setting_autoBright = val;
  prefs.putBool("useAutoBright", val);
}

void cb_setUseAccel(bool val)
{
  setting_useAccel = val;
  prefs.putBool("useAccelMeter", val);
}

void cb_setLanguage(uint16_t val)
{
  curr_lang = val;
  prefs.putUInt("language", val);

  esp_restart(); // Temporary solution
}
