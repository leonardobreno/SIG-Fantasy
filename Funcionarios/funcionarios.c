#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionarios.h"
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

Funcionario* funcionarios = NULL;
int num_funcionarios = 0;
int capacidade_funcionarios = 0;

void gerenciar_funcionarios(void) {
    carregar_funcionarios_binario();
    char op;
    do {
        op = menu_funcionario();
        switch (op) {
            case '1':
                menu_pesquisar_funcionario();
                break;
            case '2':
                menu_cadastro_funcionario();
                break;
            case '3':
                menu_alterar_funcionario();
                break;
            case '4':
                menu_excluir_logico_funcionario();
                break;
            case '5':
                menu_listar_excluidos_funcionario();
                break;
            case '6':
                menu_recuperar_funcionario();
                break;
            case '7':
                menu_excluir_fisico_funcionarios();
                break;
            case '0':
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                SLEEP(1);
        }
    } while (op != '0');
    liberar_memoria_funcionarios();
}

void salvar_funcionarios_binario() {
    FILE* arquivo = fopen("Funcionarios/funcionarios.dat", "wb");
    if (!arquivo) {
        printf("Erro fatal: Não foi possível abrir o arquivo para escrita!\n");
        return;
    }
    fwrite(funcionarios, sizeof(Funcionario), num_funcionarios, arquivo);
    fclose(arquivo);
}

