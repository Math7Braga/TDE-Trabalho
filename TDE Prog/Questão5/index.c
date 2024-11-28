#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct para filmes
typedef struct {
    int id;
    char titulo[50];
    char genero[20];
    int ano;
} Filme;

// Nome do arquivo para armazenar os filmes
const char *arquivoFilmes = "filmes.txt";

// Declaração das funções
void adicionarFilme();
void alterarFilme();
void excluirFilme();
void consultarFilmePorID();
void listarFilmes();
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
        printf("\n=== Controle de Filmes ===\n");
        printf("1. Adicionar novo filme\n");
        printf("2. Alterar dados de um filme\n");
        printf("3. Excluir um filme\n");
        printf("4. Consultar filme pelo ID\n");
        printf("5. Listar todos os filmes\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1: adicionarFilme(); break;
            case 2: alterarFilme(); break;
            case 3: excluirFilme(); break;
            case 4: consultarFilmePorID(); break;
            case 5: listarFilmes(); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para adicionar um novo filme
void adicionarFilme() {
    Filme filme;
    FILE *fp = fopen(arquivoFilmes, "a");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o ID do filme: ");
    scanf("%d", &filme.id);
    getchar(); // Limpa o buffer do teclado
    printf("Digite o título do filme: ");
    fgets(filme.titulo, 50, stdin);
    strtok(filme.titulo, "\n"); // Remove o '\n'
    printf("Digite o gênero do filme: ");
    fgets(filme.genero, 20, stdin);
    strtok(filme.genero, "\n"); // Remove o '\n'
    printf("Digite o ano de lançamento: ");
    scanf("%d", &filme.ano);

    fprintf(fp, "%d,%s,%s,%d\n", filme.id, filme.titulo, filme.genero, filme.ano);
    fclose(fp);

    printf("Filme adicionado com sucesso!\n");
}

// Função para alterar os dados de um filme
void alterarFilme() {
    int id, encontrado = 0;
    Filme filme;
    FILE *fp = fopen(arquivoFilmes, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o ID do filme que deseja alterar: ");
    scanf("%d", &id);
    getchar(); // Limpa o buffer do teclado

    while (fscanf(fp, "%d,%49[^,],%19[^,],%d\n", &filme.id, filme.titulo, filme.genero, &filme.ano) != EOF) {
        if (filme.id == id) {
            encontrado = 1;
            printf("Digite o novo título: ");
            fgets(filme.titulo, 50, stdin);
            strtok(filme.titulo, "\n"); // Remove o '\n'
            printf("Digite o novo gênero: ");
            fgets(filme.genero, 20, stdin);
            strtok(filme.genero, "\n"); // Remove o '\n'
            printf("Digite o novo ano de lançamento: ");
            scanf("%d", &filme.ano);
            getchar(); // Limpa o buffer do teclado
        }
        fprintf(temp, "%d,%s,%s,%d\n", filme.id, filme.titulo, filme.genero, filme.ano);
    }

    fclose(fp);
    fclose(temp);

    remove(arquivoFilmes);
    rename("temp.txt", arquivoFilmes);

    if (encontrado) {
        printf("Dados do filme alterados com sucesso!\n");
    } else {
        printf("Filme com ID %d não encontrado!\n", id);
    }
}

// Função para excluir um filme pelo ID
void excluirFilme() {
    int id, encontrado = 0;
    Filme filme;
    FILE *fp = fopen(arquivoFilmes, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o ID do filme que deseja excluir: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d,%49[^,],%19[^,],%d\n", &filme.id, filme.titulo, filme.genero, &filme.ano) != EOF) {
        if (filme.id == id) {
            encontrado = 1;
        } else {
            fprintf(temp, "%d,%s,%s,%d\n", filme.id, filme.titulo, filme.genero, filme.ano);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(arquivoFilmes);
    rename("temp.txt", arquivoFilmes);

    if (encontrado) {
        printf("Filme excluído com sucesso!\n");
    } else {
        printf("Filme com ID %d não encontrado!\n", id);
    }
}

// Função para consultar um filme pelo ID
void consultarFilmePorID() {
    int id, encontrado = 0;
    Filme filme;
    FILE *fp = fopen(arquivoFilmes, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o ID do filme que deseja consultar: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d,%49[^,],%19[^,],%d\n", &filme.id, filme.titulo, filme.genero, &filme.ano) != EOF) {
        if (filme.id == id) {
            printf("\n=== Dados do Filme ===\n");
            printf("ID: %d\n", filme.id);
            printf("Título: %s\n", filme.titulo);
            printf("Gênero: %s\n", filme.genero);
            printf("Ano: %d\n", filme.ano);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (!encontrado) {
        printf("Filme com ID %d não encontrado!\n", id);
    }
}

// Função para listar todos os filmes cadastrados
void listarFilmes() {
    Filme filme;
    FILE *fp = fopen(arquivoFilmes, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\n=== Lista de Filmes ===\n");
    while (fscanf(fp, "%d,%49[^,],%19[^,],%d\n", &filme.id, filme.titulo, filme.genero, &filme.ano) != EOF) {
        printf("ID: %d | Título: %s | Gênero: %s | Ano: %d\n",
               filme.id, filme.titulo, filme.genero, filme.ano);
    }

    fclose(fp);
}
