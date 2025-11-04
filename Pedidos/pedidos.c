#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidos.h"
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

Pedido* pedidos = NULL;
int num_pedidos = 0;

void gerenciar_pedidos(void) {
    carregar_pedidos_binario();
    char op;
    do {
        op = menu_pedido();
        switch (op) {
            case '1':
                menu_pesquisar_pedido();
                break;
            case '2':
                menu_cadastro_pedido();
                break;
            case '3':
                menu_alterar_pedido();
                break;
            case '4':
                menu_excluir_logico_pedido();
                break;
            case '5':
                menu_listar_excluidos_pedidos();
                break;
            case '6':
                menu_recuperar_pedido();
                break;
            case '7':
                menu_excluir_fisico_pedidos();
                break;
            case '0':
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                SLEEP(1);
        }
    } while (op != '0');
    liberar_memoria_pedidos();
}

unsigned long get_next_pedido_id() {
    if (num_pedidos == 0) {
        return 1;
    }
    
    unsigned long max_id = pedidos[0].id_pedido;
    for (int i = 1; i < num_pedidos; i++) {
        if (pedidos[i].id_pedido > max_id) {
            max_id = pedidos[i].id_pedido;
        }
    }
    return max_id + 1;
}

void salvar_pedidos_binario() {
    FILE* arquivo = fopen("Pedidos/pedidos.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro fatal: Nao foi possivel abrir o arquivo para escrita!\n");
        return;
    }
    fwrite(pedidos, sizeof(Pedido), num_pedidos, arquivo);
    fclose(arquivo);
}

