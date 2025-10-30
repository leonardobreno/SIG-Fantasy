#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utilidades/utilidades.h"

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #define SLEEP(s) sleep(s)
    #define CLEAR_SCREEN "clear"
#endif

typedef struct {
    char nome[50];
    char tamanho[10];
    char cor[20];
    int ativo; // 1 = ativo, 0 = excluído
} Fantasia;

Fantasia* fantasias = NULL;
int num_fantasias = 0;
int capacidade_fantasias = 0;

// ---------- FUNÇÕES AUXILIARES ----------

void salvar_fantasias_binario() {
    FILE* arquivo = fopen("Fantasias/fantasias.dat", "wb");
    if (!arquivo) {
        printf("Erro ao salvar fantasias!\n");
        return;
    }
    fwrite(fantasias, sizeof(Fantasia), num_fantasias, arquivo);
    fclose(arquivo);
}

void carregar_fantasias_binario() {
    FILE* arquivo = fopen("Fantasias/fantasias.dat", "rb");
    if (!arquivo) {
        // Arquivo não existe, inicia vazio
        fantasias = NULL;
        num_fantasias = 0;
        capacidade_fantasias = 0;
        return;
    }
    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    rewind(arquivo);
    num_fantasias = tamanho_arquivo / sizeof(Fantasia);
    capacidade_fantasias = num_fantasias;
    if (num_fantasias > 0) {
        fantasias = (Fantasia*)malloc(num_fantasias * sizeof(Fantasia));
        fread(fantasias, sizeof(Fantasia), num_fantasias, arquivo);
    }
    fclose(arquivo);
}

void liberar_memoria_fantasias() {
    if (fantasias) {
        free(fantasias);
        fantasias = NULL;
        num_fantasias = 0;
        capacidade_fantasias = 0;
    }
}

// ---------- MENU PRINCIPAL ----------

