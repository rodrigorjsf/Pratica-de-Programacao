#include "rotinas.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_COLUNA 69

void InserirCaractere(char letra, Caractere ** atual, Linha ** linhaAtual, int * insert) {
	Caractere * novo = (Caractere *)malloc(sizeof(Caractere));
	int OP = *insert;
	novo->Letra = letra;
	novo->Proxima = NULL;
	novo->Anterior = NULL;
	if(OP == 1)
	{
		if ((*atual) == NULL)
		{
			*atual = novo;
			if ((*linhaAtual)->primeiro == NULL)
				(*linhaAtual)->primeiro = (*atual);
			else
			{
				novo->Proxima = (*linhaAtual)->primeiro;
				(*linhaAtual)->primeiro->Anterior = novo;
				(*linhaAtual)->primeiro = novo;
			}
		}
		else
		{
			if ((*atual)->Proxima == NULL) {
				(*atual)->Proxima = novo;
				novo->Anterior = (*atual);
				(*atual) = novo;
			}
			else
			{
				novo->Anterior = (*atual);
				novo->Proxima = (*atual)->Proxima;
				(*atual)->Proxima->Anterior = novo;
				(*atual)->Proxima = novo;
				(*atual) = novo;
			}
		}
	}
	else
	{
		if ((*atual) == NULL)
		{
			*atual = novo;
			if ((*linhaAtual)->primeiro == NULL)
				(*linhaAtual)->primeiro = (*atual);
			else
			{
				(*linhaAtual)->primeiro->Letra = letra;
				(*atual) = (*linhaAtual)->primeiro;
			}
		}
		else
		{
			if ((*atual)->Proxima == NULL) {
				(*atual)->Proxima = novo;
				novo->Anterior = (*atual);
				(*atual) = novo;
			}
			else
			{
				(*atual)->Proxima->Letra = letra;
				(*atual) = (*atual)->Proxima;
			}
	}
}
}



void InserirNovaLinha(Linha ** Texto, Linha ** linhaAtual, Caractere ** atual, int * posColuna) {
	Linha * novaLinha = (Linha *)malloc(sizeof(Linha));
	Caractere * QuebraLinha = (Caractere *)malloc(sizeof(Caractere));
	Caractere * QuebraLinhaAux = (Caractere *)malloc(sizeof(Caractere));
	Caractere * aux;
	int count, i = 0;

	novaLinha->primeiro = NULL;
	novaLinha->Anterior = NULL;
	novaLinha->Proxima = NULL;

	QuebraLinha->Letra = '\n';
	QuebraLinha->Anterior = NULL;
	QuebraLinha->Proxima = NULL;

	QuebraLinhaAux->Letra = '\n';
	QuebraLinhaAux->Anterior = NULL;
	QuebraLinhaAux->Proxima = NULL;

	if ((*atual) == NULL)
	{
		if ((*linhaAtual)->Anterior == NULL)
			*Texto = novaLinha;

		novaLinha->primeiro = QuebraLinha;
		novaLinha->Anterior = (*linhaAtual)->Anterior;
		novaLinha->Proxima = (*linhaAtual);
		if ((*linhaAtual)->Anterior != NULL)
			(*linhaAtual)->Anterior->Proxima = novaLinha;
		(*linhaAtual)->Anterior = novaLinha;

	}
	else
	{
		QuebraLinha->Anterior = (*atual);
		QuebraLinha->Proxima = NULL;

		novaLinha->primeiro = (*atual)->Proxima;
		if (novaLinha->primeiro != NULL)
			novaLinha->primeiro->Anterior = NULL;

		(*atual)->Proxima = QuebraLinha;

		novaLinha->Anterior = (*linhaAtual);
		novaLinha->Proxima = (*linhaAtual)->Proxima;

		if ((*linhaAtual)->Proxima != NULL)
            {
			(*linhaAtual)->Proxima->Anterior = novaLinha;
			count = CountCaracteresLine(novaLinha);
			for (aux = novaLinha->primeiro; i < (count - 1); i++){
                        aux = aux->Proxima;
			}
			aux->Proxima = QuebraLinhaAux;
            QuebraLinhaAux->Anterior = aux;
            }



		(*linhaAtual)->Proxima = novaLinha;
		(*atual) = NULL;

		(*linhaAtual) = novaLinha;
	}
}

