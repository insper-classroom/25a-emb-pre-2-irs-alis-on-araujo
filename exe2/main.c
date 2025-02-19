#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED_PIN = 4;
const int BTN_PIN_R = 28;
volatile char btn_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x8) { // fall edge
    btn_flag = 1;
  }
}

int main() {
  stdio_init_all();
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_set_irq_enabled_with_callback(
    BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if (btn_flag == 1) {
      int led_state = gpio_get(LED_PIN);
      gpio_put(LED_PIN, !led_state);
      btn_flag = 0;
    }
  }
}
