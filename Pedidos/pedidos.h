#ifndef PEDIDOS_H
#define PEDIDOS_H

typedef struct {
    unsigned long id_pedido;
    char cpf_cliente[15];
    char id_fantasia[20];
    float preco;
    char data_pedido[11];
    int ativo;
} Pedido;

void gerenciar_pedidos(void);

#endif