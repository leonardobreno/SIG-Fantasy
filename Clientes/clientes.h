#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct {
    char nome[51];
    char cpf[15];
    char celular[20];
    char email[51];
    int ativo;
} Cliente;

void gerenciar_clientes(void);

#endif