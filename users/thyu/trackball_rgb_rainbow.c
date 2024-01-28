#include QMK_KEYBOARD_H
#include "trackball_rgb_rainbow.h"

#include "color.h"

#define MIN_WPM 10
#define MAX_WPM 100

uint8_t clamp(uint32_t x) {
    if (x > 255) {
        return 255;
    } 
    return (uint8_t)x;
}

void housekeeping_task_user(void) {
  bool run_animation = is_keyboard_master();
  // With two trackballs, always run the animation. Note that if TRACKBALL_RGB_RAINBOW isn't 'yes' we're not including
  // this file in the build.
#if defined(SPLIT_POINTING_ENABLE)
  run_animation = true;
#endif
  if (run_animation) {
    static uint32_t timer = 0;
    static HSV color = { .h = 45, .s = 255, .v = 255 };

    if (timer_elapsed32(timer) < 100)
        return;
    
    timer = timer_read32();

    uint8_t wpm = get_current_wpm();
    uint8_t capped_wpm = wpm > MAX_WPM ? MAX_WPM : wpm;

    // type faster, color more bright, top at 255/5 + 10 = 61 wpm
    if (capped_wpm < MIN_WPM) {
        color.v = 0;
    } else {
        color.v = clamp((uint32_t)(capped_wpm - MIN_WPM) * 5);
    }

    // type faster, change color from green to blue to red
    // start from h = 45 (yellow) to h = 145 (blue), top at 100 wpm
    if (capped_wpm < MIN_WPM) {
        color.h = 0; 
    } else {
        color.h = clamp(45 + ((uint32_t)capped_wpm * (145 - 45))/MAX_WPM);
    }
    
    RGB rgb = hsv_to_rgb(color);
    pimoroni_trackball_set_rgbw(rgb.r, rgb.g, rgb.b, 0);
  }
}
