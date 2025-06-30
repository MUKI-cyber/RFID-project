void delay_s(unsigned int s)

{

	T0PR=15000000-1;

	T0TCR=0x1;

	while(T0TC<s);

	T0TCR=0x3;

	T0TCR=0x0;

}


void delay_ms(unsigned int s)

{

	T0PR=15000-1;

	T0TCR=0x1;

	while(T0TC<s);

	T0TCR=0x3;

	T0TCR=0x0;

}


void delay_mics(unsigned int s)

{

	T0PR=15-1;

	T0TCR=0x1;

	while(T0TC<s);

	T0TCR=0x3;

	T0TCR=0x0;

}
