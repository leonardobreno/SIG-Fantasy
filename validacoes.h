#ifndef VALIDACAO_H
#define VALIDACAO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>


int validar_cpf(char *cpf);
int validar_id_fantasia(const char *obs);
int validar_preco(float preco);
int valida_data(char *data);
int ano_bissexto(int ano);
int valida_dia(int dia, int mes, int ano);
int ano_atual(void);
int valida_ano(int ano);

#endif // VALIDACAO_H