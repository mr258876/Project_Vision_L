#include <Arduino.h>

#include "The_Vision_L_globals.h"

#include "ui/ui.h"
#include "ui/ui_multiLanguage.h"
#include "ui/ui_supply_functions.h"

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
  if (scr)
  {
    cleanObj((lv_obj_t *)scr);
    lv_obj_del_async((lv_obj_t *)scr);
  }
}

void refreshScr(void *scr)
{
  lv_obj_invalidate((lv_obj_t *)scr);
}

void cb_timer_ScrDelTimer(lv_timer_t *timer)
{
  lv_obj_t *scr = (lv_obj_t *)(timer->user_data);
  delScr(scr);
  lv_timer_del(timer);
}

void cb_leaveResinScreen(lv_event_t *e)
{
  lv_timer_del(ui_timer_ResinDispTimer);                                             // 删除树脂显示刷新定时器
  lv_group_remove_all_objs(ui_group);                                                // 删除控制组内对象
  ui_MenuScreen_screen_init();                                                       // 初始化下个要显示的屏幕
  lv_group_focus_obj(ui_MenuButton2);                                                // 聚焦在树脂按钮上
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_FADE_ON, 250, 0, false);          // 切换屏幕
  refreshScr(ui_MenuScreen);                                                         // 刷新屏幕消除切换回菜单后的残留部分
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 250, ui_ResinScreen); // 创建定时器异步删除屏幕
}

void cb_leaveClockScreen(lv_event_t *e)
{
  lv_anim_del_all();                                                   // 删除时钟背景动画
  lv_timer_del(ui_timer_ClockTimerSecond);                             // 删除秒针刷新定时器
  lv_timer_del(ui_timer_ClockTimerMinute);                             // 删除分针刷新定时器
  lv_timer_del(ui_timer_ClockTimerHour);                               // 删除时针刷新定时器
  lv_group_remove_all_objs(ui_group);                                  // 删除控制组内对象
  ui_MenuScreen_screen_init();                                         // 初始化下个要显示的屏幕
  lv_group_focus_obj(ui_MenuButton3);                                  // 聚焦在时钟按钮上
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false); // 切换屏幕
  refreshScr(ui_MenuScreen);                                           // 刷新屏幕消除切换回菜单后的残留部分
  delScr(ui_ClockScreen);                                              // 屏幕切换后释放资源
}

void cb_leaveDigitalClockScreen(lv_event_t *e)
{
  lv_timer_del(ui_timer_DigitalClockTimer);                            // 删除秒针刷新定时器
  lv_timer_del(ui_timer_DigitalClockResinTimer);                       // 删除分针刷新定时器
  lv_timer_del(ui_timer_DigitalClockWeatherTimer);                     // 删除天气数据刷新定时器
  lv_group_remove_all_objs(ui_group);                                  // 删除控制组内对象
  ui_MenuScreen_screen_init();                                         // 初始化下个要显示的屏幕
  lv_group_focus_obj(ui_MenuButton3);                                  // 聚焦在时钟按钮上
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false); // 切换屏幕
  refreshScr(ui_MenuScreen);                                           // 刷新屏幕消除切换回菜单后的残留部分
  delScr(ui_DigitalClockScreen);                                       // 屏幕切换后释放资源
}

void cb_leaveSettingScreen(lv_event_t *e)
{
  lv_anim_del_all();                                                                   // 删除时钟背景动画
  lv_timer_del(ui_timer_SettingDispTimer);                                             // 删除设置值显示刷新定时器
  lv_group_remove_all_objs(ui_group);                                                  // 删除控制组内对象
  ui_MenuScreen_screen_init();                                                         // 初始化下个要显示的屏幕
  lv_group_focus_obj(ui_MenuButton4);                                                  // 聚焦在设置按钮上
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_FADE_ON, 250, 0, false);            // 切换屏幕
  refreshScr(ui_MenuScreen);                                                           // 刷新屏幕消除切换回菜单后的残留部分
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 250, ui_SettingScreen); // 创建定时器异步删除屏幕
}

