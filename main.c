#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "buttondebounce.h"


#define GPIO_BUTTON_A    22

button_debounce_t button1;


const uint8_t LED_PIN = 25;

uint32_t last_led = 0;
uint8_t last_state = 0;


uint32_t current_tick()  {
    return time_us_32() / 1000;
}


void init_gpio() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(GPIO_BUTTON_A);
    gpio_set_dir(GPIO_BUTTON_A, GPIO_IN);
    gpio_pull_up(GPIO_BUTTON_A);
}

int main() {
    stdio_init_all();

    init_gpio();

    puts("Started ...\n");

    button1.gpio_a = GPIO_BUTTON_A;

    while (1) {

        button_task(&button1);

        if (last_state != button1.state) {
            last_state = button1.state;
            printf("state: %d \r\n", button1.state);
        }

        if (current_tick() - last_led > 200) {
            last_led = current_tick();
            uint8_t led_status = gpio_get(LED_PIN);
            if (led_status) {
                gpio_put(LED_PIN, 0);
            }
            else {
                gpio_put(LED_PIN, 1);
            }
        }
    }
}