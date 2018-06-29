
#ifndef displayboard_H
#define	displayboard_H



// Includes
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "UART.h"

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)
//****************************pg 111*****************************
//#pragma config OSC = INTIO67

// CONFIG1H
#pragma config FOSC =  INTOSC_HS     // Oscillator Selection bits (XT oscillator (XT))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 0         // Brown-out Reset Voltage bits (Maximum setting)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 1        // Watchdog Timer Postscale Select bits (1:1)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = ON     // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for low-power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = ON         // Code Protection bit (Block 0 (000800-001FFFh) is code-protected)
#pragma config CP1 = ON         // Code Protection bit (Block 1 (002000-003FFFh) is code-protected)
#pragma config CP2 = ON         // Code Protection bit (Block 2 (004000-005FFFh) is code-protected)
//#pragma config CP3 = ON         // Code Protection bit (Block 3 (006000-007FFFh) is code-protected)

// CONFIG5H
#pragma config CPB = ON         // Boot Block Code Protection bit (Boot block (000000-0007FFh) is code-protected)
#pragma config CPD = ON         // Data EEPROM Code Protection bit (Data EEPROM is code-protected)

// CONFIG6L
#pragma config WRT0 = ON        // Write Protection bit (Block 0 (000800-001FFFh) is write-protected)
#pragma config WRT1 = ON        // Write Protection bit (Block 1 (002000-003FFFh) is write-protected)
#pragma config WRT2 = ON        // Write Protection bit (Block 2 (004000-005FFFh) is write-protected)
//#pragma config WRT3 = ON        // Write Protection bit (Block 3 (006000-007FFFh) is write-protected)

// CONFIG6H
#pragma config WRTC = ON        // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are write-protected)
#pragma config WRTB = ON        // Boot Block Write Protection bit (Boot block (000000-0007FFh) is write-protected)
#pragma config WRTD = ON        // Data EEPROM Write Protection bit (Data EEPROM is write-protected)

// CONFIG7L
#pragma config EBTR0 = ON       // Table Read Protection bit (Block 0 (000800-001FFFh) is protected from table reads executed in other blocks)
#pragma config EBTR1 = ON       // Table Read Protection bit (Block 1 (002000-003FFFh) is protected from table reads executed in other blocks)
#pragma config EBTR2 = ON       // Table Read Protection bit (Block 2 (004000-005FFFh) is protected from table reads executed in other blocks)
//#pragma config EBTR3 = ON       // Table Read Protection bit (Block 3 (006000-007FFFh) is protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = ON       // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is protected from table reads executed in other blocks)
// Defines


//I/O Mapping

#define A_7SEGI  PORTAbits.RA0
#define A_7SEGI_TRIS TRISAbits.TRISA0
#define B_7SEGI  PORTAbits.RA1
#define B_7SEGI_TRIS TRISAbits.TRISA1
#define C_7SEGI  PORTAbits.RA2
#define C_7SEGI_TRIS TRISAbits.TRISA2
#define D_7SEGI  PORTAbits.RA3
#define D_7SEGI_TRIS TRISAbits.TRISA3
#define E_7SEGI  PORTAbits.RA4
#define E_7SEGI_TRIS TRISAbits.TRISA4
#define F_7SEGI  PORTAbits.RA5
#define F_7SEGI_TRIS TRISAbits.TRISA5
#define G_7SEGI  PORTEbits.RE0
#define G_7SEGI_TRIS TRISEbits.TRISE0



//Control Lines
#define Digit0_TRIS TRISBbits.TRISB0
#define Digit1_TRIS TRISBbits.TRISB1
#define Digit2_TRIS TRISBbits.TRISB2
#define Digit3_TRIS TRISBbits.TRISB3
#define Digit4_TRIS TRISBbits.TRISB4
#define Digit5_TRIS TRISBbits.TRISB5

#define Digit0 PORTBbits.RB0
#define Digit1 PORTBbits.RB1
#define Digit2 PORTBbits.RB2
#define Digit3 PORTBbits.RB3
#define Digit4 PORTBbits.RB4
#define Digit5 PORTBbits.RB5
#define DigitBus PORTB


#define _XTAL_FREQ 8000000

 uint8_t sevenSegValues[10]= {0b11111100, 0b01100000,0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111111, 0b11100000,0b11111111, 0b11100110}; // Pre-defined values of each digit for digits 0-9
 //Segment order goes as... "0bABCDEFGP" (P for decimal point, which is not used here but totally can be if you mod this code!)
 uint8_t barSegment = 0b00000010;// displays a '-' for ez refrence
 uint8_t emptySegment = 0b00000000; // Blank Segment, ez refrence
 uint8_t cathodes[8] = {0b10000000,0b01000000,0b00100000,0b00010000,0b00001000,0b00000100,0b00000010,0b00000001}; //Addresses each individual digit, 0 is A anode, 1 is B ... 6 is G
 void initialize(void);
 void outputSevenSeg();
 void Read_New_Value(char *Output);
 void multiDigitOut(char* charBuffer);
 void driveSegments();

#endif	/* snrproj_H */
