#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct para veículos
typedef struct {
    int id;
    char modelo[50];
    char placa[10];
    int ano;
} Veiculo;

// Nome do arquivo para armazenar os veículos
const char *arquivoVeiculos = "veiculos.txt";

// Declaração das funções
void adicionarVeiculo();
void alterarVeiculo();
void excluirVeiculo();
void consultarVeiculoPorPlaca();
void listarVeiculos();
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
        printf("\n=== Registro de Veículos ===\n");
        printf("1. Adicionar novo veículo\n");
        printf("2. Alterar dados de um veículo\n");
        printf("3. Excluir um veículo\n");
        printf("4. Consultar veículo pela placa\n");
        printf("5. Listar todos os veículos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1: adicionarVeiculo(); break;
            case 2: alterarVeiculo(); break;
            case 3: excluirVeiculo(); break;
            case 4: consultarVeiculoPorPlaca(); break;
            case 5: listarVeiculos(); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para adicionar um novo veículo
void adicionarVeiculo() {
    Veiculo veiculo;
    FILE *fp = fopen(arquivoVeiculos, "a");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o ID do veículo: ");
    scanf("%d", &veiculo.id);
    getchar(); // Limpa o buffer do teclado
    printf("Digite o modelo do veículo: ");
    fgets(veiculo.modelo, 50, stdin);
    strtok(veiculo.modelo, "\n"); // Remove o '\n'
    printf("Digite a placa do veículo: ");
    fgets(veiculo.placa, 10, stdin);
    strtok(veiculo.placa, "\n"); // Remove o '\n'
    printf("Digite o ano de fabricação: ");
    scanf("%d", &veiculo.ano);

    fprintf(fp, "%d,%s,%s,%d\n", veiculo.id, veiculo.modelo, veiculo.placa, veiculo.ano);
    fclose(fp);

    printf("Veículo adicionado com sucesso!\n");
}

// Função para alterar os dados de um veículo
void alterarVeiculo() {
    int id, encontrado = 0;
    Veiculo veiculo;
    FILE *fp = fopen(arquivoVeiculos, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o ID do veículo que deseja alterar: ");
    scanf("%d", &id);
    getchar(); // Limpa o buffer do teclado

    while (fscanf(fp, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        if (veiculo.id == id) {
            encontrado = 1;
            printf("Digite o novo modelo: ");
            fgets(veiculo.modelo, 50, stdin);
            strtok(veiculo.modelo, "\n"); // Remove o '\n'
            printf("Digite a nova placa: ");
            fgets(veiculo.placa, 10, stdin);
            strtok(veiculo.placa, "\n"); // Remove o '\n'
            printf("Digite o novo ano de fabricação: ");
            scanf("%d", &veiculo.ano);
            getchar(); // Limpa o buffer do teclado
        }
        fprintf(temp, "%d,%s,%s,%d\n", veiculo.id, veiculo.modelo, veiculo.placa, veiculo.ano);
    }

    fclose(fp);
    fclose(temp);

    remove(arquivoVeiculos);
    rename("temp.txt", arquivoVeiculos);

    if (encontrado) {
        printf("Dados do veículo alterados com sucesso!\n");
    } else {
        printf("Veículo com ID %d não encontrado!\n", id);
    }
}

// Função para excluir um veículo pelo ID
void excluirVeiculo() {
    int id, encontrado = 0;
    Veiculo veiculo;
    FILE *fp = fopen(arquivoVeiculos, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o ID do veículo que deseja excluir: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        if (veiculo.id == id) {
            encontrado = 1;
        } else {
            fprintf(temp, "%d,%s,%s,%d\n", veiculo.id, veiculo.modelo, veiculo.placa, veiculo.ano);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(arquivoVeiculos);
    rename("temp.txt", arquivoVeiculos);

    if (encontrado) {
        printf("Veículo excluído com sucesso!\n");
    } else {
        printf("Veículo com ID %d não encontrado!\n", id);
    }
}

// Função para consultar um veículo pela placa
void consultarVeiculoPorPlaca() {
    char placa[10];
    int encontrado = 0;
    Veiculo veiculo;
    FILE *fp = fopen(arquivoVeiculos, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite a placa do veículo que deseja consultar: ");
    fgets(placa, 10, stdin);
    strtok(placa, "\n"); // Remove o '\n'

    while (fscanf(fp, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        if (strcmp(veiculo.placa, placa) == 0) {
            printf("\n=== Dados do Veículo ===\n");
            printf("ID: %d\n", veiculo.id);
            printf("Modelo: %s\n", veiculo.modelo);
            printf("Placa: %s\n", veiculo.placa);
            printf("Ano: %d\n", veiculo.ano);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (!encontrado) {
        printf("Veículo com placa %s não encontrado!\n", placa);
    }
}

// Função para listar todos os veículos cadastrados
void listarVeiculos() {
    Veiculo veiculo;
    FILE *fp = fopen(arquivoVeiculos, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\n=== Lista de Veículos ===\n");
    while (fscanf(fp, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        printf("ID: %d | Modelo: %s | Placa: %s | Ano: %d\n",
               veiculo.id, veiculo.modelo, veiculo.placa, veiculo.ano);
    }

    fclose(fp);
}
