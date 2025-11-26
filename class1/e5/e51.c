//cy23263,²“¡•à
#include <stdio.h>

double sum(double a,double b)//sumŠÖ”‚ğì‚é
{
	double sum;
	sum = a + b;//˜a‚ğŒvZ
	return sum;//–ß‚è’l‚Ísum
}

double product(double a, double b)//productŠÖ”‚ğì‚é
{
	double product;
	product = a * b;//Ï‚ğŒvZ
	return product;//–ß‚è’l‚Íproduct
}

int main(void)
{
	double x, y, z, u,v;

	printf("x,y,z:");
	scanf("%lf%lf%lf",&x,&y,&z);//x,y,z‚ğ“ü—Í

	u = sum(x, y);//x,y‚ğsumŠÖ”‚É‘ã“ü
	v = product(u, z);//x‚Æy‚Ì˜a‚Æz‚ğ‘ã“ü
	printf("(x+y)*z = %f", v);

	return 0;
}