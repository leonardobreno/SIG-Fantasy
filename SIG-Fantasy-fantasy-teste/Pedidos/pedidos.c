#include <stdio.h>   
    // Entrada e saída
#include <stdlib.h>  
    // Funções utilitárias
#include <unistd.h>  
    // Funções do Linux/Unix
#include <string.h>  
    // Manipulação de strings
#include "../Utilidades/utilidades.h"

char id_fantasia[60] = "";
char id_cliente[60] = "";
char preco[60] = "";
char data_pedido[60] = "";

char menu_pedido(void) {
    char op;
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                    Modulo Pedidos                               ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                               -> 1 • Listar pedido                              ║\n");    
    printf("║                               -> 2 • Cadastrar pedido                           ║\n");
    printf("║                               -> 3 • Alterar pedido                             ║\n");
    printf("║                               -> 4 • Excluir pedido                             ║\n");
    printf("║                               -> 5    • Voltar                                  ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &op);
    limpar_buffer();
    return op;
}

void cad_pedido(char id_fantasia[], char id_cliente[], char preco[], char data_pedido[]){
    FILE *pedidos = fopen("Pedidos/pedidos.txt", "a");
    if(pedidos != NULL){
        fprintf(pedidos, "%s, %s, %s, %s\n", id_fantasia, id_cliente, preco, data_pedido);
        fclose(pedidos);
    }
    else{
        printf("arquivo nao encontrado!\n");
    }
}

int menu_pesquisar_pedido(char data_pesquisar[]) {
    int comparacao = strcmp(data_pesquisar, data_pedido);
    if (comparacao == 0)
    {
        system("clear||cls");
        printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                    Pedido Pesquisado                            ║\n");
        printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("Id da fantasia: %s\n", id_fantasia);
        printf("Id do cliente: %s\n", id_cliente);
        printf("Preco do pedido: %s\n", preco);
        printf("Data do pedido: %s\n", data_pedido);
        return 1;
    }
    else
    {
        system("clear||cls");
        printf("data_pesquisada: %s\n", data_pesquisar);
        printf("\nNao tem nenhum pedido nessa data.");
        return 0;
    }
    
}

void menu_cadastro_pedido(char id_fantasia[], char id_cliente[], char preco[], char data_pedido[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Cadastro Pedido                               ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o id da fantasia: ");
    scanf("%[^\n]", id_fantasia);
    limpar_buffer();

    printf("Digite o id do cliente: ");
    scanf("%[^\n]", id_cliente);
    limpar_buffer();

    printf("Digite o preco do pedido: ");
    scanf("%[^\n]", preco);
    limpar_buffer();

    printf("Digite a data do pedido: ");
    scanf(" %[^\n]", data_pedido);
    limpar_buffer();

    cad_pedido(id_fantasia, id_cliente, preco, data_pedido);

    printf("\nCadastro realizado!\n");
    sleep(1);
}

void menu_alterar_pedido(int* id_fantasia, int* id_cliente, float* preco, char data_pedido[]) {
    system("clear||cls");
    printf("╔═════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   Alterar Pedido                                ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Digite o novo id da fantasia: ");
    scanf(" %d", id_fantasia);
    limpar_buffer();

    printf("Digite o novo id do cliente: ");
    scanf(" %d", id_cliente);
    limpar_buffer();

    printf("Digite o novo preco do pedido: ");
    scanf(" %f", preco);
    limpar_buffer();

    printf("Digite a nova data do pedido: ");
    scanf(" %[^\n]", data_pedido);
    limpar_buffer();

    printf("\nPedido alterado!\n");
    sleep(1);
}

void menu_deletar_pedido(int* id_fantasia, int* id_cliente, float* preco, char data_pedido[]) {
    *id_fantasia = 0;
    *id_cliente = 0;
    *preco = 0;
    data_pedido[0] = '\0';
}

void modulo_pedido(void) {
    char op;
    char op_delete = '2';
    char data_procurar[50] = "";
    int pedido_achado;

    do {
        op = menu_pedido();
        switch(op) {
            case '1':
                printf("\nDigite a data do pedido que deseja pesquisar: ");
                scanf("%[^\n]", data_procurar);
                menu_pesquisar_pedido(data_procurar);
                getchar();
                printf("\nPressione Enter para voltar...\n");
                limpar_buffer();                  
                break;
            case '2':
                menu_cadastro_pedido(&id_fantasia, &id_cliente, &preco, data_pedido);
                break;
            case '3':
                menu_alterar_pedido(&id_fantasia, &id_cliente, &preco, data_pedido);
                break;
            case '4':
                system("clear||cls");
                printf("\nDigite a data do pedido que deseja pesquisar: ");
                scanf("%[^\n]", data_procurar);
                pedido_achado = menu_pesquisar_pedido(data_procurar);
                getchar();
                if (pedido_achado == 1)
                {
                    printf("\nDeseja excluir esse pedido?\n");
                    printf("1 - Sim\n");
                    printf("2 - Nao\n");
                    op_delete = getchar();
                    limpar_buffer();
                    switch (op_delete){
                    case '1':
                        menu_deletar_pedido(&id_fantasia, &id_cliente, &preco, data_pedido);
                        system("clear||cls");
                        printf("Pedido excluido com sucesso!\n");
                        sleep(1);
                        break;
                    
                    case '2':
                        printf("Abortando exclusao...\n");
                        sleep(1);
                        break;
                    
                    default:
                        printf("Opção inválida!\n");
                        sleep(1);
                        break;
                    }
                    sleep(1);  
                }
                else {
                    sleep(1);
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
    } while(op != '5');
}
