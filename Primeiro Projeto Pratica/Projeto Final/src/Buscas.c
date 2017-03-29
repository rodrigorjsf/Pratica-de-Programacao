#include "Buscas.h"
#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"
#include "Validacoes.h"
#include "Tempoedata.h"
#include "Types.h"

int BuscarPassagemCPF (FILE * arq, char cpf [], int pos)
{
    int cont = -1, status;
    TPass p;
    if (pos > -1){
        cont = pos;
        pos++;
        fseek (arq, pos * sizeof (TPass), 0);
    }
    else
        fseek (arq, 0, 0);
    while (1)
    {
        status = fread (&p, sizeof (TPass), 1, arq);
        if (status != 1)
        {
            if (!feof(arq))
                return -2;
            else
                return -1;
        }
        else
        {
            cont++;
            if (p.status == 1 && strcmp (p.cpf, cpf) == 0)
                return cont;
        }
    }
}
int BuscarPassagemCodReserva (FILE * arq, char cod [])
{
	int cont = -1, status;
		TPass p;

		fseek (arq, 0, 0);
		while (1)
		{
			status = fread (&p, sizeof (TPass), 1, arq);
			if (status != 1)
			{
				if (!feof(arq))
				    return -2;
				else
					return -1;
			}
			else
			{
				cont++;
				if (p.status == 1 && strcmp (p.codReserva, cod) == 0)
					return cont;
			}
		}
}

int BuscarPassagemCodVoo (FILE * arq, char cod [], int pos)
{
	int cont = -1, status;
	TPass p;
	if (pos > -1){
		cont = pos;
		pos++;
		fseek (arq, pos * sizeof (TPass), 0);
	}
	else{
		fseek (arq, 0, 0);
	}
	while (1)
	{
		status = fread (&p, sizeof (TPass), 1, arq);
		if (status != 1)
		{
			if (!feof(arq))
				return -2;
			else
				return -1;
			}
		else
		{
			cont++;
			if (p.status == 1 && strcmp (p.codVoo, cod) == 0)
				return cont;
		}
	}
}

int procurarVooPassagem(FILE *arqVoo, int origem, int destino, Data d, char cod[]) {
	TVoo v;
	int cont = -1;
	char Locais[9][50] = {"RECIFE","SALVADOR","SAO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE"};
	int diaAux1, mesAux1, diaAux2, mesAux2;
	fseek(arqVoo, 0, 0);
	while (1) {
		if (fread(&v, sizeof(TVoo), 1, arqVoo) != 1) {
			if (!feof(arqVoo)) {
				return -2;
			}
			else {
				return -1;
			}
		}
		else {
			cont++;
			 diaAux1 = atoi(d.dia);
			 diaAux2 = atoi(v.dia);
			 mesAux1 = atoi(d.mes);
			 mesAux2 = atoi(v.mes);
			if (v.status == 1 && strcmp(v.origem, Locais[origem-1]) == 0 && strcmp(v.destino, Locais[destino-1]) == 0 && diaAux1 == diaAux2 && mesAux1 == mesAux2 && strcmp(v.codVoo, cod) == 0) {
				if (v.poltronas > 0) {
					return cont;
				}
				else {
					printf("Nao ha poltronas disponiveis \n");
					return -3;
				}
			}
		}
	}
}

int BuscarCliente (FILE * arq, char cpf [])
{
	int cont = -1, status;
		TCliente c;

		fseek (arq, 0, 0);
		while (1)
		{
			status = fread (&c, sizeof (TCliente), 1, arq);
			if (status != 1)
			{
				if (!feof(arq))
				    return -2;
				else
					return -1;
			}
			else
			{
				cont++;
				if (c.status == 1 && strcmp (c.cpf, cpf) == 0)
					return cont;
			}
		}
}

int BuscarVoo(FILE * arq, char cod[]) {
	int cont = -1, status;
	TVoo v;
	fseek(arq, 0, 0);
	while (1) {
		status = fread(&v, sizeof(TVoo), 1, arq);
		if (status != 1) {
			if (!feof(arq))
				return -2;
			else
				return -1;
		}
		else {
			cont++;
			if (v.status == 1 && strcmp(v.codVoo, cod) == 0)
				return cont;
		}
	}

}
int BuscarVooPorData(FILE * arq, Data d) {
	int cont = -1, status;
	TVoo v;
	int diaAux1, mesAux1, diaAux2, mesAux2;
	fseek(arq, 0, 0);
	while (1) {
		status = fread(&v, sizeof(TVoo), 1, arq);
		if (status != 1) {
			if (!feof(arq))
				return -2;
			else
				return -1;
		}
		else {
			cont++;
			diaAux1 = atoi(d.dia);
			diaAux2 = atoi(v.dia);
			mesAux1 = atoi(d.mes);
			mesAux2 = atoi(v.mes);
			if (v.status == 1 && diaAux1 == diaAux2 && mesAux1 == mesAux2)
				return cont;
		}
	}

}

int BuscarTodosVoos (FILE * arq, int origem, int destino, Data d , int pos)
{
    int cont = -1, status;
    char Locais[9][50] = {"RECIFE","SALVADOR","SAO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE"};
    TVoo v;
    int diaAux1, mesAux1, diaAux2, mesAux2;
    if (pos > -1){
    	cont = pos;
    	pos++;
        fseek (arq, pos * sizeof (TVoo), 0);
    }
    else{
        fseek (arq, 0, 0);
    }
    while (1)
    {
        status = fread (&v, sizeof (TVoo), 1, arq);
        if (status != 1)
        {
            if (!feof(arq))
                return -2; // erro de leitura
            else
                return -1; // nao achou
        }
        else
        {
            cont++;
            diaAux1 = atoi(d.dia);
			diaAux2 = atoi(v.dia);
			mesAux1 = atoi(d.mes);
			mesAux2 = atoi(v.mes);
            if (v.status == 1 && diaAux1 == diaAux2 && mesAux1 == mesAux2 && strcmp(v.destino,Locais[destino-1]) == 0 && strcmp(v.origem,Locais[origem-1]) == 0)
            	return cont;
        }
    }
}
