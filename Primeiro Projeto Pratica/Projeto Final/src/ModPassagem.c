#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"
#include "Validacoes.h"
#include "Buscas.h"
#include "Tempoedata.h"
#include "Types.h"

void gerarCodigoReserva (TPass * p)
{
	int i;
	char aux, cod[6];
	for(i = 0;i < 5;i++){
		aux = (rand() % 9) + 48;
		cod[i] = aux;
	}
	cod[i] = '\0';
	strcpy (p->codReserva,cod);
}


void ConsultarPassagem (FILE * arqCliente, FILE * arqPass, FILE * arqVoo,char cpf [])
{
    int pos, posAux = -1,cont = 0;
    int voo, status, validar, c;
    TPass p;
    TVoo v;
    c = BuscarCliente (arqCliente,cpf);
    if (c == -1){
        printf ("\nCliente nao cadastrado. \n");
        system("pause");
        return;
    }
    else if (c == -2){
        printf ("Erro de leitura \n");
        return;
    }
    printf ("\nHISTORICO DE PASSAGEM(NS):\n");
    do{
    pos = BuscarPassagemCPF (arqPass, cpf, posAux);
    posAux = pos;
    if (pos == -1){
        printf ("\nTotal de %d Passagem(ens). \n", cont);
        system("pause");
    }
    else if (pos == -2)
        printf ("Erro de leitura \n");
    else {
        fseek(arqPass, pos * sizeof (TPass), 0);
        status = fread (&p,sizeof (TPass), 1, arqPass);
        if (status != 1)
            printf ("Erro de leitura \n");
        else {
            voo = BuscarVoo(arqVoo, p.codVoo);
            if (voo == -1){
                printf ("\nEste voo nao esta cadastrado no momento. \n");
                system("pause");
            }
            else if (voo == -2)
                printf ("Erro de leitura \n");
            else
            {
                fseek(arqVoo, voo * sizeof (TVoo), 0);
                status = fread (&v,sizeof (TVoo), 1, arqVoo);
                validar = comparaHora_e_Data (v.dia, v.mes, v.hora, v.min);
                if (validar == 1)
                {
                	printf ("\n-PASSAGEM ATIVA-\n");
                	printf ("Codigo do Voo: %s \n", v.codVoo);
                    printf ("Codigo de Reserva: %s \n", p.codReserva);
                    printf ("Data do Voo: %s/%s/2017 \n", v.dia,v.mes);
                    printf ("Horario: %s:%s \n", v.hora, v.min);
                    printf ("Origem: %s \n", v.origem);
                    printf ("Destino: %s \n", v.destino);
                    printf ("Valor: %.2f \n\n", v.valor);
                    printf ("Valor: %d \n\n", v.status);

                }
                else
                {
                	printf ("\n-PASSAGEM INATIVA-\n");
                	printf ("Codigo do Voo: %s \n", v.codVoo);
                	printf ("Codigo de Reserva: %s \n", p.codReserva);
                	printf ("Data do Voo: %s/%s/2017 \n", v.dia,v.mes);
                	printf ("Horario: %s:%s \n", v.hora, v.min);
                	printf ("Origem: %s \n", v.origem);
                	printf ("Destino: %s \n", v.destino);
                	printf ("Valor: %.2f \n\n", v.valor);
                	printf ("Valor: %d \n\n", v.status);
                }

            }
        }
    }
    cont++;
    }while (pos != -1);
}

void ImagemVoo(char voo[6][6]) {
	printf(" |  A B C D E F | \n");
	printf(" J|1 %c %c %c %c %c %c |J  \n", voo[0][0], voo[0][1], voo[0][2], voo[0][3], voo[0][4], voo[0][5]);
	printf(" A|2 %c %c %c %c %c %c |A  \n", voo[1][0], voo[1][1], voo[1][2], voo[1][3], voo[1][4], voo[1][5]);
	printf(" N|3 %c %c %c %c %c %c |N  \n", voo[2][0], voo[2][1], voo[2][2], voo[2][3], voo[2][4], voo[2][5]);
	printf(" E|4 %c %c %c %c %c %c |E  \n", voo[3][0], voo[3][1], voo[3][2], voo[3][3], voo[3][4], voo[3][5]);
	printf(" L|5 %c %c %c %c %c %c |L  \n", voo[4][0], voo[4][1], voo[4][2], voo[4][3], voo[4][4], voo[4][5]);
	printf(" A|6 %c %c %c %c %c %c |A  \n", voo[5][0], voo[5][1], voo[5][2], voo[5][3], voo[5][4], voo[5][5]);

}