void cb_loadResinScreen(lv_event_t *e)
{
  lv_group_remove_all_objs(ui_group);
  ui_ResinScreen_screen_init();
  lv_scr_load_anim(ui_ResinScreen, LV_SCR_LOAD_ANIM_FADE_ON, 250, 0, false);
  refreshScr(ui_ResinScreen);
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 250, ui_MenuScreen);
}

void cb_loadClock(lv_event_t *e)
{
  if (setting_useDigitalClock)
  {
    cb_loadDigitalClockScreen(e);
  }
  else
  {
    cb_loadClockScreen(e);
  }
}

void cb_switchClockScreen(lv_event_t *e)
{
  if (setting_useDigitalClock)
  {
    cb_leaveDigitalClockScreen(e);
    cb_loadClockScreen(e);
  }
  else
  {
    cb_leaveClockScreen(e);
    cb_loadDigitalClockScreen(e);
  }

  setting_useDigitalClock = !setting_useDigitalClock;
  prefs.putBool("useDigitalClock", setting_useDigitalClock);
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

void cb_loadDigitalClockScreen(lv_event_t *e)
{
  // Check whether time is avaliable
  if (!info_timeSynced)
  {
    // if not, pop out error message
    mbox = lv_msgbox_create(ui_MenuScreen, lang[curr_lang][54], lang[curr_lang][55], {}, false); // LV_SYMBOL_WARNING "错误：" "未同步时间\n"
    lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(mbox);
    ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 5000, mbox);

    return;
  }

  // Remove menu screen, Load clock screen
  lv_group_remove_all_objs(ui_group);
  ui_DigitalClockScreen_screen_init();
  lv_scr_load_anim(ui_DigitalClockScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
  delScr(ui_MenuScreen);
}

void cb_loadSettingScreen(lv_event_t *e)
{
  lv_group_remove_all_objs(ui_group);
  ui_SettingScreen_screen_init();
  lv_scr_load_anim(ui_SettingScreen, LV_SCR_LOAD_ANIM_FADE_ON, 250, 0, false);
  refreshScr(ui_SettingScreen);
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 250, ui_MenuScreen);
}

////////////////////////
// 重新配网界面

void cb_leaveWifiReconfigInfo()
{
  cb_ui_InfoScreen_back = NULL;
  lv_scr_load_anim(ui_SettingScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false);
  lv_group_focus_freeze(ui_group, false);
  lv_group_focus_obj(ui_SettingPanel1Button1Button);
  refreshScr(ui_SettingScreen);
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 200, ui_InfoScreen);

  cb_stopWifiReConfigure(NULL);
}

void cb_loadWifiReconfigInfo(lv_event_t *e)
{
  ui_InfoScreen_screen_init();

  lv_label_set_text(ui_InfoTitleLabel, lang[curr_lang][58]); // "配网模式"

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

////////////////////////
// SD卡异常界面

void cb_leaveSDErrorInfo()
{
  cb_ui_InfoScreen_back = NULL;
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false);
  lv_group_focus_freeze(ui_group, false);
  lv_group_focus_obj(ui_MenuButton1);
  refreshScr(ui_MenuScreen);
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 200, ui_InfoScreen);

  cb_stopWifiReConfigure(NULL);
}

