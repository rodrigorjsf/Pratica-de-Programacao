#include "teclas.h"
#include "file.h"

void MoverCursor(int x, int y);
void ImprimirTexto(Linha * Texto, Caractere * Atual, Linha * linhaAtual, char fileDir[]);
void QuebraLinhaAutomatica(Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * LinhaAtual, int * ColunaAtual, int qtdCaractere);
void OperarTeclaTeclado(Keyboard keyboard, int * LinhaAtual, int * ColunaAtual, Linha ** Texto, Caractere ** atual, Linha ** linhaAtual, FILE ** arq, char fileDir[]);
void EventoCharacter(char letra, int * LinhaAtual, int * ColunaAtual, Linha * Texto, Caractere ** atual, Linha ** linhaAtual);
void EventoLeftArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** linhaAtual);
void EventoEnter(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual);
void EventoRightArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** linhaAtual);
void EventoUpArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** linhaAtual);
void EventoDownArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** linhaAtual);
void EventoBackspace(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** linhaAtual);
void EventoDelete(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** linhaAtual);
void EventOpenFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual);
void EventSaveFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual);
void EventCloseEditor(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual);
