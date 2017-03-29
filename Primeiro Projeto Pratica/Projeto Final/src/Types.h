#ifndef TYPES_H_
#define TYPES_H_

typedef struct cliente {
	char cpf[12];
	char nome [100];
	char telefone [12];
	char email [100];
	int status;
}TCliente;

typedef struct voo {
	char codVoo [8];
	char origem [50];
	char destino [50];
	char dia [3];
	char mes [3];
	char hora [3];
	char min [3];
	int poltronas;
	char mapaPoltronas [6][6];
	float valor;
	int status;
}TVoo;

typedef struct passagem {
	char codReserva [6];
	char cpf [12];
	char codVoo [8];
	char poltrona[3];
	int status;
}TPass;

typedef struct data {
	char dia[3];
	char mes[3];
}Data;

typedef struct horario {
	char hora[3];
	char min[3];
}Horario;

#endif /* TYPES_H_ */
