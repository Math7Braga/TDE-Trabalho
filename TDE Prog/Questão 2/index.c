#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct para funcionário
typedef struct {
    int id;
    char nome[50];
    char cargo[30];
    int salario;
} Funcionario;

// Nome do arquivo de dados
const char *arquivoFuncionarios = "funcionarios.txt";

// Funções
void cadastrarFuncionario();
void alterarFuncionario();
void excluirFuncionario();
void consultarFuncionario();
void listarFuncionarios();
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
        printf("\n=== Cadastro de Funcionários ===\n");
        printf("1. Cadastrar novo funcionário\n");
        printf("2. Alterar dados de um funcionário\n");
        printf("3. Excluir um funcionário\n");
        printf("4. Consultar informações de um funcionário\n");
        printf("5. Listar todos os funcionários\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1: cadastrarFuncionario(); break;
            case 2: alterarFuncionario(); break;
            case 3: excluirFuncionario(); break;
            case 4: consultarFuncionario(); break;
            case 5: listarFuncionarios(); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para cadastrar um novo funcionário
void cadastrarFuncionario() {
    Funcionario funcionario;
    FILE *fp = fopen(arquivoFuncionarios, "a");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o ID do funcionário: ");
    scanf("%d", &funcionario.id);
    getchar(); // Limpar buffer
    printf("Digite o nome do funcionário: ");
    fgets(funcionario.nome, 50, stdin);
    strtok(funcionario.nome, "\n"); // Remove o '\n'
    printf("Digite o cargo do funcionário: ");
    fgets(funcionario.cargo, 30, stdin);
    strtok(funcionario.cargo, "\n"); // Remove o '\n'
    printf("Digite o salário do funcionário: ");
    scanf("%d", &funcionario.salario);

    fprintf(fp, "%d,%s,%s,%d\n", funcionario.id, funcionario.nome, funcionario.cargo, funcionario.salario);
    fclose(fp);

    printf("Funcionário cadastrado com sucesso!\n");
}

// Função para alterar dados de um funcionário
void alterarFuncionario() {
    int id, encontrado = 0;
    Funcionario funcionario;
    FILE *fp = fopen(arquivoFuncionarios, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o ID do funcionário que deseja alterar: ");
    scanf("%d", &id);
    getchar(); // Limpar buffer

    while (fscanf(fp, "%d,%49[^,],%29[^,],%d\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        if (funcionario.id == id) {
            encontrado = 1;
            printf("Digite o novo cargo: ");
            fgets(funcionario.cargo, 30, stdin);
            strtok(funcionario.cargo, "\n"); // Remove o '\n'
            printf("Digite o novo salário: ");
            scanf("%d", &funcionario.salario);
            getchar(); // Limpar buffer
        }
        fprintf(temp, "%d,%s,%s,%d\n", funcionario.id, funcionario.nome, funcionario.cargo, funcionario.salario);
    }

    fclose(fp);
    fclose(temp);

    remove(arquivoFuncionarios);
    rename("temp.txt", arquivoFuncionarios);

    if (encontrado) {
        printf("Dados do funcionário alterados com sucesso!\n");
    } else {
        printf("Funcionário com ID %d não encontrado!\n", id);
    }
}

// Função para excluir um funcionário pelo ID
void excluirFuncionario() {
    int id, encontrado = 0;
    Funcionario funcionario;
    FILE *fp = fopen(arquivoFuncionarios, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o ID do funcionário que deseja excluir: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d,%49[^,],%29[^,],%d\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        if (funcionario.id == id) {
            encontrado = 1;
        } else {
            fprintf(temp, "%d,%s,%s,%d\n", funcionario.id, funcionario.nome, funcionario.cargo, funcionario.salario);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(arquivoFuncionarios);
    rename("temp.txt", arquivoFuncionarios);

    if (encontrado) {
        printf("Funcionário excluído com sucesso!\n");
    } else {
        printf("Funcionário com ID %d não encontrado!\n", id);
    }
}

// Função para consultar informações de um funcionário
void consultarFuncionario() {
    int id, encontrado = 0;
    Funcionario funcionario;
    FILE *fp = fopen(arquivoFuncionarios, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o ID do funcionário que deseja consultar: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d,%49[^,],%29[^,],%d\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        if (funcionario.id == id) {
            printf("\n=== Dados do Funcionário ===\n");
            printf("ID: %d\n", funcionario.id);
            printf("Nome: %s\n", funcionario.nome);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Salário: R$ %d\n", funcionario.salario);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (!encontrado) {
        printf("Funcionário com ID %d não encontrado!\n", id);
    }
}

// Função para listar todos os funcionários
void listarFuncionarios() {
    Funcionario funcionario;
    FILE *fp = fopen(arquivoFuncionarios, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\n=== Lista de Funcionários ===\n");
    while (fscanf(fp, "%d,%49[^,],%29[^,],%d\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        printf("ID: %d | Nome: %s | Cargo: %s | Salário: R$ %d\n",
               funcionario.id, funcionario.nome, funcionario.cargo, funcionario.salario);
    }

    fclose(fp);
}
