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

// Funções do módulo pedidos
unsigned long get_next_pedido_id(void);
void salvar_pedidos_binario(void);
void carregar_pedidos_binario(void);
void liberar_memoria_pedidos(void);
void menu_cadastro_pedido(void);
void menu_pesquisar_pedido(void);
void menu_alterar_pedido(void);
void menu_excluir_logico_pedido(void);
void menu_listar_excluidos_pedidos(void);
void menu_recuperar_pedido(void);
void menu_excluir_fisico_pedidos(void);
char menu_pedido(void);
void gerenciar_pedidos(void);

#endif