void cb_loadSDErrorInfo(lv_event_t *e)
{
  ui_InfoScreen_screen_init();

  lv_label_set_text(ui_InfoTitleLabel, lang[curr_lang][54]); // "错误"

  lv_obj_t *ui_InfoPanelLabel1 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel1, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel1, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel1, 15);
  lv_obj_set_y(ui_InfoPanelLabel1, 10);
  lv_label_set_text(ui_InfoPanelLabel1, lang[curr_lang][12]); // "未检测到SD卡\n"
  lv_obj_set_style_text_color(ui_InfoPanelLabel1, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_InfoPanelLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_InfoPanelLabel1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_InfoPanelLabel2 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel2, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel2, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel2, 25);
  lv_obj_set_y(ui_InfoPanelLabel2, 0);
  lv_obj_set_align(ui_InfoPanelLabel2, LV_ALIGN_LEFT_MID);
  lv_label_set_text(ui_InfoPanelLabel2, LV_SYMBOL_SD_CARD);
  lv_obj_set_style_text_font(ui_InfoPanelLabel2, &ui_font_FontAwesomeIcon48, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_InfoPanelLabel3 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel3, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel3, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel3, 100);
  lv_obj_set_y(ui_InfoPanelLabel3, 0);
  lv_obj_set_align(ui_InfoPanelLabel3, LV_ALIGN_LEFT_MID);
  lv_label_set_text(ui_InfoPanelLabel3, lang[curr_lang][67]); // "请检查SD卡，\n然后重试。"
  lv_obj_set_style_text_font(ui_InfoPanelLabel3, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_InfoPanelLabel4 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel4, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel4, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel4, 50);
  lv_obj_set_y(ui_InfoPanelLabel4, 10);
  lv_obj_set_align(ui_InfoPanelLabel4, LV_ALIGN_LEFT_MID);
  lv_label_set_text(ui_InfoPanelLabel4, LV_SYMBOL_CLOSE);
  lv_obj_set_style_text_color(ui_InfoPanelLabel4, lv_color_hex(0xE20000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_InfoPanelLabel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_InfoPanelLabel4, &ui_font_FontAwesomeIcon24, LV_PART_MAIN | LV_STATE_DEFAULT);

  cb_ui_InfoScreen_back = cb_leaveSDErrorInfo;

  lv_scr_load_anim(ui_InfoScreen, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false);

  lv_group_focus_obj(ui_InfoTitleBackButton);
  lv_group_focus_freeze(ui_group, true);
  refreshScr(ui_InfoScreen);
}

////////////////////////
// 播放列表异常界面

void cb_leavePlaylistErrorInfo()
{
  cb_ui_InfoScreen_back = NULL;
  lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false);
  lv_group_focus_freeze(ui_group, false);
  lv_group_focus_obj(ui_MenuButton1);
  refreshScr(ui_MenuScreen);
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 200, ui_InfoScreen);

  cb_stopWifiReConfigure(NULL);
}

void cb_loadPlaylistErrorInfo(lv_event_t *e)
{
  ui_InfoScreen_screen_init();

  lv_label_set_text(ui_InfoTitleLabel, lang[curr_lang][54]); // "错误"

  lv_obj_t *ui_InfoPanelLabel1 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel1, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel1, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel1, 15);
  lv_obj_set_y(ui_InfoPanelLabel1, 10);
  lv_label_set_text(ui_InfoPanelLabel1, lang[curr_lang][13]); // "没有可播放的文件"
  lv_obj_set_style_text_color(ui_InfoPanelLabel1, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_InfoPanelLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_InfoPanelLabel1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_InfoPanelLabel2 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel2, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel2, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel2, 25);
  lv_obj_set_y(ui_InfoPanelLabel2, 0);
  lv_obj_set_align(ui_InfoPanelLabel2, LV_ALIGN_LEFT_MID);
  lv_label_set_text(ui_InfoPanelLabel2, LV_SYMBOL_IMAGE);
  lv_obj_set_style_text_font(ui_InfoPanelLabel2, &ui_font_FontAwesomeIcon48, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_InfoPanelLabel3 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel3, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel3, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel3, 100);
  lv_obj_set_y(ui_InfoPanelLabel3, 0);
  lv_obj_set_align(ui_InfoPanelLabel3, LV_ALIGN_LEFT_MID);
  lv_label_set_text(ui_InfoPanelLabel3, lang[curr_lang][109]); // "请检查播放列表，\n然后重试。"
  lv_obj_set_style_text_font(ui_InfoPanelLabel3, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_InfoPanelLabel4 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel4, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel4, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel4, 50);
  lv_obj_set_y(ui_InfoPanelLabel4, 10);
  lv_obj_set_align(ui_InfoPanelLabel4, LV_ALIGN_LEFT_MID);
  lv_label_set_text(ui_InfoPanelLabel4, LV_SYMBOL_CLOSE);
  lv_obj_set_style_text_color(ui_InfoPanelLabel4, lv_color_hex(0xE20000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_InfoPanelLabel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_InfoPanelLabel4, &ui_font_FontAwesomeIcon24, LV_PART_MAIN | LV_STATE_DEFAULT);

  cb_ui_InfoScreen_back = cb_leaveSDErrorInfo;

  lv_scr_load_anim(ui_InfoScreen, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false);

  lv_group_focus_obj(ui_InfoTitleBackButton);
  lv_group_focus_freeze(ui_group, true);
  refreshScr(ui_InfoScreen);
}

