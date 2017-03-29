#ifndef TEMPOEDATA_H_
#define TEMPOEDATA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include "Types.h"

void CadastrarData (Data * d);
void CadastrarHorarioNaEstrutura (TVoo * v);
void CadastrarHorario (Horario * h);
int comparaHora_e_Data (char dia[], char mes[], char hora[], char min[]);
int comparaHoraLocal (Horario horario);
int comparaDataLocal (Data data);

#endif /* TEMPOEDATA_H_ */
