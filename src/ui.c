// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: The_Vision_L

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_StartupScreen;
lv_obj_t *ui_StartupTitle1;
lv_obj_t *ui_StartupTitle2;
lv_obj_t *ui_StartupLabel1;
lv_obj_t *ui_StartupLabel2;
lv_obj_t *ui_StartupSpinner;
lv_obj_t *ui_SettingScreen;

lv_obj_t *ui_SettingsTitlePanel;
lv_obj_t *ui_SettingsTitle;
lv_obj_t *ui_SettingsSidePanel;
lv_obj_t *ui_Button1;
lv_obj_t *ui_Label1;
lv_obj_t *ui_Button2;
lv_obj_t *ui_Label2;
lv_obj_t *ui_Button3;
lv_obj_t *ui_Label3;
lv_obj_t *ui_Button4;
lv_obj_t *ui_Label4;
lv_obj_t *ui_Button5;
lv_obj_t *ui_Label5;
lv_obj_t *ui_SettingsInfoPanel;

lv_obj_t *ui_VideoScreen;

lv_obj_t *ui_ResinScreen;
lv_obj_t *ui_DailyNotePanel;
lv_obj_t *ui_NoteResinLabel;
lv_obj_t *ui_NoteHomeCoinLabel;
lv_obj_t *ui_NoteExpeditionsLabel;
lv_obj_t *ui_NoteTransformerLabel;
lv_obj_t *ui_NoteResinImage;
lv_obj_t *ui_NoteHomeCoinImage;
lv_obj_t *ui_NoteExpeditionsImage;
lv_obj_t *ui_NoteTransformerImage;
lv_obj_t *ui_NoteUpdateTimeLabel;

lv_group_t *ui_group;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 1
#error "#error LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

// ui_EloAnimation0
// FUNCTION HEADER
void aniTitleSlideInY_Animation(lv_obj_t *TargetObject, int delay);

// FUNCTION
void aniTitleSlideInY_Animation(lv_obj_t *TargetObject, int delay)
{

    //
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, -100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);
}

// ui_EloAnimation0
// FUNCTION HEADER
void aniTitleSlideInX_Animation(lv_obj_t *TargetObject, int delay);

// FUNCTION
void aniTitleSlideInX_Animation(lv_obj_t *TargetObject, int delay)
{

    //
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, -100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);
}

///////////////////// FUNCTIONS ////////////////////
static void ui_event_StartupScreen(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_SCREEN_LOAD_START)
    {
        cb_hardwareSetup(e);
    }
}

static void ui_event_ResinScreen(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_KEY)
    {
        switch (lv_event_get_key(e))
        {
        case LV_KEY_ENTER:
            cb_leaveResinScreen(e);
            break;
        case LV_KEY_PREV:
            cb_getDailyNoteFromResinScreen(e);
            break;
        default:
            break;
        }
    }
}

