
// PIC16F1827 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 32000000//クロック周波数を指定

int main(void)
{
	OSCCON = 0x70;//内蔵発振回路のクロック周波数を設定
	ANSELA = 0x00;//RA0からRA4までのディジタル設定
	ANSELB = 0x00;//RB1からRB7までのディジタル設定
	TRISA = 0x28;//PORTAの設定
	TRISB = 0x00;//PORTBの設定
	LATA = 0x00;//入力
	LATB = 0x00;//出力
	while(1)/*繰り返す*/
	{	
		/*Cを点灯*/
		LATB0 = 1;
		LATB1 = 1;
		LATB5 = 1;
		LATB6 = 1;
		__delay_ms(1000);/*1秒継続*/
		/*Cを消灯*/
		LATB0 = 0;
		LATB1 = 0;
		LATB5 = 0;
		LATB6 = 0;
		__delay_ms(300);/*0.3秒継続*/
		/*Yを点灯*/
		LATB1 = 1; 
		LATB2 = 1;
		LATB4 = 1;
		LATB6 = 1;
		LATB7 = 1;
		__delay_ms(1000);/*1秒継続*/
		/*Yを消灯*/
		LATB1 = 0; 
		LATB2 = 0;
		LATB4 = 0;
		LATB6 = 0;
		LATB7 = 0;
		__delay_ms(300);/*0.3秒継続*/
		/*.を点灯*/
		LATB3 = 1;
		__delay_ms(1000);/*1秒継続*/
		/*.を消灯*/
		LATB3 = 0;
		__delay_ms(300);/*0.3秒継続*/
		
	}
	return 0;
}