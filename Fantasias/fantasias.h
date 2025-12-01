#ifndef FANTASIAS_H
#define FANTASIAS_H

typedef struct {
    char nome[50];
    char tamanho[10];
    char cor[20];
    int ativo; // 1 = ativo, 0 = excluído
} Fantasia;

extern Fantasia* fantasias;
extern int num_fantasias;

void gerenciar_fantasias(void);

char menu_fantasia(void);

void menu_cadastro_fantasia(void);
void menu_pesquisar_fantasia(void);
void menu_alterar_fantasia(void);
void menu_excluir_fantasia(void);
void menu_listar_lixeira_fantasias(void);
void menu_recuperar_fantasia(void);
void menu_excluir_fisico_fantasias(void);

void salvar_fantasias_binario(void);
void carregar_fantasias_binario(void);
void liberar_memoria_fantasias(void);


#endif // FANTASIAS_H