int DeletarCaractereAtual(Linha **linhaAtual, Caractere **caracterAtual, int * LinhaAtual, int * ColunaAtual) {
	Caractere *toDelete = (*caracterAtual);
	if (toDelete == NULL){
		ConcatenarBackspace(linhaAtual, caracterAtual, LinhaAtual, ColunaAtual);
		return DELETE_CONCATENADO;
	}
	else{
		if (toDelete->Proxima != NULL && toDelete->Anterior != NULL)
		{
			toDelete->Anterior->Proxima = toDelete->Proxima;
			toDelete->Proxima->Anterior = toDelete->Anterior;
			(*caracterAtual) = toDelete->Anterior;
			free(toDelete);
		}
		else if (toDelete->Proxima == NULL && toDelete->Anterior == NULL)
		{
			(*linhaAtual)->primeiro = NULL;
			(*caracterAtual) = NULL;
			free(toDelete);
		}
		else if (toDelete->Proxima == NULL) {
			toDelete->Anterior->Proxima = NULL;
			(*caracterAtual) = toDelete->Anterior;
			free(toDelete);
		}
		else if (toDelete->Anterior == NULL) {
			toDelete->Proxima->Anterior = NULL;
			(*linhaAtual)->primeiro = toDelete->Proxima;
			(*caracterAtual) = NULL;
			free(toDelete);
		}
	}
	return DELETE_SUCESS;
}

void ConcatenarBackspace(Linha ** linhaAtual, Caractere ** caractereAtual, int * LinhaAtual, int * ColunaAtual) {
	int count, countAux, i = 0;
	Caractere * ToDelete;
	Caractere * aux1;
	Caractere * QuebraLinha = (Caractere *)malloc(sizeof(Caractere));
	Linha * lAux1 = (*linhaAtual)->Anterior;
	QuebraLinha->Letra = '\n';
	QuebraLinha->Anterior = NULL;
	QuebraLinha->Proxima = NULL;

	if (lAux1 == NULL)
		return;

	count = CountCaracteresLine(lAux1);
	for (ToDelete = lAux1->primeiro; i < (count - 1); i++)
		ToDelete = ToDelete->Proxima;
	(*caractereAtual) = ToDelete;

	if (CountCaracteresLine((*linhaAtual)) == 0) {
		DeletarLinhaBackspace(linhaAtual, caractereAtual, LinhaAtual, ColunaAtual);
		return;
	}
	/*if (CountCaracteresLine(lAux1) == 0) {
			DeletarLinhaBackspace(&lAux1, caractereAtual, LinhaAtual, ColunaAtual);
			(*LinhaAtual)--;
			(*ColunaAtual) = count;
			return;
	}*/

	free(ToDelete->Proxima);
	ToDelete->Proxima = (*linhaAtual)->primeiro;

	if ((*linhaAtual)->primeiro != NULL)
		(*linhaAtual)->primeiro->Anterior = ToDelete;
	i = 0;
	countAux = CountCaracteresLine(lAux1);
	if(countAux > MAX_COLUNA){
	for (aux1 = lAux1->primeiro; i < MAX_COLUNA; i++)
		aux1 = aux1->Proxima;
	}
	(*linhaAtual)->primeiro = aux1->Proxima;
	(*linhaAtual)->primeiro->Anterior = NULL;
	aux1->Proxima = QuebraLinha;
	QuebraLinha->Anterior = aux1;

	for (aux1 = lAux1->primeiro; i < MAX_COLUNA; i++){
		if (aux1 == (*caractereAtual)){
			countAux = i;
			break;
		}
		aux1 = aux1->Proxima;
	}

	//lAux->Proxima = (*linhaAtual)->Proxima;
	if (CountCaracteresLine((*linhaAtual)) == 0) {
		DeletarLinhaBackspace(linhaAtual, caractereAtual, LinhaAtual, ColunaAtual);
		return;
	}
	(*LinhaAtual)--;
	(*ColunaAtual) = count;
	(*linhaAtual) = lAux1;
}

