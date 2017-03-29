#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"
#include "Validacoes.h"
#include "Buscas.h"
#include "Tempoedata.h"
#include "Types.h"

void gerarMaiusculo (char nome[], TCliente * c)
{
	char maiusculo[100];
	int i, j = 0, cont = 0;
	for(i=0; nome[i]!= '\0'; i++){
		if (isalpha (nome[i]) != 0){
			maiusculo[j] = toupper(nome[i]);
			j++;
			cont = 0;
		}
		else if (cont < 1){
			maiusculo[j] = ' ';
			j++;
			cont++;
		}
	}
	maiusculo[j] = '\0';
	strcpy (c->nome,maiusculo);
}

int validaNome(char nome[]) {
	int i;

	for (i = 0; i < strlen(nome); i++) {
		if (nome[0] == '\n')
			return 0;
		else {
			return 1;
		}
		if (isalpha(nome[i]) == 0) {
			if (isspace(nome[i]) == 0)
				return 0;
		}
	}
	return 1;
}

int validaTelefone(char telefone[]) {
	int i;

	for (i = 0; i < strlen(telefone); i++) {
		if (telefone[i] == '\n') {
			return 1;
		}
		if (isdigit(telefone[i]) == 0) {
			return 0;
		}
	}
	return 1;
}

int validaEmail(char email[]) {
	int cont = -1, aux, auxArrobaPositon, i, j = 0;
	auxArrobaPositon = strlen(email);

	for (i = 0; i < strlen(email); i++) {
		/*if (email[i] == '\n') {

			return 1;
		}*/
		if (email[i] == '_'){
			aux = i;
			if (aux >= auxArrobaPositon)
				return 0;
		}
		else if (isalnum(email[i]) == 0) {
			if (email[i] != '.') {
				if (email[i] == '@' && j != 1) {
					auxArrobaPositon = i;
					j++;
				}
				else {
					return 0;
				}
				if (email[i] != '@') {//!arroba
					return 0;
				}
			}
		}
		cont++;
	}

	if (j == 0)
		return 0;

	return 1;
}

int RecebeCPF(char cpf[]){

	int validar;
	char op;
	validar = ValidaCPF (cpf);
	if (validar == 0)
	{
		printf("\nCPF invalido, deseja tentar denovo? (S/N) \n");
		do{
			op = getche();
			if (op != 78 && op != 83 && op != 110 && op != 115)
			{
				printf("Opcao invalida. Deseja recadastrar o CPF? (S/N) \n");
			}
			else if (op == 78 || op == 110)
				return 2;                             // se for invalido e nao deseja tentar novamente
			else
				return 0;                    //se for invalido e desejar tentar denovo
		}while(1);
	}
	else
		return 1;	                                               /////////// se for valido
}

void CadastrarNome (TCliente * c)
{
	char nome [100];
	int i, aux;
	do{
		i = 0;
		system("cls");
		printf("Digite o nome do cliente: \n");
		while(i < 99)
		{
			nome[i] = getche();
			if (i == 98)
				nome[i+1] = '\0';
			if (nome[i] == 13)
			{
				nome[i] = '\0';
				break;
			}
			i++;
		}
		aux = validaNome(nome);
		if (aux == 1){
			gerarMaiusculo(nome, c);
		}
		else{
			printf("\nNome invalido. Por favor, inserir nome valido. Enter pra continuar.\n");
			getch();
		}
	}while (aux == 0);
}

void CadastrarTelefone (TCliente * c)
{
	char tel[12];
	int i, aux;
	do{
		i = 0;
		system("cls");
		printf("Digite o telefone do cliente: \n");
		while(i < 11)
		{
			if (i == 0)
				printf ("(");
			tel[i] = getche();
			if (i == 1)
				printf (") ");
			if (i == 6)
				printf ("-");
			if (i == 10)
				tel[i+1] = '\0';
			i++;
		}
		aux = validaTelefone(tel);
		if (aux == 1)
			strcpy(c->telefone, tel);
		else{
			printf("\nTelefone invalido. Por favor, inserir numero valido. Enter pra continuar. \n");
			getch();
		}
	}while (aux == 0);
}

void CadastrarEmail (TCliente * c)
{
	char email[100];
	int i, aux;
	do{
		i = 0;
		system("cls");
		printf("Digite o e-mail do cliente: \n");
		while(i < 99)
		{
			email[i] = getche();
			if (i == 98)
				email[i+1] = '\0';
			if (email[i] == 13)
			{
				email[i] = '\0';
				break;
			}
			i++;
		}
		aux = validaEmail(email);
		if (aux == 1)
			strcpy(c->email, email);
		else{
			printf("\nE-Mail invalido. Por favor, inserir e-mail valido. Enter pra continuar.\n");
			getch();
		}
	}while(aux == 0);
}

void CadastrarCliente (FILE * arq, char cpf [])
{
	TCliente cliente;
	int aux;

	aux = BuscarCliente (arq, cpf);
	if (aux > -1){
		printf ("\nCliente ja cadastrado. \n");
		 system("pause");
	}
	else{

		int status;
		strcpy (cliente.cpf, cpf);
		cliente.status = 1;
		CadastrarNome (&cliente);
		CadastrarTelefone (&cliente);
		CadastrarEmail (&cliente);
		fseek (arq, 0, 2);
		status = fwrite(&cliente,sizeof(TCliente),1,arq);
		if (status != 1)
			printf ("\nErro de gravacao \n");
		else
			printf ("\nCliente cadastrado com sucesso \n");
		getch();
	}
}

