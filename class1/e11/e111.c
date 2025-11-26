//cy23263,ç≤ì°ï‡
#include <stdio.h>
#include <math.h>
int main(void) {

	int i;
	double sum1=0,sum2=0,ave,dis,deta[4];

	for (i = 1; i <= 4; i++) {//4âÒåJÇËï‘Ç∑
		printf("%då¬ñ⁄ÇÃÉfÅ[É^:", i);
		scanf("%lf",&deta[i - 1]);//ÉfÅ[É^ÇÃì¸óÕ
	}
	for (i = 1; i <= 4; i++) {//ÉfÅ[É^1Å`4Çë´Ç∑
		sum1 = sum1 + deta[i - 1];//çáåvÇåvéZ
	}

	ave = sum1 / 4;//ïΩãœÇåvéZ

	for (i = 1;i <= 4; i++) {
		sum2 = sum2 + pow((deta[i - 1] - ave),2);//äeílà¯Ç≠ïΩãœÇÃ2èÊÇÃçáåvÇåvéZ
	}

	dis = sum2 / 4;//ï™éUÇåvéZ

	printf("ï™éU:%f", dis);//ï™éUÇèoóÕ
	return 0;
}