#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "editor.h"
#define FALSE 0
#define TRUE 1
#define WHITE 15
#define MAX_COLUNA 79
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char *argv[ ]){
	system ("cls");
	int LinhaAtualCont = 0;
	int ColunaAtualCont = 0;
	int insert = 1;
	char c; Linha * Texto = (Linha *)malloc(sizeof(Linha));
	Caractere * caractereAtual;
	Linha * linhaAtual;
	Keyboard keyboard;
	Texto->Anterior = NULL;
	Texto->primeiro = NULL;
	Texto->Proxima = NULL;
	caractereAtual = Texto->primeiro;
	linhaAtual = Texto;

	FILE * arquivo = NULL;
	char fileDir[30];
	strcpy(fileDir,argv[1]);
	arquivo = Abrir(fileDir);
	if (arquivo == NULL)
	{
		printf("\n\nCriando Arquivo");
		printf(".");
		Sleep(1000);
		printf(".");
		Sleep(1000);
		printf(".\n");
		arquivo = Criar(argv[1]);
		if (arquivo != NULL)
		{
			system("cls");
			printf("\n\nArquivo criado com sucesso!\n");
		}
	}
	else
	{
		printf("\nArquivo encontrado!");
		Sleep(2000);
		system("cls");
		printf("\n\nAbrindo Arquivo");
		printf(".");
		Sleep(1000);
		printf(".");
		Sleep(1000);
		printf(".");
		printf("\nArquivo Aberto com Sucesso!");
		c = fgetc(arquivo);
		while (!feof(arquivo))
		{
			MoverCursor(ColunaAtualCont, LinhaAtualCont);
			if (c != '\n')
			{
				keyboard.chave = c;
				keyboard.comando = 0;
			}
			else
			{
				keyboard.chave = 0;
				keyboard.comando = 0;
				if (CountCaracteresLine((linhaAtual)) < 79 && linhaAtual->primeiro != NULL)
					keyboard.comando = ENTER;
			}
			OperarTeclaTeclado(keyboard, &LinhaAtualCont, &ColunaAtualCont, &Texto, &caractereAtual, &linhaAtual, &arquivo, fileDir, &insert);
			c = fgetc(arquivo);
		}
	}

	while (1)
	{
		ImprimirTexto(Texto, caractereAtual, linhaAtual, fileDir, insert);
		MoverCursor(ColunaAtualCont, LinhaAtualCont);
		keyboard = GetUserInput();
		OperarTeclaTeclado(keyboard, &LinhaAtualCont, &ColunaAtualCont, &Texto, &caractereAtual, &linhaAtual, &arquivo, fileDir, &insert);
	}
}

void MoverCursor(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y + 2;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!SetConsoleCursorPosition(hConsole, coord))
		printf("Erro ao mover o cursor!");
}

void OperarTeclaTeclado(Keyboard keyboard, int * LinhaAtual, int * ColunaAtual, Linha ** Texto, Caractere ** caractereAtual, Linha ** linhaAtual, FILE ** arq, char fileDir[], int * insert)
{

	if (keyboard.comando == UP_ARROW)
		EventoUpArrow(LinhaAtual, ColunaAtual, caractereAtual, linhaAtual);
	else if (keyboard.comando == DOWN_ARROW)
		EventoDownArrow(LinhaAtual, ColunaAtual, caractereAtual, linhaAtual);
	else if (keyboard.comando == LEFT_ARROW)
		EventoLeftArrow(LinhaAtual, ColunaAtual, caractereAtual, linhaAtual);
	else if (keyboard.comando == RIGHT_ARROW)
		EventoRightArrow(LinhaAtual, ColunaAtual, caractereAtual, linhaAtual);
	else if (keyboard.comando == DEL)
		EventoDelete(LinhaAtual, ColunaAtual, caractereAtual, linhaAtual);
	else if (keyboard.comando == BACKSPACE)
		EventoBackspace(LinhaAtual, ColunaAtual, caractereAtual, linhaAtual);
	else if (keyboard.comando == INSERT)
			EventoInsert(insert);
	else if (keyboard.comando == ENTER)
		EventoEnter(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.comando == SAVE_FILE)
		EventSaveFile(arq, fileDir, Texto, linhaAtual, caractereAtual, ColunaAtual, LinhaAtual);
	else if (keyboard.comando == ESC)
		return;
	else if (keyboard.comando == CLOSE)
		EventCloseEditor(arq, fileDir, Texto, linhaAtual, caractereAtual, ColunaAtual, LinhaAtual);
	else if (keyboard.chave != 0)
		EventoCharacter(keyboard.chave, LinhaAtual, ColunaAtual, *Texto, caractereAtual, linhaAtual, insert);
}

void EventoLeftArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** linhaAtual)
{
	int i = 0;
	if ((*ColunaAtual) > 0)
	{
		(*ColunaAtual)--;
		(*caracterAtual) = (*caracterAtual)->Anterior;
	}
	else
	{
		if ((*linhaAtual)->Anterior != NULL)
		{
			(*LinhaAtual)--;
			(*linhaAtual) = (*linhaAtual)->Anterior;
			*ColunaAtual = CountCaracteresLine((*linhaAtual));
			for ((*caracterAtual) = (*linhaAtual)->primeiro; i < (*ColunaAtual); (*caracterAtual) = (*caracterAtual)->Proxima, i++);

			if ((*caracterAtual) != NULL)
			{
				if ((*caracterAtual)->Letra == '\n')
					(*caracterAtual) = (*caracterAtual)->Anterior;
			}
		}
	}
}

void EventoRightArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** linhaAtual)
{
	int qntCaracteres = CountCaracteresLine((*linhaAtual));
	if ((*ColunaAtual) < qntCaracteres)
	{
		(*ColunaAtual)++;
		if ((*caracterAtual) != NULL)
			(*caracterAtual) = (*caracterAtual)->Proxima;
		else
			(*caracterAtual) = (*linhaAtual)->primeiro;
	}
	else
	{
		if ((*linhaAtual)->Proxima != NULL)
		{
			(*LinhaAtual)++;
			(*linhaAtual) = (*linhaAtual)->Proxima;
			(*caracterAtual) = NULL;
			*ColunaAtual = 0;
		}
		else return;
	}
}

void EventoUpArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** linhaAtual)
{
	int countLinhaDestino, i = 0;
	if ((*LinhaAtual) <= 0)
		return;
	else if ((*caracterAtual) == NULL)
	{
		(*LinhaAtual)--;
		(*linhaAtual) = (*linhaAtual)->Anterior;
		(*caracterAtual) = NULL;
	}

	else
	{
		(*LinhaAtual)--;
		(*linhaAtual) = (*linhaAtual)->Anterior;
		countLinhaDestino = CountCaracteresLine((*linhaAtual));
		if ((*ColunaAtual) > countLinhaDestino)
		{
			for ((*caracterAtual) = (*linhaAtual)->primeiro; i < countLinhaDestino - 1; (*caracterAtual) = (*caracterAtual)->Proxima, i++);
			(*ColunaAtual) = countLinhaDestino;
		}
		else
		for ((*caracterAtual) = (*linhaAtual)->primeiro; i < (*ColunaAtual - 1); (*caracterAtual) = (*caracterAtual)->Proxima, i++);

		if ((*caracterAtual) != NULL)
		{
			if ((*caracterAtual)->Letra == '\n')
				(*caracterAtual) = (*caracterAtual)->Anterior;
		}
	}
}

void EventoDownArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** linhaAtual)
{
	int countLinhaDestino, i = 0;
	if ((*linhaAtual)->Proxima == NULL)
		return;
	else
	{
		(*LinhaAtual)++;
		countLinhaDestino = CountCaracteresLine((*linhaAtual)->Proxima);
		(*linhaAtual) = (*linhaAtual)->Proxima;
		if ((*ColunaAtual) > countLinhaDestino)
		{
			for ((*caracterAtual) = (*linhaAtual)->primeiro; i < countLinhaDestino - 1; (*caracterAtual) = (*caracterAtual)->Proxima, i++);

			(*ColunaAtual) = countLinhaDestino;
		}
		else if ((*caracterAtual) == NULL)
			return;
		else
		for ((*caracterAtual) = (*linhaAtual)->primeiro; i < (*ColunaAtual - 1); (*caracterAtual) = (*caracterAtual)->Proxima, i++);

		if ((*caracterAtual) != NULL)
		{
			if ((*caracterAtual)->Letra == '\n')
				(*caracterAtual) = (*caracterAtual)->Anterior;
		}
	}
}