////////////////////////
// 距离传感器校准界面

lv_group_t * ui_group_ProxCalibrationInfo;
lv_timer_t * ui_timer_ProxCalibrationTimer;
uint16_t proxReading = 0;

void cb_leaveProxCalibrationInfo()
{
  lv_timer_del(ui_timer_ProxCalibrationTimer);
  cb_ui_InfoScreen_back = NULL;
  lv_scr_load_anim(ui_SettingScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false);
  lv_group_set_default(ui_group);
  lv_group_del(ui_group_ProxCalibrationInfo);
  lv_group_focus_obj(ui_SettingPanel2Button1Button);
  refreshScr(ui_SettingScreen);
  ui_timer_ScrDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 200, ui_InfoScreen);
}

void cb_timer_ProxCalibrationTimer(lv_timer_t *timer)
{
  proxReading = cb_readProx();
  lv_label_set_text_fmt(((lv_obj_t *)timer->user_data), lang[curr_lang][114], proxReading);  // "距离读数：150"
}

void ui_event_ProxCal_Button(lv_event_t *e)
{
  lv_event_code_t event = lv_event_get_code(e);
  lv_obj_t *ta = lv_event_get_target(e);
  if (event == LV_EVENT_CLICKED)
  {
    cb_setProxThres(proxReading);
    cb_leaveProxCalibrationInfo();
  }
}

