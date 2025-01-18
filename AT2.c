#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/uart.h"

#define buz 3
#define gled 11
#define bled 12
#define rled 13

uint8_t i;
uint8_t leds[] = {gled, bled, rled};

void ledinitset(){ //iniciando e direcionando todos os leds.
    for (i = 0 ; i < 3; i++){
        gpio_init(11 + i);
        gpio_set_dir (11 + i, GPIO_OUT);
        gpio_put(11 + i, 0);
    }
}

void buzzinitset(){ //inicializando e direcionando o buzzer.
    gpio_init(buz);
    gpio_set_dir(buz, GPIO_OUT);
    gpio_put(buz, 0);
}

void lightbuz(){
for(i = 0 ; i < 3 ; i++){
    gpio_put(leds +i, 1);
    sleep_ms(400);
    gpio_put(leds + i, 0);
    }
        sleep_ms(500);
for (i = 0 ; i < 3 ; i++){
    gpio_put(leds + i, 1);
    }
        sleep_ms(1000);
for (i = 0 ; i < 3 ; i++){
    gpio_put(leds + i, 0);
}
}

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    return 0;
}

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5



int main()
{
    stdio_init_all();

    // Timer example code - This example fires off the callback after 2000ms
    add_alarm_in_ms(2000, alarm_callback, NULL, false);
    // For more examples of timer use see https://github.com/raspberrypi/pico-examples/tree/master/timer

    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART
    
    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, " Hello, UART!\n");
    
    // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

    while (true) {
        sleep_ms(20);
    }
}
