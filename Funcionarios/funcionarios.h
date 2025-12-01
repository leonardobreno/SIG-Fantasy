#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#define MAX_NOME 51
#define MAX_CPF 15
#define MAX_CELULAR 20
#define MAX_EMAIL 51
#define MAX_SALARIO 20

typedef struct {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    char celular[MAX_CELULAR];
    char email[MAX_EMAIL];
    char salario[MAX_SALARIO];
    int ativo; // 1 = ativo, 0 = excluído
} Funcionario;


extern Funcionario* funcionarios;
extern int num_funcionarios;
extern int capacidade_funcionarios;


void gerenciar_funcionarios(void);

// Funções de CRUD
void menu_cadastro_funcionario(void);
void menu_pesquisar_funcionario(void);
void menu_alterar_funcionario(void);
void menu_excluir_logico_funcionario(void);
void menu_listar_excluidos_funcionario(void);
void menu_recuperar_funcionario(void);
void menu_excluir_fisico_funcionarios(void);
void menu_relatorio_funcionario(void);

// Funções auxiliares
void salvar_funcionarios_binario(void);
void carregar_funcionarios_binario(void);
void liberar_memoria_funcionarios(void);
void menu_relatorio_funcionario(void); 


// Funções auxiliares
void salvar_funcionarios_binario(void);

// Menu principal
char menu_funcionario(void);

#endif // FUNCIONARIOS_H
