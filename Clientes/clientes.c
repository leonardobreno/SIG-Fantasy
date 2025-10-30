#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
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

Cliente* clientes = NULL;
int num_clientes = 0;
int capacidade_clientes = 0;

void gerenciar_clientes(void) {
    carregar_clientes_binario();
    char op;
    do {
        op = menu_cliente();
        switch (op) {
            case '1':
                menu_pesquisar_cliente();
                break;
            case '2':
                menu_cadastro_cliente();
                break;
            case '3':
                menu_alterar_cliente();
                break;
            case '4':
                menu_excluir_logico_cliente();
                break;
            case '5':
                menu_listar_excluidos();
                break;
            case '6':
                menu_recuperar_cliente();
                break;
            case '7':
                menu_excluir_fisico_clientes();
                break;
            case '0':
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                SLEEP(1);
        }
    } while (op != '0');
    liberar_memoria_clientes();
}

void salvar_clientes_binario() {
    FILE* arquivo = fopen("clientes.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro fatal: Nao foi possivel abrir o arquivo para escrita!\n");
        return;
    }
    fwrite(clientes, sizeof(Cliente), num_clientes, arquivo);
    fclose(arquivo);
}

void carregar_clientes_binario() {
    FILE* arquivo = fopen("clientes.dat", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de dados 'clientes.dat' nao encontrado. Iniciando com base de dados vazia.\n");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    rewind(arquivo);

    num_clientes = tamanho_arquivo / sizeof(Cliente);
    capacidade_clientes = num_clientes;

    clientes = (Cliente*) malloc(num_clientes * sizeof(Cliente));
    if (clientes == NULL) {
        printf("Erro fatal: Falha ao alocar memoria!\n");
        fclose(arquivo);
        return;
    }
    fread(clientes, sizeof(Cliente), num_clientes, arquivo);
    fclose(arquivo);
}

void liberar_memoria_clientes() {
    if (clientes != NULL) {
        free(clientes);
        clientes = NULL;
        num_clientes = 0;
        capacidade_clientes = 0;
    }
}

void menu_cadastro_cliente() {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    Cadastro Cliente                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    Cliente novo_cliente;

    printf("Digite o nome: ");
    scanf(" %50[^\n]", novo_cliente.nome);
    limpar_buffer();

    printf("Digite o CPF: ");
    scanf(" %14[^\n]", novo_cliente.cpf);
    limpar_buffer();
    
    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(novo_cliente.cpf, clientes[i].cpf) == 0) {
            printf("\nERRO: Ja existe um cliente (ativo ou inativo) com este CPF!\n");
            SLEEP(2);
            return;
        }
    }

    printf("Digite o numero de celular: ");
    scanf(" %19[^\n]", novo_cliente.celular);
    limpar_buffer();

    printf("Digite o Email: ");
    scanf(" %50[^\n]", novo_cliente.email);
    limpar_buffer();

    novo_cliente.ativo = 1;

    Cliente* temp = realloc(clientes, (num_clientes + 1) * sizeof(Cliente));
    if (temp == NULL) {
        printf("Erro: Nao foi possivel alocar memoria para o novo cliente!\n");
        return;
    }
    clientes = temp;

    clientes[num_clientes] = novo_cliente;
    num_clientes++;
    capacidade_clientes++;

    salvar_clientes_binario();

    printf("\nCadastro realizado com sucesso!\n");
    SLEEP(1);
}

