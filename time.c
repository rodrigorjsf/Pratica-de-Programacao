#include <stdio.h>
#include <time.h>

typedef struct tempo {
	int hora, min, seg;
}Tempo;

typedef struct data {
	int dia, mes, ano;
}Data;

int main () {
	time_t tp;
	struct tm *local;
	Tempo t;
	Data d;
	tp = time (NULL);
	local = localtime (&tp);
	printf (asctime (local));
	t.hora = local->tm_hour;
	t.min = local->tm_min;
	t.seg = local->tm_sec;
	d.dia = local->tm_mday;
	d.mes = local->tm_mon + 1;
	d.ano = local->tm_year + 1900;
	printf ("Data: %d / %d / %d \n", d.dia, d.mes, d.ano);
	printf ("Hora: %d:%d:%d \n", t.hora, t.min, t.seg);
	system ("pause");
	return 0;
  }
