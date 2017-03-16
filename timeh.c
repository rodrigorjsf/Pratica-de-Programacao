#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct data {
	int dia, mes, ano;
}Data;

int bissexto (int ano){
	int anoAux1, anoAux2;
	anoAux1 = ano%4;
	anoAux2 = ano%400;
	if (anoAux1 == 0){
		anoAux1 = ano%100;
		if (anoAux1 == 0)
			return 0;
		else
			return 1;
	}
	else if (anoAux2 == 0)
		return 1;
	return 0;
}
int validaData(Data dt2){
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
        printf ("Data valida \n");
	return 1;
}

double difData(Data dt1, Data dt2) {
	int contAno = 0, contMes = 0, cont, ano, i;
        int diasNoAnoAtual = 0, mesAux, anoAux, diaAux;
	int QuantDias[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
	int mesBissexto = 29; 
	if (dt2.ano < dt1.ano)
	{
            diaAux = dt2.dia;
            mesAux = dt2.mes;
            anoAux = dt2.ano;            
            ano = bissexto(anoAux);
            for (i = mesAux-1; i < 12;i++)
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
            anoAux += 1;
            ano = bissexto(anoAux);
            for (i = anoAux; i < dt1.ano; i++)
            {
                
                if (ano == 1)
                    contAno += 366;
                else
                    contAno += 365;
            }
            ano = bissexto(dt1.ano);
            for (i = 0; i < dt1.mes-1; i++)
            {
                if (ano == 1)
                {
                    if (i == 1)
                        diasNoAnoAtual = diasNoAnoAtual + mesBissexto;                   
                    else
                        diasNoAnoAtual = diasNoAnoAtual + QuantDias[i];            
                }
                else
                    diasNoAnoAtual = diasNoAnoAtual + QuantDias[i];
            }          
            if (QuantDias[mesAux-1] == dt2.dia)
                cont = (diasNoAnoAtual+contAno+contMes+dt1.dia) - QuantDias[mesAux-1];
            else
                cont = (diasNoAnoAtual+contAno+contMes+dt1.dia) - diaAux;
	}
	else if (dt2.ano > dt1.ano)
	{
            diaAux = dt1.dia;
            mesAux = dt1.mes;
            anoAux = dt1.ano; 
            ano = bissexto(anoAux);
            for (i = mesAux-1; i < 12;i++)
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
            anoAux += 1;
            for (i = anoAux; i < dt2.ano; i++)
            {
                ano = bissexto(anoAux);
                if (ano == 1)
                    contAno += 366;
                else
                    contAno += 365;
            }
            ano = bissexto(dt2.ano);
            for (i = 0; i < dt2.mes-1; i++)
            {
                if (ano == 1)
                {
                    if (i == 1)
                        diasNoAnoAtual = diasNoAnoAtual + mesBissexto;                   
                    else
                        diasNoAnoAtual = diasNoAnoAtual + QuantDias[i];            
                }
                else
                    diasNoAnoAtual = diasNoAnoAtual + QuantDias[i];
            }          
            if (QuantDias[mesAux-1] == dt1.dia)                
                cont = (diasNoAnoAtual+contAno+contMes+dt2.dia) - QuantDias[mesAux-1];
            else
                cont = (diasNoAnoAtual+contAno+contMes+dt2.dia) - diaAux;  
	}
        else
        { 
            
            if (dt1.mes < dt2.mes)
            {    
                diaAux = dt1.dia;
                mesAux = dt1.mes;
                anoAux = dt1.ano;
                ano = bissexto(anoAux);               
                for (i = mesAux-1; i < dt2.mes-1;i++)
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
                if (QuantDias[mesAux-1] == dt1.dia)                
                    cont = (contMes+dt2.dia) - QuantDias[mesAux-1];
                else
                    cont = (contMes+dt2.dia) - diaAux;  
            }
            else if (dt1.mes > dt2.mes)
            {
                diaAux = dt2.dia;
                mesAux = dt2.mes;
                anoAux = dt2.ano;
                ano = bissexto(anoAux);               
                for (i = mesAux-1; i < dt1.mes-1;i++)
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
                if (QuantDias[mesAux-1] == dt2.dia)                
                    cont = (contMes+dt1.dia) - QuantDias[mesAux-1];
                else
                    cont = (contMes+dt1.dia) - diaAux;  
            }  
            else
            {
                if (dt1.dia < dt2.dia)
                    cont = dt2.dia - dt1.dia;
                else if (dt1.dia > dt2.dia)
                    cont = dt1.dia - dt2.dia;
                else
                    cont = 0;
            }
        }
        return cont;
}

int main () {
	time_t tp;
	struct tm *local;
	Data dt1, dt2;
	int validar, dias;
	tp = time (NULL);
	local = localtime (&tp);
	printf (asctime (local));
	dt1.dia = local->tm_mday;
	dt1.mes = local->tm_mon + 1;
	dt1.ano = local->tm_year + 1900;
	printf ("Data: %d / %d / %d \n", dt1.dia, dt1.mes, dt1.ano);
	do{
	printf ("Digite uma data \n");
	printf ("Dia: \n");
	scanf ("%d", &dt2.dia);
	printf ("Mes: \n");
	scanf ("%d", &dt2.mes);
	printf ("Ano: \n");
	scanf ("%d", &dt2.ano);
	validar = validaData(dt2);
	if (validar == 0)
		printf ("Data invalida \n");
	}while (validar != 1);
	dias = difData (dt1, dt2);
	printf ("A diferenca em dias entre as datas eh: %d \n", dias);
        system ("pause");
	return 0;
}

