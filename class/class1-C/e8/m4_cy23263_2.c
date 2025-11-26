//きらきら星
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

void __interrupt() warikomi(void);//プロトタイプ宣言

int count=0,oto;//global変数設定
int main(void)
{	
	OSCCON = 0x70;//内蔵発振回路のクロック周波数を設定
	ANSELA = 0x00;//RA0からRA4までのディジタル設定
	ANSELB =0x00;//RB1からRB7までのディジタル設定
	TRISA = 0x00;//PORTAの設定
	TRISB = 0x00;//PORTBの設定
	LATA = 0x28;//入力
	LATB = 0x00;//出力
	TMR0CS=0;//タイマをクロックで動かす
	TMR0=0x00;//タイマの現在地
	TMR0IF=0;//タイマーオバーフロー割込みが発生してない
	TMR0IE=1;//タイマーオバーフロー割込みを許可
	GIE=1;//割込みの許可
	while(1){
		oto=60;//ドを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=60;//ドを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=40;//ソを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=40;//ソを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=36;//ラを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=36;//ラを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=40;//ソを出す
		__delay_ms(1000);//1秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=45;//ファを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=45;//ファを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=47;//ミを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=47;//ミを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=53;//レを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=53;//レを出す
		__delay_ms(600);//0.6秒間
		GIE=0;//割込み無許可
		__delay_ms(200);//0.2秒間
		GIE=1;//割込み許可
		oto=60;//ドを出す
		__delay_ms(1000);//1秒間
		GIE=0;//割込み無許可
		__delay_ms(3000);//3秒間
		GIE=1;//割込み許可
	}
	
	return 0;
}
	
	
	void __interrupt() warikomi(void){//割り込み関数warikomiを作成
	if(TMR0IF==1 && TMR0IE==1){//タイマオーバーフロー割込みが発生かつ許可されたとき
	count++;//割込み数
	if(count>=oto){//oto回以上の割込み数になったとき
		LATA2 = 1-LATA2;//High,Lowを入れ替え
		count= 0;//割込み数をリセット
	}
	TMR0IF=0;//タイマオーバーフロー割込みが発生してない
}
return;
	}
