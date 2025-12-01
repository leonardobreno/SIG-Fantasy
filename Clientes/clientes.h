#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct {
    char nome[51];
    char cpf[15];
    char celular[20];
    char email[51];
    int ativo;
} Cliente;

extern Cliente* clientes;
extern int num_clientes;
extern int capacidade_clientes;


// Funções do módulo clientes
void gerenciar_clientes(void);
void salvar_clientes_binario(void);
void carregar_clientes_binario(void);
void liberar_memoria_clientes(void);
void menu_cadastro_cliente(void);
void menu_pesquisar_cliente(void);
void menu_alterar_cliente(void);
void menu_excluir_logico_cliente(void);
void menu_listar_excluidos(void);
void menu_recuperar_cliente(void);
void menu_excluir_fisico_clientes(void);
char menu_cliente(void);

#endif
