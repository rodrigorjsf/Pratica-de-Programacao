#include "rotinas.h"

#include <stdio.h>
#include <stdlib.h>

void InserirCaractere(char letra, Caractere ** atual, Linha ** linhaAtual) {
	Caractere * novo = (Caractere *)malloc(sizeof(Caractere));
	novo->Letra = letra;
	novo->Proxima = NULL;
	novo->Anterior = NULL;

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

void InserirNovaLinha(Linha ** Texto, Linha ** linhaAtual, Caractere ** atual, int * posColuna) {
	Linha * novaLinha = (Linha *)malloc(sizeof(Linha));
	Caractere * QuebraLinha = (Caractere *)malloc(sizeof(Caractere));

	novaLinha->primeiro = NULL;
	novaLinha->Anterior = NULL;
	novaLinha->Proxima = NULL;

	QuebraLinha->Letra = '\n';
	QuebraLinha->Anterior = NULL;
	QuebraLinha->Proxima = NULL;

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
			(*linhaAtual)->Proxima->Anterior = novaLinha;

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
	int count, i = 0;
	Caractere * ToDelete;
	Linha * lAux = (*linhaAtual)->Anterior;
	if (lAux == NULL)
		return;

	count = CountCaracteresLine(lAux);

	for (ToDelete = lAux->primeiro; i < (count - 1); i++)
		ToDelete = ToDelete->Proxima;
	(*caractereAtual) = ToDelete;

	if (CountCaracteresLine((*linhaAtual)) == 0) {
		DeletarLinhaBackspace(linhaAtual, caractereAtual, LinhaAtual, ColunaAtual);
		return;
	}

	free(ToDelete->Proxima);
	ToDelete->Proxima = (*linhaAtual)->primeiro;

	if ((*linhaAtual)->primeiro != NULL)
		(*linhaAtual)->primeiro->Anterior = ToDelete;

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

	free(toDelete);

	(*LinhaAtual)--;
	(*ColunaAtual) = CountCaracteresLine((*linhaAtual));
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