char menu_fantasia(void) {
    char op;
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  Modulo Fantasias                               ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                               -> 1 • Pesquisar fantasia                         ║\n");
    printf("║                               -> 2 • Cadastrar fantasia                         ║\n");
    printf("║                               -> 3 • Alterar fantasia                           ║\n");
    printf("║                               -> 4 • Excluir fantasia                           ║\n");
    printf("║                               -> 5 • Listar lixeira                             ║\n");
    printf("║                               -> 6 • Recuperar fantasia                         ║\n");
    printf("║                               -> 7 • Excluir TODOS (Fisico)                     ║\n");
    printf("║                               -> 0 • Voltar                                     ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opcao: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}

// ---------- CADASTRO ----------

void menu_cadastro_fantasia() {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 Cadastro Fantasia                               ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    Fantasia nova;
    printf("Digite o nome da fantasia: ");
    scanf(" %49[^\n]", nova.nome);
    limpar_buffer();
    printf("Digite o tamanho: ");
    scanf(" %9[^\n]", nova.tamanho);
    limpar_buffer();
    printf("Digite a cor: ");
    scanf(" %19[^\n]", nova.cor);
    limpar_buffer();
    nova.ativo = 1;

    Fantasia* temp = realloc(fantasias, (num_fantasias + 1) * sizeof(Fantasia));
    if (!temp) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        SLEEP(2);
        return;
    }
    fantasias = temp;
    fantasias[num_fantasias] = nova;
    num_fantasias++;
    capacidade_fantasias++;

    salvar_fantasias_binario();
    printf("\nCadastro realizado com sucesso!\n");
    SLEEP(1);
}

// ---------- PESQUISA ----------

void menu_pesquisar_fantasia() {
    char nome_procurar[50];
    int encontrado = 0;

    system(CLEAR_SCREEN);
    printf("Digite o nome da fantasia que deseja pesquisar: ");
    scanf(" %49[^\n]", nome_procurar);
    limpar_buffer();

    for (int i = 0; i < num_fantasias; i++) {
        if (strcmp(nome_procurar, fantasias[i].nome) == 0 && fantasias[i].ativo == 1) {
            system(CLEAR_SCREEN);
            printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                               Fantasia Encontrada                               ║\n");
            printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
            printf("Nome: %s\n", fantasias[i].nome);
            printf("Tamanho: %s\n", fantasias[i].tamanho);
            printf("Cor: %s\n", fantasias[i].cor);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNenhuma fantasia ativa encontrada com este nome.\n");
    }
    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

// ---------- ALTERAR ----------

void menu_alterar_fantasia() {
    char nome_procurar[50];
    int idx = -1;

    system(CLEAR_SCREEN);
    printf("Digite o nome da fantasia que deseja alterar: ");
    scanf(" %49[^\n]", nome_procurar);
    limpar_buffer();

    for (int i = 0; i < num_fantasias; i++) {
        if (strcmp(nome_procurar, fantasias[i].nome) == 0 && fantasias[i].ativo == 1) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("\nNenhuma fantasia ativa encontrada com este nome.\n");
        SLEEP(1);
        return;
    }

    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               Alterar Fantasia                                  ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    printf("Nome atual: %s\n", fantasias[idx].nome);
    printf("Tamanho atual: %s\n", fantasias[idx].tamanho);
    printf("Cor atual: %s\n\n", fantasias[idx].cor);

    char novo_nome[50], novo_tamanho[10], nova_cor[20];
    printf("Digite o novo nome (Enter para manter): ");
    scanf(" %49[^\n]", novo_nome);
    limpar_buffer();
    printf("Digite o novo tamanho (Enter para manter): ");
    scanf(" %9[^\n]", novo_tamanho);
    limpar_buffer();
    printf("Digite a nova cor (Enter para manter): ");
    scanf(" %19[^\n]", nova_cor);
    limpar_buffer();

    if (strlen(novo_nome) > 0) strcpy(fantasias[idx].nome, novo_nome);
    if (strlen(novo_tamanho) > 0) strcpy(fantasias[idx].tamanho, novo_tamanho);
    if (strlen(nova_cor) > 0) strcpy(fantasias[idx].cor, nova_cor);

    salvar_fantasias_binario();
    printf("\nFantasia alterada com sucesso!\n");
    SLEEP(1);
}

// ---------- EXCLUIR LOGICO ----------

void menu_excluir_fantasia() {
    char nome_procurar[50];
    int idx = -1;

    system(CLEAR_SCREEN);
    printf("Digite o nome da fantasia que deseja excluir: ");
    scanf(" %49[^\n]", nome_procurar);
    limpar_buffer();

    for (int i = 0; i < num_fantasias; i++) {
        if (strcmp(nome_procurar, fantasias[i].nome) == 0 && fantasias[i].ativo == 1) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("\nNenhuma fantasia ativa encontrada com este nome.\n");
        SLEEP(1);
        return;
    }

    fantasias[idx].ativo = 0;
    salvar_fantasias_binario();

    printf("Fantasia excluida (logicamente) com sucesso! Esta na lixeira.\n");
    SLEEP(1);
}

// ---------- LISTAR LIXEIRA ----------

void menu_listar_lixeira_fantasias() {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               Lixeira de Fantasias                              ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    int encontrados = 0;
    for (int i = 0; i < num_fantasias; i++) {
        if (fantasias[i].ativo == 0) {
            printf("Nome: %s\n", fantasias[i].nome);
            printf("Tamanho: %s\n", fantasias[i].tamanho);
            printf("Cor: %s\n", fantasias[i].cor);
            printf("---------------------------------------------------\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhuma fantasia excluida na lixeira.\n");
    }
    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

// ---------- RECUPERAR ----------

void menu_recuperar_fantasia() {
    char nome_procurar[50];
    int idx = -1;

    system(CLEAR_SCREEN);
    printf("Digite o nome da fantasia que deseja recuperar: ");
    scanf(" %49[^\n]", nome_procurar);
    limpar_buffer();

    for (int i = 0; i < num_fantasias; i++) {
        if (strcmp(nome_procurar, fantasias[i].nome) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Nenhuma fantasia encontrada com este nome.\n");
        SLEEP(1);
        return;
    }

    if (fantasias[idx].ativo == 1) {
        printf("Esta fantasia ja esta ativa!\n");
    } else {
        fantasias[idx].ativo = 1;
        salvar_fantasias_binario();
        printf("Fantasia recuperada com sucesso!\n");
    }
    SLEEP(1);
}

// ---------- EXCLUSAO FISICA ----------

void menu_excluir_fisico_fantasias() {
    char confirmacao[5];
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                            EXCLUSAO FISICA TOTAL                                ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nDigite 'SIM' para confirmar: ");
    scanf(" %4[^\n]", confirmacao);
    limpar_buffer();

    if (strcmp(confirmacao, "SIM") == 0) {
        liberar_memoria_fantasias();
        salvar_fantasias_binario();
        printf("Todos os dados de fantasias foram excluidos fisicamente.\n");
    } else {
        printf("Operacao cancelada.\n");
    }
    SLEEP(2);
}

// ---------- MÓDULO PRINCIPAL ----------

void gerenciar_fantasias() {
    carregar_fantasias_binario();
    char op;
    do {
        op = menu_fantasia();
        switch(op) {
            case '1':
                menu_pesquisar_fantasia();
                break;
            case '2':
                menu_cadastro_fantasia();
                break;
            case '3':
                menu_alterar_fantasia();
                break;
            case '4':
                menu_excluir_fantasia();
                break;
            case '5':
                menu_listar_lixeira_fantasias();
                break;
            case '6':
                menu_recuperar_fantasia();
                break;
            case '7':
                menu_excluir_fisico_fantasias();
                break;
            case '0':
                printf("Voltando ao menu principal...\n");
                SLEEP(1);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                SLEEP(1);
        }
    } while(op != '0');
    liberar_memoria_fantasias();
}
