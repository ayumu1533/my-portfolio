//cy23263,ç≤ì°ï‡
#include <stdio.h>
#include <math.h>
#define PI 3.141592
int main(void)
{
	int i,deg;
	double rad;

	for (i = 0; i <= 70; i += 10) {//8âÒåJÇËï‘Ç∑
		deg = 10 + i;//åvéZ
		rad = PI / 180 * (double)deg;//äpìxÇÉâÉWÉAÉìÇ…ïœä∑
		printf("%d:%f %f %f\n", deg, sin(rad), cos(rad), tan(rad));//sin,cos,tanÇèoóÕ
	}
	return 0;
}