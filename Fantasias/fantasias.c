#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Utilidades/utilidades.h"
#include "../Validacoes/validacoes.h"

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
    int ativo;
} Fantasia;

Fantasia* fantasias = NULL;
int num_fantasias = 0;
int capacidade_fantasias = 0;


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
    printf("║                               -> 8 • Gerar Relatórios (Filtro)                    ║\n");
    printf("║                               -> 0 • Voltar                                     ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opcao: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}

//CADASTRO

void menu_cadastro_fantasia() {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 Cadastro Fantasia                               ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    Fantasia nova;

    do {
        printf("Digite o nome da fantasia: ");
        scanf(" %49[^\n]", nova.nome);
        limpar_buffer();

        if (!validar_nome(nova.nome)) {
            printf("\n⚠️  Nome inválido! Use apenas letras e espaços (até 50 caracteres).\n");
            SLEEP(2);
            system(CLEAR_SCREEN);
            printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                                 Cadastro Fantasia                               ║\n");
            printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        }
    } while (!validar_nome(nova.nome));

  
    do {
        printf("Digite o tamanho da fantasia: ");
        scanf(" %9[^\n]", nova.tamanho);
        limpar_buffer();

        if (!validar_tamanho_fantasia(nova.tamanho)) {
            printf("\n⚠️  Tamanho inválido! Use até 9 caracteres (ex: P, M, G, GG, 40, etc.).\n");
            SLEEP(2);
            system(CLEAR_SCREEN);
            printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                                 Cadastro Fantasia                               ║\n");
            printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
            printf("Nome: %s\n", nova.nome);
        }
    } while (!validar_tamanho_fantasia(nova.tamanho));


    do {
        printf("Digite a cor da fantasia: ");
        scanf(" %19[^\n]", nova.cor);
        limpar_buffer();

        if (!validar_cor_fantasia(nova.cor)) {
            printf("\n⚠️  Cor inválida! Use apenas letras e hífen (até 19 caracteres).\n");
            SLEEP(2);
            system(CLEAR_SCREEN);
            printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                                 Cadastro Fantasia                               ║\n");
            printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
            printf("Nome: %s\nTamanho: %s\n", nova.nome, nova.tamanho);
        }
    } while (!validar_cor_fantasia(nova.cor));

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
    printf("\n✅ Cadastro realizado com sucesso!\n");
    SLEEP(1);
}

//pesquisa

void menu_pesquisar_fantasia() {
    char nome_procurar[50];
    int encontrado = 0;

    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 Pesquisar Fantasia                              ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    printf("Digite o nome da fantasia que deseja pesquisar: ");
    scanf(" %49[^\n]", nome_procurar);
    limpar_buffer();


    if (!validar_nome(nome_procurar)) {
        printf("\nERRO: Nome inválido! Use apenas letras e espaços (máx. 50 caracteres).\n");
        printf("Pressione Enter para voltar...");
        limpar_buffer();
        return;
    }

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


//alteração

void menu_alterar_fantasia() {
    char nome_procurar[50];
    int idx = -1;

    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               Alterar Fantasia                                  ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    printf("Digite o nome da fantasia que deseja alterar: ");
    scanf(" %49[^\n]", nome_procurar);
    limpar_buffer();

    if (!validar_nome(nome_procurar)) {
        printf("\nERRO: Nome inválido! Use apenas letras e espaços.\n");
        SLEEP(2);
        return;
    }

    for (int i = 0; i < num_fantasias; i++) {
        if (strcmp(nome_procurar, fantasias[i].nome) == 0 && fantasias[i].ativo == 1) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("\nNenhuma fantasia ativa encontrada com este nome.\n");
        SLEEP(2);
        return;
    }

    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               Alterar Fantasia                                  ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    printf("Nome atual: %s\n", fantasias[idx].nome);
    printf("Tamanho atual: %s\n", fantasias[idx].tamanho);
    printf("Cor atual: %s\n\n", fantasias[idx].cor);

    char novo_nome[50] = "", novo_tamanho[10] = "", nova_cor[20] = "";

    printf("Digite o novo nome (Enter para manter): ");
    fgets(novo_nome, sizeof(novo_nome), stdin);
    novo_nome[strcspn(novo_nome, "\n")] = '\0';  // remove \n

    printf("Digite o novo tamanho (Enter para manter): ");
    fgets(novo_tamanho, sizeof(novo_tamanho), stdin);
    novo_tamanho[strcspn(novo_tamanho, "\n")] = '\0';

    printf("Digite a nova cor (Enter para manter): ");
    fgets(nova_cor, sizeof(nova_cor), stdin);
    nova_cor[strcspn(nova_cor, "\n")] = '\0';

    if (strlen(novo_nome) > 0) {
        if (!validar_nome(novo_nome)) {
            printf("\nERRO: Nome inválido! A alteração foi cancelada.\n");
            SLEEP(2);
            return;
        }
        strcpy(fantasias[idx].nome, novo_nome);
    }

   if (!validar_tamanho_fantasia(novo_tamanho)) {
    printf("\nERRO: Tamanho inválido! Use apenas letras, números e espaços.\n");
    SLEEP(2);
    return;
}


    if (strlen(nova_cor) > 0) {
        if (!validar_nome(nova_cor)) {
            printf("\nERRO: Cor inválida! Use apenas letras e espaços.\n");
            SLEEP(2);
            return;
        }
        strcpy(fantasias[idx].cor, nova_cor);
    }

    salvar_fantasias_binario();
    printf("\nFantasia alterada com sucesso!\n");
    SLEEP(1);
}


// exclusão logica

void menu_excluir_fantasia() {
    char nome_procurar[50];
    int idx = -1;

    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                             Exclusão Lógica Fantasia                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    printf("Digite o nome da fantasia que deseja excluir: ");
    fgets(nome_procurar, sizeof(nome_procurar), stdin);
    nome_procurar[strcspn(nome_procurar, "\n")] = '\0'; 

    if (!validar_nome(nome_procurar)) {
        printf("\nERRO: Nome inválido! A exclusão foi cancelada.\n");
        SLEEP(2);
        return;
    }

    for (int i = 0; i < num_fantasias; i++) {
        if (strcmp(nome_procurar, fantasias[i].nome) == 0 && fantasias[i].ativo == 1) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("\nNenhuma fantasia ativa encontrada com este nome.\n");
        SLEEP(2);
        return;
    }

    char confirmacao[5];
    printf("\nTem certeza que deseja excluir a fantasia '%s'? (SIM/NAO): ", fantasias[idx].nome);
    fgets(confirmacao, sizeof(confirmacao), stdin);
    confirmacao[strcspn(confirmacao, "\n")] = '\0';

    if (strcmp(confirmacao, "SIM") != 0) {
        printf("Operação cancelada.\n");
        SLEEP(1);
        return;
    }

    fantasias[idx].ativo = 0;
    salvar_fantasias_binario();

    printf("Fantasia excluída (logicamente) com sucesso! Está na lixeira.\n");
    SLEEP(2);
}


// lixeira

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
        printf("\nNenhuma fantasia excluída na lixeira.\n");
    } else {
        printf("\nTotal de fantasias excluídas: %d\n", encontrados);
    }

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}