void DeletarLinhaBackspace(Linha ** linhaAtual, Caractere ** caracterAtual, int * LinhaAtual, int * ColunaAtual) {
	Linha * toDelete = (*linhaAtual);
	Linha * lAux1 = (*linhaAtual)->Anterior;
	Caractere * cToDelete, * aux1;
	int count, i = 0;

	if ((*linhaAtual)->primeiro != NULL)
		free(toDelete->primeiro);

	(*linhaAtual) = toDelete->Anterior;

	(*linhaAtual)->Proxima = toDelete->Proxima;
	if (toDelete->Proxima != NULL) {
		toDelete->Proxima->Anterior = (*linhaAtual);
		if ((*linhaAtual)->primeiro->Letra == '\n')
			(*caracterAtual) = NULL;

	}
	else
	{
		count = CountCaracteresLine((*linhaAtual));
		for (cToDelete = (*linhaAtual)->primeiro; i < (count - 1); i++)
			cToDelete = cToDelete->Proxima;
		if (cToDelete->Letra == '\n')
		{
			free(cToDelete);
			(*linhaAtual)->primeiro = NULL;
			(*caracterAtual) = NULL;
		}
		else
		{
			free(cToDelete->Proxima);
			cToDelete->Proxima = NULL;
		}
	}
	for (aux1 = lAux1->primeiro; i < MAX_COLUNA; i++){
		if (aux1 == (*caracterAtual)){
			count = i+1;
			break;
		}
		aux1 = aux1->Proxima;
	}
	free(toDelete);

	(*LinhaAtual)--;
	(*ColunaAtual) = count;
}

int DeletarProximoCaractere(Linha ** linhaAtual, Caractere ** caracterAtual, Caractere ** prox) {
	Caractere * toDelete;
	Linha * lAux, *lAuxToDelete;
	lAux = (*linhaAtual);
	lAuxToDelete = lAux->Proxima;
	toDelete = (*caracterAtual);

	if (toDelete == NULL)
	{
		toDelete = lAux->primeiro;
		lAux->primeiro = toDelete->Proxima;
		if (toDelete->Proxima != NULL)
			toDelete->Proxima->Anterior = lAux->primeiro;
		free(toDelete);

	}
	else if (lAux->Proxima != NULL)
	{
		if (toDelete->Proxima->Letra == '\n')
		{
			free(toDelete->Proxima);
			toDelete->Proxima = lAux->Proxima->primeiro;
			toDelete->Proxima->Anterior = toDelete;
			lAux->Proxima = lAuxToDelete->Proxima;
			free(lAuxToDelete);
		}
		else{
			toDelete = (*caracterAtual)->Proxima;
			(*caracterAtual)->Proxima = toDelete->Proxima;
			if (toDelete->Proxima != NULL)
				toDelete->Proxima->Anterior = (*caracterAtual);
			free(toDelete);
		}
	}
	else if (toDelete->Proxima != NULL)
	{
		toDelete = (*caracterAtual)->Proxima;
		(*caracterAtual)->Proxima = toDelete->Proxima;
		if (toDelete->Proxima != NULL)
			toDelete->Proxima->Anterior = (*caracterAtual);
		free(toDelete);
	}

	return DELETE_SUCESS;
}

int CountCaracteresLine(Linha * linhaAtual) {
	int i = 0;
	Caractere * aux = linhaAtual->primeiro;

	if (aux != NULL)
	{
		while (aux != NULL)
		{
			if (aux->Letra != '\n')
				i++;
			aux = aux->Proxima;
		}
	}
	return i;
}
