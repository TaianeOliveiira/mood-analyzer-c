#include <stdio.h>
#include <string.h>
#include <ctype.h>

void minusculo(char texto[]) {
    for(int i = 0; texto[i]; i++) {
        texto[i] = tolower(texto[i]);
    }
}

int contem(char texto[], char palavra[]) {
    return strstr(texto, palavra) != NULL;
}

void salvarHistorico(char texto[], char resultado[]) {
    FILE *f = fopen("historico.txt", "a");
    fprintf(f, "Texto: %sResultado: %s\n\n", texto, resultado);
    fclose(f);
}

void mensagemMotivacional(char humor[]) {
    printf("\n💬 Mensagem:\n");

    if (strcmp(humor, "feliz") == 0) {
        printf("Continue assim, você tá no caminho certo 💖\n");
    } 
    else if (strcmp(humor, "triste") == 0) {
        printf("Vai passar, um dia de cada vez 🌱\n");
    } 
    else if (strcmp(humor, "estressado") == 0) {
        printf("Respira um pouco, você não precisa resolver tudo hoje 🌸\n");
    } 
    else {
        printf("Tudo bem não estar 100%% o tempo todo ✨\n");
    }
}

void analisarHumor(char texto[]) {

    int feliz = 0, triste = 0, estressado = 0;

    // FELIZ
    if (contem(texto, "feliz") || contem(texto, "amo") || contem(texto, "animada") || contem(texto, "bem") || contem(texto, "ótimo"))
        feliz += 2;

    // TRISTE
    if (contem(texto, "triste") || contem(texto, "cansada") || contem(texto, "sozinha") || contem(texto, "mal") || contem(texto, "chorando"))
        triste += 2;

    // ESTRESSADO
    if (contem(texto, "raiva") || contem(texto, "ódio") || contem(texto, "estressada") || contem(texto, "irritada") || contem(texto, "nervosa"))
        estressado += 2;

    int total = feliz + triste + estressado;

    if (total == 0) total = 1;

    int pf = (feliz * 100) / total;
    int pt = (triste * 100) / total;
    int pe = (estressado * 100) / total;

    printf("\n--- Resultado ---\n");
    printf("Feliz: %d%%\n", pf);
    printf("Triste: %d%%\n", pt);
    printf("Estressada: %d%%\n", pe);

    char resultado[20];

    if (pf > pt && pf > pe) {
        printf("\nVocê parece estar FELIZ 😊\n");
        strcpy(resultado, "feliz");
    } 
    else if (pt > pf && pt > pe) {
        printf("\nVocê parece estar TRISTE 😔\n");
        strcpy(resultado, "triste");
    } 
    else if (pe > pf && pe > pt) {
        printf("\nVocê parece estar ESTRESSADA 😤\n");
        strcpy(resultado, "estressado");
    } 
    else {
        printf("\nHumor NEUTRO 🤔\n");
        strcpy(resultado, "neutro");
    }

    mensagemMotivacional(resultado);
    salvarHistorico(texto, resultado);
}

int main() {
    char texto[300];

    printf("Como você está se sentindo hoje?\n");
    fgets(texto, sizeof(texto), stdin);

    minusculo(texto);
    analisarHumor(texto);

    printf("\n(Seu texto foi salvo no histórico 💾)\n");

    return 0;
}