/*
 * File:   UART.h
 *
 * Created on February 10, 2018, 4:08 AM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

char UART_Init(const long int baudrate);
void UART_Write(char data);
void UART_Write_Text(char *text);
char UART_Read_NoBlocking();
char UART_Read_Blocking();
void testSegments(char digit);




#endif	/* UART_H */
