#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED_PIN_R = 4;
const int LED_PIN_G = 6;
const int BTN_PIN_G = 26;
const int BTN_PIN_R = 28;
volatile char red_flag = 0;
volatile char green_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
      red_flag = 1;
    }

  else if (events == 0x8) { // rise edge
      green_flag = 1;
    }
  }

int main() {
  stdio_init_all();
  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);
  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);
  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                          &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);
  while (true) {
    if (red_flag == 1) {
      int led_state_r = gpio_get(LED_PIN_R);
      gpio_put(LED_PIN_R, !led_state_r);
      red_flag = 0;
    }
    if (green_flag == 1) {
      int led_state_g = gpio_get(LED_PIN_G);
      gpio_put(LED_PIN_G, !led_state_g);
      green_flag = 0;
    }
  }
}
