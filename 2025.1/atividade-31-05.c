#include <stdio.h>
#include <ctype.h>

void contarVogais(char *texto) {
    int i = 0, contador = 0;
    while (texto[i] != '\0') {
        char c = tolower(texto[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            contador++;
        }
        i++;
    }
    printf("Número de vogais: %d\n", contador);
}

void capitalizarPalavras(char *texto) {
    int i = 0;
    int nova_palavra = 1;

    while (texto[i] != '\0') {
        if (texto[i] == ' ') {
            nova_palavra = 1;
        } else if (nova_palavra && texto[i] >= 'a' && texto[i] <= 'z') {
            texto[i] = texto[i] - 32;
            nova_palavra = 0;
        } else {
            nova_palavra = 0;
        }
        i++;
    }
    printf("Frase com palavras capitalizadas: %s", texto);
}

int main() {
    char texto[256];

    printf("Digite uma frase: ");
    fgets(texto, sizeof(texto), stdin);

    printf("Você digitou: %s", texto);

    contarVogais(texto);
    capitalizarPalavras(texto);

    return 0;
}
