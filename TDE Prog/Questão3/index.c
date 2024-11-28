#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct para livro
typedef struct {
    int codigo;
    char titulo[50];
    char autor[50];
    int ano;
} Livro;

// Nome do arquivo de dados
const char *arquivoLivros = "livros.txt";

// Funções
void adicionarLivro();
void alterarLivro();
void excluirLivro();
void consultarLivro();
void listarLivros();
void menu();

// Função principal
int main() {
    menu();
    return 0;
}

// Menu do programa
void menu() {
    int opcao;
    do {
        printf("\n=== Gerenciamento de Livros ===\n");
        printf("1. Adicionar novo livro\n");
        printf("2. Alterar dados de um livro\n");
        printf("3. Excluir um livro\n");
        printf("4. Consultar informações de um livro\n");
        printf("5. Listar todos os livros\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1: adicionarLivro(); break;
            case 2: alterarLivro(); break;
            case 3: excluirLivro(); break;
            case 4: consultarLivro(); break;
            case 5: listarLivros(); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para adicionar um novo livro
void adicionarLivro() {
    Livro livro;
    FILE *fp = fopen(arquivoLivros, "a");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o código do livro: ");
    scanf("%d", &livro.codigo);
    getchar(); // Limpar buffer
    printf("Digite o título do livro: ");
    fgets(livro.titulo, 50, stdin);
    strtok(livro.titulo, "\n"); // Remove o '\n'
    printf("Digite o autor do livro: ");
    fgets(livro.autor, 50, stdin);
    strtok(livro.autor, "\n"); // Remove o '\n'
    printf("Digite o ano de publicação: ");
    scanf("%d", &livro.ano);

    fprintf(fp, "%d,%s,%s,%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
    fclose(fp);

    printf("Livro adicionado com sucesso!\n");
}

// Função para alterar os dados de um livro
void alterarLivro() {
    int codigo, encontrado = 0;
    Livro livro;
    FILE *fp = fopen(arquivoLivros, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o código do livro que deseja alterar: ");
    scanf("%d", &codigo);
    getchar(); // Limpar buffer

    while (fscanf(fp, "%d,%49[^,],%49[^,],%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) != EOF) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            printf("Digite o novo título: ");
            fgets(livro.titulo, 50, stdin);
            strtok(livro.titulo, "\n"); // Remove o '\n'
            printf("Digite o novo autor: ");
            fgets(livro.autor, 50, stdin);
            strtok(livro.autor, "\n"); // Remove o '\n'
            printf("Digite o novo ano de publicação: ");
            scanf("%d", &livro.ano);
            getchar(); // Limpar buffer
        }
        fprintf(temp, "%d,%s,%s,%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
    }

    fclose(fp);
    fclose(temp);

    remove(arquivoLivros);
    rename("temp.txt", arquivoLivros);

    if (encontrado) {
        printf("Dados do livro alterados com sucesso!\n");
    } else {
        printf("Livro com código %d não encontrado!\n", codigo);
    }
}

// Função para excluir um livro pelo código
void excluirLivro() {
    int codigo, encontrado = 0;
    Livro livro;
    FILE *fp = fopen(arquivoLivros, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o código do livro que deseja excluir: ");
    scanf("%d", &codigo);

    while (fscanf(fp, "%d,%49[^,],%49[^,],%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) != EOF) {
        if (livro.codigo == codigo) {
            encontrado = 1;
        } else {
            fprintf(temp, "%d,%s,%s,%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(arquivoLivros);
    rename("temp.txt", arquivoLivros);

    if (encontrado) {
        printf("Livro excluído com sucesso!\n");
    } else {
        printf("Livro com código %d não encontrado!\n", codigo);
    }
}

// Função para consultar informações de um livro
void consultarLivro() {
    int codigo, encontrado = 0;
    Livro livro;
    FILE *fp = fopen(arquivoLivros, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o código do livro que deseja consultar: ");
    scanf("%d", &codigo);

    while (fscanf(fp, "%d,%49[^,],%49[^,],%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) != EOF) {
        if (livro.codigo == codigo) {
            printf("\n=== Dados do Livro ===\n");
            printf("Código: %d\n", livro.codigo);
            printf("Título: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Ano: %d\n", livro.ano);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (!encontrado) {
        printf("Livro com código %d não encontrado!\n", codigo);
    }
}

// Função para listar todos os livros
void listarLivros() {
    Livro livro;
    FILE *fp = fopen(arquivoLivros, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\n=== Lista de Livros ===\n");
    while (fscanf(fp, "%d,%49[^,],%49[^,],%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) != EOF) {
        printf("Código: %d | Título: %s | Autor: %s | Ano: %d\n",
               livro.codigo, livro.titulo, livro.autor, livro.ano);
    }

    fclose(fp);
}
