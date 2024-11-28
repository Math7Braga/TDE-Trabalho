#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct para cidades
typedef struct {
    int codigo;
    char nome[50];
    char estado[30];
    int populacao;
} Cidade;

// Nome do arquivo para armazenar as cidades
const char *arquivoCidades = "cidades.txt";

// Declaração das funções
void incluirCidade();
void alterarCidade();
void excluirCidade();
void consultarCidade();
void listarCidades();
void menu();

// Função principal
int main() {
    menu();
    return 0;
}

// Função para exibir o menu do programa
void menu() {
    int opcao;
    do {
        printf("\n=== Cadastro de Cidades ===\n");
        printf("1. Incluir nova cidade\n");
        printf("2. Alterar dados de uma cidade\n");
        printf("3. Excluir uma cidade\n");
        printf("4. Consultar cidade pelo código\n");
        printf("5. Listar todas as cidades\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1: incluirCidade(); break;
            case 2: alterarCidade(); break;
            case 3: excluirCidade(); break;
            case 4: consultarCidade(); break;
            case 5: listarCidades(); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para incluir uma nova cidade
void incluirCidade() {
    Cidade cidade;
    FILE *fp = fopen(arquivoCidades, "a");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o código da cidade: ");
    scanf("%d", &cidade.codigo);
    getchar(); // Limpa o buffer do teclado
    printf("Digite o nome da cidade: ");
    fgets(cidade.nome, 50, stdin);
    strtok(cidade.nome, "\n"); // Remove o '\n'
    printf("Digite o estado da cidade: ");
    fgets(cidade.estado, 30, stdin);
    strtok(cidade.estado, "\n"); // Remove o '\n'
    printf("Digite a população da cidade: ");
    scanf("%d", &cidade.populacao);

    fprintf(fp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
    fclose(fp);

    printf("Cidade incluída com sucesso!\n");
}

// Função para alterar os dados de uma cidade
void alterarCidade() {
    int codigo, encontrado = 0;
    Cidade cidade;
    FILE *fp = fopen(arquivoCidades, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o código da cidade que deseja alterar: ");
    scanf("%d", &codigo);
    getchar(); // Limpa o buffer do teclado

    while (fscanf(fp, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            encontrado = 1;
            printf("Digite o novo nome da cidade: ");
            fgets(cidade.nome, 50, stdin);
            strtok(cidade.nome, "\n"); // Remove o '\n'
            printf("Digite o novo estado da cidade: ");
            fgets(cidade.estado, 30, stdin);
            strtok(cidade.estado, "\n"); // Remove o '\n'
            printf("Digite a nova população da cidade: ");
            scanf("%d", &cidade.populacao);
            getchar(); // Limpa o buffer do teclado
        }
        fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
    }

    fclose(fp);
    fclose(temp);

    remove(arquivoCidades);
    rename("temp.txt", arquivoCidades);

    if (encontrado) {
        printf("Dados da cidade alterados com sucesso!\n");
    } else {
        printf("Cidade com código %d não encontrada!\n", codigo);
    }
}

// Função para excluir uma cidade pelo código
void excluirCidade() {
    int codigo, encontrado = 0;
    Cidade cidade;
    FILE *fp = fopen(arquivoCidades, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o código da cidade que deseja excluir: ");
    scanf("%d", &codigo);

    while (fscanf(fp, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            encontrado = 1;
        } else {
            fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(arquivoCidades);
    rename("temp.txt", arquivoCidades);

    if (encontrado) {
        printf("Cidade excluída com sucesso!\n");
    } else {
        printf("Cidade com código %d não encontrada!\n", codigo);
    }
}

// Função para consultar uma cidade pelo código
void consultarCidade() {
    int codigo, encontrado = 0;
    Cidade cidade;
    FILE *fp = fopen(arquivoCidades, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o código da cidade que deseja consultar: ");
    scanf("%d", &codigo);

    while (fscanf(fp, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            printf("\n=== Dados da Cidade ===\n");
            printf("Código: %d\n", cidade.codigo);
            printf("Nome: %s\n", cidade.nome);
            printf("Estado: %s\n", cidade.estado);
            printf("População: %d\n", cidade.populacao);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (!encontrado) {
        printf("Cidade com código %d não encontrada!\n", codigo);
    }
}

// Função para listar todas as cidades cadastradas
void listarCidades() {
    Cidade cidade;
    FILE *fp = fopen(arquivoCidades, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\n=== Lista de Cidades ===\n");
    while (fscanf(fp, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        printf("Código: %d | Nome: %s | Estado: %s | População: %d\n",
               cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
    }

    fclose(fp);
}
