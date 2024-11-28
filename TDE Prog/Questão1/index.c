#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct para aluno
typedef struct {
    int matricula;
    char nome[50];
    char curso[30];
    int idade;
} Aluno;

// Funções
void incluirAluno();
void alterarAluno();
void excluirAluno();
void consultarAluno();
void listarAlunos();
void menu();

// Nome do arquivo
const char *arquivo = "alunos.dat";

// Função principal
int main() {
    menu();
    return 0;
}

// Exibe o menu
void menu() {
    int opcao;
    do {
        printf("\n=== Sistema de Gerenciamento de Alunos ===\n");
        printf("1. Incluir novo aluno\n");
        printf("2. Alterar informações de um aluno\n");
        printf("3. Excluir um aluno\n");
        printf("4. Consultar informações de um aluno\n");
        printf("5. Listar todos os alunos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirAluno();
                break;
            case 2:
                alterarAluno();
                break;
            case 3:
                excluirAluno();
                break;
            case 4:
                consultarAluno();
                break;
            case 5:
                listarAlunos();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Inclui um novo aluno
void incluirAluno() {
    Aluno aluno;
    FILE *fp = fopen(arquivo, "ab");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o número da matrícula: ");
    scanf("%d", &aluno.matricula);
    getchar(); // Limpar buffer
    printf("Digite o nome do aluno: ");
    fgets(aluno.nome, 50, stdin);
    strtok(aluno.nome, "\n"); // Remove o \n
    printf("Digite o curso do aluno: ");
    fgets(aluno.curso, 30, stdin);
    strtok(aluno.curso, "\n"); // Remove o \n
    printf("Digite a idade do aluno: ");
    scanf("%d", &aluno.idade);

    fwrite(&aluno, sizeof(Aluno), 1, fp);
    fclose(fp);
    printf("Aluno cadastrado com sucesso!\n");
}

// Altera informações de um aluno
void alterarAluno() {
    int matricula;
    int encontrado = 0;
    Aluno aluno;
    FILE *fp = fopen(arquivo, "rb+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite a matrícula do aluno que deseja alterar: ");
    scanf("%d", &matricula);

    while (fread(&aluno, sizeof(Aluno), 1, fp)) {
        if (aluno.matricula == matricula) {
            printf("Digite o novo nome do aluno: ");
            getchar(); // Limpar buffer
            fgets(aluno.nome, 50, stdin);
            strtok(aluno.nome, "\n");
            printf("Digite o novo curso: ");
            fgets(aluno.curso, 30, stdin);
            strtok(aluno.curso, "\n");
            printf("Digite a nova idade: ");
            scanf("%d", &aluno.idade);

            fseek(fp, -sizeof(Aluno), SEEK_CUR);
            fwrite(&aluno, sizeof(Aluno), 1, fp);
            printf("Informações alteradas com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno não encontrado!\n");
    }

    fclose(fp);
}

// Exclui um aluno pelo número de matrícula
void excluirAluno() {
    int matricula, encontrado = 0;
    Aluno aluno;
    FILE *fp = fopen(arquivo, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite a matrícula do aluno que deseja excluir: ");
    scanf("%d", &matricula);

    while (fread(&aluno, sizeof(Aluno), 1, fp)) {
        if (aluno.matricula == matricula) {
            encontrado = 1;
        } else {
            fwrite(&aluno, sizeof(Aluno), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(arquivo);
    rename("temp.dat", arquivo);

    if (encontrado) {
        printf("Aluno excluído com sucesso!\n");
    } else {
        printf("Aluno não encontrado!\n");
    }
}

// Consulta informações de um aluno
void consultarAluno() {
    int matricula, encontrado = 0;
    Aluno aluno;
    FILE *fp = fopen(arquivo, "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite a matrícula do aluno: ");
    scanf("%d", &matricula);

    while (fread(&aluno, sizeof(Aluno), 1, fp)) {
        if (aluno.matricula == matricula) {
            printf("\n=== Informações do Aluno ===\n");
            printf("Matrícula: %d\n", aluno.matricula);
            printf("Nome: %s\n", aluno.nome);
            printf("Curso: %s\n", aluno.curso);
            printf("Idade: %d\n", aluno.idade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno não encontrado!\n");
    }

    fclose(fp);
}

// Lista todos os alunos
void listarAlunos() {
    Aluno aluno;
    FILE *fp = fopen(arquivo, "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\n=== Lista de Alunos ===\n");
    while (fread(&aluno, sizeof(Aluno), 1, fp)) {
        printf("Matrícula: %d | Nome: %s | Curso: %s | Idade: %d\n",
               aluno.matricula, aluno.nome, aluno.curso, aluno.idade);
    }

    fclose(fp);
}