void menu_pesquisar_cliente() {
    char cpf_procurar[15];
    int encontrado = 0;

    system(CLEAR_SCREEN);
    printf("Digite o CPF do cliente que deseja pesquisar: ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(cpf_procurar, clientes[i].cpf) == 0 && clientes[i].ativo == 1) {
            system(CLEAR_SCREEN);
            printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                                  Cliente Encontrado                             ║\n");
            printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
            printf("Nome: %s\n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Celular: %s\n", clientes[i].celular);
            printf("Email: %s\n", clientes[i].email);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNenhum cliente *ativo* encontrado com o CPF: %s\n", cpf_procurar);
    }
    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

void menu_alterar_cliente() {
    char cpf_procurar[15];
    int encontrado_idx = -1;

    system(CLEAR_SCREEN);
    printf("Digite o CPF do cliente que deseja alterar: ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(cpf_procurar, clientes[i].cpf) == 0 && clientes[i].ativo == 1) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx != -1) {
        system(CLEAR_SCREEN);
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                    Alterar Cliente                              ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("Cliente encontrado! (Deixe em branco e pressione Enter para nao alterar)\n\n");
        
        printf("Nome: %s\n", clientes[encontrado_idx].nome);
        printf("CPF: %s\n", clientes[encontrado_idx].cpf);

        char novo_celular[20], novo_email[51];

        printf("Celular atual: %s\n", clientes[encontrado_idx].celular);
        printf("Digite o novo celular: ");
        scanf(" %19[^\n]", novo_celular);
        limpar_buffer();

        printf("Email atual: %s\n", clientes[encontrado_idx].email);
        printf("Digite o novo email: ");
        scanf(" %50[^\n]", novo_email);
        limpar_buffer();

        if (strlen(novo_celular) > 0) {
            strcpy(clientes[encontrado_idx].celular, novo_celular);
        }
        if (strlen(novo_email) > 0) {
            strcpy(clientes[encontrado_idx].email, novo_email);
        }
        
        salvar_clientes_binario();
        printf("\nCliente alterado com sucesso!\n");
    } else {
        printf("\nNenhum cliente *ativo* encontrado com o CPF: %s\n", cpf_procurar);
    }
    SLEEP(1);
}

void menu_excluir_logico_cliente() {
    char cpf_procurar[15];
    int encontrado_idx = -1;

    system(CLEAR_SCREEN);
    printf("Digite o CPF do cliente que deseja deletar (Exclusao Logica): ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(cpf_procurar, clientes[i].cpf) == 0 && clientes[i].ativo == 1) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx != -1) {
        clientes[encontrado_idx].ativo = 0; 
        
        salvar_clientes_binario();
        printf("Cliente excluido (logicamente) com sucesso! Ele esta na lixeira.\n");
    } else {
        printf("Nenhum cliente ativo encontrado com esse CPF!\n");
    }
    SLEEP(1);
}

void menu_listar_excluidos() {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                Lixeira de Clientes                              ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    int encontrados = 0;
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].ativo == 0) {
            printf("Nome: %s\n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("---------------------------------------------------\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum cliente excluido encontrado na lixeira.\n");
    }

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

void menu_recuperar_cliente() {
    char cpf_procurar[15];
    int encontrado_idx = -1;

    system(CLEAR_SCREEN);
    printf("Digite o CPF do cliente que deseja RECUPERAR da lixeira: ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(cpf_procurar, clientes[i].cpf) == 0) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx == -1) {
        printf("Nenhum cliente (ativo ou inativo) encontrado com esse CPF!\n");
    } else {
        if (clientes[encontrado_idx].ativo == 1) {
            printf("Este cliente ja esta ativo! Nao precisa recuperar.\n");
        } else {
            clientes[encontrado_idx].ativo = 1;
            salvar_clientes_binario();
            printf("Cliente recuperado com sucesso!\n");
        }
    }
    SLEEP(1);
}

void menu_excluir_fisico_clientes() {
    char confirmacao[5];
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              EXCLUSAO FISICA TOTAL                              ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n!!! ATENCAO !!!\n");
    printf("Isso apagara TODOS os dados de clientes do sistema, inclusive os da lixeira.\n");
    printf("Esta acao NAO PODE ser desfeita.\n");
    printf("O arquivo 'clientes.dat' sera esvaziado.\n\n");
    printf("Digite 'SIM' (em maiusculas) para confirmar: ");
    scanf(" %4[^\n]", confirmacao);
    limpar_buffer();

    if (strcmp(confirmacao, "SIM") == 0) {
        
        liberar_memoria_clientes(); 
        
        clientes = NULL;
        num_clientes = 0;
        capacidade_clientes = 0;

        salvar_clientes_binario(); 

        printf("SUCESSO: Todos os dados de clientes foram excluidos fisicamente.\n");
    } else {
        printf("Operacao cancelada.\n");
    }
    SLEEP(2);
}


char menu_cliente(void) {
    char op;
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    Modulo Clientes                              ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                  -> 1 • Pesquisar cliente                       ║\n");
    printf("║                                  -> 2 • Cadastrar cliente                       ║\n");
    printf("║                                  -> 3 • Alterar cliente                         ║\n");
    printf("║                                  -> 4 • Deletar cliente (Lixeira)               ║\n");
    printf("║                                  -> 5 • Listar Lixeira                          ║\n");
    printf("║                                  -> 6 • Recuperar cliente                       ║\n");
    printf("║                                  -> 7 • Excluir TODOS (Fisico)                  ║\n");
    printf("║                                  -> 0 • Voltar                                  ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}