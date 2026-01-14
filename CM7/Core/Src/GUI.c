#include "../Inc/GUI.h"
#include "lv_port_disp.h"
#include "main.h"
#include "src/core/lv_obj_pos.h"
#include "src/core/lv_obj_style.h"
#include "src/core/lv_obj_style_gen.h"
#include "src/display/lv_display.h"
#include "src/font/lv_font.h"
#include "src/font/lv_symbol_def.h"
#include "src/misc/lv_area.h"
#include "src/widgets/bar/lv_bar.h"
#include "src/widgets/button/lv_button.h"
#include "src/widgets/label/lv_label.h"
#include <stdint.h>

void initScreen(void) {
  RSX_GPIO_Port->BSRR = RSX_Pin << 16;
  HAL_Delay(20);
  RSX_GPIO_Port->BSRR = RSX_Pin;
  HAL_Delay(150);
  lv_init();
  lv_tick_set_cb(HAL_GetTick);
  lv_display_t *screen = lv_ili9341_create(240, 320, LV_LCD_FLAG_NONE,
                                           my_lcd_send_cmd, my_lcd_send_color);
  uint8_t *buf1 = NULL;
  uint8_t *buf2 = NULL;
  uint32_t buf_size =
      HOR_RES * BUFFER_LINES *
      lv_color_format_get_size(lv_display_get_color_format(screen));

  buf1 = lv_malloc(buf_size);
  if (buf1 == NULL) {
    LV_LOG_ERROR("display draw buffer malloc failed");
    Error_Handler();
  }

  lv_display_set_buffers(screen, buf1, buf2, buf_size,
                         LV_DISPLAY_RENDER_MODE_PARTIAL);
}

