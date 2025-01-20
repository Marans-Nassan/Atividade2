#include <stdio.h>
#include "pico/stdlib.h"

#define buz 3
#define gled 11
#define bled 12
#define rled 13

uint8_t i;
uint8_t leds[] = {gled, bled, rled}; 

void ledinitset(){ //iniciando e direcionando todos os leds.
    for (i = 0 ; i < 3; i++){
        gpio_init(leds[i]);
        gpio_set_dir (leds[i], GPIO_OUT);
        gpio_put(leds[i], 0);
    }
}

void buzzinitset(){ //inicializando e direcionando o buzzer.
    gpio_init(buz);
    gpio_set_dir(buz, GPIO_OUT);
    gpio_put(buz, 0);
}

void lightbuz(){ //funcionamento dos leds... ligando e desligand
for(i = 0 ; i < 3 ; i++){
    gpio_put(leds[i], 1);
    sleep_ms(400);
    gpio_put(leds[i], 0);
    }
        sleep_ms(500);
for (i = 0 ; i < 3 ; i++){
    gpio_put(leds[i], 1);
    }
        sleep_ms(1000);
for (i = 0 ; i < 3 ; i++){
    gpio_put(leds[i], 0);
}
}

void note(uint8_t buzzer, uint16_t notefreq, uint16_t duration_ms){ //EMISSÃO SONORA DO BUZZER
    int halfc = 1000000 / (2 * notefreq); // Calcula o tempo de espera para cada meio ciclo de onda
    int cycles = (notefreq * duration_ms) / 1000; // Número total de ciclos necessários para a duração

    for (int i = 0; i < cycles; i++) {
        gpio_put(3, 1);  // Muda o estado para HIGH iniciando 1º parte do ciclo
        sleep_us(halfc); // Aguarda metade do tempo de um ciclo (meio período)
        gpio_put(3, 0);  // Muda o estado para LOW  iniciando 2º parte do ciclo
        sleep_us(halfc); // Aguarda a outra metade do tempo (meio período)
    }
}

int main(){

ledinitset();
buzzinitset();    
      
    while (true) {
        sleep_ms(20);
        lightbuz();
        note(3, 262, 2000);
        sleep_ms(100);
    }
}