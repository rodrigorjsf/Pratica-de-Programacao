#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

void InserirCaractere(char letra, Caractere ** atual, Linha ** linhaAtual) {
	Caractere * novo = (Caractere *)malloc(sizeof(Caractere));
	novo->Letra = letra;
	novo->Proxima = NULL;
	novo->Anterior = NULL;

	if ((*atual) == NULL)
	{
		*atual = novo;
		if ((*linhaAtual)->Inicio == NULL)
			(*linhaAtual)->Inicio = (*atual);
		else
		{
			novo->Proxima = (*linhaAtual)->Inicio;
			(*linhaAtual)->Inicio->Anterior = novo;
			(*linhaAtual)->Inicio = novo;
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

void InserirNovaLinha(Linha ** Texto, Linha ** linhaAtual, Caractere ** atual, int * posColuna) {
	Linha * novaLinha = (Linha *)malloc(sizeof(Linha));
	Caractere * QuebraLinha = (Caractere *)malloc(sizeof(Caractere));

	novaLinha->Inicio = NULL;
	novaLinha->Anterior = NULL;
	novaLinha->Proxima = NULL;

	QuebraLinha->Letra = '\n';
	QuebraLinha->Anterior = NULL;
	QuebraLinha->Proxima = NULL;

	if ((*atual) == NULL)
	{
		if ((*linhaAtual)->Anterior == NULL)
			*Texto = novaLinha;

		novaLinha->Inicio = QuebraLinha;
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

		novaLinha->Inicio = (*atual)->Proxima;
		if (novaLinha->Inicio != NULL)
			novaLinha->Inicio->Anterior = NULL;

		(*atual)->Proxima = QuebraLinha;

		novaLinha->Anterior = (*linhaAtual);
		novaLinha->Proxima = (*linhaAtual)->Proxima;

		if ((*linhaAtual)->Proxima != NULL)
			(*linhaAtual)->Proxima->Anterior = novaLinha;

		(*linhaAtual)->Proxima = novaLinha;
		(*atual) = NULL;

		(*linhaAtual) = novaLinha;
	}
}

void ConcatenarBackspace(Linha ** linhaAtual, Caractere ** caractereAtual, int * LinhaAtual, int * ColunaAtual) {
	int count, i = 0;
	Caractere * ToDelete;
	Linha * lAux = (*linhaAtual)->Anterior;
	if (lAux == NULL)
		return;

	count = CountCaracteresLine(lAux);

	for (ToDelete = lAux->Inicio; i < (count - 1); ToDelete = ToDelete->Proxima, i++);
	(*caractereAtual) = ToDelete;

	if (CountCaracteresLine((*linhaAtual)) == 0) {
		DeletarLinhaBackspace(linhaAtual, caractereAtual, LinhaAtual, ColunaAtual);
		return;
	}

	free(ToDelete->Proxima);
	ToDelete->Proxima = (*linhaAtual)->Inicio;

	if ((*linhaAtual)->Inicio != NULL)
		(*linhaAtual)->Inicio->Anterior = ToDelete;

	lAux->Proxima = (*linhaAtual)->Proxima;

	(*LinhaAtual)--;
	(*ColunaAtual) = count;

	free((*linhaAtual));
	(*linhaAtual) = lAux;
}

void DeletarLinhaBackspace(Linha ** linhaAtual, Caractere ** caracterAtual, int * LinhaAtual, int * ColunaAtual) {
	Linha * toDelete = (*linhaAtual);
	Caractere * cToDelete;
	int count, i = 0;

	if ((*linhaAtual)->Inicio != NULL)
		free(toDelete->Inicio);

	(*linhaAtual) = toDelete->Anterior;

	(*linhaAtual)->Proxima = toDelete->Proxima;
	if (toDelete->Proxima != NULL) {
		toDelete->Proxima->Anterior = (*linhaAtual);
		if ((*linhaAtual)->Inicio->Letra == '\n')
			(*caracterAtual) = NULL;

	}
	else
	{
		count = CountCaracteresLine((*linhaAtual));
		for (cToDelete = (*linhaAtual)->Inicio; i < (count - 1); cToDelete = cToDelete->Proxima, i++);
		if (cToDelete->Letra == '\n')
		{
			free(cToDelete);
			(*linhaAtual)->Inicio = NULL;
			(*caracterAtual) = NULL;
		}
		else
		{
			free(cToDelete->Proxima);
			cToDelete->Proxima = NULL;
		}
	}

	free(toDelete);

	(*LinhaAtual)--;
	(*ColunaAtual) = CountCaracteresLine((*linhaAtual));
}

void DestruirTexto(Linha ** Texto, Linha ** linhaAtual, Caractere ** caracterAtual, int * LinhaAtual, int * ColunaAtual) {
	Linha * lAux, *lAuxProx;
	Caractere * cAux, *cAuxProx;
	lAux = (*Texto);
	while (lAux != NULL)
	{
		lAuxProx = lAux->Proxima;
		cAux = lAux->Inicio;
		while (cAux != NULL)
		{
			cAuxProx = cAux->Proxima;
			free(cAux);
			cAux = cAuxProx;
		}
		free(lAux);
		lAux = lAuxProx;
	}
	(*Texto) = (Linha *)malloc(sizeof(Linha));
	(*Texto)->Anterior = NULL;
	(*Texto)->Proxima = NULL;
	(*Texto)->Inicio = NULL;
	(*linhaAtual) = (*Texto);
	(*caracterAtual) = NULL;
	(*LinhaAtual) = 0;
	(*ColunaAtual) = 0;
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
			(*linhaAtual)->Inicio = NULL;
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
			(*linhaAtual)->Inicio = toDelete->Proxima;
			(*caracterAtual) = NULL;
			free(toDelete);
		}
	}
	return DELETE_SUCESS;
}

int DeletarProximoCaractere(Linha ** linhaAtual, Caractere ** caracterAtual, Caractere ** prox) {
	Caractere * toDelete;
	Linha * lAux, *lAuxToDelete;
	lAux = (*linhaAtual);
	lAuxToDelete = lAux->Proxima;
	toDelete = (*caracterAtual);

	if (toDelete == NULL)
	{
		toDelete = lAux->Inicio;
		lAux->Inicio = toDelete->Proxima;
		if (toDelete->Proxima != NULL)
			toDelete->Proxima->Anterior = lAux->Inicio;
		free(toDelete);

	}
	else if (lAux->Proxima != NULL)
	{
		if (toDelete->Proxima->Letra == '\n')
		{
			free(toDelete->Proxima);
			toDelete->Proxima = lAux->Proxima->Inicio;
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
	Caractere * aux = linhaAtual->Inicio;

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
