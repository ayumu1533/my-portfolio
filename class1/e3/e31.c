//cy23263,²“¡•à
#include <stdio.h>

int main(void)
{
	int i, j;

	for (i = 1; i <= 9; i++) {//9‰ñŒJ‚è•Ô‚·
		for (j = 10-i; j >=1; j--) {//9‚©‚ç1‚Ü‚ÅŒJ‚è•Ô‚·
			printf("%d", j);//Œ‹‰Ê‚ğo—Í
		}
		printf("\n");
	}
	return 0;
}