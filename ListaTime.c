//http://mixdereferencias.blogspot.com.br/2013/10/quantos-dias-tem-cada-mes-do-ano.html
//http://escolakids.uol.com.br/calculo-do-ano-bissexto.htm


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct data {
	int dia, mes, ano;
}Data;

int bissexto (int ano){
	int anoAux;
	anoAux = ano/4;
	if (
}

int validaData(Data dt1, Data dt2){
	int mesPar, auxMes;
	mesPar = dt2.mes/2;

	if (mesPar == 0){
		if (dt2.mes == 2){
			auxMes = 28;
		}
		auxMes = 
	}
	if (dt2.ano < dt1.ano)
		return 0;
	else if (dt2.mes < 1 || dt2.mes
}

int main () {
	time_t tp;
	struct tm *local;
	Data dt1, dt2;
	int validar;
	tp = time (NULL);
	local = localtime (&tp);
	printf (asctime (local));
	dt1.dia = local->tm_mday;
	dt1.mes = local->tm_mon + 1;
	dt1.ano = local->tm_year + 1900;
	printf ("Data: %d / %d / %d \n", dt1.dia, dt1.mes, dt1.ano);
	system ("pause");
	do{
	printf ("Digite uma data \n");
	printf ("Dia: \n");
	scanf ("%d", &dt2.dia);
	printf ("Mes: \n");
	scanf ("%d", &dt2.mes);
	printf ("Ano: \n");
	scanf ("%d", &dt2.ano);
	validar = validaData(dt1, dt2);
	if (validar == 0)
		printf ("Data invalida \n");
	}while (validar != 1);
	dias = difData (dt1, dt2);
	printf ("A diferenca em dias entre as datas eh: %d \n", dias);
	return 0;
}

