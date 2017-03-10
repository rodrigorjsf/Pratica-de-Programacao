#include "HeaderCliente.h"

void CadastrarCliente (FILE * arq)
{
	TCliente cliente;
	int aux, i, validar,sair = 0;
	char cpf[12],op;
	do
	{
		do{
			i = 0;
			system ("cls");
			printf ("Informe o cpf do Cliente: ");
			while(i <= 11){
				cpf[i] = getche();
				if (i == 2)
					printf (".");
				if (i == 5)
					printf (".");
				if (i == 8)
					printf ("-");
				if (i == 11)
					cpf[12] = '\0';
				if (cpf[i] < 48 || cpf[i] > 57) /////////////////////////////////////////////
					{
					printf ("Informe uma sequencia de 11 numeros sem espacos entre eles.");
					system ("pause");
					break;
					}
				else
					i++;
			}
		}while (strlen(cpf) != 11)
		i = 0;
		while(i <= strlen(cpf))
		{
			if ((cpf[i] < 48 || cpf[i] > 57) && cpf[i] != '\0')
			{
				printf("CPF digitado nao e valido! \n");
				break;
			}
			i++
		}
		validar = ValidaCPF (cpf);
		if (validar == 0)
		{

			printf("CPF invalido, deseja tentar denovo? (S/N) \n");
			do{
			op = getche();
			if (op != 78 && op != 83 && op != 110 && op != 115)
			{
				printf("Opcao invalida. Deseja recadastrar o CPF? (S/N) \n");
			}
			else if (op == 78 || op == 110){
				sair = 1;
				break;
			}
			else
				break;
			}while();
		}
	}while (validar == 0 || sair == 1);
	if (sair == 1)
		return;
	else
	{
		aux = BuscarCliente (arq, cpf);
		if (aux > -1)
			printf ("Cliente ja cadastrado. \n");
		else{
			char nome [100], tel[11], email[100];
			int status;
			strcpy (cliente.cpf, cpf);
			cliente.status = 1;
			do{
				printf("Digite o nome do cliente: \n");
				fgets (nome, sizeof(nome), stdin);
				if (ValidaNome(nome) == 1)
					strcpy(cliente.nome, nome);
				else
					printf("Nome invalido. Por favor, inserir nome valido. \n");
			}while (ValidaNome(nome) == 0);
			do{
				printf("Digite o telefone do cliente: \n");
				fgets (tel, sizeof(tel), stdin);
				if (ValidaTelefone(tel) == 1)
					strcpy(cliente.telefone, tel);
				else
					printf("Telefone invalido. Por favor, inserir numero valido. \n");
			}while (ValidaTelefone(tel) == 0);
			do{
				printf("Digite o e-mail do cliente: \n");
				fgets (email, sizeof(email), stdin);
				if (ValidaEmail(email) == 1)
					strcpy(cliente.email, email);
				else
					printf("E-Mail invalido. Por favor, inserir e-mail valido. \n");
			}while(ValidaEmail(email) == 0);
			status = fwrite(&cliente,sizeof(TCliente),1,arq);
			if (status != 1)
				printf ("Erro de gravacao \n");
			else
				printf ("Cliente cadastrado com sucesso \n");
			system ("pause");
		}
	}
}

int BuscarCliente (FILE * arq, char cpf [])
{
	int cont = -1, status;
		TCliente c;

		fseek (arq, 0, 0);
		while (1)
		{
			status = fread (&c, sizeof (TCliente), 1, arq);
			if (status != 1)
			{
				if (!feof(arq))
				    return -2; // erro de leitura
				else
					return -1; // nao achou
			}
			else
			{
				cont++;
				if (c.status == 1 && strcmp (c.nome, cpf) == 0)
					return cont;
			}
		}
}


int ValidaCPF (char cpf[]){
	int icpf[12];
	int i,soma=0,digito1,result1,result2,digito2,valor;

	printf("Digite o cpf: ");
	scanf(" %s",cpf);
	for(i=0;i<11;i++)  //Efetua a conversao de array de char para um array de int.
	{
		icpf[i]=cpf[i]-48;
	}
	for(i=0;i<9;i++)  //PRIMEIRO DIGITO.
	{
		soma+=icpf[i]*(10-i);
	}
	result1=soma%11;
	if( (result1==0) || (result1==1) )
	{
		digito1=0;
	}
	else
	{
		digito1 = 11-result1;
	}
	soma=0;
	for(i=0;i<10;i++)  //SEGUNDO DIGITO.
	{
		soma+=icpf[i]*(11-i);
	}
	valor=(soma/11)*11;
	result2=soma-valor;
	if( (result2==0) || (result2==1) )
	{
		digito2=0;
	}
	else
	{
		digito2=11-result2;
	}
	if((digito1==icpf[9]) && (digito2==icpf[10]))   //RESULTADOS DA VALIDACAO.
	{
		printf("\nCPF VALIDADO.\n");
		return 1;                       // retorna 1 para valido
	}
	else
	{
		printf("Problema com os digitos. CPF invalido.\n");
	}
	return 0;      // retorna 0 para cpf invalido
}
--------------------------------------------------------------------------------------------------------------------------------------
#include "HeaderCliente.h"