void carregar_funcionarios_binario() {
    FILE* arquivo = fopen("Funcionarios/funcionarios.dat", "rb");
    if (!arquivo) {
        printf("Arquivo de dados 'funcionarios.dat' não encontrado. Iniciando com base de dados vazia.\n");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    rewind(arquivo);

    num_funcionarios = tamanho_arquivo / sizeof(Funcionario);
    capacidade_funcionarios = num_funcionarios;

    funcionarios = malloc(num_funcionarios * sizeof(Funcionario));
    if (!funcionarios) {
        printf("Erro fatal: Falha ao alocar memória!\n");
        fclose(arquivo);
        return;
    }

    fread(funcionarios, sizeof(Funcionario), num_funcionarios, arquivo);
    fclose(arquivo);
}

void liberar_memoria_funcionarios() {
    if (funcionarios) {
        free(funcionarios);
        funcionarios = NULL;
        num_funcionarios = 0;
        capacidade_funcionarios = 0;
    }
}

void menu_cadastro_funcionario() {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           Cadastro Funcionario                          ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════╝\n");

    Funcionario novo;

    printf("Digite o nome: ");
    scanf(" %50[^\n]", novo.nome);
    limpar_buffer();

    printf("Digite o CPF: ");
    scanf(" %14[^\n]", novo.cpf);
    limpar_buffer();

    for (int i = 0; i < num_funcionarios; i++) {
        if (strcmp(novo.cpf, funcionarios[i].cpf) == 0) {
            printf("\nERRO: Já existe um funcionário (ativo ou inativo) com este CPF!\n");
            SLEEP(2);
            return;
        }
    }

    printf("Digite o celular: ");
    scanf(" %19[^\n]", novo.celular);
    limpar_buffer();

    printf("Digite o email: ");
    scanf(" %50[^\n]", novo.email);
    limpar_buffer();

    printf("Digite o salário: ");
    scanf(" %19[^\n]", novo.salario);
    limpar_buffer();

    novo.ativo = 1;

    Funcionario* temp = realloc(funcionarios, (num_funcionarios + 1) * sizeof(Funcionario));
    if (!temp) {
        printf("Erro: Não foi possível alocar memória para o novo funcionário!\n");
        return;
    }
    funcionarios = temp;

    funcionarios[num_funcionarios] = novo;
    num_funcionarios++;
    capacidade_funcionarios++;

    salvar_funcionarios_binario();
    printf("\nCadastro realizado com sucesso!\n");
    SLEEP(1);
}

void menu_pesquisar_funcionario() {
    char cpf_procurar[15];
    int encontrado = 0;

    system(CLEAR_SCREEN);
    printf("Digite o CPF do funcionário que deseja pesquisar: ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_funcionarios; i++) {
        if (strcmp(cpf_procurar, funcionarios[i].cpf) == 0 && funcionarios[i].ativo == 1) {
            system(CLEAR_SCREEN);
            printf("╔═════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                       Funcionário Encontrado                            ║\n");
            printf("╚═════════════════════════════════════════════════════════════════════════╝\n");
            printf("Nome: %s\nCPF: %s\nCelular: %s\nEmail: %s\nSalário: %s\n",
                   funcionarios[i].nome,
                   funcionarios[i].cpf,
                   funcionarios[i].celular,
                   funcionarios[i].email,
                   funcionarios[i].salario);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNenhum funcionário *ativo* encontrado com o CPF: %s\n", cpf_procurar);
    }

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

void menu_alterar_funcionario() {
    char cpf_procurar[15];
    int encontrado_idx = -1;

    system(CLEAR_SCREEN);
    printf("Digite o CPF do funcionário que deseja alterar: ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_funcionarios; i++) {
        if (strcmp(cpf_procurar, funcionarios[i].cpf) == 0 && funcionarios[i].ativo == 1) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx != -1) {
        system(CLEAR_SCREEN);
        printf("╔═════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                           Alterar Funcionário                           ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════╝\n");
        printf("Funcionário encontrado! (Deixe em branco para não alterar)\n\n");

        printf("Nome: %s\n", funcionarios[encontrado_idx].nome);
        printf("CPF: %s\n", funcionarios[encontrado_idx].cpf);

        char novo_celular[20], novo_email[51], novo_salario[20];

        printf("Celular atual: %s\n", funcionarios[encontrado_idx].celular);
        printf("Digite novo celular: ");
        scanf(" %19[^\n]", novo_celular);
        limpar_buffer();

        printf("Email atual: %s\n", funcionarios[encontrado_idx].email);
        printf("Digite novo email: ");
        scanf(" %50[^\n]", novo_email);
        limpar_buffer();

        printf("Salário atual: %s\n", funcionarios[encontrado_idx].salario);
        printf("Digite novo salário: ");
        scanf(" %19[^\n]", novo_salario);
        limpar_buffer();

        if (strlen(novo_celular) > 0) strcpy(funcionarios[encontrado_idx].celular, novo_celular);
        if (strlen(novo_email) > 0) strcpy(funcionarios[encontrado_idx].email, novo_email);
        if (strlen(novo_salario) > 0) strcpy(funcionarios[encontrado_idx].salario, novo_salario);

        salvar_funcionarios_binario();
        printf("\nFuncionário alterado com sucesso!\n");
    } else {
        printf("\nNenhum funcionário *ativo* encontrado com o CPF: %s\n", cpf_procurar);
    }

    SLEEP(1);
}

void menu_excluir_logico_funcionario() {
    char cpf_procurar[15];
    int encontrado_idx = -1;

    system(CLEAR_SCREEN);
    printf("Digite o CPF do funcionário para exclusão lógica: ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_funcionarios; i++) {
        if (strcmp(cpf_procurar, funcionarios[i].cpf) == 0 && funcionarios[i].ativo == 1) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx != -1) {
        funcionarios[encontrado_idx].ativo = 0;
        salvar_funcionarios_binario();
        printf("Funcionário excluído logicamente (na lixeira).\n");
    } else {
        printf("Nenhum funcionário ativo encontrado com esse CPF!\n");
    }

    SLEEP(1);
}

void menu_listar_excluidos_funcionario() {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           Lixeira de Funcionários                       ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════╝\n");

    int encontrados = 0;
    for (int i = 0; i < num_funcionarios; i++) {
        if (funcionarios[i].ativo == 0) {
            printf("Nome: %s\nCPF: %s\n---------------------------------------------------\n",
                   funcionarios[i].nome, funcionarios[i].cpf);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum funcionário excluído encontrado.\n");
    }

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

void menu_recuperar_funcionario() {
    char cpf_procurar[15];
    int encontrado_idx = -1;

    system(CLEAR_SCREEN);
    printf("Digite o CPF do funcionário para recuperar da lixeira: ");
    scanf(" %14[^\n]", cpf_procurar);
    limpar_buffer();

    for (int i = 0; i < num_funcionarios; i++) {
        if (strcmp(cpf_procurar, funcionarios[i].cpf) == 0) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx == -1) {
        printf("Nenhum funcionário encontrado com esse CPF!\n");
    } else {
        if (funcionarios[encontrado_idx].ativo == 1) {
            printf("Este funcionário já está ativo!\n");
        } else {
            funcionarios[encontrado_idx].ativo = 1;
            salvar_funcionarios_binario();
            printf("Funcionário recuperado com sucesso!\n");
        }
    }

    SLEEP(1);
}

void menu_excluir_fisico_funcionarios() {
    char confirmacao[5];

    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         EXCLUSÃO FÍSICA TOTAL                           ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nATENÇÃO: Isso apagará todos os dados de funcionários, inclusive os da lixeira.\n");
    printf("Digite 'SIM' para confirmar: ");
    scanf(" %4[^\n]", confirmacao);
    limpar_buffer();

    if (strcmp(confirmacao, "SIM") == 0) {
        liberar_memoria_funcionarios();
        funcionarios = NULL;
        num_funcionarios = 0;
        capacidade_funcionarios = 0;
        salvar_funcionarios_binario();
        printf("SUCESSO: Todos os dados de funcionários foram excluídos fisicamente.\n");
    } else {
        printf("Operação cancelada.\n");
    }

    SLEEP(2);
}

char menu_funcionario(void) {
    char op;
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                            Módulo Funcionários                          ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                    -> 1 • Pesquisar funcionário                         ║\n");
    printf("║                    -> 2 • Cadastrar funcionário                         ║\n");
    printf("║                    -> 3 • Alterar funcionário                           ║\n");
    printf("║                    -> 4 • Deletar funcionário (Lixeira)                 ║\n");
    printf("║                    -> 5 • Listar Lixeira                                ║\n");
    printf("║                    -> 6 • Recuperar funcionário                         ║\n");
    printf("║                    -> 7 • Excluir TODOS (Físico)                        ║\n");
    printf("║                    -> 0 • Voltar                                        ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}