void drawMainScreen(void) {
  /*Change the active screen's background color*/
  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57),
                            LV_PART_MAIN);

  // artist name
  char artistName[32] = "Kanye West";
  int32_t artistNameY = 60;
  lv_obj_t *artistNameText = lv_label_create(lv_screen_active());
  lv_obj_set_style_text_font(artistNameText, &lv_font_montserrat_16, 0);
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff),
                              LV_PART_MAIN);
  lv_label_set_text(artistNameText, artistName);
  lv_obj_align(artistNameText, LV_ALIGN_CENTER, 0, artistNameY);

  // song name
  char songName[32] = "I Wonder";
  int32_t songNameY = artistNameY - 20;
  lv_obj_t *songNameText = lv_label_create(lv_screen_active());
  lv_obj_set_style_text_font(songNameText, &lv_font_montserrat_18, 0);
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff),
                              LV_PART_MAIN);
  lv_label_set_text(songNameText, songName);
  lv_obj_align(songNameText, LV_ALIGN_CENTER, 0, songNameY);

  // play button
  int32_t btnWidth = 40;
  int32_t btnHeight = 40;
  int32_t btnY = artistNameY + 70;
  lv_obj_t *playBtn = lv_button_create(lv_screen_active());
  lv_obj_align(playBtn, LV_ALIGN_CENTER, 0, btnY);
  lv_obj_set_size(playBtn, btnWidth, btnHeight);
  lv_obj_t *playLabel = lv_label_create(playBtn);
  lv_label_set_text(playLabel, LV_SYMBOL_PAUSE);
  lv_obj_set_style_bg_opa(playBtn, LV_OPA_TRANSP, 0);
  lv_obj_set_style_shadow_width(playBtn, 0, 0);
  lv_obj_center(playLabel);

  // skip button
  lv_obj_t *skipBtn = lv_button_create(lv_screen_active());
  lv_obj_align(skipBtn, LV_ALIGN_CENTER, 48, btnY);
  lv_obj_set_size(skipBtn, btnWidth, btnHeight);
  lv_obj_t *skipLabel = lv_label_create(skipBtn);
  lv_label_set_text(skipLabel, LV_SYMBOL_NEXT);
  lv_obj_set_style_bg_opa(skipBtn, LV_OPA_TRANSP, 0);
  lv_obj_set_style_shadow_width(skipBtn, 0, 0);
  lv_obj_center(skipLabel);

  // back button
  lv_obj_t *backBtn = lv_button_create(lv_screen_active());
  lv_obj_align(backBtn, LV_ALIGN_CENTER, -48, btnY);
  lv_obj_set_size(backBtn, btnWidth, btnHeight);
  lv_obj_t *backLabel = lv_label_create(backBtn);
  lv_label_set_text(backLabel, LV_SYMBOL_PREV);
  lv_obj_set_style_bg_opa(backBtn, LV_OPA_TRANSP, 0);
  lv_obj_set_style_shadow_width(backBtn, 0, 0);
  lv_obj_center(backLabel);

  // shuffle button
  lv_obj_t *shuffleBtn = lv_button_create(lv_screen_active());
  lv_obj_set_size(shuffleBtn, btnWidth, btnHeight);
  lv_obj_set_style_bg_opa(shuffleBtn, LV_OPA_TRANSP, 0);
  lv_obj_align(shuffleBtn, LV_ALIGN_CENTER, 96, btnY);
  lv_obj_set_style_shadow_width(shuffleBtn, 0, 0);
  lv_obj_t *shuffleLabel = lv_label_create(shuffleBtn);
  lv_label_set_text(shuffleLabel, LV_SYMBOL_SHUFFLE);
  lv_obj_center(shuffleLabel);

  // repeat button
  lv_obj_t *repeatBtn = lv_button_create(lv_screen_active());
  lv_obj_set_size(repeatBtn, btnWidth, btnHeight);
  lv_obj_set_style_bg_opa(repeatBtn, LV_OPA_TRANSP, 0);
  lv_obj_align(repeatBtn, LV_ALIGN_CENTER, -96, btnY);
  lv_obj_set_style_shadow_width(repeatBtn, 0, 0);
  lv_obj_t *repeatLabel = lv_label_create(repeatBtn);
  lv_label_set_text(repeatLabel, LV_SYMBOL_LOOP);
  lv_obj_center(repeatLabel);

  // music bar
  int32_t musicBarY = artistNameY + 25;
  lv_obj_t *musicBar = lv_bar_create(lv_screen_active());
  lv_obj_set_size(musicBar, 220, 10);
  lv_obj_align(musicBar, LV_ALIGN_CENTER, 0, musicBarY);
  lv_bar_set_value(musicBar, 100, LV_ANIM_OFF);

  // album art
  lv_obj_t *albumArt = lv_obj_create(lv_screen_active());
  lv_obj_set_size(albumArt, 150, 150);
  lv_obj_align(albumArt, LV_ALIGN_CENTER, 0, btnY - 190);
  lv_obj_set_style_bg_opa(albumArt, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(albumArt, 3, 0);

  // time left on song
  lv_obj_t *timeLeftLabel = lv_label_create(lv_screen_active());
  lv_label_set_text(timeLeftLabel, "1:33");
  lv_obj_set_style_text_font(timeLeftLabel, &lv_font_montserrat_12, 0);
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff),
                              LV_PART_MAIN);
  lv_obj_align(timeLeftLabel, LV_ALIGN_CENTER, -100, btnY - 25);

  // time played on song
  lv_obj_t *timePlayedLabel = lv_label_create(lv_screen_active());
  lv_label_set_text(timePlayedLabel, "2:36");
  lv_obj_set_style_text_font(timePlayedLabel, &lv_font_montserrat_12, 0);
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff),
                              LV_PART_MAIN);
  lv_obj_align(timePlayedLabel, LV_ALIGN_CENTER, 100, btnY - 25);

  // settings button
  lv_obj_t *settingsBtn = lv_button_create(lv_screen_active());
  lv_obj_set_size(settingsBtn, btnWidth - 5, btnHeight - 5);
  lv_obj_set_style_bg_opa(settingsBtn, LV_OPA_TRANSP, 0);
  lv_obj_align(settingsBtn, LV_ALIGN_TOP_LEFT, 0, 0);
  lv_obj_set_style_shadow_width(settingsBtn, 0, 0);
  lv_obj_t *settingsLabel = lv_label_create(settingsBtn);
  lv_label_set_text(settingsLabel, LV_SYMBOL_SETTINGS);
  lv_obj_center(settingsLabel);
}
