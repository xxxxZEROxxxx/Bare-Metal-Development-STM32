#include "GPIO/gpio.h"
#include "main.h"
#include "SYSTICK/systick.h"
//#include "stm32f4xx.h"

int main(void) {

    gpio_init(GPIOC, 13, OUTPUT);
    gpio_init(GPIOA, 0, INPUT);
    GPIOA->PUPDR |= (1 << 0);  // set PA0 into internal pull up
    while (1) {
        for (int i = 0; i < 3; ++i) {
            gpio_set(GPIOC,13,0);
            delay(60);
            gpio_set(GPIOC,13,1);
            delay(60);
        }
        delay(1000);
    }
}

