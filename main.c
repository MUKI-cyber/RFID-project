#include <lpc21xx.h>
#include <string.h>
#include"types.h"
#include"lcd.h"
#include"i2c.h"
#include"rtc.c"


void uart0_init() {
    PINSEL0 &= ~0x0F;   // Clear P0.0 and P0.1
    PINSEL0 |= 0x05;    // Enable UART0 RXD/TXD

    U0LCR = 0x83;       // Enable DLAB
    U0DLL = 97;         // For 9600 baud with PCLK = 15MHz
    U0DLM = 0;
    U0LCR = 0x03;       // 8-bit, no parity, 1 stop bit
    //U0FCR = 0x07;       // Enable and reset FIFO
}


void uart0_tx(unsigned char d)
 {
 U0THR=d;
 while(((U0LSR>>5)&1)==0);
 }
char uart0_rx() {
    while ((U0LSR & 1)==0);  // Wait until data is received
    return U0RBR;
}

void uart0_str(const char *str) {
    while (*str) {
        uart0_tx(*str++);
    }
}

void uart0_flush() {
    while (U0LSR & 0x01) {
        volatile char dummy = U0RBR;
    }
}
int main() {
     char rfid[11];
	 char ch;
     int zoro,luffy;
	 int i;							
	 unsigned char sec = 0,min = 15,hours = 14,day = 19,date=19,month=6,year=25;
     lcd_config();
	 init_i2c();
    uart0_init();
	 
	   	 lcd_cmd(0x01);
		 lcd_string("project...");
 	delay_ms(1000);
      rtc_write(sec,min,hours,day,date,month,year);
	  lcd_cmd(0x01);
		 lcd_string("rtc set");
 	delay_ms(1000);
     while(1) {
	 lcd_cmd(0x01);
		 lcd_string("Scan Card...");
 	delay_ms(1000);
 	
	 	uart0_flush();
		delay_ms(100);
		
         for(i = 0; i < 10; i++)
 		  {
             rfid[i]= uart0_rx();
 			//uart0_tx(rfid[i]);
           }
         rfid[10] = '\0';
		 uart0_str(rfid);
		 lcd_cmd(0x01);
		 lcd_string("data recived");
 	delay_ms(2000); 
		 
         lcd_cmd(0x01);         // Clear LCD
         lcd_cmd(0x80);         // First line
         lcd_string("Card ID:");
         lcd_cmd(0xC0);         // Second line
         lcd_string(rfid);      // Display RFID data
         delay_ms(2000);
         
 		zoro=strcmp(rfid, "06006783BB");
 		luffy=strcmp(rfid,"06003B6837");
 		if(zoro==0)
 		{
 			
			lcd_cmd(0x01);
 			lcd_string("ZORO");
			delay_ms(1000);
		
 	    }
 		else if(luffy==0)
 		{
			lcd_cmd(0x01);
 			lcd_string("LUFFY");
			delay_ms(1000);
			
		
 		}
		else
		{
		   lcd_cmd(0x01);
 			lcd_string("not matched");
			delay_ms(1000);
		}
 		
		rtc_read(&sec,&min,&hours,&day,&date,&month,&year);

			lcd_cmd(0xc0);

			lcd_string("Time:");

			lcd_time_display(hours);

			lcd_data(':');

			lcd_time_display(min);

			lcd_data(':');

			lcd_time_display(sec);

			lcd_cmd(0xc0);
			delay_ms(3000);
     }
 }