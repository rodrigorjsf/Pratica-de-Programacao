#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int bissexto (int ano){
	int anoAux1, anoAux2;
	anoAux1 = ano/4;
	anoAux2 = ano/400;
	if (anoAux1 == 0){
		anoAux1 = ano/100;
		if (anoAux1 == 0)
			return 0;
		else
			return 1;
	}
	else if (anoAux2 == 0)
		return 1;
	return 0;
}

int main () {
	int ano, v;

	printf ("Digite o ano: \n");
	scanf ("%i", &ano);
	v = bissexto(ano);
	if (v == 1)
		printf ("O ano de %d e bissexto. \n", ano);
	else
		printf ("O ano de %d nao e bissexto. \n", ano);
	return 0;
}


