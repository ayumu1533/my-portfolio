//cy23263,²“¡•à
#include <stdio.h>

int discriminant(double a, double b, double c)//discriminantŠÖ”‚ğì‚é
{
	double d;
	d = b * b - 4 * a * c;//”»•Ê®‚ğŒvZ	
	if (a == 0) {//2Ÿ•û’ö®‚Å‚Í‚È‚¢
	return -1;
    }
	if (d > 0) {//À”‰ğ‚ª2ŒÂ‚Ì
		return 2;
	}
	
	else if (d < 0) {//À”‰ğ‚ª0ŒÂ‚Ì
		return 0;
	}

	else {//À”‰ğ‚ª1ŒÂ‚Ì
		return 1;
	}
}

int main(void)
{
	double a, b, c;
	int d;
	printf("2Ÿ•û’ö®‚ÌŒW”a,b,c‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢:");
	scanf("%lf %lf %lf", &a, &b, &c);//ŒW”a,b,c‚ğ“ü—Í
	d = discriminant(a, b, c);//discriminantŠÖ”‚Éa,b,c‚ğ‘ã“ü
	if (d == -1) {//2Ÿ•û’ö®‚Å‚È‚¢
		printf("2Ÿ•û’ö®‚Å‚Í‚ ‚è‚Ü‚¹‚ñ");//Œ‹‰Ê‚ğo—Í
	}
	else {
		printf("À”‰ğ‚Í%dŒÂ‚Å‚·",d);//‚»‚ê‚¼‚ê‚ÌÀ”‰ğ‚ÌŒÂ”‚ğo—Í
	}
	return 0;
}