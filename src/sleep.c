#include "pin_config.h"

int main(void)
{
    int toggle = 0;
    stdio_init_all();
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    while (true) {
        toggle = !toggle;
        for (volatile int i = 0; i < 1000; i ++){}
        gpio_put(OUT_PIN, toggle);
        sleep_ms(DELAY_MS);
        
    }
}
