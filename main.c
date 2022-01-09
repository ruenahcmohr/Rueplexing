/*

   This code was written today to do the things.
     By me.


Rueplexing two 7 segment displays :)
    
                       +---\/---+
        (/RESET)  PC6  |1     28|  PC5  (ADC5 / SCL)
           (RXD)  PD0  |2     27|  PC4  (ADC4 / SDA)
           (TXD)  PD1  |3     26|  PC3  (ADC3)
          (INT0)  PD2  |4     25|  PC2  (ADC2)
          (INT1)  PD3  |5     24|  PC1  (ADC1)
      (XCK / T0)  PD4  |6     23|  PC0  (ADC0)
                  VCC  |7     22|  GND
                  GND  |8     21|  AREF
 (XTAL1 / TOSC1)  PB6  |9     20|  AVCC
 (XTAL2 / TOSC2)  PB7  |10    19|  PB5  (SCK)
            (T1)  PD5  |11    18|  PB4  (MISO)
          (AIN0)  PD6  |12    17|  PB3  (MOSI / OC2)
          (AIN1)  PD7  |13    16|  PB2  (SS / OC1B)
          (ICP1)  PB0  |14    15|  PB1  (OC1A)
                       +--------+

PORTB to leds:
 0 A
 1 B
 2 C
 3 D --[330 ohms]--> 7 segments
 4 E 
 5 F
 6 G
 7 Common
 
 Use a common cathode and a common anode display, connect the commons together.
 
 
 
PORTD is input byte



 AAAAAAA
F       B
F       B
F       B
F       B
 GGGGGGG
E       C
E       C
E       C
E       C
 DDDDDDD
 
 The LSN will come out on the commoon cathode display, the MSN on the common anode.

*/

#include <avr/io.h>
#include "avrcommon.h"
#include "nopDelay.h"
#include "7seg.h"



/****************************| MANE CODY... |***********************************/
 
int main (void)  {

  DDRB = (OUTPUT << PB0)|(OUTPUT << PB1)|(OUTPUT << PB2)|(OUTPUT << PB3)|(OUTPUT << PB4)|(OUTPUT << PB5)|(OUTPUT << PB6)|(OUTPUT << PB7);
  
  DDRC = (INPUT << PC0)|(INPUT << PC1)|(INPUT << PC2)|(INPUT << PC3)|(INPUT << PC4)|(INPUT << PC5)|(INPUT << PC6);
  
  DDRD = (INPUT << PD0)|(INPUT << PD1)|(INPUT << PD2)|(INPUT << PD3)|(INPUT << PD4)|(INPUT << PD5)|(INPUT << PD6)|(INPUT << PD7);        
          
  PORTD = 0xFF; // turn up pullups	  
	                         

  while(1) {

    // do lsb
    ClearBit(7, PORTB); 
    PORTB = CG[PIND & 0x0F];
    
    Delay(500);
    
    // do msb
    
    SetBit(7, PORTB); 
    PORTB = ~CG[(PIND & 0xF0) >> 4] | 0x80;

    Delay(500);

  }
  
  return 0;
}
    
//------------------------| FUNCTIONS |------------------------

