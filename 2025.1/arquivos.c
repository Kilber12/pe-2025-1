#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int videoID;
    char videoTitulo[100];
    char videoGenero[50];
} Filme;

typedef struct {
    int usuarioID;
    char usuarioNome[100];
    int videosFavoritos[10]; // IDs dos vídeos favoritos
    int totalFavoritos;
} Cliente;

// Função auxiliar: busca título do vídeo por ID
void buscarTituloPorID(int id, char *titulo) {
    FILE *arquivoVideos = fopen("videos.dat", "rb");
    Filme f;
    strcpy(titulo, "Nao encontrado");
    if (arquivoVideos) {
        while (fread(&f, sizeof(Filme), 1, arquivoVideos)) {
            if (f.videoID == id) {
                strcpy(titulo, f.videoTitulo);
                break;
            }
        }
        fclose(arquivoVideos);
    }
}

// Cadastrar vídeo
void cadastrarVideo() {
    FILE *arquivoVideos = fopen("videos.dat", "ab");
    Filme f;
    printf("ID do video: ");
    scanf("%d", &f.videoID);
    getchar();
    printf("Titulo: ");
    fgets(f.videoTitulo, 100, stdin);
    f.videoTitulo[strcspn(f.videoTitulo, "\n")] = 0;
    printf("Genero: ");
    fgets(f.videoGenero, 50, stdin);
    f.videoGenero[strcspn(f.videoGenero, "\n")] = 0;
    fwrite(&f, sizeof(Filme), 1, arquivoVideos);
    fclose(arquivoVideos);
}

// Cadastrar usuário
void cadastrarUsuario() {
    FILE *arquivoUsuarios = fopen("usuarios.dat", "ab");
    Cliente c;
    printf("ID do usuario: ");
    scanf("%d", &c.usuarioID);
    getchar();
    printf("Nome: ");
    fgets(c.usuarioNome, 100, stdin);
    c.usuarioNome[strcspn(c.usuarioNome, "\n")] = 0;
    printf("Quantos videos favoritados (max 10)? ");
    scanf("%d", &c.totalFavoritos);
    for (int i = 0; i < c.totalFavoritos; i++) {
        printf("ID do video favorito %d: ", i + 1);
        scanf("%d", &c.videosFavoritos[i]);
    }
    fwrite(&c, sizeof(Cliente), 1, arquivoUsuarios);
    fclose(arquivoUsuarios);
}

// Listar todos os vídeos
void listarVideos() {
    FILE *arquivoVideos = fopen("videos.dat", "rb");
    Filme f;
    printf("\n--- Lista de Videos ---\n");
    if (arquivoVideos) {
        while (fread(&f, sizeof(Filme), 1, arquivoVideos)) {
            printf("ID: %d | Titulo: %s | Genero: %s\n", f.videoID, f.videoTitulo, f.videoGenero);
        }
        fclose(arquivoVideos);
    } else {
        printf("Nenhum video cadastrado.\n");
    }
}

// Listar todos os usuários com títulos dos vídeos favoritos
void listarUsuariosComFavoritos() {
    FILE *arquivoUsuarios = fopen("usuarios.dat", "rb");
    Cliente c;
    printf("\n--- Lista de Usuarios ---\n");
    if (arquivoUsuarios) {
        while (fread(&c, sizeof(Cliente), 1, arquivoUsuarios)) {
            printf("ID: %d | Nome: %s\n", c.usuarioID, c.usuarioNome);
            printf("Favoritos: ");
            for (int i = 0; i < c.totalFavoritos; i++) {
                char titulo[100];
                buscarTituloPorID(c.videosFavoritos[i], titulo);
                printf("%s", titulo);
                if (i < c.totalFavoritos - 1) printf(", ");
            }
            printf("\n---------------------\n");
        }
        fclose(arquivoUsuarios);
    } else {
        printf("Nenhum usuario cadastrado.\n");
    }
}

// Atualizar título do vídeo
void atualizarTituloVideo() {
    int id;
    printf("ID do video a atualizar: ");
    scanf("%d", &id);

    FILE *arquivoVideos = fopen("videos.dat", "r+b");
    Filme f;
    if (arquivoVideos) {
        while (fread(&f, sizeof(Filme), 1, arquivoVideos)) {
            if (f.videoID == id) {
                getchar();
                printf("Novo titulo: ");
                fgets(f.videoTitulo, 100, stdin);
                f.videoTitulo[strcspn(f.videoTitulo, "\n")] = 0;
                fseek(arquivoVideos, -sizeof(Filme), SEEK_CUR);
                fwrite(&f, sizeof(Filme), 1, arquivoVideos);
                printf("Titulo atualizado.\n");
                break;
            }
        }
        fclose(arquivoVideos);
    } else {
        printf("Arquivo nao encontrado.\n");
    }
}

// Remover vídeo (cria novo arquivo sem ele)
void removerVideo() {
    int id;
    printf("ID do video a remover: ");
    scanf("%d", &id);

    FILE *arquivoVideos = fopen("videos.dat", "rb");
    FILE *novoArquivo = fopen("temp.dat", "wb");

    if (arquivoVideos && novoArquivo) {
        Filme f;
        int encontrado = 0;
        while (fread(&f, sizeof(Filme), 1, arquivoVideos)) {
            if (f.videoID != id) {
                fwrite(&f, sizeof(Filme), 1, novoArquivo);
            } else {
                encontrado = 1;
            }
        }
        fclose(arquivoVideos);
        fclose(novoArquivo);
        remove("videos.dat");
        rename("temp.dat", "videos.dat");
        if (encontrado)
            printf("Video removido com sucesso.\n");
        else
            printf("Video nao encontrado.\n");
    } else {
        printf("Erro ao acessar arquivos.\n");
    }
}

// Menu principal
void menu() {
    int opcao;
    do {
        printf("\n--- Menu Streaming ---\n");
        printf("1 - Cadastrar video\n");
        printf("2 - Cadastrar usuario\n");
        printf("3 - Listar videos\n");
        printf("4 - Listar usuarios com favoritos\n");
        printf("5 - Atualizar titulo de video\n");
        printf("6 - Remover video\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarVideo(); break;
            case 2: cadastrarUsuario(); break;
            case 3: listarVideos(); break;
            case 4: listarUsuariosComFavoritos(); break;
            case 5: atualizarTituloVideo(); break;
            case 6: removerVideo(); break;
            case 0: printf("Encerrando programa...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

// Função principal
int main() {
    menu();
    return 0;
}
