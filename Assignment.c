/*
 * File:   Assignment.c
 * Author: BASIT AKRAM
 *
 * Created on November 13, 2022, 2:23 PM
 */

// FOSC
#pragma config FPR = XT                 // Primary Oscillator Mode (XT)
#pragma config FOS = PRI                // Oscillator Source (Primary Oscillator)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

#include "stdio.h"
#include "xc.h"
#include "timer.h"
#include "spi.h"

#define BUFFER_SIZE 16

//memory buffer for read and write data
typedef struct {
    char buffer[BUFFER_SIZE];
    int readIndex;
    int writeIndex;
} CircularBuffer;
volatile CircularBuffer cb;

void write_buffer( volatile CircularBuffer* cb, char value){
cb->buffer[cb->writeIndex] = value;
cb->writeIndex++;
if (cb->writeIndex == BUFFER_SIZE)
cb->writeIndex = 0;
}

int read_buffer(volatile CircularBuffer* cb, char* value) {
    if (cb->readIndex == cb->writeIndex)
        return 0;
    *value = cb->buffer[cb->readIndex];
    cb->readIndex++;
    if (cb->readIndex == BUFFER_SIZE)
        cb->readIndex = 0;
    return 1;
}

//interrupt to receive data from UART receiver
void __attribute__ (( __interrupt__ , __auto_psv__ ) ) _U2RXInterrupt() {
    IFS1bits.U2RXIF = 0;
    char value = U2RXREG;
    write_buffer(&cb, value);
}

int int0 = 0;
void __attribute__((__interrupt__, __auto_psv__)) _INT0Interrupt(void)
{
    IFS0bits.INT0IF = 0;
    int0 = 1;
}

int int1 = 0;
void __attribute__((__interrupt__, __auto_psv__)) _INT1Interrupt(void)
{
    IFS1bits.INT1IF = 0;
    int1 = 1;
}

int main(void) {
    
    //variables declarations
    int count = 0;
    char value;
    char str[16];
    int colIndex = 0;
    
    //set S5 & S6 button as input
    TRISEbits.TRISE8 = 1;
    TRISDbits.TRISD0 = 1;    
    
    cb.readIndex = 0;
    cb.writeIndex = 0;
    
    IEC0bits.INT0IE = 1; // enable INT0 interrupt!
    IEC1bits.INT1IE = 1; // enable INT1 interrupt!
    
    SPI_setup();
    UART_setup();
    
    /*-----QUESTION 1 LOGICAL CODE------*/
    tmr_wait_ms(2,1000);            //TIMER 1 WAIT FOR 1 SEC
    tmr_setup_period(1,40);         //TIMER 2 SETUP FOR 40 MS  (it is not working less than 40ms)
    
     while (1) {
        IEC1bits.U2RXIE = 0;
        int read = read_buffer(&cb, &value);  //READ DATA FROM BUFFER
        IEC1bits.U2RXIE = 1;
        
        if (read == 1){
            
            /*-----QUESTION 2 LOGICAL CODE------*/
            //code for first row 
            move_cursor_first_row(colIndex);
            put_char_SPI(value);                   
            count++;
            colIndex++;
            
            /*-----QUESTION 3 & 4 LOGICAL CODE------*/
            //condition to clear screen with given conditions
            int clr = count%16;
            if (value == '\r' || value == '\n' || clr == 0) {
                move_cursor_first_row(0);
                clear_LCD(0);
                move_cursor_first_row(0);
                //count = 0;
                colIndex = 0;
            }
            
            /*-----QUESTION 5 LOGICAL CODE------*/
            //code for second row
            move_cursor_second_row(0);
            sprintf(str ,"CharRecv: %d", count);
            write_string_LCD(str);
            
        }
       
        /*-----QUESTION 6 LOGICAL CODE------*/
        if(int0 == 1){
            U2TXREG = count;
            int0 = 0;
        }

        /*-----QUESTION 7 LOGICAL CODE------*/
        if(int1 == 1){
            move_cursor_first_row(0);
            clear_LCD(0);
            move_cursor_first_row(0);
            count = 0;
            colIndex = 0;
            int1 = 0;
        }
        
        tmr_wait_period(1); // wait what is needed for the next loop
     }
        return 0;
}