void EventoEnter(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual)
{
	InserirNovaLinha(Texto, linhaAtual, atual, ColunaAtual);
	(*LinhaAtual)++;
	(*ColunaAtual) = 0;
}

void EventoBackspace(int * LinhaAtualCount, int * ColunaAtualCount, Caractere ** caracterAtual, Linha ** linhaAtual)
{
	if (DeletarCaractereAtual(linhaAtual, caracterAtual, LinhaAtualCount, ColunaAtualCount) == DELETE_SUCESS)
		(*ColunaAtualCount)--;

}

void EventoDelete(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** linhaAtual)
{
	DeletarProximoCaractere(linhaAtual, caracterAtual, &(*caracterAtual)->Proxima);
}

void EventoCharacter(char letra, int * LinhaAtual, int * ColunaAtual, Linha * Texto, Caractere ** atual, Linha ** linhaAtual, int * insert)
{
	InserirCaractere(letra, atual, linhaAtual, insert);
	(*ColunaAtual)++;
	QuebraLinhaAutomatica(&Texto, linhaAtual, atual, LinhaAtual, ColunaAtual, MAX_COLUNA);
}

void EventoInsert(int * insert)
{
	if (*insert == 1)
		*insert = 0;
	else
		*insert = 1;
}

void ImprimirTexto(Linha * Texto, Caractere * caractereAtual, Linha * linhaAtual, char fileDir[], int insert) {
	int qtdLinha = 0;
	char op[4];
	Linha * lAux = Texto;
	Caractere * cAux = NULL;
	system("cls");
	if (insert == 1)
		strcpy(op,"ON");
	else
		strcpy(op,"OFF");
	printf("INSERT: %s \n\n", op);

	while (lAux != NULL)
	{
		qtdLinha++;
		cAux = lAux->primeiro;


		while (cAux != NULL)
		{
			printf("%c", cAux->Letra);
			cAux = cAux->Proxima;
		}
		lAux = lAux->Proxima;
	}
}

void QuebraLinhaAutomatica(Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * LinhaAtual, int * ColunaAtual, int qtdCaractere) {
	int i = 0;
	if (CountCaracteresLine((*linhaAtual)) > qtdCaractere) {
		for ((*caractereAtual) = (*linhaAtual)->primeiro; i < qtdCaractere; i++)
			(*caractereAtual) = (*caractereAtual)->Proxima;
		InserirNovaLinha(Texto, linhaAtual, caractereAtual, ColunaAtual);
		(*ColunaAtual) = 0;
		(*LinhaAtual)++;
	}
}


void EventSaveFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual) {
	system("cls");
	if (Salvar(Texto, fileDir) == SUCESSO)
		printf("Arquivo salvo com sucesso!\n");
	else
		printf("Erro ao salvar o arquivo. Verifique se há permissão de escrita no disco.\n");
	system("pause");
}

void EventCloseEditor(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual)
{
	system("cls");
	char novamente;
	do{
		printf("\n\nDeseja salvar? (S/N) ");
		novamente = toupper(getchar());
	} while (novamente != 'N' && novamente != 'S');
	system("cls");
	if (novamente == 'S')
	{
		printf("Arquivo sendo salvo");
		printf(".");
		Sleep(1000);
		printf(".");
		Sleep(1000);
		printf(".\n");
		if (Salvar(Texto, fileDir) == SUCESSO)
			printf("Arquivo salvo com sucesso!\n");
		else
			printf("Erro ao salvar o arquivo!\n");
		Sleep(1000);
	}
	exit(0);
}

