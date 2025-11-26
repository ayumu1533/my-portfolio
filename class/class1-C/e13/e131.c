//cy23263,ç≤ì°ï‡
#include <stdio.h>


int main(void) {
	double data[3][2], den[3], den_sum = 0, den_ave;
	int i;
	for (i = 0; i < 3; i++) {//ÇRå¬ÇÃï®ëÃ
		printf("%då¬ñ⁄ÇÃéøó Ç∆ëÃêœ:", i + 1);
		scanf("%lf %lf", &data[i][0], &data[i][1]);//ÇRå¬ÇÃï®ëÃÇÃéøó Ç∆ëÃêœÇì¸óÕ
		den[i] = data[i][0] / data[i][1];//ÇRå¬ÇÃï®ëÃÇÃñßìxÇåvéZ
		den_sum += den[i];//ñßìxÇçáåv
	}
	den_ave = den_sum / 3;//ñßìxÇÃïΩãœÇåvéZ
	printf("ñßìxÇÃïΩãœ:%lf", den_ave);//åãâ ÇèoóÕ


	return 0;
}