void preencherMatriz(FILE *arqVoo, char matriz[6][6], int posi) {
	TVoo voo;
	int i, j;

	fseek(arqVoo, posi * sizeof(TVoo), 0);
	if (fread(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
		printf("Erro ao ler \n");
	}
	else {
		for (i = 0; i < 6; i++) {
			for (j = 0; j < 6; j++) {
				matriz[i][j] = voo.mapaPoltronas[i][j];
			}
		}

	}

}

int confirmaCompra(FILE *arqVoo, int i, int j, int posi) {
	TVoo voo;

	if (i < 0 || i > 5){
		printf("Opcao invalida. Escolha entre 1 a 6. \n");
		return 0;
	}
	fseek(arqVoo, posi * sizeof(TVoo), 0);
	if (fread(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
		printf("Erro ao ler \n");
	}
	else {
		if (voo.mapaPoltronas[i][j] == 'o') {
			voo.mapaPoltronas[i][j] = 'x';
			voo.poltronas = voo.poltronas - 1;
		}
		else {
			printf("Poltrona ja ocupada \n");
			return 0;
		}
	}

	fseek(arqVoo, -sizeof(TVoo), 1);
	if (fwrite(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
		printf("Erro ao gravar \n");
	}
	else {
		printf("Compra confirmada \n");
		return 1;
	}
	return 0;
}

float valorPassagem(FILE *arqVoo, int posi) {
	TVoo voo;

	fseek(arqVoo, posi * sizeof(TVoo), 0);
	if (fread(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
		printf("Erro ao ler \n");
	}
	else {
		return voo.valor;
	}
	return 0;
}

void liberarPoltrona(char matriz[6][6], int i, int j) {
	matriz[i][j] = 'o';
}

void acharCodigoVoo(FILE *arqVoo, int posi, char * cod) {
	TVoo voo;
	fseek(arqVoo, posi * sizeof(TVoo), 0);
	if (fread(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
		printf("Erro ao ler \n");
	}
	else {
		strcpy (cod, voo.codVoo);
	}
}

void venderPassagem(FILE *arqPass, FILE *arqCliente, FILE *arqVoo, int origem, int destino, Data d) {
	TPass passagem;
	TVoo v;
	int i, pos = -1,posi, num, conf = 1 ,aux, auxCod;
	char auxMapa[6][6], op, auxCpf[12],codVoo [8], cod [8];
	char Locais[9][50] = {"RECIFE","SALVADOR","SAO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE"};
	pos = BuscarTodosVoos (arqVoo,origem, destino, d,pos);
	if ( pos == -1){
		printf("\nNenhum voo encontrado.\n");
	}
	else{
	ProcurarVoo(arqVoo, origem, destino, d);
	do
	{
		i = 0;
		printf ("Informe o Codigo do Voo que deseja comprar passagem: ");
		while(i < 7){
			codVoo[i] = getche();
			if (isalpha(codVoo[i]) != 0)
				codVoo[i] = toupper(codVoo[i]);
			if (i == 6)
				codVoo[i+1] = '\0';
			i++;
		}
		aux = RecebeCOD(codVoo);
	}while (aux == 0);
	if (aux == 2){
		printf ("\nCodigo Invalido.\n");
		system("pause");
		return;
	}
	posi = procurarVooPassagem(arqVoo, origem, destino, d, codVoo);
	if (posi < 0) {
		printf("\nVoo nao encontrado ou nao existem poltronas disponiveis \n");
	}
	else {
		fseek(arqVoo, posi * sizeof (TVoo), 0);
		fread (&v,sizeof (TVoo), 1, arqVoo);
		fseek(arqPass, 0, 2);
		do{
			i = 0;
			system ("cls");
			printf ("Informe o CPF do Passageiro: ");
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
		{
			if (BuscarCliente(arqCliente, auxCpf) < 0) {
				printf("Cliente nao cadastrado \n");
				return;
			}
			else
				strcpy(passagem.cpf, auxCpf);
		}
		acharCodigoVoo(arqVoo, posi, cod);
		strcpy(passagem.codVoo, cod);

		preencherMatriz(arqVoo, auxMapa, posi); ///////////////
		printf("\nLugares disponiveis \n");
		ImagemVoo(auxMapa);

		do {
			do {
				printf("Digite a letra do seu acento: \n");
				printf("(A / B / C / D / E / F) \n");
				printf("'S' - Sair da passagem de passagens \n");
				printf("Digite: ");
				op = getchar();
				fflush(stdin);
				op = tolower(op);
				switch (op) {
				case 'a':
					printf("Digite o numero do seu assento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 0, posi);
					break;
				case 'b':
					printf("Digite o numero do seu assento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 1, posi);
					break;
				case 'c':
					printf("Digite o numero do seu assento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 2, posi);
					break;
				case 'd':
					printf("Digite o numero do seu assento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 3, posi);
					break;
				case 'e':
					printf("Digite o numero do seu assento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 4, posi);
					break;
				case 'f':
					printf("Digite o numero do seu assento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 5, posi);
					break;
				case 's':
					break;
				default:
					printf("Opcao invalida \n");
				}
			} while (conf == 0);
			if (conf == 1 && op != 's')
				break;
		} while (op != 's');
		if (op == 's')
			return;
		op = toupper(op);
		passagem.poltrona[0] = op;
		passagem.poltrona[1] = num + 48;
		passagem.poltrona[2] = '\0';
		gerarCodigoReserva(&passagem);
		auxCod = BuscarPassagemCodReserva(arqPass, passagem.codReserva);
		if (auxCod > -1){
		    do{
		        gerarCodigoReserva(&passagem);
		        auxCod = BuscarPassagemCodReserva(arqPass, passagem.codReserva);
            }while (auxCod > -1);
	    }
		printf("Seu codigo da reserva eh: %s \n", passagem.codReserva);
		passagem.status = 1;

		printf("----------BOLETO---------- \n");
		printf("-------------------------- \n");
		printf("--Informacoes da reserva: \n");
		printf("--Origem: %s \n", Locais[origem-1]);
		printf("--Destino: %s \n", Locais[destino-1]);
		printf("--Data do voo: %s/%s/2017 \n", d.dia, d.mes);
		printf("--Horario de partida do voo: %s:%s \n", v.hora, v.min);
		printf("--Assento: %c%d \n", op, num);
		printf("--Codigo da reserva: %s \n", passagem.codReserva);
		printf("--Valor: %.2f \n", valorPassagem(arqVoo, posi));
		printf("-------------------------- \n");
		printf("-------------------------- \n");
		fseek(arqPass,0,2);
		if (fwrite(&passagem, sizeof(TPass), 1, arqPass) != 1) {
			printf("Erro ao gravar \n");
		}
		else {
			printf("Passagem vendida com sucesso \n");
		}

	}
	}
	system("pause");
}



void cancelarPassagem(FILE *arqPass, FILE *arqVoo, char codReserva[]) {
	TPass passagem;
	TVoo voo;
	Data d;
	char op, num;
	int pos1, pos2, i, diaAtual, diaPass, subDia;
	time_t tp;
	struct tm *local;
	tp = time (NULL);
	local = localtime (&tp);
	strftime(d.dia, sizeof(d.dia), "%d", local);
	strftime(d.mes, sizeof(d.mes), "%m", local);
	diaAtual = atoi(d.dia);

	fseek(arqPass, 0, 0);
	pos1 = BuscarPassagemCodReserva (arqPass, codReserva);
	if (pos1 == -1){
		printf ("\nPassagem nao cadastrada \n");
		system("pause");
	}
	else if (pos1 == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(arqPass, pos1 * sizeof (TPass), 0);
		fread (&passagem,sizeof (TPass), 1, arqPass);
		if(passagem.status == 1 && strcmp(passagem.codReserva,codReserva) == 0) {
			fseek(arqVoo, 0, 0);
			pos2 = BuscarVoo (arqVoo, passagem.codVoo);
				if (pos2 == -1){
					printf ("\nVoo nao cadastrado \n");
					system("pause");
				}
				else if (pos2 == -2)
					printf ("Erro de leitura \n");
				else {
					fseek(arqVoo, pos2 * sizeof (TVoo), 0);
					fread (&voo, sizeof(TVoo), 1, arqVoo);
					diaPass = atoi(voo.dia);
					subDia = diaAtual/diaPass;
					if (subDia < 2){
						printf("\nCancelamento negado. Cancelamento so pode ser feito com ate dois dias de antecedencia. \n");
						system("pause");
						return;
					}
					else{
						printf("\n-----Documento de Credito----- \n");
						printf("Informacoes do cancelamento: \n");
						printf("Cpf: ");
						i = 0;
						while(i < 11){
							printf ("%c",passagem.cpf[i] );
							if (i == 2)
								printf (".");
							if (i == 5)
								printf (".");
							if (i == 8)
								printf ("-");
							i++;
						}
						printf("\n");
						printf("Codigo do Voo: %s \n", passagem.codVoo);
						if(voo.status == 1 && strcmp(voo.codVoo, passagem.codVoo) == 0) {
							op = passagem.poltrona[0];
							num = passagem.poltrona[1];
							op = tolower(op);
							i = num-48;
							if(op == 'a') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 0);
							}
							else if(op == 'b') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 1);
							}
							else if(op == 'c') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 2);
							}
							else if(op == 'd') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 3);
							}
							else if(op == 'e') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 4);
							}
							else if(op == 'f') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 5);
							}
							else {
								printf("Houve algum erro \n");
							}
							printf("Metade do valor da compra: %.2f \n", voo.valor/2);
							printf("------------------------------ \n");

							voo.poltronas = voo.poltronas + 1;
							passagem.status = 0;

							fseek(arqPass, -sizeof(TPass), 1);
							if(fwrite(&passagem, sizeof(TPass), 1, arqPass) != 1) {
								printf("Erro ao gravar \n");
							}
							else {
								printf("Voo cancelado com sucesso \n");
								system("pause");
							}

							fseek(arqVoo, -sizeof(TVoo), 1);
							if(fwrite(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
								printf("Erro ao gravar \n");
							}
							else {
								printf("Poltrona liberada com sucesso \n");
								system("pause");
							}
							return;
						}
					}
				}
		}

	}
}

void consultarPassageirosVoo(FILE *arqPass, FILE *arqCliente, char codVoo[])
{
	TPass passagem;
	TCliente cliente;
	int pos1,pos2, posAux = -1, cont = 0, i = 0;
	do
	{
		pos1 = BuscarPassagemCodVoo(arqPass, codVoo, posAux);
		posAux = pos1;
		if (pos1 == -1){
			if (cont == 0)
				printf("\nNenhuma passagem para esse voo foi comprada. \n");
			else
				printf("\n%d passageiro(s) nesse voo. \n", cont);
		}
		else if(pos1 == -2)
			printf("\nErro ao ler \n");
		else
		{
			fseek(arqPass, pos1 * sizeof (TPass), 0);
			fread (&passagem, sizeof(TPass), 1, arqPass);
			if(passagem.status == 1 && strcmp(passagem.codVoo, codVoo) == 0)
			{
				pos2 = BuscarCliente (arqCliente, passagem.cpf);
				if (pos2 == -1)
					printf("\nNao achou.\n");
				else if (pos2 == -2)
					printf("\nErro ao ler \n");
				else
				{
					fseek(arqCliente, pos2 * sizeof (TCliente), 0);
					fread (&cliente, sizeof(TCliente), 1, arqCliente);
						if(cliente.status == 1 && strcmp(cliente.cpf, passagem.cpf) == 0)
						{
							printf("\n--------------- \n");
							printf("Cpf: ");
							i = 0;
							while(i < 11)
							{
								printf ("%c",passagem.cpf[i] );
								if (i == 2)
									printf (".");
								if (i == 5)
									printf (".");
								if (i == 8)
									printf ("-");
								i++;
							}
							printf("\n");
							printf("Nome: %s \n", cliente.nome);
							printf("Poltrona: %s \n", passagem.poltrona);
							printf("--------------- \n");
							cont++;
						}
				}
			}
		}
	}while(pos1 != -1);
	system("pause");
}


void MenuPassagem (FILE * arqPassagem, FILE * arqVoo,FILE * arqCliente, char op)
{
	char auxCpf[12], codVooAux[8], Reserva[6];
	int i, aux;
	if (op == '1')
		menuProcurarVoo (arqPassagem,arqCliente,arqVoo,op);
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
				ConsultarPassagem (arqCliente, arqPassagem, arqVoo, auxCpf);
	}
	else if (op == '3')
	{
		do
		{
			i = 0;
			system ("cls");
			printf ("Informe o Codigo de reserva: ");
			while(i < 5){
				Reserva[i] = getche();
				if (i == 4)
					Reserva[i+1] = '\0';
				i++;
			}
		}while (i < 5);
		if (validaCodReserva(Reserva) == 0){
			printf ("\nCodigo invalido. \n");
			system("pause");
		}
		else
			cancelarPassagem(arqPassagem ,arqVoo, Reserva);
	}
	else
	{
		do
		{
			i = 0;
			system ("cls");
			printf ("Informe o Codigo do Voo: ");
			while(i < 7){
				codVooAux[i] = getche();
				if (isalpha(codVooAux[i]) != 0)
					codVooAux[i] = toupper(codVooAux[i]);
				if (i == 6)
					codVooAux[i+1] = '\0';
				i++;
			}
			aux = RecebeCOD(codVooAux);
		}while (aux == 0);
		if (aux == 2)
			return;
		else if(BuscarVoo(arqVoo, codVooAux) == -1){
			printf ("\nCodigo de voo nao cadastrado. \n");
			system("pause");
			return;
		}
		else
			consultarPassageirosVoo (arqPassagem, arqCliente, codVooAux);
	}
}

