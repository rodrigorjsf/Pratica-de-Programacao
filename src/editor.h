#include "teclas.h"
#include "file.h"

void MoverCursor(int x, int y);
void ImprimirTexto(Linha * Texto, Caractere * Atual, Linha * linhaAtual, char fileDir[]);
void QuebraLinhaAutomatica(Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * LinhaAtual, int * ColunaAtual, int qtdCaractere);
void OperarKeyboardInput(Keyboard keyboard, int * LinhaAtual, int * ColunaAtual, Linha ** Texto, Caractere ** atual, Linha ** linhaAtual, FILE ** arq, char fileDir[]);
void EventCharKey(char letra, int * LinhaAtual, int * ColunaAtual, Linha * Texto, Caractere ** atual, Linha ** linhaAtual);
void EventLeftArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual);
void EventEnter(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual);
void EventRightArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventUpArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventDownArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventBackspace(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventDelete(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventOpenFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual);
void EventSaveFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual);
void EventCloseEditor(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual);
