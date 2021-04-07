#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
DigitalIn ISR1(A0);         // increase the freq
DigitalIn ISR2(A1);         // decrease freq
DigitalIn ISR3(A2);         // confirm the freq
DigitalIn mypin(USER_BUTTON);
AnalogOut aout(PA_4);       // set the analog output
AnalogIn AIN(A3);           // set the analog input
EventQueue queue(32 * EVENTS_EVENT_SIZE);

float temp = 1;     // the frequency shown on the uLCD
float slew = 1; 
float freq = 4.166;     // the confirm frequency (the frequency of the output wave)	
float data[240];    // sampled data
uint16_t sample = 0;


Thread t;

int main(){
    aout = 1;
    while (1) {
		// scan the button
		if (ISR1 == 1) {
            if (temp != 1){
                temp = temp * 2;
            }
			uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.cls();
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%.3f\n", temp);
		}
		if (ISR2 == 1) {
			if (temp != 0.125) {
                temp = temp / 2;
            }
			//conf = 1;
			uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.cls();
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%.3f\n", temp);
		}
		if (ISR3 == 1) {
            slew = temp;
			uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.cls();
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%.3f\n", slew);
            break;
		}
	}
	printf("%f\r\n", slew);
    //sw3.rise(quene.event(DAC));

	while(1){
		//if (!mypin) break;
        if (slew == 1) {
            for (int i = 0; i < 80; i++) {
                sample = (uint16_t)(59578 * i / 80);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);
            }
            for (int i = 80; i < 160; i++) {
                sample = (uint16_t)(59578);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);
            }
            for (int i = 160; i < 240; i++) {
                sample = (uint16_t)(59578 * (240 - i) / 80);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);
            }
        }
        else if (slew == 0.5) {
            for (int i = 0; i < 40; i++) {
                sample = (uint16_t)(59578 *i / 40);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);
            }
            for (int i = 40; i < 200; i++) {
                sample = (uint16_t)(59578);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);
            }
            for (int i = 200; i < 240; i++) {
                sample = (uint16_t)(59578 * (240 - i) / 40);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);
            }
        }
        else if (slew == 0.25) {
            for (int i = 0; i < 20; i++) {
                sample = (uint16_t)(59578 *i / 20);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);
            }
            for (int i = 20; i < 220; i++) {
                sample = (uint16_t)(59578);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);
            }
            for (int i = 220; i < 240; i++) {
                sample = (uint16_t)(59578 * (240 - i) / 20);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);
            }
        }
        else if (slew == 0.125) {
            for (int i = 0; i < 10; i++) {
                sample = (uint16_t)(59578* i / 10);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);

            }
            for (int i = 10; i < 230; i++) {
                sample = (uint16_t)(59578);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);

            }
            for (int i = 230; i < 240; i++) {
                sample = (uint16_t)(59578 * (240 - i) / 10);
                aout.write_u16(sample);
                //data[i] = AIN;
                wait_us(20000/freq);
                
            }
        }    
    }
    

    for (int i = 0; i < 240; i++) {
            //printf("%f\r\n", data[i]);
    }
}