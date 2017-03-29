#include "Tempoedata.h"
#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"
#include "Validacoes.h"
#include "Buscas.h"
#include "Types.h"

void CadastrarData (Data * d)
{
    int i;
    Data data;
    do
    {
        i = 0;
        system("cls");
        printf("Digite a DATA partida: \n");
        printf("DIA: ");
        while (i < 2)
        {

            if (i == 0)
            	data.dia[i] = getche();
            else{
            	data.dia[i] = getche();
            	if (data.dia[i] == 13)
            	{
            		data.dia[i] = '\0';
            		break;
            	}
            	else
            		data.dia[i+1] = '\0';
            }
            i++;
        }
        i = 0;
        printf("\n");
        printf("MES: ");
        while (i < 2)
        {
        	if (i == 0)
        		data.mes[i] = getche();
        	else{
        		data.mes[i] = getche();
        		if (data.mes[i] == 13)
        		{
        			data.mes[i] = '\0';
        			break;
        		}
        		else
        			data.mes[i+1] = '\0';
        	}
        	i++;
        }
        printf("\n");
        if (ValidaData(data) == 0 )
        {
            printf("Data invalida, digite novamente. \n");
            system("pause");
        }
        else if (comparaDataLocal (data) == 0)
        {
        	printf("Data invalida, digite novamente. \n");
        	system("pause");
        }
        else
        {
            strcpy(d->dia, data.dia);
            strcpy(d->mes, data.mes);
        }
    } while (ValidaData(data) == 0 || comparaDataLocal (data) == 0);
}

void CadastrarHorarioNaEstrutura (TVoo * v)
{
    int i, j;
    Horario horario;
    Data data;
    strcpy(data.mes, v->mes);
    strcpy(data.dia, v->dia);
    do
    {
        i = 0;
        j = 0;
        printf("\nDigite o horario de partida(hh/mm): ");
        while(i < 4)
        {
            if (j < 2 && i < 2)
            {
            	if (j == 1){
            		horario.hora[j] = getche();
            		horario.hora[j+1] = '\0';
            		printf(":");
            		j = 0;
            	}
            	else{
            		horario.hora[j] = getche();
            		j++;
            	}
            }
            else
            {
            	if (j == 1){
            		horario.min[j] = getche();
            		horario.min[j+1] = '\0';
            		j = 0;
            	}
            	else{
            		horario.min[j] = getche();
            		j++;
            	}
            }
            i++;
        }
        if (ValidaHora(horario) == 0){
            printf("\nHorario invalido, digite novamente. \n");
        }
        else if (comparaHoraLocal (horario) == 0 && comparaDataLocal (data) == 2)
        {
        	printf("\n Horario invalido, digite novamente. \n");
        	system("pause");
        }
        else{
            strcpy(v->hora, horario.hora);
            strcpy(v->min, horario.min);
        }
    } while (ValidaHora(horario) == 0 || (comparaHoraLocal (horario) == 0 && comparaDataLocal (data) == 2));
}

void CadastrarHorario (Horario * h)
{
    int i, j;
    Horario  horario;
    do
    {
        i = 0;
        j = 0;
        printf("\nDigite o horario de partida(hh/mm): ");
        while(i < 4)
        {
            if (j < 2 && i < 2)
            {
            	if (j == 1){
            		horario.hora[j] = getche();
            		horario.hora[j+1] = '\0';
            		printf(":");
            		j = 0;
            	}
            	else{
            		horario.hora[j] = getche();
            		j++;
            	}
            }
            else
            {
            	if (j == 1){
            		horario.min[j] = getche();
            		horario.min[j+1] = '\0';
            		j = 0;
            	}
            	else{
            		horario.min[j] = getche();
            		j++;
            	}
            }
            i++;
        }
        if (ValidaHora(horario) == 0){
            printf("\nHorario invalido, digite novamente. \n");
        }
        else{
            strcpy(h->hora, horario.hora);
            strcpy(h->min, horario.min);
        }
    } while (ValidaHora(horario) == 0);
}

int comparaHora_e_Data (char dia[], char mes[], char hora[], char min[])
{
    Data d;
    time_t tp;
    struct tm *local;
    Horario h;
    tp = time (NULL);
    int diaLocal, diaRecebido, mesLocal, mesRecebido;
    int horaLocal, horaRecebido, minLocal, minRecebido;
    local = localtime (&tp);
    strftime(d.dia, sizeof(d.dia), "%d", local);
    strftime(d.mes, sizeof(d.mes), "%m", local);
    strftime(h.hora, sizeof(h.hora), "%H", local);
    strftime(h.min, sizeof(h.min), "%M", local);
    diaLocal = atoi (d.dia);
    diaRecebido = atoi (dia);
    mesLocal = atoi (d.mes);
	mesRecebido = atoi (mes);
	horaLocal = atoi (h.hora);
	horaRecebido = atoi (hora);
	minLocal = atoi (h.min);
	minRecebido = atoi (min);
	if (mesRecebido < mesLocal)
		return 0;
	else if (mesRecebido == mesLocal)
		{
		if (diaRecebido < diaLocal)
			return 0;
		else if (diaRecebido == diaLocal)
		{
			if(horaRecebido < horaLocal)
				return 0;
			else if (horaRecebido == horaLocal)
			{
				if (minRecebido < minLocal)
					return 0;
				else
					return 1;
			}
			else
				return 1;
		}
		else
			return 1;
		}
	else
		return 1;
}

int comparaHoraLocal (Horario horario)
{
    time_t tp;
    struct tm *local;
    Horario h;
    tp = time (NULL);
    int horaLocal, horaRecebido, minLocal, minRecebido;
    local = localtime (&tp);
    strftime(h.hora, sizeof(h.hora), "%H", local);
    strftime(h.min, sizeof(h.min), "%M", local);
	horaLocal = atoi (h.hora);
	horaRecebido = atoi (horario.hora);
	minLocal = atoi (h.min);
	minRecebido = atoi (horario.min);
	if(horaRecebido < horaLocal)
		return 0;
	else if (horaRecebido == horaLocal)
	{
		if (minRecebido < minLocal)
			return 0;
		else
			return 1;
	}
	else
		return 1;
}

int comparaDataLocal (Data data)
{
    Data d;
    time_t tp;
    struct tm *local;
    tp = time (NULL);
    int diaLocal, diaRecebido, mesLocal, mesRecebido;
    local = localtime (&tp);
    strftime(d.dia, sizeof(d.dia), "%d", local);
    strftime(d.mes, sizeof(d.mes), "%m", local);
    diaLocal = atoi (d.dia);
    diaRecebido = atoi (data.dia);
    mesLocal = atoi (d.mes);
	mesRecebido = atoi (data.mes);
	if (mesRecebido < mesLocal)
		return 0;
	else if (mesRecebido == mesLocal)
		{
		if (diaRecebido < diaLocal)
			return 0;
		else if (diaRecebido > diaLocal)
			return 1;
		else
			return 2;
		}
	else
		return 1;
}
