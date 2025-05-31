#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 100
#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_EDITORA 100

typedef struct {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char editora[MAX_EDITORA];
    int anoPublicacao;
    int qtdPaginas;
} Livro;

void preencherVetor(Livro livros[], int *n) {
    char buffer[50];
    printf("Digite o número de livros a serem cadastrados: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", n);

    for (int i = 0; i < *n; i++) {
        printf("Livro %d:\n", i + 1);

        printf("Título: ");
        fgets(livros[i].titulo, MAX_TITULO, stdin);
        livros[i].titulo[strcspn(livros[i].titulo, "\n")] = 0; // Remove o newline

        printf("Autor: ");
        fgets(livros[i].autor, MAX_AUTOR, stdin);
        livros[i].autor[strcspn(livros[i].autor, "\n")] = 0;

        printf("Editora: ");
        fgets(livros[i].editora, MAX_EDITORA, stdin);
        livros[i].editora[strcspn(livros[i].editora, "\n")] = 0;

        printf("Ano de Publicação: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &livros[i].anoPublicacao);

        printf("Quantidade de Páginas: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &livros[i].qtdPaginas);
    }
}

void imprimirVetor(Livro livros[], int n) {
    printf("\nLista de Livros:\n");
    for (int i = 0; i < n; i++) {
        printf("Título: %s, Autor: %s, Editora: %s, Ano: %d, Páginas: %d\n",
               livros[i].titulo, livros[i].autor, livros[i].editora,
               livros[i].anoPublicacao, livros[i].qtdPaginas);
    }
}

int buscarPorTitulo(Livro livros[], int n, const char *titulo) {
    for (int i = 0; i < n; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0) {
            return i; // Retorna a posição do livro
        }
    }
    return -1; // Livro não encontrado
}

void ordenarPorTitulo(Livro livros[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(livros[j].titulo, livros[j + 1].titulo) > 0) {
                Livro temp = livros[j];
                livros[j] = livros[j + 1];
                livros[j + 1] = temp;
            }
        }
    }
}

int buscaBinariaPorTitulo(Livro livros[], int n, const char *titulo) {
    int esquerda = 0;
    int direita = n - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(livros[meio].titulo, titulo);

        if (cmp == 0) {
            return meio; // Livro encontrado
        }
        if (cmp < 0) {
            esquerda = meio + 1; // Busca na metade direita
        } else {
            direita = meio - 1; // Busca na metade esquerda
        }
    }
    return -1; // Livro não encontrado
}

int main() {
    Livro livros[MAX_LIVROS];
    int n;

    preencherVetor(livros, &n);
    imprimirVetor(livros, n);

    ordenarPorTitulo(livros, n);
    printf("\nLivros ordenados por título:\n");
    imprimirVetor(livros, n);

    char tituloBusca[MAX_TITULO];
    printf("\nDigite o título do livro a ser buscado: ");
    fgets(tituloBusca, MAX_TITULO, stdin);
    tituloBusca[strcspn(tituloBusca, "\n")] = 0; // Remove o newline

    int posicao = buscaBinariaPorTitulo(livros, n, tituloBusca);
    if (posicao != -1) {
        printf("Livro encontrado na posição: %d\n", posicao);
    } else {
        printf("Livro não encontrado.\n");
    }

    return 0;
}

