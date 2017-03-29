#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"
#include "Validacoes.h"
#include "Buscas.h"
#include "Tempoedata.h"
#include "Types.h"


void ModuloCliente (FILE * arqPassagem, FILE * arqVoo,FILE * arqCliente);
void ModuloPassagem (FILE * arqPassagem, FILE * arqVoo, FILE * arqCliente);
void ModuloVoo (FILE *arqPass, FILE *arqCliente, FILE * arqVoo );
void manutencao(FILE *arqCliente, FILE *arqVoo, FILE *arqPassagem);

int main () {
	system("color F0");
	char op, nomeArqum [] = "Cliente.dat", nomeArqdois [] = "Passagem.dat", nomeArqtres [] = "Voo.dat";
	FILE * arqCliente,*arqPassagem,*arqVoo;
	arqCliente = criarArquivo (nomeArqum);
	arqPassagem = criarArquivo (nomeArqdois);
	arqVoo = criarArquivo (nomeArqtres);
	atualizarVoos_e_Passagens (arqVoo,arqPassagem);
	arqPassagem = criarArquivo (nomeArqdois);
	arqVoo = criarArquivo (nomeArqtres);
	if (arqCliente == NULL || arqPassagem == NULL || arqVoo == NULL )
		printf ("Erro ao tentar criar/abrir arquivo \n");
	else {

	    do {
	       printf ("Consultar: \n");
	   	   printf ("1 - Modulo do Cliente \n");
	   	   printf ("2 - Modulo de Passagens \n");
		   printf ("3 - Modulo de Voos \n");
		   printf ("4 - Sair \n");
		   printf ("Digite a opcao: ");
		   op = getchar (); fflush (stdin);
		   switch (op) {
		   case '1': ModuloCliente (arqPassagem, arqVoo, arqCliente);
				     break;
		   case '2': ModuloPassagem (arqPassagem, arqVoo, arqCliente);
				     break;
		   case '3': ModuloVoo (arqPassagem, arqCliente, arqVoo);
				     break;
		   case '4': manutencao (arqCliente, arqVoo, arqPassagem);
		             break;
		   default: printf ("Opcao invalida \n");
		   }
		} while (op != '4');
	}
    return 0;
}

void ModuloCliente (FILE * arqPassagem, FILE * arqVoo,FILE * arqCliente){
	char op;
	do {
		system ("cls");
		printf ("-------------------- Modulo do Cliente -------------------- \n");
		printf ("1 - Cadastrar Cliente \n");
		printf ("2 - Alterar Cliente \n");
		printf ("3 - Exibir Cliente \n");
		printf ("4 - Remover Cliente \n");
		printf ("5 - Sair \n");
		printf ("informe a opcao: ");
		op = getchar (); fflush (stdin);
		switch (op) {
		case '1':
			MenuCliente (arqPassagem,arqVoo,arqCliente,op);
			break;
		case '2':
			MenuCliente (arqPassagem,arqVoo,arqCliente,op);
			break;
		case '3':
			MenuCliente (arqPassagem,arqVoo,arqCliente,op);
			break;
		case '4':
			MenuCliente (arqPassagem,arqVoo,arqCliente,op);
			break;
		case '5':
			break;
		default: printf ("Opcao invalida \n");
		}
	} while (op != '5');
}

void ModuloPassagem (FILE * arqPassagem, FILE * arqVoo, FILE * arqCliente){
	char op;
	do {
		system ("cls");
		printf ("-------------------- Modulo de Passagem -------------------- \n");
		printf ("1 - Comprar Passagem \n");
		printf ("2 - Consultar Passagens de Cliente \n");
		printf ("3 - Cancelar Passagem \n");
		printf ("4 - Consultar passageiro de um voo  \n");
		printf ("5 - Sair \n");
		printf ("informe a opcao: ");
		op = getchar (); fflush (stdin);
		switch (op) {
		case '1':
			MenuPassagem (arqPassagem,arqVoo,arqCliente,op);
			break;
		case '2':
			MenuPassagem (arqPassagem,arqVoo,arqCliente,op);
			break;
		case '3':
			MenuPassagem (arqPassagem,arqVoo,arqCliente,op);
			break;
		case '4':
			MenuPassagem (arqPassagem,arqVoo,arqCliente,op);
			break;
		case '5':
			break;
		default: printf ("Opcao invalida \n");
		}
	} while (op != '5');
}

