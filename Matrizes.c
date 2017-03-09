// RODRIGO JORGE DE SANTANA FRANÇA

#include <stdio.h>
#include <stdlib.h>

void calculaEstoqueTotal (int tab[][50]){
	int soma = 0;
	int i, j;
	for (j = 0; j <=49; j++)
		for (i = 0; i <= 19; i++) {
			soma += tab [i][j];
			if(i == 19){
			printf ("Produto %i: \n",j+1);
			printf ("Estoque total de %i  \n\n",soma);
			}
			soma = 0;
		}
		system ("pause");
}

void itensPorArmazem (int tab[][50])
{
	int soma = 0;
	int i, j;
	for (i = 0; i <=19; i++)
		for (j = 0; j <= 49; j++) {
			soma += tab [i][j];
			if(j == 49){
			printf ("Armazem %i: \n",i+1);
			printf ("%i itens armazenados \n",soma);
			}
			soma = 0;
		}
		system ("pause");
}

int maior_estoque (int tab[][50], int prod) {

	int i, j, aux, armazem;
	j = prod - 1;
	for (i = 0; i <= 19; i++) {
		if (i = 0){
			aux = tab[i][j];
			armazem = i;
		}
		else 
		{
			if (tab[i][j] > aux){
				aux = tab[i][j];
				armazem = i;
			}
		}		
	}
	return armazem + 1;
}

void calcula_custo (int tabum[][50], int tabdois[][50]) {


	int i, j, valor = 0, soma = 0, multi = 0;
	printf ("Estoque de cada produto em cada Armazem: \n\n");
	for (i = 0; i <=19; i++){
		printf ("----------- Armazem %i -----------\n",i+1);
		for (j = 0; j <= 49; j++) {			
			valor = tabum [i][j] * tabdois[i][j];
			printf ("Produto %i: \n",j+1);
			printf ("Estoque no valor de %d \n\n",valor);

		}
	}
	valor = 0;
	printf ("Estoque em cada Armazem: \n\n");
	for (i = 0; i <=19; i++){
		printf ("----------- Armazem %i -----------\n",i+1);
		for (j = 0; j <= 49; j++) {			
			multi = tabum [i][j] * tabdois[i][j];
			valor += multi; 
			if (j = 49)
				printf ("Estoque total no valor de %d \n\n",valor);
		}
	}
	valor = 0;
	multi = 0;
	printf ("Estoque de cada Produto em todos os Armazens: \n\n");
	for (j = 0; j <=49; j++){
		printf ("----------- Produto %i -----------\n",j+1);
		for (i = 0; i <= 19; i++) {			
			multi = tabum [i][j] * tabdois[i][j];
			valor += multi; 
			if (i = 19){
				printf ("Valor total do produto em todos os armazens de: %d \n\n",valor);
			}

		}
	}
	system ("pause");
}


int main() {
	int tab1 [20][50];
	int tab2 [20][50];
	char op;
	int i, j, prod, maior = 0;

	for (i = 0; i <= 19; i++){
		printf ("Armazem %i: \n",i+1);
		for (j = 0; j <= 49; j++) {
			printf ("Digite a quantidade em estoque do Produto %i: ",j+1);
			scanf("%i", &tab1[i][j]); fflush(stdin);
			printf ("Digite o valor do Produto %i: ",j+1);
			scanf("%i", &tab2[i][j]); fflush(stdin);
			}
	}
	do{
		system ("cls");
		printf ("1 - Estoque total de cada produto. \n");
		printf ("2 - Quantidade de itens armazenado em cada armazem. \n");
		printf ("3 - Qual armazem tem maior quantidade de determinado produto. \n");
		printf ("4 - Exibir custo total de: \n");
		printf (" -> Cada produto em cada armazem. \n");
		printf (" -> Estoque em cada armazem. \n");
		printf (" -> Cada produto em todos os armazens. \n");
		printf ("5 - Sair \n");
		printf ("informe a opcao: ");
		op = getchar (); fflush (stdin);
		switch (op) {
		case '1': calculaEstoqueTotal(tab1);
			      break;
		case '2': itensPorArmazem(tab1);
				  break;
		case '3':printf (" Qual produto deseja consultar? (1 a 50) \n");
			     scanf ("%i", &prod); fflush(stdin);
			     maior = maior_estoque (tab1, prod);
				 printf (" O Armazem %i tem a maior quantidade desse produto.\n", maior);
				  break;
		case '4': calcula_custo (tab1, tab2);
				  break;
		case '5': break;
		default: printf ("Opcao invalida \n");
		}
	} while (op != '5');
	

	return 0;
}
