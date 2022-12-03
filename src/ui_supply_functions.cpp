#include <Arduino.h>
#include <Preferences.h>
#include "ui.h"
#include "rtos_externs.h"
#include "The_Vision_L_globals.h"
#include "ui_multiLanguage.h"

void cleanObj(lv_obj_t *obj)
{
  for (int i = 0; i < lv_obj_get_child_cnt(obj); i++)
  {
    cleanObj(lv_obj_get_child(obj, i));
  }
  lv_obj_remove_style_all(obj);
  lv_mem_free(lv_obj_get_user_data(obj));
}

void delScr(void *scr)
{
  cleanObj((lv_obj_t *)scr);
  lv_obj_del_async((lv_obj_t *)scr);
}

void refreshScr(void *scr)
{
  lv_obj_invalidate((lv_obj_t *)scr);
}

void cb_timer_ScrDelTimer(lv_timer_t *timer)
{
  lv_obj_t *scr = (lv_obj_t *)(timer->user_data);
  delScr(scr);
}

void cb_leaveResinScreen_async(void *parameter)
{
  lv_group_remove_all_objs(ui_group);                                       // 删除控制组内对象
  ui_MenuScreen_screen_init();                                              // 初始化下个要显示的屏幕
  lv_group_focus_obj(ui_MenuButton2);                                       // 聚焦在树脂按钮上
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_FADE_ON, 250, 0, false); // 切换屏幕

  refreshScr(ui_MenuScreen); // 刷新屏幕消除切换回菜单后的残留部分
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 250, ui_ResinScreen);
  lv_timer_set_repeat_count(ui_timer_ScrDelTimer, 1);
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
  lv_group_focus_obj(ui_MenuButton3);                                  // 聚焦在时钟按钮上
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false); // 切换屏幕
  refreshScr(ui_MenuScreen);                                           // 刷新屏幕消除切换回菜单后的残留部分
  delScr(ui_ClockScreen);                                              // 屏幕切换后释放资源
}
void cb_leaveClockScreen(lv_event_t *e)
{
  lv_anim_del_all();                              // 删除时钟背景动画
  lv_timer_del(ui_timer_ClockTimerSecond);        // 删除秒针刷新定时器
  lv_timer_del(ui_timer_ClockTimerMinute);        // 删除分针刷新定时器
  lv_timer_del(ui_timer_ClockTimerHour);          // 删除时针刷新定时器
  lv_async_call(cb_leaveClockScreen_async, NULL); // 异步调用屏幕切换函数
}

void cb_leaveSettingScreen_async(void *parameter)
{
  lv_group_remove_all_objs(ui_group);                                       // 删除控制组内对象
  ui_MenuScreen_screen_init();                                              // 初始化下个要显示的屏幕
  lv_group_focus_obj(ui_MenuButton4);                                       // 聚焦在设置按钮上
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_FADE_ON, 250, 0, false); // 切换屏幕
  refreshScr(ui_MenuScreen);
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 250, ui_SettingScreen);
  lv_timer_set_repeat_count(ui_timer_ScrDelTimer, 1);
}
void cb_leaveSettingScreen(lv_event_t *e)
{
  lv_anim_del_all();                                // 删除时钟背景动画
  lv_timer_del(ui_timer_SettingDispTimer);          // 删除设置值显示刷新定时器
  lv_async_call(cb_leaveSettingScreen_async, NULL); // 异步调用屏幕切换函数
}

void cb_loadResinScreen(lv_event_t *e)
{
  lv_group_remove_all_objs(ui_group);
  ui_ResinScreen_screen_init();
  lv_scr_load_anim(ui_ResinScreen, LV_SCR_LOAD_ANIM_FADE_ON, 250, 0, false);
  refreshScr(ui_ResinScreen);
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 250, ui_MenuScreen);
  lv_timer_set_repeat_count(ui_timer_ScrDelTimer, 1);
}

void cb_loadClockScreen(lv_event_t *e)
{
  // Check whether time is avaliable
  if (!info_timeSynced)
  {
    // if not, pop out error message
    mbox = lv_msgbox_create(ui_MenuScreen, lang[curr_lang][54], lang[curr_lang][55], {}, false); // LV_SYMBOL_WARNING "错误：" "未同步时间\n"
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
  delScr(ui_MenuScreen);

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
  lv_scr_load_anim(ui_SettingScreen, LV_SCR_LOAD_ANIM_FADE_ON, 250, 0, false);
  refreshScr(ui_SettingScreen);
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 250, ui_MenuScreen);
  lv_timer_set_repeat_count(ui_timer_ScrDelTimer, 1);
}

void cb_leaveWifiReconfigInfo()
{
  cb_ui_InfoScreen_back = NULL;
  lv_scr_load_anim(ui_SettingScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false);
  lv_group_focus_freeze(ui_group, false);
  lv_group_focus_obj(ui_SettingPanel1Button1Button);
  refreshScr(ui_SettingScreen);
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 200, ui_InfoScreen);
  lv_timer_set_repeat_count(ui_timer_ScrDelTimer, 1);

  cb_stopWifiReConfigure(NULL);
}

void cb_loadWifiReconfigInfo(lv_event_t *e)
{
  ui_InfoScreen_screen_init();

  lv_obj_t *ui_InfoPanelLabel1 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel1, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel1, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel1, 0);
  lv_obj_set_y(ui_InfoPanelLabel1, 0);
  lv_obj_set_align(ui_InfoPanelLabel1, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_InfoPanelLabel1, lang[curr_lang][33]); // "使用微信扫描QR码\n进行网络配置"
  lv_obj_set_style_text_font(ui_InfoPanelLabel1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_InfoPanelQR1 = lv_qrcode_create(ui_InfoPanel, 100, lv_color_black(), lv_color_white());
  lv_qrcode_update(ui_InfoPanelQR1, lang[curr_lang][34], strlen(lang[curr_lang][34])); // "http://iot.espressif.cn/configWXDeviceWiFi.html"
  lv_obj_set_x(ui_InfoPanelQR1, 0);
  lv_obj_set_y(ui_InfoPanelQR1, 60);
  lv_obj_set_align(ui_InfoPanelQR1, LV_ALIGN_TOP_MID);
  lv_obj_clear_flag(ui_InfoPanelQR1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_radius(ui_InfoPanelQR1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_InfoPanelQR1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_InfoPanelQR1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(ui_InfoPanelQR1, lv_color_white(), 0);
  lv_obj_set_style_border_width(ui_InfoPanelQR1, 5, 0);

  cb_ui_InfoScreen_back = cb_leaveWifiReconfigInfo;

  lv_scr_load_anim(ui_InfoScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false);

  lv_group_focus_obj(ui_InfoTitleBackButton);
  lv_group_focus_freeze(ui_group, true);
  refreshScr(ui_InfoScreen);

  cb_startWifiReConfigure(NULL);
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