void cb_loadProxCalibrationInfo(lv_event_t *e)
{
  ui_InfoScreen_screen_init();

  ui_group_ProxCalibrationInfo = lv_group_create();
  lv_group_set_default(ui_group_ProxCalibrationInfo);
  lv_group_add_obj(ui_group_ProxCalibrationInfo, ui_InfoTitleBackButton);

  lv_label_set_text(ui_InfoTitleLabel, lang[curr_lang][28]); // "设置"

  lv_obj_t *ui_InfoPanelLabel1 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel1, 180);
  lv_obj_set_height(ui_InfoPanelLabel1, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel1, 15);
  lv_obj_set_y(ui_InfoPanelLabel1, 0);
  lv_label_set_text(ui_InfoPanelLabel1, lang[curr_lang][112]); // 距离传感器校准
  lv_obj_set_style_text_color(ui_InfoPanelLabel1, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_InfoPanelLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_InfoPanelLabel1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_InfoPanelLabel2 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel2, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel2, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel2, 20);
  lv_obj_set_y(ui_InfoPanelLabel2, 20);
  lv_obj_set_align(ui_InfoPanelLabel2, LV_ALIGN_LEFT_MID);
  lv_label_set_text(ui_InfoPanelLabel2, "距离读数：150");
  lv_obj_set_style_text_font(ui_InfoPanelLabel2, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_InfoPanelLabel3 = lv_label_create(ui_InfoPanel);
  lv_obj_set_width(ui_InfoPanelLabel3, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_InfoPanelLabel3, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_InfoPanelLabel3, 20);
  lv_obj_set_y(ui_InfoPanelLabel3, -20);
  lv_obj_set_align(ui_InfoPanelLabel3, LV_ALIGN_LEFT_MID);
  lv_label_set_text(ui_InfoPanelLabel3, lang[curr_lang][113]); // "Cover the sensor,\nthen click \"calibrate\"."
  lv_obj_set_style_text_font(ui_InfoPanelLabel3, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_ProxCal_Button = lv_btn_create(ui_InfoPanel);
  lv_obj_set_width(ui_ProxCal_Button, 100);
  lv_obj_set_height(ui_ProxCal_Button, 30);
  lv_obj_set_x(ui_ProxCal_Button, 20);
  lv_obj_set_y(ui_ProxCal_Button, 120);
  lv_obj_add_flag(ui_ProxCal_Button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
  lv_obj_clear_flag(ui_ProxCal_Button, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
  lv_obj_set_style_radius(ui_ProxCal_Button, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_ProxCal_Button, lv_color_hex(0xD8CDB9), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_ProxCal_Button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_outline_color(ui_ProxCal_Button, lv_color_hex(0xFFCC33), LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_outline_opa(ui_ProxCal_Button, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_outline_width(ui_ProxCal_Button, 4, LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_outline_pad(ui_ProxCal_Button, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

  lv_obj_t *ui_ProxCal_Button_Label = lv_label_create(ui_ProxCal_Button);
  lv_obj_set_width(ui_ProxCal_Button_Label, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_ProxCal_Button_Label, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_ProxCal_Button_Label, LV_ALIGN_CENTER);
  lv_label_set_text(ui_ProxCal_Button_Label, lang[curr_lang][115]); // "校准"
  lv_obj_set_style_text_color(ui_ProxCal_Button_Label, lv_color_hex(0x495366), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_ProxCal_Button_Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_ProxCal_Button_Label, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_timer_ProxCalibrationTimer = lv_timer_create(cb_timer_ProxCalibrationTimer, 500, ui_InfoPanelLabel2);
  lv_timer_ready(ui_timer_ProxCalibrationTimer);

  lv_obj_add_event_cb(ui_ProxCal_Button, ui_event_ProxCal_Button, LV_EVENT_ALL, NULL);

  cb_ui_InfoScreen_back = cb_leaveProxCalibrationInfo;

  lv_scr_load_anim(ui_InfoScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false);

  lv_group_focus_obj(ui_ProxCal_Button);
  refreshScr(ui_InfoScreen);
}

////////////////////////
// 初次配网界面

void cb_loadWifiConfigInfoStartupScreen(lv_event_t *e)
{
  lv_obj_clean(ui_StartupScreen);

  lv_obj_t *ui_NetConfigureTitle = lv_label_create(ui_StartupScreen);

  lv_obj_set_width(ui_NetConfigureTitle, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_NetConfigureTitle, LV_SIZE_CONTENT);

  lv_obj_set_x(ui_NetConfigureTitle, 25);
  lv_obj_set_y(ui_NetConfigureTitle, 35);

  lv_label_set_text(ui_NetConfigureTitle, lang[curr_lang][32]); // "网络配置"

  lv_obj_set_style_text_color(ui_NetConfigureTitle, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_NetConfigureTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_NetConfigureTitle, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_NetConfigureLabel = lv_label_create(ui_StartupScreen);

  lv_obj_set_width(ui_NetConfigureLabel, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_NetConfigureLabel, LV_SIZE_CONTENT);

  lv_obj_set_x(ui_NetConfigureLabel, 30);
  lv_obj_set_y(ui_NetConfigureLabel, 85);

  lv_label_set_text(ui_NetConfigureLabel, lang[curr_lang][35]); // "神之眼的部分功能\n依赖网络。\n\n使用微信\n扫描右侧\nQR码配\n置网络。"

  lv_obj_set_style_text_color(ui_NetConfigureLabel, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui_NetConfigureLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_NetConfigureLabel, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *qr = lv_qrcode_create(ui_StartupScreen, 100, lv_color_black(), lv_color_white());

  /*Set data*/
  lv_qrcode_update(qr, lang[curr_lang][34], strlen(lang[curr_lang][34])); // "http://iot.espressif.cn/configWXDeviceWiFi.html"
  lv_obj_set_x(qr, 105);
  lv_obj_set_y(qr, 110);

  /*Add a border with bg_color*/
  lv_obj_set_style_border_color(qr, lv_color_white(), 0);
  lv_obj_set_style_border_width(qr, 5, 0);
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
  lv_obj_invalidate(lv_scr_act());
}