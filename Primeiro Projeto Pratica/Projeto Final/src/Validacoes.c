#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"
#include "Validacoes.h"
#include "Buscas.h"
#include "Tempoedata.h"
#include "Types.h"

FILE * criarArquivo (char nome[]) {
	FILE * arq;
	arq = fopen (nome, "r+b");
	if (arq == NULL) {
		arq = fopen (nome, "w+b");
	}
	return arq;
}


void opcoesOrigem ()
{
    int i;
    char origens[9][50] = {"1- RECIFE","2 - SALVADOR","3 - SAO PAULO","4 - RIO DE JANEIRO","5 - CURITIBA","6 - PORTO ALEGRE","7 - NATAL","8 - MANAUS","9 - BELO HORIZONTE"};
    char origensEstado[9][10] = {"- PE","- BA","- SP","- RJ","- PR","- RS","- RN","- AM","- MG"};
    printf ("Opcoes de Origem: \n");
    for(i = 0; i < 9; i++)
        printf ("%s %s \n", origens[i], origensEstado[i]);
    printf ("\n");
}

void opcoesDestinos ()
{
    int i;
    char destinos[9][50] = {"1- RECIFE","2 - SALVADOR","3 - SAO PAULO","4 - RIO DE JANEIRO","5 - CURITIBA","6 - PORTO ALEGRE","7 - NATAL","8 - MANAUS","9 - BELO HORIZONTE"};
    char origensEstado[9][10] = {"- PE","- BA","- SP","- RJ","- PR","- RS","- RN","- AM","- MG"};
    printf ("Opcoes de Destino: \n");
    for(i = 0; i < 9; i++)
        printf ("%s %s \n", destinos[i], origensEstado[i]);
    printf ("\n");
}

int bissexto (int ano){
	int anoAux1, anoAux2;
	anoAux1 = ano%4;
	anoAux2 = ano%400;
	if (anoAux1 == 0){
		anoAux1 = ano%100;
		if (anoAux1 == 0)
			return 0;
		else
			return 1;
	}
	else if (anoAux2 == 0)
		return 1;
	return 0;
}

int ValidaCPF (char cpf[]){
	int icpf[12];
	int aux, i = 0,soma=0,digito1,result1,result2,digito2,valor;
	aux = strlen (cpf);
	do{
		if (isdigit(cpf[i]) == 0)
		{
			if(i == aux && cpf[i] == '\0')
				break;
			else
			{
			printf ("\n %d", i);
			printf ("\nCPF Invalido. \nInforme uma sequencia de 11 numeros sem espacos entre eles.");
			system ("pause");
			return 0;
			}
		}
		else
			i++;
	}while (i != aux+1);
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
	if((digito1==icpf[9]) && (digito2==icpf[10]))
	{
		return 1;
	}
	else
	{
		printf("\nProblema com os digitos. CPF invalido.\n");
		system("pause");
	}
	return 0;
}



int validaRemocao (FILE * arqPass, FILE * arqVoo,char cpf[])
{
    int pos, posAux = -1;
    int voo, status, validar = 0;
    TPass p;
    TVoo v;
    do{
    pos = BuscarPassagemCPF (arqPass, cpf, posAux);
    posAux = pos;
    if (pos == -1)
        return validar;
    else if (pos == -2)
        printf ("Erro de leitura \n");
    else
    {
        fseek(arqPass, pos * sizeof (TPass), 0);
        status = fread (&p,sizeof (TPass), 1, arqPass);
        if (status != 1)
            printf ("Erro de leitura \n");
        else {
            voo = BuscarVoo(arqVoo, p.codVoo);
            if (voo == -1)
                return validar;
            else if (voo == -2)
                printf ("Erro de leitura \n");
            else
            {
                fseek(arqVoo, voo * sizeof (TVoo), 0);
                status = fread (&v,sizeof (TVoo), 1, arqVoo);
                validar = comparaHora_e_Data (v.dia, v.mes, v.hora, v.min);
                if (validar == 1)
                    return validar;
            }
        }
    }
    }while (pos != -2);
    return validar;
}

int validaDataCorreta(Data d){
	int diaAux,mesAux,quantDias, ano;
	int QuantDias1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
	diaAux = atoi (d.dia);
	mesAux = atoi (d.mes);
	ano = bissexto(ANO);

	if (mesAux < 1 || mesAux > 12){
		return 0;
	}
	if (diaAux < 1 || diaAux > 31){
		return 0;
	}
	if (mesAux == 2){
		if (ano == 1)
			quantDias = 29;
		else
			quantDias = QuantDias1[mesAux-1];
		if (diaAux < 1 || diaAux > quantDias){
			return 0;
		}
	}
	else
	{
		quantDias = QuantDias1[mesAux-1];
		if (diaAux < 1 || diaAux > quantDias){
			return 0;
		}
	}
	return 1;
}

