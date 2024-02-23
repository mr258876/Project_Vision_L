#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "ui/ui_multiLanguage.h"
#include "ui/ui_supply_functions.h"

void cleanObj(lv_obj_t *obj)
{
  for (int i = 0; i < lv_obj_get_child_cnt(obj); i++)
  {
    cleanObj(lv_obj_get_child(obj, i));
  }
  lv_obj_remove_style_all(obj);
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

void cb_timer_mboxDelTimer(lv_timer_t *timer)
{
  lv_obj_t *mbox = (lv_obj_t *)(timer->user_data);
  lv_msgbox_close(mbox);
}

void mboxCreate(lv_obj_t *parent, const char *title, const char *content, const char **btn_txts, bool add_close_btn, uint32_t timeout)
{
  lv_obj_t *mbox = lv_msgbox_create(parent, title, content, btn_txts, add_close_btn);
  lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_center(mbox);

  if (timeout > 0)
  {
    lv_timer_t *mbox_timer = lv_timer_create(cb_timer_mboxDelTimer, timeout, mbox);
    lv_timer_set_repeat_count(mbox_timer, 1);

    ui_obj_timer_t *obj_timer_data = (ui_obj_timer_t *)lv_mem_alloc(sizeof(ui_obj_timer_t));
    obj_timer_data->obj = mbox;
    obj_timer_data->timer = mbox_timer;
    lv_obj_set_user_data(mbox, obj_timer_data);
  }

  lv_obj_add_event_cb(mbox, ui_event_mbox, LV_EVENT_ALL, NULL);
}

void cb_timer_ScrDelTimer(lv_timer_t *timer)
{
  lv_obj_t *scr = ((ui_obj_timer_t *)timer->user_data)->obj;
  delScr(scr);
  if (timer->user_data) lv_mem_free(timer->user_data);
  lv_timer_del(timer);
}