void CadastrarCliente (FILE * arq)
{
	TCliente cliente;
	int aux, i, validar,sair = 0;
	char cpf[12],op;
	do
	{
		do{
			i = 0;
			system ("cls");
			printf ("Informe o cpf do Cliente: ");
			while(i <= 11){
				cpf[i] = getche();
				if (i == 2)
					printf (".");
				if (i == 5)
					printf (".");
				if (i == 8)
					printf ("-");
				if (i == 11)
					cpf[12] = '\0';

			}
		}while (strlen(cpf) != 11);
		i = 0;
		validar = ValidaCPF (cpf);
		if (validar == 0)
		{

			printf("CPF invalido, deseja tentar denovo? (S/N) \n");
			do{
			op = getche();
			if (op != 78 && op != 83 && op != 110 && op != 115)
			{
				printf("Opcao invalida. Deseja recadastrar o CPF? (S/N) \n");
			}
			else if (op == 78 || op == 110){
				sair = 1;
				break;
			}
			else
				break;
			}while(1);
		}
	}while (validar == 0 || sair != 1);
	if (sair == 1)
		return;
	else
	{                                                /////////// ate aqui validacao cpf
		aux = BuscarCliente (arq, cpf);
		if (aux > -1)
			printf ("Cliente ja cadastrado. \n");
		else{
			char nome [100], tel[11], email[100];
			int status;
			strcpy (cliente.cpf, cpf);
			cliente.status = 1;
			do{
				printf("Digite o nome do cliente: \n");
				fgets (nome, sizeof(nome), stdin);
				if (ValidaNome(nome) == 1)
					strcpy(cliente.nome, nome);
				else
					printf("Nome invalido. Por favor, inserir nome valido. \n");
			}while (ValidaNome(nome) == 0);
			do{
				printf("Digite o telefone do cliente: \n");
				fgets (tel, sizeof(tel), stdin);
				if (ValidaTelefone(tel) == 1)
					strcpy(cliente.telefone, tel);
				else
					printf("Telefone invalido. Por favor, inserir numero valido. \n");
			}while (ValidaTelefone(tel) == 0);
			do{
				printf("Digite o e-mail do cliente: \n");
				fgets (email, sizeof(email), stdin);
				if (ValidaEmail(email) == 1)
					strcpy(cliente.email, email);
				else
					printf("E-Mail invalido. Por favor, inserir e-mail valido. \n");
			}while(ValidaEmail(email) == 0);
			status = fwrite(&cliente,sizeof(TCliente),1,arq);
			if (status != 1)
				printf ("Erro de gravacao \n");
			else
				printf ("Cliente cadastrado com sucesso \n");
			system ("pause");
		}
	}
}

int BuscarCliente (FILE * arq, char cpf [])
{
	int cont = -1, status;
		TCliente c;

		fseek (arq, 0, 0);
		while (1)
		{
			status = fread (&c, sizeof (TCliente), 1, arq);
			if (status != 1)
			{
				if (!feof(arq))
				    return -2; // erro de leitura
				else
					return -1; // nao achou
			}
			else
			{
				cont++;
				if (c.status == 1 && strcmp (c.nome, cpf) == 0)
					return cont;
			}
		}
}


int ValidaCPF (char cpf[]){
	int icpf[12];
	int i = 0,soma=0,digito1,result1,result2,digito2,valor;

	do{
		if (isdigit(cpf[i]) == 0) /////////////////////////////////////////////
		{
			printf ("CPF Invalido. Informe uma sequencia de 11 numeros sem espacos entre eles.");
			system ("pause");
			return 0;
		}
		else
			i++;
	}while (i != 12);
	for(i=0;i<11;i++)  //Efetua a conversao de array de char para um array de int.
	{
		icpf[i]=cpf[i]-48;
	}
	for(i=0;i<9;i++)  //PRIMEIRO DIGITO.
	{
		soma+=icpf[i]*(10-i);
	}
	result1=soma%11;
	if( (result1==0) || (result1==1) )
	{
		digito1=0;
	}
	else
	{
		digito1 = 11-result1;
	}
	soma=0;
	for(i=0;i<10;i++)  //SEGUNDO DIGITO.
	{
		soma+=icpf[i]*(11-i);
	}
	valor=(soma/11)*11;
	result2=soma-valor;
	if( (result2==0) || (result2==1) )
	{
		digito2=0;
	}
	else
	{
		digito2=11-result2;
	}
	if((digito1==icpf[9]) && (digito2==icpf[10]))   //RESULTADOS DA VALIDACAO.
	{
		printf("\nCPF VALIDADO.\n");
		return 1;                       // retorna 1 para valido
	}
	else
	{
		printf("Problema com os digitos. CPF invalido.\n");
	}
	return 0;      // retorna 0 para cpf invalido
}