int validaHoraCorreta (Horario horario){
    int horaAux,minAux;
    horaAux = atoi (horario.hora);
    minAux = atoi (horario.min);
    if (horaAux < 0 || horaAux > 23)
        return 0;
    if (minAux < 0 || minAux > 59)
        return 0;
    return 1;
}

int ValidaData(Data d) {
	int aux, cont = 0, i;

	for (i = 0; i < 2; i++) {
		if (isdigit(d.dia[i]) == 0 && cont == 0){
			return 0;
		}
		cont++;
	}
        i = 0;
        cont = 0;
	for (i = 0; i < 2; i++) {
		if (isdigit(d.mes[i]) == 0 && cont ==0){
			return 0;
		}
		cont++;
	}
	aux = validaDataCorreta(d);
	if (aux == 0){
		return 0;
	}
	return 1;
}


int ValidaHora(Horario horario) {
	int i;

	for (i = 0; i < 2; i++) {
		if (isdigit(horario.hora[i]) == 0) {
			return 0;
		}
	}
	for (i = 0; i < 2; i++) {
		if (isdigit(horario.min[i]) == 0) {
			return 0;
		}
	}
        if (validaHoraCorreta(horario) == 0)
            return 0;
	return 1;
}
int ValidaCodVoo(char cod[]) {
	int i;

	for (i = 0; i < 3; i++) {
		if (isalpha(cod[i]) == 0) {
			return 0;
		}
	}

	for (i = 3; i < 7; i++) {
		if (isdigit(cod[i]) == 0) {
			return 0;
		}
	}

	return 1;
}

int validaCodReserva(char cod[]) {
	int i;

	for (i = 0; i < 5; i++) {
		if (isdigit(cod[i]) == 0) {
			return 0;
		}
	}
	return 1;
}
void atualizarVoos_e_Passagens (FILE *arqVoo, FILE *arqPassagem)
{
	FILE *passagemTemp, *vooTemp;
	int fim = 1, pos, aux, status;
	TVoo v;
	TPass p;
	Data d;
	Horario h;
	passagemTemp = fopen ("auxiliarPassagem", "w+b");
	vooTemp = fopen ("auxiliarVoos", "w+b");
	if (passagemTemp == NULL || vooTemp == NULL) {
		printf ("Erro ao executar o processo de atualizacao dos arquivo. \n");
		if(passagemTemp != NULL )
			fclose (passagemTemp);
		if(vooTemp != NULL)
			fclose (vooTemp);
	}
	else
	{
		fseek(arqVoo, 0, 0);
		do
		{
		status = fread(&v, sizeof(TVoo), 1, arqVoo);
		if (status != 1)
		{
			if (!feof(arqVoo))
			{
				printf ("\nErro de leitura1 \n");
				fim = 0;
				break;
			}
			else
			{
				fim = 0;
				break;
			}
		}
		else
		{
			strcpy (d.dia,v.dia);
			strcpy (d.mes,v.mes);
			strcpy (h.hora,v.hora);
			strcpy (h.min,v.min);
			aux = comparaHora_e_Data (d.dia, d.mes, h.hora, h.min);
			if (aux == 0)
			{
				v.status = 0;
				fseek(arqPassagem, 0, 0);
				do
				{
					status = fread(&p, sizeof(TPass), 1, arqPassagem);
					if (status != 1)
					{
						if (!feof(arqPassagem))
						{
							printf ("\nErro de leitura2 \n");
							pos = 0;
							break;
						}
						else
						{
							pos = 0;
							break;
						}
					}
					else
					{
						if (strcmp (p.codVoo,v.codVoo) == 0)
						{
							p.status = 0;
							status = fwrite (&p,sizeof (TPass), 1, passagemTemp);
							if (status != 1)
								printf ("\nErro de gravacao \n");
						}
						else{
							status = fwrite (&p,sizeof (TPass), 1, passagemTemp);
							if (status != 1)
								printf ("\nErro de gravacao \n");
						}
					}
				}while (pos != 0);
				status = fwrite (&v,sizeof (TVoo), 1, vooTemp);
				if (status != 1)
					printf ("\nErro de gravacao \n");
			}
			else{
				status = fwrite (&v,sizeof (TVoo), 1, vooTemp);
				if (status != 1)
					printf ("\nErro de gravacao \n");
			}
		}

	}while(fim != 0);
		fclose (arqPassagem);
		fclose (arqVoo);
		fclose (passagemTemp);
		fclose (vooTemp);
		remove ("Passagem.dat");
		rename ("auxiliarPassagem", "Passagem.dat");
		remove ("Voo.dat");
		rename ("auxiliarVoos", "Voo.dat");
    }
}

