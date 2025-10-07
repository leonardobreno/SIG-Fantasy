#include <stdio.h>     
#include <stdlib.h>   
#include <unistd.h>    
#include <string.h>    
#include "../Utilidades/utilidades.h"


char id_pedido[10] = "";
char id_fantasia[60] = "";
char id_cliente[60] = ""; 
char preco[60] = "";
char data_pedido[60] = "";


char menu_pedido(void);
int obter_proximo_id(void);
void cad_pedido(char id[], char id_fantasia[], char id_cliente[], char preco[], char data_pedido[]);
int menu_pesquisar_pedido(char id_pesquisar[]);
void menu_cadastro_pedido(void);
void menu_alterar_pedido(void);
void menu_deletar_pedido(char id_pesquisar[]);
void modulo_pedido(void);


char menu_pedido(void) {
    char op;
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  Modulo Pedidos                                 ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                -> 1 • Listar pedido                           ║\n");
    printf("║                                -> 2 • Cadastrar pedido                        ║\n");
    printf("║                                -> 3 • Alterar pedido                          ║\n");
    printf("║                                -> 4 • Excluir pedido                          ║\n");
    printf("║                                -> 5 • Voltar                                  ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}


int obter_proximo_id(void) {
    FILE *pedidos = fopen("Pedidos/pedidos.txt", "r");
    if (pedidos == NULL) {
        return 1;
    }

    char id_temp[10];
    int ultimo_id = 0;


    while (fscanf(pedidos, " %9[^,],%*[^,],%*[^,],%*[^,],%*[^\n]\n", id_temp) == 1) {
        int id_atual = atoi(id_temp);
        if (id_atual > ultimo_id) {
            ultimo_id = id_atual;
        }
    }
    fclose(pedidos);
    return ultimo_id + 1;
}


void cad_pedido(char id[], char id_fantasia[], char id_cliente[], char preco[], char data_pedido[]){
    system("mkdir -p Pedidos"); 
    FILE *pedidos = fopen("Pedidos/pedidos.txt", "a");
    if (pedidos != NULL) {
        fprintf(pedidos, "%s,%s,%s,%s,%s\n", id, id_fantasia, id_cliente, preco, data_pedido);
        fclose(pedidos);
    } else {
        printf("Erro: nao foi possivel abrir o arquivo de pedidos!\n");
        sleep(2);
    }
}

int menu_pesquisar_pedido(char id_pesquisar[]) {
    FILE *busca = fopen("Pedidos/pedidos.txt", "r");
    int encontrado = 0;
    char id_temp[10], fantasia_temp[60], cliente_temp[60], preco_temp[60], data_temp[60];

    if (busca == NULL) {
        printf("Arquivo de pedidos não encontrado ou vazio!\n");
        return 0;
    }

    while (fscanf(busca, " %9[^,],%59[^,],%59[^,],%59[^,],%59[^\n]\n", id_temp, fantasia_temp, cliente_temp, preco_temp, data_temp) == 5) {
        if (strcmp(id_pesquisar, id_temp) == 0) {
            encontrado = 1;
            strcpy(id_pedido, id_temp);
            strcpy(id_fantasia, fantasia_temp);
            strcpy(id_cliente, cliente_temp);
            strcpy(preco, preco_temp);
            strcpy(data_pedido, data_temp);
            break;
        }
    }
    fclose(busca);
    system("clear||cls");

    if (encontrado) {
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                 Pedido Encontrado                               ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("ID do Pedido: %s\n", id_pedido);
        printf("ID da Fantasia: %s\n", id_fantasia);
        printf("CPF do Cliente: %s\n", id_cliente);
        printf("Preço do Pedido: R$ %s\n", preco);
        printf("Data do Pedido: %s\n", data_pedido);
        return 1;
    } else {
        printf("ID pesquisado: %s\n", id_pesquisar);
        printf("\nNenhum pedido encontrado com este ID.\n");
        return 0;
    }
}

void menu_cadastro_pedido() {
    char novo_id[10];
    sprintf(novo_id, "%d", obter_proximo_id());

    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                Cadastro de Pedido                               ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("ID do Pedido gerado: %s\n", novo_id);

    printf("Digite o ID da fantasia: ");
    scanf(" %59[^\n]", id_fantasia);
    limpar_buffer();

    printf("Digite o CPF do cliente: ");
    scanf(" %59[^\n]", id_cliente);
    limpar_buffer();

    printf("Digite o preço do pedido: ");
    scanf(" %59[^\n]", preco);
    limpar_buffer();

    printf("Digite a data do pedido (DD/MM/AAAA): ");
    scanf(" %59[^\n]", data_pedido);
    limpar_buffer();

    cad_pedido(novo_id, id_fantasia, id_cliente, preco, data_pedido);

    printf("\nCadastro realizado com sucesso!\n");
    sleep(1);
}

void menu_alterar_pedido() {
    char id_pesquisar[10];
    FILE *busca = fopen("Pedidos/pedidos.txt", "r");
    FILE *alterar = fopen("Pedidos/alterar.txt", "w");
    int encontrado = 0;
    char id_temp[10], fantasia_temp[60], cliente_temp[60], preco_temp[60], data_temp[60];

    if (busca == NULL || alterar == NULL) {
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    system("clear||cls");
    printf("Digite o ID do pedido que deseja alterar: ");
    scanf(" %9[^\n]", id_pesquisar);
    limpar_buffer();

    while (fscanf(busca, " %9[^,],%59[^,],%59[^,],%59[^,],%59[^\n]\n", id_temp, fantasia_temp, cliente_temp, preco_temp, data_temp) == 5) {
        if (strcmp(id_pesquisar, id_temp) == 0) {
            encontrado = 1;
            printf("\nPedido encontrado! Insira os novos dados:\n");
            
            printf("Novo ID da fantasia: ");
            scanf(" %59[^\n]", fantasia_temp);
            limpar_buffer();

            printf("Novo CPF do cliente: ");
            scanf(" %59[^\n]", cliente_temp);
            limpar_buffer();

            printf("Novo preço do pedido: ");
            scanf(" %59[^\n]", preco_temp);
            limpar_buffer();

            printf("Nova data do pedido (DD/MM/AAAA): ");
            scanf(" %59[^\n]", data_temp);
            limpar_buffer();
        }
        fprintf(alterar, "%s,%s,%s,%s,%s\n", id_temp, fantasia_temp, cliente_temp, preco_temp, data_temp);
    }

    fclose(busca);
    fclose(alterar);
    remove("Pedidos/pedidos.txt");
    rename("Pedidos/alterar.txt", "Pedidos/pedidos.txt");

    system("clear||cls");
    if (encontrado) {
        printf("Pedido alterado com sucesso!\n");
    } else {
        printf("Nenhum pedido encontrado com o ID %s!\n", id_pesquisar);
    }
    sleep(2);
}

void menu_deletar_pedido(char id_pesquisar[]) {
    FILE *busca = fopen("Pedidos/pedidos.txt", "r");
    FILE *excluir = fopen("Pedidos/temp_excluir.txt", "w");
    char id_temp[10], linha[256]; 
    int encontrado = 0;

    if (busca == NULL || excluir == NULL) {
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), busca)) {
        sscanf(linha, "%[^,]", id_temp);
        if (strcmp(id_pesquisar, id_temp) != 0) {
            fputs(linha, excluir);
        } else {
            encontrado = 1;
        }
    }

    fclose(busca);
    fclose(excluir);

    remove("Pedidos/pedidos.txt");
    rename("Pedidos/temp_excluir.txt", "Pedidos/pedidos.txt");

    system("clear||cls");
    if (encontrado) {
        printf("Pedido com ID %s excluído com sucesso!\n", id_pesquisar);
    } else {
        printf("Nenhum pedido encontrado com o ID %s!\n", id_pesquisar);
    }
    sleep(2);
}



void modulo_pedido(void) {
    char op;
    char id_procurar[10];
    int pedido_achado;

    do {
        op = menu_pedido();
        switch(op) {
            case '1':
                printf("\nDigite o ID do pedido que deseja pesquisar: ");
                scanf(" %9[^\n]", id_procurar);
                limpar_buffer();
                menu_pesquisar_pedido(id_procurar);
                printf("\nPressione Enter para voltar...\n");
                getchar();
                break;
            case '2':
                menu_cadastro_pedido();
                break;
            case '3':
                menu_alterar_pedido();
                break;
            case '4':
                printf("\nDigite o ID do pedido que deseja excluir: ");
                scanf(" %9[^\n]", id_procurar);
                limpar_buffer();
                
                pedido_achado = menu_pesquisar_pedido(id_procurar);
                if (pedido_achado) {
                    char op_delete;
                    printf("\nDeseja realmente excluir este pedido? (1 - Sim / 2 - Nao): ");
                    scanf(" %c", &op_delete);
                    limpar_buffer();

                    if (op_delete == '1') {
                        menu_deletar_pedido(id_procurar);
                    } else {
                        printf("\nOperação de exclusão cancelada.\n");
                        sleep(1);
                    }
                } else {
                    printf("\nPressione Enter para continuar...");
                    getchar();
                }
                break;
            case '5':
                printf("Voltando ao menu principal...\n");
                sleep(1);
                break;
            default:
                printf("Opção inválida!\n");
                sleep(1);
        }
    } while (op != '5');
}