void AlterarCliente(FILE * arq, char cpf []){
    TCliente cliente;
    int pos, status;
    char op;

    pos = BuscarCliente (arq, cpf);
    if (pos == -1){
        printf ("\nCliente nao cadastrado \n");
        system ("pause");
    }

    else if (pos == -2)
        printf ("Erro de leitura \n");
    else {
        fseek(arq, pos * sizeof (TCliente), 0);
        status = fread (&cliente,sizeof (TCliente), 1, arq);
    	do{
    		printf("\nEscolha o que deseja altrar: \n");
    		printf ("1 - Alterar nome \n");
    		printf ("2 - Alterar email \n");
    		printf ("3 - Alterar telefone \n");
    		printf ("4 - Sair \n");
    		printf ("informe a opcao: ");
    		op = getchar (); fflush (stdin);
    		switch (op) {
    		case '1':
    			CadastrarNome (&cliente);
    			break;
    		case '2':
    			CadastrarEmail (&cliente);
    			break;
    		case '3':
    			CadastrarTelefone (&cliente);
    			break;
        	case '4':
        		break;
        	default: printf("Opcao invalida. \n");
    		}
    	}while(op != '4');
    	fseek(arq, -sizeof(TCliente), 1);
    	status = fwrite (&cliente,sizeof (TCliente), 1, arq);
    	if (status != 1)
    		printf ("\nErro de gravacao \n");
    	else{
    		printf ("\nCliente alterado com sucesso \n");
    		system ("pause");
    	}
    }
}

void ExibirCliente (FILE * arq, char cpf []) {
	TCliente c;
	int i=0, pos, status;

	pos = BuscarCliente (arq, cpf);
	if (pos == -1){
		printf ("\nCliente nao cadastrado \n");
		system ("pause");
	}
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(arq, pos * sizeof (TCliente), 0);
		status = fread (&c,sizeof (TCliente), 1, arq);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
			printf ("\nNome: %s \n", c.nome);
			printf ("Fone: ");
			while(i < 11)
			{
				if (i == 0)
					printf ("(");
				printf ("%c", c.telefone[i]);
				if (i == 1)
					printf (") ");
				if (i == 6)
					printf ("-");
				i++;
			}
			printf ("\n");
			printf ("Email: %s \n", c.email);
			getch();
		}
	}
}

void RemoverCliente (FILE * arqPass, FILE * arqVoo,FILE * arq, char cpf []) {
	TCliente c;
	int pos, status, valida;

	pos = BuscarCliente (arq, cpf);
	if (pos == -1){
		printf ("\nCliente nao cadastrado \n");
		system ("pause");
	}
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(arq, pos * sizeof (TCliente), 0);
		status = fread (&c,sizeof (TCliente), 1, arq);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
                    valida = validaRemocao (arqPass,arqVoo,cpf);
                    if (valida == 1){
                        printf ("\nNao e possivel excluir esse cliente no momento. Ele ainda possui reseva para voos futuros. \n");
                        system ("pause");
                    }
                    else
                    {
                        c.status = 0;
                        fseek(arq, -sizeof(TCliente), 1);
                        status = fwrite (&c,sizeof (TCliente), 1, arq);
                        if (status != 1)
                            printf ("Erro de gravacao \n");
                        else{
                            printf ("\nCliente removido com sucesso \n");
                            system ("pause");
                        }
                    }
		}
	}
}

void MenuCliente (FILE * arqPassagem, FILE * arqVoo,FILE * arqCliente, char op)
{
	char auxCpf[12];
	int i, aux;
	if (op == '1')
	{
		do{
			i = 0;
			system ("cls");
			printf ("Informe o CPF do Cliente: ");
			while(i < 11){
				auxCpf[i] = getche();
				if (i == 2)
					printf (".");
				if (i == 5)
					printf (".");
				if (i == 8)
					printf ("-");
				if (i == 10)
					auxCpf[i+1] = '\0';
				i++;
			}
			aux = RecebeCPF(auxCpf);
		}while (aux == 0);
		if (aux == 2)
			return;
		else
			CadastrarCliente (arqCliente, auxCpf);
	}
	else if (op == '2')
	{
		do{
			i = 0;
			system ("cls");
			printf ("Informe o CPF do Cliente: ");
			while(i < 11){
				auxCpf[i] = getche();
				if (i == 2)
					printf (".");
				if (i == 5)
					printf (".");
				if (i == 8)
					printf ("-");
				if (i == 10)
					auxCpf[i+1] = '\0';
				i++;
			}
			aux = RecebeCPF(auxCpf);
		}while (aux == 0);
		if (aux == 2)
			return;
		else
			AlterarCliente (arqCliente, auxCpf);
	}
	else if (op == '3')
	{
		do{
			i = 0;
			system ("cls");
			printf ("Informe o CPF do Cliente: ");
			while(i < 11){
				auxCpf[i] = getche();
				if (i == 2)
					printf (".");
				if (i == 5)
					printf (".");
				if (i == 8)
					printf ("-");
				if (i == 10)
					auxCpf[i+1] = '\0';
				i++;
			}
			aux = RecebeCPF(auxCpf);
		}while (aux == 0);
		if (aux == 2)
			return;
		else
			ExibirCliente (arqCliente, auxCpf);
	}
	else
	{
		do{
			i = 0;
			system ("cls");
			printf ("Informe o CPF do Cliente: ");
			while(i < 11){
				auxCpf[i] = getche();
				if (i == 2)
					printf (".");
				if (i == 5)
					printf (".");
				if (i == 8)
					printf ("-");
				if (i == 10)
					auxCpf[i+1] = '\0';
				i++;
			}
			aux = RecebeCPF(auxCpf);
		}while (aux == 0);
		if (aux == 2)
			return;
		else
			RemoverCliente (arqPassagem,arqVoo,arqCliente, auxCpf);
	}
}




