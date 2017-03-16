#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct data {
	int dia, mes, ano;
}Data;

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
int validaData(Data dt1, Data dt2){
	int auxDia1, ano;
	int QuantDias1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
	ano = bissexto(dt2.ano);
	if (dt2.ano < 0)
		return 0;
	if (dt2.mes < 1 || dt2.mes > 12)
		return 0;
	if (dt2.dia < 1)
		return 0;
	if (dt2.mes == 2){
		if (ano == 1)
			auxDia1 = 29;
		else
			auxDia1 = QuantDias1[dt2.mes-1];
		if (dt2.dia < 1 || dt2.dia > auxDia1)
			return 0;
	}
	else
	{
		auxDia1 = QuantDias1[dt2.mes-1];
		if (dt2.dia < 1 || dt2.dia > auxDia1)
			return 0;
	}
	return 1;
}

int difDias(Data dt1, Data dt2) {
	int contAno = 0, contMes = 0, cont, auxDia1, ano, i;
	int QuantDias[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
	int mesBissexto = 29;
	ano = bissexto(dt2.ano);
	contDia = QuantDias[dt2.mes-1]-dt2.dia;

	if (dt2.ano < dt1.ano)
	{
		ano = bissexto(dt2.ano);
		for (i = dt2.mes-1; i < 12;dt2.mes++)
		{
			if (ano == 1)
			{
				if (i == 1)
					contMes = contMes + mesBissexto;
				else
					contMes = contMes + QuantDias[i];
			}
			else
				contMes = contMes + QuantDias[i];
		}
		dt2.ano += 1;
		for (i = dt2.ano; i < dt1.ano; dt2.ano++)
		{
			ano = bissexto(dt2.ano);
			if (ano == 1)
				contAno += 366;
			else
				contAno += 365;
		}
		if (QuantDias[dt2.mes-1] == dt2.dia)
			cont = (contAno+contMes) - QuantDias[dt2.mes-1];
		else
			cont = (contAno+contMes) - dt2.dia;
		return cont;
	}
	else
	{
		ano = bissexto(dt1.ano);
		for (i = dt1.mes-1; i < 12;dt1.mes++)
		{
			if (ano == 1)
			{
				if (i == 1)
					contMes = contMes + mesBissexto;
				else
					contMes = contMes + QuantDias[i];
			}
			else
				contMes = contMes + QuantDias[i];
		}
		dt1.ano += 1;
		for (i = dt1.ano; i < dt2.ano; dt1.ano++)
		{
			ano = bissexto(dt1.ano);
			if (ano == 1)
				contAno += 366;
			else
				contAno += 365;
		}
		if (QuantDias[dt1.mes-1] == dt1.dia)
			cont = (contAno+contMes) - QuantDias[dt1.mes-1];
		else
			cont = (contAno+contMes) - dt1.dia;
		return cont;
	}

}


/*int validaData(Data dt1, Data dt2){
	int mesPar, auxDia1, auxDia2, ano;
	int QuantDias1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
	mesPar = dt2.mes%2;
	ano = bissexto(dt2.ano);
	if (dt2.ano < 0)
		return 0;
	if (dt2.mes < 1 || dt2.mes > 12)
		return 0;
	if (dt2.dia < 1)
		return 0;
	if (dt2.mes < 8){
		if (mesPar == 0){
			if (dt2.mes == 2){
				if (ano == 1)
					auxDia1 = 29;
				else
					auxDia1 = QuantDias1[dt2.mes-1];
				if (dt2.dia < 1 || dt2.dia > auxDia1)
					return 0;
			}
			else
			{
				auxDia1 = QuantDias1[dt2.mes-1];
				if (dt2.dia < 1 || dt2.dia > auxDia1)
					return 0;
			}
		}
		else
		{
			auxDia1 = QuantDias1[dt2.mes-1];
			if (dt2.dia < 1 || dt2.dia > auxDia1)
				return 0;
		}
	}
	else
	{
		auxDia1 = QuantDias1[dt2.mes-1];
		if (dt2.dia < 1 || dt2.dia > auxDia1)
			return 0;
	}
	return 1;
}*/

int main () {
	time_t tp;
	struct tm *local;
	Data dt1, dt2;
	int validar,dias;
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
