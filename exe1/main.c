#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
volatile char btn_flag = -1;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    btn_flag = 1;
  } else if (events == 0x8) { // rise edge
    btn_flag = 0;
  }
}

int main() {
  stdio_init_all();
  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_set_irq_enabled_with_callback(
    BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  
  while (1) {
    if (btn_flag == 1) {
      printf("fall \n");
      btn_flag = -1; // reset flag
    } else if (btn_flag == 0) {
      printf("rise \n");
      btn_flag = -1; // reset flag
    }
  }
}