void carregar_pedidos_binario() {
    FILE* arquivo = fopen("Pedidos/pedidos.dat", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de dados 'pedidos.dat' nao encontrado. Iniciando com base de dados vazia.\n");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    rewind(arquivo);

    num_pedidos = tamanho_arquivo / sizeof(Pedido);

    pedidos = (Pedido*) malloc(num_pedidos * sizeof(Pedido));
    if (pedidos == NULL) {
        printf("Erro fatal: Falha ao alocar memoria!\n");
        fclose(arquivo);
        return;
    }
    fread(pedidos, sizeof(Pedido), num_pedidos, arquivo);
    fclose(arquivo);
}

void liberar_memoria_pedidos() {
    if (pedidos != NULL) {
        free(pedidos);
        pedidos = NULL;
        num_pedidos = 0;
    }
}

void menu_cadastro_pedido() {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 Cadastro Pedido                                 ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    Pedido novo_pedido;
    char buffer_preco[20];

    novo_pedido.id_pedido = get_next_pedido_id();
    printf("ID do Pedido (Gerado Automaticamente): %lu\n", novo_pedido.id_pedido);

    do {
        printf("Digite o CPF do cliente (11 números): ");
        scanf(" %14[^\n]", novo_pedido.cpf_cliente);
        limpar_buffer();
        if (!validar_cpf(novo_pedido.cpf_cliente)) {
            printf("ERRO: CPF inválido! Deve conter exatamente 11 números.\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("Digite o ID/Nome da fantasia (1-19 caracteres): ");
        scanf(" %19[^\n]", novo_pedido.id_fantasia);
        limpar_buffer();
        if (!validar_texto_geral(novo_pedido.id_fantasia, 19)) {
            printf("ERRO: Fantasia inválida! Não pode ser vazio ou conter apenas espaços.\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("Digite o Preço (ex: 150.90): ");
        scanf(" %19[^\n]", buffer_preco);
        limpar_buffer();
        if (!validar_salario_string(buffer_preco)) {
            printf("ERRO: Preço inválido! Use apenas números e um ponto/vírgula.\n");
        } else {
            break;
        }
    } while (1);
    sscanf(buffer_preco, "%f", &novo_pedido.preco);
    
    do {
        printf("Digite a Data do Pedido (dd/mm/aaaa): ");
        scanf(" %10[^\n]", novo_pedido.data_pedido);
        limpar_buffer();
        if (!validar_data(novo_pedido.data_pedido)) {
            printf("ERRO: Data inválida! Use o formato dd/mm/aaaa com valores válidos.\n");
        } else {
            break;
        }
    } while (1);

    novo_pedido.ativo = 1;

    Pedido* temp = realloc(pedidos, (num_pedidos + 1) * sizeof(Pedido));
    if (temp == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        return;
    }
    pedidos = temp;

    pedidos[num_pedidos] = novo_pedido;
    num_pedidos++;

    salvar_pedidos_binario();

    printf("\nCadastro realizado com sucesso!\n");
    SLEEP(1);
}

void menu_pesquisar_pedido() {
    char id_str[20];
    unsigned long id_procurar;
    int encontrado = 0;

    system(CLEAR_SCREEN);
    
    do {
        printf("Digite o ID do pedido que deseja pesquisar: ");
        scanf(" %19[^\n]", id_str);
        limpar_buffer();
        if (!validar_id_numerico_string(id_str)) {
            printf("ERRO: ID inválido! Digite apenas números.\n");
        } else {
            break;
        }
    } while(1);
    id_procurar = strtoul(id_str, NULL, 10);

    for (int i = 0; i < num_pedidos; i++) {
        if (pedidos[i].id_pedido == id_procurar && pedidos[i].ativo == 1) {
            system(CLEAR_SCREEN);
            printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                                Pedido Encontrado                                ║\n");
            printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
            printf("ID Pedido: %lu\n", pedidos[i].id_pedido);
            printf("CPF Cliente: %s\n", pedidos[i].cpf_cliente);
            printf("Fantasia: %s\n", pedidos[i].id_fantasia);
            printf("Preço: R$ %.2f\n", pedidos[i].preco);
            printf("Data: %s\n", pedidos[i].data_pedido);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNenhum pedido *ativo* encontrado com o ID: %lu\n", id_procurar);
    }
    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

void menu_alterar_pedido() {
    char id_str[20];
    unsigned long id_procurar;
    int encontrado_idx = -1;

    system(CLEAR_SCREEN);

    do {
        printf("Digite o ID do pedido que deseja alterar: ");
        scanf(" %19[^\n]", id_str);
        limpar_buffer();
        if (!validar_id_numerico_string(id_str)) {
            printf("ERRO: ID inválido! Digite apenas números.\n");
        } else {
            break;
        }
    } while(1);
    id_procurar = strtoul(id_str, NULL, 10);

    for (int i = 0; i < num_pedidos; i++) {
        if (pedidos[i].id_pedido == id_procurar && pedidos[i].ativo == 1) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx != -1) {
        system(CLEAR_SCREEN);
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                 Alterar Pedido                                  ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("Pedido encontrado! (Deixe em branco e pressione Enter para nao alterar)\n\n");
        
        printf("ID Pedido: %lu (Nao alteravel)\n", pedidos[encontrado_idx].id_pedido);

        char novo_cpf[15], nova_fantasia[20], nova_data[11];
        char buffer_preco[20];
        
        do {
            printf("CPF Cliente atual: %s\n", pedidos[encontrado_idx].cpf_cliente);
            printf("Digite o novo CPF: ");
            scanf(" %14[^\n]", novo_cpf);
            limpar_buffer();
            if (strlen(novo_cpf) == 0) break;
            if (!validar_cpf(novo_cpf)) {
                printf("ERRO: CPF inválido! Tente novamente.\n");
            } else {
                strcpy(pedidos[encontrado_idx].cpf_cliente, novo_cpf);
                break;
            }
        } while (1);

        do {
            printf("Fantasia atual: %s\n", pedidos[encontrado_idx].id_fantasia);
            printf("Digite a nova fantasia: ");
            scanf(" %19[^\n]", nova_fantasia);
            limpar_buffer();
            if (strlen(nova_fantasia) == 0) break;
            if (!validar_texto_geral(nova_fantasia, 19)) {
                printf("ERRO: Fantasia inválida! Tente novamente.\n");
            } else {
                strcpy(pedidos[encontrado_idx].id_fantasia, nova_fantasia);
                break;
            }
        } while (1);

        do {
            printf("Preço atual: %.2f\n", pedidos[encontrado_idx].preco);
            printf("Digite o novo preço: ");
            scanf(" %19[^\n]", buffer_preco);
            limpar_buffer();
            if (strlen(buffer_preco) == 0) break;
            if (!validar_salario_string(buffer_preco)) {
                printf("ERRO: Preço inválido! Tente novamente.\n");
            } else {
                sscanf(buffer_preco, "%f", &pedidos[encontrado_idx].preco);
                break;
            }
        } while (1);

        do {
            printf("Data atual: %s\n", pedidos[encontrado_idx].data_pedido);
            printf("Digite a nova data: ");
            scanf(" %10[^\n]", nova_data);
            limpar_buffer();
            if (strlen(nova_data) == 0) break;
            if (!validar_data(nova_data)) {
                printf("ERRO: Data inválida! Tente novamente.\n");
            } else {
                strcpy(pedidos[encontrado_idx].data_pedido, nova_data);
                break;
            }
        } while (1);
        
        salvar_pedidos_binario();
        printf("\nPedido alterado com sucesso!\n");
    } else {
        printf("\nNenhum pedido *ativo* encontrado com o ID: %lu\n", id_procurar);
    }
    SLEEP(1);
}

void menu_excluir_logico_pedido() {
    char id_str[20];
    unsigned long id_procurar;
    int encontrado_idx = -1;

    system(CLEAR_SCREEN);
    
    do {
        printf("Digite o ID do pedido que deseja deletar (Exclusao Logica): ");
        scanf(" %19[^\n]", id_str);
        limpar_buffer();
        if (!validar_id_numerico_string(id_str)) {
            printf("ERRO: ID inválido! Digite apenas números.\n");
        } else {
            break;
        }
    } while(1);
    id_procurar = strtoul(id_str, NULL, 10);

    for (int i = 0; i < num_pedidos; i++) {
        if (pedidos[i].id_pedido == id_procurar && pedidos[i].ativo == 1) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx != -1) {
        pedidos[encontrado_idx].ativo = 0;
        salvar_pedidos_binario();
        printf("Pedido excluido (logicamente) com sucesso! Ele esta na lixeira.\n");
    } else {
        printf("Nenhum pedido ativo encontrado com esse ID!\n");
    }
    SLEEP(1);
}

void menu_listar_excluidos_pedidos() {
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               Lixeira de Pedidos                                ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");

    int encontrados = 0;
    for (int i = 0; i < num_pedidos; i++) {
        if (pedidos[i].ativo == 0) {
            printf("ID Pedido: %lu\n", pedidos[i].id_pedido);
            printf("CPF Cliente: %s\n", pedidos[i].cpf_cliente);
            printf("Fantasia: %s\n", pedidos[i].id_fantasia);
            printf("---------------------------------------------------\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum pedido excluido encontrado na lixeira.\n");
    }

    printf("\nPressione Enter para continuar...");
    limpar_buffer();
}

void menu_recuperar_pedido() {
    char id_str[20];
    unsigned long id_procurar;
    int encontrado_idx = -1;

    system(CLEAR_SCREEN);

    do {
        printf("Digite o ID do pedido que deseja RECUPERAR da lixeira: ");
        scanf(" %19[^\n]", id_str);
        limpar_buffer();
        if (!validar_id_numerico_string(id_str)) {
            printf("ERRO: ID inválido! Digite apenas números.\n");
        } else {
            break;
        }
    } while(1);
    id_procurar = strtoul(id_str, NULL, 10);

    for (int i = 0; i < num_pedidos; i++) {
        if (pedidos[i].id_pedido == id_procurar) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx == -1) {
        printf("Nenhum pedido (ativo ou inativo) encontrado com esse ID!\n");
    } else {
        if (pedidos[encontrado_idx].ativo == 1) {
            printf("Este pedido ja esta ativo! Nao precisa recuperar.\n");
        } else {
            pedidos[encontrado_idx].ativo = 1;
            salvar_pedidos_binario();
            printf("Pedido recuperado com sucesso!\n");
        }
    }
    SLEEP(1);
}

void menu_excluir_fisico_pedidos() {
    char confirmacao[5];
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                             EXCLUSAO FISICA TOTAL                               ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n!!! ATENCAO !!!\n");
    printf("Isso apagara TODOS os dados de pedidos do sistema, inclusive os da lixeira.\n");
    printf("Esta acao NAO PODE ser desfeita.\n");
    printf("O arquivo 'pedidos.dat' sera esvaziado.\n\n");
    printf("Digite 'SIM' (em maiusculas) para confirmar: ");
    scanf(" %4[^\n]", confirmacao);
    limpar_buffer();

    if (strcmp(confirmacao, "SIM") == 0) {
        
        liberar_memoria_pedidos(); 
        
        pedidos = NULL;
        num_pedidos = 0;

        salvar_pedidos_binario(); 

        printf("SUCESSO: Todos os dados de pedidos foram excluidos fisicamente.\n");
    } else {
        printf("Operacao cancelada.\n");
    }
    SLEEP(2);
}


char menu_pedido(void) {
    char op;
    system(CLEAR_SCREEN);
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 Modulo Pedidos                                  ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                               -> 1 • Pesquisar pedido                           ║\n");
    printf("║                               -> 2 • Cadastrar pedido                           ║\n");
    printf("║                               -> 3 • Alterar pedido                             ║\n");
    printf("║                               -> 4 • Deletar pedido (Lixeira)                     ║\n");
    printf("║                               -> 5 • Listar Lixeira                             ║\n");
    printf("║                               -> 6 • Recuperar pedido                           ║\n");
    printf("║                               -> 7 • Excluir TODOS (Fisico)                     ║\n");
    printf("║                               -> 0 • Voltar                                     ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}