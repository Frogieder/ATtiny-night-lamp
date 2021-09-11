/*
* ##################
* #     TO DO      #
* ##################
*
* X * light up the LED
* X * detect touch
*   * touch logic
*   * automatic turn off
*   * add pwm support
* X * implement efficient sleeping
*   * use photoresistor to turn on
*
*/

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
// #include <stdint.h>
// #include <stdlib.h>

#define TRIG 2
#define ECHO 0
#define LED 1

#define NOOP asm volatile("nop" ::)
// #undef NOOP
// #define NOOP ; // if I ever get mad, noop gets defined like this :P

uint32_t calibration;

// thank you kind internet stranger called Olek
uint32_t measure_cap(uint8_t pin)
{
    uint32_t i = 0;
    while (PORTB & (1 << pin))
        ;               // wait for discharge sensor pin
    DDRB |= (1 << pin); // set sensor pin as output, dicharge it to end
    NOOP;
    NOOP;
    NOOP;
    DDRB &= ~(1 << TRIG); // set "charger" as input, i third state (as disconnected)
    DDRB &= ~(1 << pin);  // set sensor pin as input,
    DDRB |= (1 << TRIG);  // now "plug in the charger"
    PORTB |= (1 << TRIG); // start charging sensor
    do
    {
        i++;                        // increment counter
    } while (!(PINB & (1 << pin))); // wait until the pin is in high state
    PORTB &= ~(1 << TRIG);          // stop charging
    return i;
}   

static inline void adc_init()
{
    /*
    // ADMUX |= (1 << ADLAR) | MUX3;
    //– REFS0 ADLAR – – – MUX1 MUX
    ADMUX = 0b00100011; // setup the ADC multilpexer - adjust results to left to easily read 8-bit output; set ADC input to ADC3
    // ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
    ADCSRA = 0b00000011; // ADC status register A - set clock divider to 1/8
    DIDR0 |= 1 << ADC3D; // disable digital input on ADC3
    */
}

static inline void touch_init(void)
{
    // calibrate the capacity sensor
    for (int i = 0; i < 40; i++)
    {
        uint32_t value = measure_cap(ECHO);
        // set calibration value to the highest measured value
        calibration = value > calibration ? value : calibration;
    }
}

static inline void pwm_init()
{
    // TO DO
}

static inline void wdt_init_first()
{
    // clear MCU status reg as we don't care about the reset source
    MCUSR = 0;
    // sequence to clear watchdog settings
    WDTCR = (1 << WDCE) | (1 << WDE);
    WDTCR = 0;
    
}

static inline void wdt_enable()
{
    // set watchdog to interrupt mode each 30 ms
    WDTCR = (1 << WDCE) | (1 << WDE);
    WDTCR = (1 << WDIE) | WDTO_30MS;
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
}

static inline void init(void)
{
    wdt_init_first();
    touch_init();
    adc_init();
    pwm_init();

    DDRB = 1 << LED; // set LED pin as output
}

int main(void)
{
    cli();
    init();
    // bool is_dark = 0;
    wdt_enable();
    sei();
    while (1)
    {
        if (MCUCR & _BV(SE))
        {
            cli();
            sleep_bod_disable();
            sei();
            sleep_cpu();
        }

            /*
        ADCSRA |= 1 << ADEN; // enable ADC
        ADCSRA |= 1 << ADSC; // start conversion

        while (ADCSRA & (1 << ADSC)) 
            ;       //wait till the conversion completes (hardware clears start conversion bit)
        int adc_reading = ADCH; // retrieve upper 8-bits from ADC results
        ADCSRA &= ~(1 << ADEN); // enable ADC
        */
            // _delay_ms(50);
        }
}


ISR (WDT_vect)
{
    sleep_disable();
    cli();
    // re-enable watchdog interrupts
    WDTCR |= (1 << WDIE);

/*
      #############
     # MAIN LOOP #
    #############
*/
    if(measure_cap(ECHO) > (calibration + 8))
    {
        PORTB |= (1 << LED);
    }
    else
    {
        PORTB &= ~(1 << LED);
    }
    sei();
    sleep_enable();
}
