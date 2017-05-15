#define DELETE_FAILURE 0
#define DELETE_SUCESS 1
#define DELETE_CONCATENADO 2

typedef struct TCaractere {
	char Letra;
	struct TCaractere * Proxima;
	struct TCaractere * Anterior;
}Caractere;


typedef struct TLinha {
	struct TLinha * Proxima;
	struct TLinha * Anterior;
	Caractere * primeiro;
}Linha;

void InserirCaractere(char letra, Caractere ** atual, Linha ** linhaAtual, int * insert);
void InserirNovaLinha(Linha ** Texto, Linha ** linhaAtual, Caractere ** atual, int * posColuna);
void ConcatenarBackspace(Linha **linhaAtual, Caractere **caractereAtual, int *LinhaAtual, int *ColunaAtual);
void DeletarLinhaBackspace(Linha ** linhaAtual, Caractere ** caracterAtual, int * LinhaAtual, int * ColunaAtual);
void DestruirTexto(Linha ** Texto, Linha ** linhaAtual, Caractere ** caracterAtual, int * LinhaAtual, int * ColunaAtual);
int DeletarCaractere(Linha ** linhaAtual, Caractere ** caractereAtual, Caractere ** caractereRemover);
int DeletarCaractereAtual(Linha **linhaAtual, Caractere **caracterAtual, int *LinhaAtual, int *ColunaAtual);
int DeletarProximoCaractere(Linha ** linhaAtual, Caractere ** caracterAtual, Caractere ** prox);
int CountCaracteresLine(Linha * linhaAtual);
