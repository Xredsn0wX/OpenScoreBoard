//Device: PIC18F4455

// Includes
#include <p18cxxx.h>
#include <xc.h>
#include<stdio.h>
#include "displayboard.h"
#include <string.h>
#include <stdlib.h>

uint8_t currentState = 0; //Puts MC into listening state
//State machine variables for control of MC
#define NEW_VAL_STATE 'q'
#define CHANGE_BRIGHTNESS 'l'

// Function Prototypes
char testVal=0b00100101;
char dataLine = 0b00000010;
int digitCount =0;
int digitCycles = 6;

//------------------------------------------------------------------------------
// Function: main()
//------------------------------------------------------------------------------
void main(void) {

    initialize();
    char DisplayValue[6] = {'0', '0', '0', '0', '0', '0'}; //Defaults scoreboard to read "000000" until the value is changed by the user
    dataLine = 0b11111111;
    while(1) {

        multiDigitOut(DisplayValue);
       currentState = UART_Read_NoBlocking();
        if (currentState == NEW_VAL_STATE){
            char testValue = UART_Read_Blocking();
			Read_New_Value(DisplayValue);
        }

       if (currentState == CHANGE_BRIGHTNESS){
           for (int i=0; i < 2; i++){
             char burnCycles = UART_Read_Blocking();
           }
           int testMax =  UART_Read_Blocking() - '0' +6;
           if (testMax > 5 && testMax < 30)
               digitCycles = testMax;



       }

    currentState = 0; //clears state back to normal

    }

} // end main()



void multiDigitOut(char* charBuffer){ //Handles and drives anodes and cathodes to dispaly digits

    DigitBus = 0; // Clears all anodes
   // __delay_us(15);
    dataLine = emptySegment; // Clears all cathodes to ensure there is no capacitence left in the LED strip
    driveSegments( );
   if (charBuffer[digitCount] != 'b') //Check to see if the current digit is intended to be blank, and will not turn respective digit on, program on computer will have to handle such a case
	dataLine = sevenSegValues[charBuffer[digitCount]-48]; //Compute which segments to light based on the input, sets cathodes
    if (charBuffer[digitCount] == '-') //Check to see if a displaying a dash was intended, if so, light cathode 'G'
        dataLine = 0b00000010;

	//Turn on respective digits according to which digit we are processing now, used to set the anodes

	//digitCount is used to see which digit is currently being processed, turn on digit we are process accordingly
    if (digitCount == 0)
		  DigitBus = 0b00000001;
    else if (digitCount == 1)
		  DigitBus = 0b00000010;
    else if (digitCount == 2)
		  DigitBus = 0b00000100;
    else if (digitCount == 3)
		DigitBus = 0b00001000;
      else if (digitCount == 4)
		    DigitBus = 0b00010000;
     else if (digitCount == 5)
		   DigitBus = 0b00100000;
    //Assumed here that when digitCount > 5, brightness is being reduced

	driveSegments( ); //shoot the current value out
	__delay_us(500); // Delay for 500us
    digitCount++; // prepare to process the next digit
    if (digitCount >= digitCycles  ) //Used to cycle through digits all 6 digits, but if increased higher it can reduce brightness since we are multiplexing. Use the 'l' command on bluetooth to make use of this
        digitCount = 0;

/*Note: programatically haveing digitCycles being higher than the digits available seems a bit foolish, however using this method allows the digit currently being lit
 to be (1 / digitCycles) The amount of time as opposed to 100% of the time, which allows you to reduce brightness since increasing digitCycles is shortening the time
 for the segments to be lit, remember we are multiplexing here...*/
}

//------------------------------------------------------------------------------
// Function: initialize()
// Initialization code for the application
//------------------------------------------------------------------------------
void initialize(void) {
    UART_Init(9600);
    OSCCON = 0xF2; // internal oscillator, 8MHz
    // Configure tristates

//Output Bits
       TRISEbits.TRISE0 = 0;
       TRISAbits.TRISA5 = 0;
       TRISAbits.TRISA4 = 0;
       TRISAbits.TRISA3 = 0;
       TRISAbits.TRISA2 = 0;
       TRISAbits.TRISA1 = 0;
       TRISAbits.TRISA0 = 0;

       Digit0_TRIS =0;
       Digit1_TRIS =0;
       Digit2_TRIS =0;
       Digit3_TRIS =0;
       Digit4_TRIS =0;
       Digit5_TRIS =0;

//Sets Pins to Digital
       ADCON1 = 0x0f;
} // end initialize()

void Read_New_Value(char *Output)
{ unsigned int i;
  char burner; //intentionally burning cycles since the buffer needs time to clear
  for(i=0;i<8;i++){
      if (i > 1) //Actually saving input
          Output[i-2] = UART_Read_Blocking();
      else  //Burning one cycle before taking in input
        burner = UART_Read_Blocking();
     }
  Output[6] = '\0'; //Null terminating string for good practice

}

//See which segments currently on the dataline must be on according to input to properly light up a digit
void driveSegments(){
    if (( dataLine & cathodes[0]) > 0)
        A_7SEGI = 1;
    else
        A_7SEGI = 0;

    if ((dataLine & cathodes[1]) > 0)
        B_7SEGI = 1;
    else
        B_7SEGI = 0;
    if ((dataLine & cathodes[2]) > 0)
        C_7SEGI = 1;
    else
        C_7SEGI = 0;
    if ((dataLine & cathodes[3]) > 0)
        D_7SEGI = 1;
    else
        D_7SEGI = 0;
    if ((dataLine & cathodes[4]) > 0)
        E_7SEGI = 1;
    else
        E_7SEGI = 0;
    if ((dataLine & cathodes[5]) > 0)
        F_7SEGI = 1;
    else
        F_7SEGI = 0;
    if ((dataLine & cathodes[6]) > 0)
        G_7SEGI = 1;
    else
        G_7SEGI = 0;
    return;
}