///////////////////// SCREENS ////////////////////
void ui_StartupScreen_screen_init(void)
{

    // ui_StartupScreen

    ui_StartupScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_StartupScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_StartupScreen, ui_event_StartupScreen, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_StartupScreen, lv_color_hex(0x394050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StartupScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupTitle1

    ui_StartupTitle1 = lv_label_create(ui_StartupScreen);

    lv_obj_set_width(ui_StartupTitle1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartupTitle1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StartupTitle1, 25);
    lv_obj_set_y(ui_StartupTitle1, 55);

    lv_label_set_text(ui_StartupTitle1, "The Vision L");

    lv_obj_set_style_text_color(ui_StartupTitle1, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupTitle1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupTitle1, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupTitle2

    ui_StartupTitle2 = lv_label_create(ui_StartupScreen);

    lv_obj_set_width(ui_StartupTitle2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartupTitle2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StartupTitle2, 25);
    lv_obj_set_y(ui_StartupTitle2, 90);

    lv_label_set_text(ui_StartupTitle2, "神之眼 L");

    lv_obj_set_style_text_color(ui_StartupTitle2, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupTitle2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupTitle2, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupLabel1

    ui_StartupLabel1 = lv_label_create(ui_StartupScreen);

    lv_obj_set_width(ui_StartupLabel1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartupLabel1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StartupLabel1, 30);
    lv_obj_set_y(ui_StartupLabel1, 155);

    lv_label_set_text(ui_StartupLabel1, "正在启动");

    lv_obj_set_style_text_color(ui_StartupLabel1, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupLabel1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupLabel2

    ui_StartupLabel2 = lv_label_create(ui_StartupScreen);

    lv_obj_set_width(ui_StartupLabel2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartupLabel2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StartupLabel2, 30);
    lv_obj_set_y(ui_StartupLabel2, 180);

    lv_label_set_text(ui_StartupLabel2, "请稍候...");

    lv_obj_set_style_text_color(ui_StartupLabel2, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartupLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartupLabel2, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartupSpinner

    ui_StartupSpinner = lv_spinner_create(ui_StartupScreen, 1000, 90);

    lv_obj_set_width(ui_StartupSpinner, 45);
    lv_obj_set_height(ui_StartupSpinner, 45);

    lv_obj_set_x(ui_StartupSpinner, 165);
    lv_obj_set_y(ui_StartupSpinner, 155);

    lv_obj_clear_flag(ui_StartupSpinner, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_set_style_arc_color(ui_StartupSpinner, lv_color_hex(0x313131), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_StartupSpinner, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_StartupSpinner, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_StartupSpinner, lv_color_hex(0xFFCC33), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_StartupSpinner, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_StartupSpinner, 8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
}

void ui_SettingScreen_screen_init(void)
{

    // ui_SettingScreen

    ui_SettingScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_SettingScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_SettingScreen, lv_color_hex(0xEAE4D7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SettingsTitlePanel

    ui_SettingsTitlePanel = lv_obj_create(ui_SettingScreen);

    lv_obj_set_width(ui_SettingsTitlePanel, 240);
    lv_obj_set_height(ui_SettingsTitlePanel, 40);

    lv_obj_set_x(ui_SettingsTitlePanel, 0);
    lv_obj_set_y(ui_SettingsTitlePanel, 0);

    lv_obj_clear_flag(ui_SettingsTitlePanel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_SettingsTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingsTitlePanel, lv_color_hex(0x454D5C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingsTitlePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingsTitlePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SettingsTitle

    ui_SettingsTitle = lv_label_create(ui_SettingsTitlePanel);

    lv_obj_set_width(ui_SettingsTitle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SettingsTitle, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_SettingsTitle, 0);
    lv_obj_set_y(ui_SettingsTitle, 0);

    lv_obj_set_align(ui_SettingsTitle, LV_ALIGN_CENTER);

    lv_label_set_text(ui_SettingsTitle, "设置");

    lv_obj_set_style_text_color(ui_SettingsTitle, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SettingsTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingsTitle, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SettingsSidePanel

    ui_SettingsSidePanel = lv_obj_create(ui_SettingScreen);

    lv_obj_set_width(ui_SettingsSidePanel, 60);
    lv_obj_set_height(ui_SettingsSidePanel, 200);

    lv_obj_set_x(ui_SettingsSidePanel, 0);
    lv_obj_set_y(ui_SettingsSidePanel, 40);

    lv_obj_clear_flag(ui_SettingsSidePanel, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_set_scroll_dir(ui_SettingsSidePanel, LV_DIR_VER);

    lv_obj_set_style_radius(ui_SettingsSidePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingsSidePanel, lv_color_hex(0xEAE6DD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingsSidePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingsSidePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button1

    ui_Button1 = lv_btn_create(ui_SettingsSidePanel);

    lv_obj_set_width(ui_Button1, 40);
    lv_obj_set_height(ui_Button1, 40);

    lv_obj_set_x(ui_Button1, -2);
    lv_obj_set_y(ui_Button1, -75);

    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_Button1);

    // ui_Label1

    ui_Label1 = lv_label_create(ui_Button1);

    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label1, 0);
    lv_obj_set_y(ui_Label1, 0);

    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label1, "Text");

    lv_obj_set_style_text_font(ui_Label1, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button2

    ui_Button2 = lv_btn_create(ui_SettingsSidePanel);

    lv_obj_set_width(ui_Button2, 40);
    lv_obj_set_height(ui_Button2, 40);

    lv_obj_set_x(ui_Button2, -2);
    lv_obj_set_y(ui_Button2, -30);

    lv_obj_set_align(ui_Button2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button2, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_Button2);

    // ui_Label2

    ui_Label2 = lv_label_create(ui_Button2);

    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label2, 0);
    lv_obj_set_y(ui_Label2, 0);

    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label2, "Text");

    lv_obj_set_style_text_font(ui_Label2, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button3

    ui_Button3 = lv_btn_create(ui_SettingsSidePanel);

    lv_obj_set_width(ui_Button3, 40);
    lv_obj_set_height(ui_Button3, 40);

    lv_obj_set_x(ui_Button3, -2);
    lv_obj_set_y(ui_Button3, 15);

    lv_obj_set_align(ui_Button3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button3, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_Button3);

    // ui_Label3

    ui_Label3 = lv_label_create(ui_Button3);

    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label3, 0);
    lv_obj_set_y(ui_Label3, 0);

    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label3, "Text");

    lv_obj_set_style_text_font(ui_Label3, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button4

    ui_Button4 = lv_btn_create(ui_SettingsSidePanel);

    lv_obj_set_width(ui_Button4, 40);
    lv_obj_set_height(ui_Button4, 40);

    lv_obj_set_x(ui_Button4, -2);
    lv_obj_set_y(ui_Button4, 60);

    lv_obj_set_align(ui_Button4, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button4, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_Button4);

    // ui_Label4

    ui_Label4 = lv_label_create(ui_Button4);

    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label4, 0);
    lv_obj_set_y(ui_Label4, 0);

    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label4, "Text");

    lv_obj_set_style_text_font(ui_Label4, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Button5

    ui_Button5 = lv_btn_create(ui_SettingsSidePanel);

    lv_obj_set_width(ui_Button5, 40);
    lv_obj_set_height(ui_Button5, 40);

    lv_obj_set_x(ui_Button5, -2);
    lv_obj_set_y(ui_Button5, 105);

    lv_obj_set_align(ui_Button5, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Button5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_Button5, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_Button5);

    // ui_Label5

    ui_Label5 = lv_label_create(ui_Button5);

    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label5, 0);
    lv_obj_set_y(ui_Label5, 0);

    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label5, "Text");

    lv_obj_set_style_text_font(ui_Label5, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SettingsInfoPanel

    ui_SettingsInfoPanel = lv_obj_create(ui_SettingScreen);

    lv_obj_set_width(ui_SettingsInfoPanel, 180);
    lv_obj_set_height(ui_SettingsInfoPanel, 200);

    lv_obj_set_x(ui_SettingsInfoPanel, 60);
    lv_obj_set_y(ui_SettingsInfoPanel, 40);

    lv_obj_clear_flag(ui_SettingsInfoPanel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(ui_SettingsInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingsInfoPanel, lv_color_hex(0xF9F6F2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingsInfoPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_SettingsInfoPanel, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SettingsInfoPanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ui_VideoScreen_screen_init(void)
{

    // ui_VideoScreen

    ui_VideoScreen = lv_obj_create(NULL);

    lv_obj_set_style_bg_color(ui_StartupScreen, lv_color_hex(0x394050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StartupScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_VideoScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(ui_group, ui_VideoScreen);
}

void ui_ResinScreen_screen_init(void)
{
    ui_ResinScreen = lv_obj_create(NULL);
    lv_obj_add_event_cb(ui_ResinScreen, ui_event_ResinScreen, LV_EVENT_ALL, NULL);
    lv_obj_clear_flag(ui_ResinScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_ResinScreen, lv_color_hex(0xEEE6DE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ResinScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_ResinScreen, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DailyNotePanel = lv_obj_create(ui_ResinScreen);
    lv_obj_set_width(ui_DailyNotePanel, 200);
    lv_obj_set_height(ui_DailyNotePanel, 200);
    lv_obj_set_align(ui_DailyNotePanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_DailyNotePanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_DailyNotePanel, lv_color_hex(0xF4F1EB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DailyNotePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_DailyNotePanel, lv_color_hex(0xDED8D2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_DailyNotePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_DailyNotePanel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_DailyNotePanel, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteResinLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteResinLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteResinLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteResinLabel, 45);
    lv_obj_set_y(ui_NoteResinLabel, 7);
    lv_label_set_text(ui_NoteResinLabel, "160/160");
    lv_obj_set_style_text_color(ui_NoteResinLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteResinLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteResinLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteHomeCoinLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteHomeCoinLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteHomeCoinLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteHomeCoinLabel, 45);
    lv_obj_set_y(ui_NoteHomeCoinLabel, 52);
    lv_label_set_text(ui_NoteHomeCoinLabel, "2.4K/2.4K");
    lv_obj_set_style_text_color(ui_NoteHomeCoinLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteHomeCoinLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteHomeCoinLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteExpeditionsLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteExpeditionsLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteExpeditionsLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteExpeditionsLabel, 45);
    lv_obj_set_y(ui_NoteExpeditionsLabel, 97);
    lv_label_set_text(ui_NoteExpeditionsLabel, "5/5");
    lv_obj_set_style_text_color(ui_NoteExpeditionsLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteExpeditionsLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteExpeditionsLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteTransformerLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteTransformerLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteTransformerLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteTransformerLabel, 45);
    lv_obj_set_y(ui_NoteTransformerLabel, 142);
    lv_label_set_text(ui_NoteTransformerLabel, "6 D 24 H");
    lv_obj_set_style_text_color(ui_NoteTransformerLabel, lv_color_hex(0x7D5F45), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteTransformerLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteTransformerLabel, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NoteResinImage = lv_img_create(ui_DailyNotePanel);
    lv_img_set_src(ui_NoteResinImage, &ui_img_Resin);
    lv_obj_set_width(ui_NoteResinImage, LV_SIZE_CONTENT);         /// 1
    lv_obj_set_height(ui_NoteResinImage, LV_SIZE_CONTENT);        /// 1
    lv_obj_add_flag(ui_NoteResinImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteResinImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteHomeCoinImage = lv_img_create(ui_DailyNotePanel);
    lv_img_set_src(ui_NoteHomeCoinImage, &ui_img_Homecoin);
    lv_obj_set_width(ui_NoteHomeCoinImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteHomeCoinImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteHomeCoinImage, 0);
    lv_obj_set_y(ui_NoteHomeCoinImage, 45);
    lv_obj_add_flag(ui_NoteHomeCoinImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteHomeCoinImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteExpeditionsImage = lv_img_create(ui_DailyNotePanel);
    lv_img_set_src(ui_NoteExpeditionsImage, &ui_img_Expeditions);
    lv_obj_set_width(ui_NoteExpeditionsImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteExpeditionsImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteExpeditionsImage, 0);
    lv_obj_set_y(ui_NoteExpeditionsImage, 90);
    lv_obj_add_flag(ui_NoteExpeditionsImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteExpeditionsImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteTransformerImage = lv_img_create(ui_DailyNotePanel);
    lv_img_set_src(ui_NoteTransformerImage, &ui_img_Transformer);
    lv_obj_set_width(ui_NoteTransformerImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteTransformerImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteTransformerImage, 0);
    lv_obj_set_y(ui_NoteTransformerImage, 135);
    lv_obj_add_flag(ui_NoteTransformerImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_NoteTransformerImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_NoteUpdateTimeLabel = lv_label_create(ui_DailyNotePanel);
    lv_obj_set_width(ui_NoteUpdateTimeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NoteUpdateTimeLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NoteUpdateTimeLabel, 0);
    lv_obj_set_y(ui_NoteUpdateTimeLabel, -89);
    lv_obj_set_align(ui_NoteUpdateTimeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_NoteUpdateTimeLabel, "20分钟前更新");
    lv_obj_set_style_text_color(ui_NoteUpdateTimeLabel, lv_color_hex(0xC2B4A4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NoteUpdateTimeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_NoteUpdateTimeLabel, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_group_add_obj(ui_group, ui_ResinScreen);
}

void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_StartupScreen_screen_init();
    // ui_SettingScreen_screen_init();
    // ui_VideoScreen_screen_init();
    // ui_ResinScreen_screen_init();
    lv_disp_load_scr(ui_StartupScreen);

    ui_group = lv_group_create();
}
