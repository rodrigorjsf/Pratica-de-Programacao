#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "editor.h"
#define FALSE 0
#define TRUE 1
#define WHITE 15
#define MAX_COLUNA 68
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char *argv[ ]){
	int LinhaAtual = 0;
	int ColunaAtual = 0, i = 0;
	char c; Linha * Texto = (Linha *)malloc(sizeof(Linha));
	Caractere * caractereAtual;
	Linha * linhaAtual;
	Keyboard keyboard;
	Texto->Anterior = NULL;
	Texto->Inicio = NULL;
	Texto->Proxima = NULL;
	caractereAtual = Texto->Inicio;
	linhaAtual = Texto;

	FILE * arquivo = NULL;
	char fileDir[30];
	strcpy(argv[1],fileDir);
	arquivo = Abrir(argv[1]);
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
		printf("\nO Arquivo encontrado!");
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
		while (!feof(arquivo)) {
			MoverCursor(ColunaAtual, LinhaAtual);
			if (c != '\n')
			{
				keyboard.Key = c;
				keyboard.Command = 0;
			}
			else
			{
				keyboard.Key = 0;
				keyboard.Command = 0;
				if (CountCaracteresLine((linhaAtual)) < 68 && linhaAtual->Inicio != NULL)
					keyboard.Command = ENTER;
			}
			OperarKeyboardInput(keyboard, &LinhaAtual, &ColunaAtual, &Texto, &caractereAtual, &linhaAtual, &arquivo, fileDir);
			c = fgetc(arquivo);
		}
	}

	while (1)
	{
		ImprimirTexto(Texto, caractereAtual, linhaAtual, fileDir);
		MoverCursor(ColunaAtual, LinhaAtual);
		keyboard = GetUserInput();
		OperarKeyboardInput(keyboard, &LinhaAtual, &ColunaAtual, &Texto, &caractereAtual, &linhaAtual, &arquivo, fileDir);
	}
}

void MoverCursor(int x, int y) {
	COORD coord;
	coord.X = x + 6;
	coord.Y = y + 1;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!SetConsoleCursorPosition(hConsole, coord))
		printf("Erro ao mover o cursor!");
}

void OperarKeyboardInput(Keyboard keyboard, int * LinhaAtual, int * ColunaAtual, Linha ** Texto, Caractere ** caractereAtual, Linha ** linhaAtual, FILE ** arq, char fileDir[]) {

	if (keyboard.Command == UP_ARROW)
		EventUpArrow(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == DOWN_ARROW)
		EventDownArrow(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == LEFT_ARROW)
		EventLeftArrow(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == RIGHT_ARROW)
		EventRightArrow(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == DEL)
		EventDelete(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == BACKSPACE)
		EventBackspace(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == ENTER)
		EventEnter(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == SAVE_FILE)
		EventSaveFile(arq, fileDir, Texto, linhaAtual, caractereAtual, ColunaAtual, LinhaAtual);
	else if (keyboard.Command == OPEN_FILE)
		EventOpenFile(arq, fileDir, Texto, linhaAtual, caractereAtual, ColunaAtual, LinhaAtual);
	else if (keyboard.Command == ESC)
		return;
	else if (keyboard.Command == CLOSE)
		EventCloseEditor(arq, fileDir, Texto, linhaAtual, caractereAtual, ColunaAtual, LinhaAtual);
	else if (keyboard.Key != 0)
		EventCharKey(keyboard.Key, LinhaAtual, ColunaAtual, *Texto, caractereAtual, linhaAtual);
}

void EventLeftArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual){
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
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < (*ColunaAtual); (*caracterAtual) = (*caracterAtual)->Proxima, i++);

			if ((*caracterAtual) != NULL)
			{
				if ((*caracterAtual)->Letra == '\n')
					(*caracterAtual) = (*caracterAtual)->Anterior;
			}
		}
	}
}

void EventRightArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	int qntCaracteres = CountCaracteresLine((*linhaAtual));
	if ((*ColunaAtual) < qntCaracteres)
	{
		(*ColunaAtual)++;
		if ((*caracterAtual) != NULL)
			(*caracterAtual) = (*caracterAtual)->Proxima;
		else
			(*caracterAtual) = (*linhaAtual)->Inicio;
	}
	else
	{
		if ((*linhaAtual)->Proxima != NULL) {
			(*LinhaAtual)++;
			(*linhaAtual) = (*linhaAtual)->Proxima;
			(*caracterAtual) = NULL;
			*ColunaAtual = 0;
		}
		else return;
	}
}

void EventUpArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	int countLinhaDestino, i = 0;
	if ((*LinhaAtual) <= 0)
		return;
	else if ((*caracterAtual) == NULL) {
		(*LinhaAtual)--;
		(*linhaAtual) = (*linhaAtual)->Anterior;
		(*caracterAtual) = NULL;
	}

	else
	{
		(*LinhaAtual)--;
		(*linhaAtual) = (*linhaAtual)->Anterior;
		countLinhaDestino = CountCaracteresLine((*linhaAtual));
		if ((*ColunaAtual) > countLinhaDestino) {
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < countLinhaDestino - 1; (*caracterAtual) = (*caracterAtual)->Proxima, i++);
			(*ColunaAtual) = countLinhaDestino;
		}
		else
		for ((*caracterAtual) = (*linhaAtual)->Inicio; i < (*ColunaAtual - 1); (*caracterAtual) = (*caracterAtual)->Proxima, i++);

		if ((*caracterAtual) != NULL)
		{
			if ((*caracterAtual)->Letra == '\n')
				(*caracterAtual) = (*caracterAtual)->Anterior;
		}
	}
}

void EventDownArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	int countLinhaDestino, i = 0;
	if ((*linhaAtual)->Proxima == NULL)
		return;
	else
	{
		(*LinhaAtual)++;
		countLinhaDestino = CountCaracteresLine((*linhaAtual)->Proxima);
		(*linhaAtual) = (*linhaAtual)->Proxima;
		if ((*ColunaAtual) > countLinhaDestino) {
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < countLinhaDestino - 1; (*caracterAtual) = (*caracterAtual)->Proxima, i++);

			(*ColunaAtual) = countLinhaDestino;
		}
		else if ((*caracterAtual) == NULL)
			return;
		else
		for ((*caracterAtual) = (*linhaAtual)->Inicio; i < (*ColunaAtual - 1); (*caracterAtual) = (*caracterAtual)->Proxima, i++);

		if ((*caracterAtual) != NULL)
		{
			if ((*caracterAtual)->Letra == '\n')
				(*caracterAtual) = (*caracterAtual)->Anterior;
		}
	}
}

void EventEnter(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual) {
	InserirNovaLinha(Texto, linhaAtual, atual, ColunaAtual);
	(*LinhaAtual)++;
	(*ColunaAtual) = 0;
}

void EventBackspace(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	if (DeletarCaractereAtual(linhaAtual, caracterAtual, LinhaAtual, ColunaAtual) == DELETE_SUCESS)
		(*ColunaAtual)--;

}

void EventDelete(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	DeletarProximoCaractere(linhaAtual, caracterAtual, &(*caracterAtual)->Proxima);
}

void EventCharKey(char letra, int * LinhaAtual, int * ColunaAtual, Linha * Texto, Caractere ** atual, Linha ** linhaAtual) {
	InserirCaractere(letra, atual, linhaAtual);
	(*ColunaAtual)++;
	QuebraLinhaAutomatica(&Texto, linhaAtual, atual, LinhaAtual, ColunaAtual, MAX_COLUNA);
}

void ImprimirTexto(Linha * Texto, Caractere * caractereAtual, Linha * linhaAtual, char fileDir[]) {
	int qtdLinha = 0;
	Linha * lAux = Texto;
	Caractere * cAux = NULL;
	system("cls");

	printf("\n");

	while (lAux != NULL)
	{

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (lAux == linhaAtual) ? WHITE : WHITE);
		qtdLinha++;
		cAux = lAux->Inicio;
		printf("%4i. ", qtdLinha);

		while (cAux != NULL)
		{

			(caractereAtual == cAux ? printf("%c", (cAux->Letra)) : printf("%c", cAux->Letra));

			cAux = cAux->Proxima;
		}
		lAux = lAux->Proxima;
	}
}

void QuebraLinhaAutomatica(Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * LinhaAtual, int * ColunaAtual, int qtdCaractere) {
	int i = 0;
	if (CountCaracteresLine((*linhaAtual)) > qtdCaractere) {
		for ((*caractereAtual) = (*linhaAtual)->Inicio; i < qtdCaractere; i++, (*caractereAtual) = (*caractereAtual)->Proxima);
		InserirNovaLinha(Texto, linhaAtual, caractereAtual, ColunaAtual);
		(*ColunaAtual) = 0;
		(*LinhaAtual)++;
	}
}

void EventOpenFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual) {
	char letra;
	system("cls");
	(*arq) = NULL;
	while ((*arq) == NULL)
	{
		printf("Informe o diretorio e o nome do arquivo:\n>>");
		gets(fileDir); fflush(stdin);
		(*arq) = Abrir(fileDir);
	}
	DestruirTexto(Texto, linhaAtual, caractereAtual, LinhaAtual, ColunaAtual);
	fseek((*arq), 0, 0);
	do
	{
		if (fread(&letra, sizeof(char), 1, (*arq)) == 1) {
			if (letra == '\n') {
				InserirNovaLinha(Texto, linhaAtual, caractereAtual, ColunaAtual);
				(*LinhaAtual)++;
				(*ColunaAtual) = 0;
			}
			else
			{
				InserirCaractere(letra, caractereAtual, linhaAtual);
				(*ColunaAtual)++;
			}
		}
	} while (!feof(*arq));
}

void EventSaveFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual) {
	system("cls");
	if (strcmp(fileDir, "") == 0){
		printf("Informe o nome do arquivo:\n>>");
		gets(fileDir); fflush(stdin);
	}
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
	printf("\n\n\t\t\t\t* * * Obrigado por utilizar nossa tecnologia * * *\n\n");
	Sleep(2000);
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

