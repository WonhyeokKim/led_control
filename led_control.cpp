#include "Arduino.h"
#include "led_control.h"

LedControl::LedControl(int led_pin) {
	pinMode(led_pin, OUTPUT);
	pin = led_pin;
	
	prefix = "[LedControl] ";
}

void LedControl::button_control(int button_pin) {
	pinMode(button_pin, INPUT_PULLUP);
	if (digitalRead(button_pin) != 1) {
		digitalWrite(pin, 1);
	} else {
		digitalWrite(pin, 0);
	}
}

void LedControl::button_control(int button_pin, int delay_sec) {
	pinMode(button_pin, INPUT_PULLUP);
	if (digitalRead(button_pin) != 1) {
		digitalWrite(pin, 1);
		delay(delay_sec * 1000);
		
		digitalWrite(pin, 0);
		delay(delay_sec * 1000);
	} else {
		digitalWrite(pin, 0);
	}
}

void LedControl::led_on() {
	digitalWrite(pin, 1);
}

void LedControl::led_off() {
	digitalWrite(pin, 0);
}

void LedControl::pot_control(int pot_pin, int mode, bool debug) {
	switch (mode) {
		case 0:
			if (analogRead(pot_pin) < 500) {
				LedControl::led_on();
			} else {
				LedControl::led_off();
			}
	
			if (debug) {
				Serial.println(prefix + String(analogRead(pot_pin)));
			}
			
			break;
			
		case 1:
			LedControl::led_on();
			delay(analogRead(pot_pin));
			LedControl::led_off();
			delay(analogRead(pot_pin));
			
			break;
	}
}

LedSpectrom::LedSpectrom(int minimum_led_pin, int maximum_led_pin) {
    minimum_pin = minimum_led_pin;
    maximum_pin = maximum_led_pin;
    
    prefix = "[LedSpectrom] ";
    
    for (int i = minimum_pin; maximum_pin >= i; i++) {
        pinMode(i, OUTPUT);
    }
}

void LedSpectrom::led_spectrom(int button_pin, int delay_ms, bool upper) {
    pinMode(button_pin, INPUT_PULLUP);
    if (digitalRead(button_pin) != 1) {
        if (upper) {
            for (int i = minimum_pin; maximum_pin >= i; i++) {
                digitalWrite(i, 1);
                delay(delay_ms);
                
                Serial.println(prefix + String(i) + ": Printing Spectrom! MODE: upper");
            }
            
            for (int i = minimum_pin; maximum_pin >= i; i++) {
            	pinMode(i, OUTPUT);
            	digitalWrite(i, 0);
            
            	Serial.println(prefix + "Off the spectrom");
        	}
        } else {
            for (int i = maximum_pin; i >= minimum_pin; i--) {
                pinMode(i, OUTPUT);
                digitalWrite(i, 1);
                delay(delay_ms);
                
                Serial.println(prefix + String(i) + ": Printing Spectrom! MODE: not upper");
            }
            
            for (int i = minimum_pin; i >= maximum_pin; i--) {
            	pinMode(i, OUTPUT);
            	digitalWrite(i, 0);
            
            	Serial.println(prefix + "Off the spectrom");
        	}
        }
        
        delay(delay_ms);
    }
}
