#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <pico/sync.h>
#include <task.h>

#define OUT_PIN 0

#define DELAY_MS 10