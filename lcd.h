#define lcd_d 0xf<<20

#define rs 1<<17

#define rw 1<<18

#define e 1<<19





void delay_ms(unsigned int seconds)



{



T0PR=15000-1;



T0TCR=0x1;



while(T0TC<seconds);



T0TCR=0x3;



T0TCR=0x0;



}

void lcd_cmd(unsigned char cmd)

{

	IOCLR1 = lcd_d;

	IOSET1 = (cmd &	0xf0)<<16;

	IOCLR1 = rs;

	IOCLR1 = rw;

	IOSET1 = e;

	delay_ms(2);

	IOCLR1 = e;



	IOCLR1 = lcd_d;

	IOSET1 = (cmd &	0x0f)<<20;

	IOCLR1 = rs;

	IOCLR1 = rw;

	IOSET1 = e;

	delay_ms(2);

	IOCLR1 = e;

}



void lcd_data(unsigned char data)

{

	IOCLR1 = lcd_d;

	IOSET1 = (data & 0xf0)<<16;

	IOSET1 = rs;

	IOCLR1 = rw;

	IOSET1 = e;

	delay_ms(2);

	IOCLR1 = e;



	IOCLR1 = lcd_d;

	IOSET1 = (data & 0x0f)<<20;

	IOSET1 = rs;

	IOCLR1 = rw;

	IOSET1 = e;

	delay_ms(2);

	IOCLR1 = e;

}



void lcd_config(void)

{

	IODIR1 |= lcd_d|rs|rw|e;

	lcd_cmd(0x01);

	lcd_cmd(0x02);

	lcd_cmd(0x0c);

	lcd_cmd(0x28);

	lcd_cmd(0x80);

}



void lcd_string(char *s)

{

	while(*s)

	lcd_data(*s++);

}



void lcd_integer(int n)

{

unsigned char arr[5];

signed char i=0;

if(n==0)

lcd_data('0');

else 

{

if(n<0)

{

lcd_data('-');

n=-n;

}

while(n>0)

{

arr[i++]=n%10;

n/=10;

}

for(--i;i>=0;i--)

lcd_data(arr[i]+48);

}

}

void lcd_time_display(unsigned char t)

{

	//lcd_command(l);

	lcd_data((t/10)+'0');

	lcd_data((t%10)+'0');

	

}
  void error() {
    lcd_cmd(0x01);
    lcd_string("I2C Error");
    while(1);  // Halt
}



 