void menu_recuperar_fantasia() {
char nome_procurar[50];
int idx = -1;

system(CLEAR_SCREEN);
printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
printf("║                             Recuperar Fantasia                                   ║\n");
printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

printf("Digite o nome da fantasia que deseja recuperar: ");
fgets(nome_procurar, sizeof(nome_procurar), stdin);
nome_procurar[strcspn(nome_procurar, "\n")] = '\0';

if (!validar_nome(nome_procurar)) {
    printf("\nERRO: Nome inválido! A recuperação foi cancelada.\n");
    SLEEP(2);
    return;
}

for (int i = 0; i < num_fantasias; i++) {
    if (strcmp(nome_procurar, fantasias[i].nome) == 0 && fantasias[i].ativo == 0) {
        idx = i;
        break;
    }
}

if (idx == -1) {
    printf("\nNenhuma fantasia encontrada na lixeira com este nome.\n");
    SLEEP(2);
    return;
}

char confirmacao[5];
printf("\nTem certeza que deseja recuperar a fantasia '%s'? (SIM/NAO): ", fantasias[idx].nome);
fgets(confirmacao, sizeof(confirmacao), stdin);
confirmacao[strcspn(confirmacao, "\n")] = '\0';

if (strcmp(confirmacao, "SIM") != 0) {
    printf("Operação cancelada.\n");
    SLEEP(1);
    return;
}

fantasias[idx].ativo = 1;
salvar_fantasias_binario();

printf("Fantasia recuperada com sucesso!\n");
SLEEP(2);

}


//exclusão fisica

void menu_excluir_fisico_fantasias() {
    char confirmacao[5];
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                            EXCLUSAO FISICA TOTAL                                ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nDigite 'SIM' para confirmar: ");
    fgets(confirmacao, sizeof(confirmacao), stdin);
    confirmacao[strcspn(confirmacao, "\n")] = '\0'; 

    if (strcmp(confirmacao, "SIM") == 0) {
        liberar_memoria_fantasias();
        salvar_fantasias_binario();
        printf("Todos os dados de fantasias foram excluidos fisicamente.\n");
    } else {
        printf("Operacao cancelada.\n");
    }
    SLEEP(2);
}

void menu_relatorio_fantasias() {
    char filtro_tamanho[10]; 
    int encontrados = 0;

    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           Relatório de Fantasias                           ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════╝\n");
    printf("Total de fantasias cadastradas: %d\n\n", num_fantasias);

    printf("Digite o TAMANHO para filtrar (Ex: P, M, G, GG):\n"); 
    printf("Opção especial: Digite 'todos' para listar todas (incl. inativas).\n");
    printf(">>> Filtro por Tamanho: ");
    scanf(" %9[^\n]", filtro_tamanho);
    limpar_buffer();

    printf("\n------------------------------------------------------------------------------------\n");
    printf("| %-30s | %-10s | %-10s | %-10s |\n", "NOME DA FANTASIA", "TAMANHO", "COR", "STATUS");
    printf("------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_fantasias; i++) {
        int imprimir = 0;
        

        // filtro
        if (strcmp(filtro_tamanho, "todos") == 0) {
            imprimir = 1;
        } 
        //  por Tamanho (P, M, G)
        else if (strcmp(fantasias[i].tamanho, filtro_tamanho) == 0) {
            imprimir = 1; 
        }

        if (imprimir) {
            printf("| %-30s | %-10s | %-10s | %-10s |\n", 
                   fantasias[i].nome, 
                   fantasias[i].tamanho, 
                   fantasias[i].cor, 
                   fantasias[i].ativo == 1 ? "Ativa" : "Inativa");
            encontrados++;
        }
    }
    printf("------------------------------------------------------------------------------------\n");
    printf("\nForam encontradas %d fantasias que atendem ao filtro.\n", encontrados);

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}




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
            case '8': 
                menu_relatorio_fantasias();
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