void ModuloVoo (FILE *arqPass, FILE *arqCliente, FILE * arqVoo ){
	char op;
	do {
		system ("cls");
		printf ("-------------------- Modulo de Voo -------------------- \n");
		printf ("1 - Cadastrar Voo \n");
		printf ("2 - Procurar Voo \n");
		printf ("3 - Alterar Valor da Passagem \n");
		printf ("4 - Cancelar Voo \n");
		printf ("5 - Sair \n");
		printf ("informe a opcao: ");
		op = getchar (); fflush (stdin);
		switch (op) {
		case '1':
			MenuVOO (arqPass,arqCliente,arqVoo ,op);
			break;
		case '2':
			MenuVOO (arqPass,arqCliente,arqVoo ,op);
			break;
		case '3':
			MenuVOO (arqPass,arqCliente,arqVoo ,op);
			break;
		case '4':
			MenuVOO (arqPass,arqCliente,arqVoo ,op);
			break;
		case '5': break;
		default: printf ("Opcao invalida \n");
		}
	} while (op != '5');
}

int buscar (FILE * arq, char nomeAux[]) {
	int cont = -1, status;
	TCliente c;

	fseek (arq, 0, 0);
	while (1) {
		status = fread (&c, sizeof (TCliente), 1, arq);
		if (status != 1) {
			if (!feof(arq))
			    return -2; // erro de leitura
			else
				return -1; // nao achou
		}
		else {
			cont++;
			if (c.status == 1 && strcmp (c.nome, nomeAux) == 0)
				return cont;
		}
	}
}

void manutencao(FILE *arqCliente, FILE *arqVoo, FILE *arqPassagem)
{
    FILE *clienteTemp, *vooTemp;
    int status;
    TVoo v;
    TCliente c;
    //atualizarVoos_e_Passagens (arqVoo, arqPassagem);
    clienteTemp = fopen ("auxiliarCliente", "w+b");
    vooTemp = fopen ("auxiliarVoo", "w+b");
    if (clienteTemp == NULL || vooTemp == NULL) {
    	printf ("Erro ao executar o processo de manutenção do arquivo \n");
    	fclose (arqCliente);
    	fclose (arqVoo);
    	if(clienteTemp != NULL )
    		fclose (clienteTemp);
    	if(vooTemp != NULL)
    		fclose (vooTemp);
    }
    else
    {
    	fseek (arqCliente, 0, 0);
    	while (1)
    	{
    		status = fread (&c, sizeof (TCliente), 1, arqCliente);
    		if (status != 1) {
    			if (!feof(arqCliente)) {
    				printf ("Erro ao executar o processo de manutenção do arquivo \n");
    				fclose (arqCliente);
    				fclose (clienteTemp);
    				remove ("auxiliarCliente");
    				return;
    			}
    			else // fim de arquivo
    				break;
    		}
    		else {
    			if (c.status == 1) {
    				status = fwrite (&c, sizeof (TCliente), 1, clienteTemp);
    				if (status != 1) {
    					printf ("Erro ao executar o processo de manutenção do arquivo \n");
    					fclose (arqCliente);
    					fclose (clienteTemp);
    					remove ("auxiliarCliente");
    					return;
    				}
    			}
    		}
    	}
    	fseek (arqVoo, 0, 0);
    	while (1)
    	{
    		status = fread (&v, sizeof (TVoo), 1, arqVoo);
    		if (status != 1) {
    			if (!feof(arqVoo)) {
    				printf ("Erro ao executar o processo de manutenção do arquivo \n");
    				fclose (arqVoo);
    				fclose (vooTemp);
    				remove ("auxiliarVoo");
    				return;
    			}
    			else // fim de arquivo
    				break;
    		}
    		else {
    			if (v.status == 1) {
    				status = fwrite (&v, sizeof (TVoo), 1, vooTemp);
    				if (status != 1) {
    					printf ("Erro ao executar o processo de manutenção do arquivo \n");
    					fclose (arqVoo);
    					fclose (vooTemp);
    					remove ("auxiliarVoo");
    					return;
    				}
    			}
    		}
    	}
    	fclose (arqCliente);
    	fclose (arqVoo);
    	fclose (arqPassagem);
    	fclose (clienteTemp);
    	fclose (vooTemp);
    	remove ("Cliente.dat");
    	rename ("auxiliarCliente", "Cliente.dat");
    	remove ("Voo.dat");
    	rename ("auxiliarVoo", "Voo.dat");
    }
}

