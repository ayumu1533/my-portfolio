//cy23263,佐藤歩
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

int show_number(int x)//関数show_numberを作成
{
	
	if(x==0){//0を点灯
		LATB=0x77;
	}
	else if(x==1){//1を点灯
		LATB=0x14;
	}
	else if(x==2){//2を点灯
		LATB=0xB3;
	}	
	else if(x==3){//3を点灯
		LATB=0xB6;
	}
	else if(x==4){//4を点灯
		LATB=0xD4;
	}
	else if(x==5){//5を点灯
		LATB=0xE6;
	}
	else if(x==6){//6を点灯
		LATB=0xE7;
	}
	else if(x==7){//7を点灯
		LATB=0x74;
	}
	else if(x==8){//8を点灯
		LATB=0xF7;
	}
	else if(x==9){//9を点灯
		LATB=0xF6;
	}
}


int main(void)
{
	OSCCON = 0x70;			//内蔵発振回路のクロック周波数を設定
	ANSELA = 0x00;			//RA0からRA4までのディジタル設定
	ANSELB = 0x00;			//RB1からRB7までのディジタル設定
	TRISA = 0x30;			//PORTAの設定
	TRISB = 0x00;			//PORTBの設定
	LATA = 0x00;			//入力
	LATB = 0x00;			//出力
	
	int i;
	while(1){	
	if(RA4==0){
		LATB=0x63;			//Cを点灯
		__delay_ms(1000);	//1秒遅延
		LATB=0x00;			//Cを消灯
		__delay_ms(300);	//0.3秒遅延
		LATB=0xD6;			//Yを点灯
		__delay_ms(1000);	//1秒遅延
		LATB=0x00;			//Yを消灯
		__delay_ms(300);	//0.3秒遅延
		show_number(2);		//2を点灯
		__delay_ms(1000);	//1秒遅延
		LATB=0x00;			//2を消灯
		__delay_ms(300);	//0.3秒遅延
		show_number(3);		//3を点灯
		__delay_ms(1000);	//1秒遅延
		LATB=0x00;			//3を消灯
		__delay_ms(300);	//0.3秒遅延
		show_number(2);		//2を点灯
		__delay_ms(1000);	//1秒遅延
		LATB=0x00;			//2を消灯
		__delay_ms(300);	//0.3秒遅延
		show_number(6);		//6を点灯
		__delay_ms(1000);	//1秒遅延
		LATB=0x00;			//6を消灯
		__delay_ms(300);	//0.3秒遅延
		show_number(3);		//3を点灯
		__delay_ms(1000);	//1秒遅延
		LATB=0x00;			//3を消灯
		__delay_ms(300);	//0.3秒遅延
		LATB3=1;			//.を点灯
		__delay_ms(1000);	//1秒遅延
		LATB3=0;			//.を消灯
		__delay_ms(300);	//0.3秒遅延
	}
	else if(RA4 ==1){		//スイッチを押してない時
		for(i=0;i<=9;i++){
			show_number(i); //0～9を順々に点灯
			__delay_ms(500);//0.5秒遅延
		}
	}
	}
	return 0;
}
