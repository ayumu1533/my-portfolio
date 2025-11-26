//cy23263,²“¡•à
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
	int i=0,dice;

	srand((unsigned int)time(NULL));//ƒ‰ƒ“ƒ_ƒ€
	
	dice = rand() % 6 + 1;//1`6‚Ì”‚ªo‚é
	do {
		printf("1`6‚Ì”:");
		scanf("%d", &i);//1`6‚Ì”‚ð“ü—Í
		if (i > dice) {
			printf("‚à‚Á‚Æ¬‚³‚¢”‚Å‚·\n");//“ü—Í‚µ‚½”‚ª‚³‚¢‚±‚ë‚Ì–Ú‚æ‚è‘å‚«‚¢
		}
		else if (dice > i) {
			printf("‚à‚Á‚Æ‘å‚«‚¢”‚Å‚·\n");//“ü—Í‚µ‚½”‚ª‚³‚¢‚±‚ë‚Ì–Ú‚æ‚è¬‚³‚¢
		}
		else {
			printf("³‰ð‚Å‚·");//“ü—Í‚µ‚½”‚ª‚³‚¢‚±‚ë‚Ì–Ú‚Æ“¯‚¶
		}
	} while (dice !=i);//“ü—Í‚µ‚½”‚Æ‚³‚¢‚±‚ë‚Ì–Ú‚ªˆá‚¤‚Æ‚«Œp‘±
	return 0;
}