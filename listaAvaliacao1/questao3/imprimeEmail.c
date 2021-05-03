#include <stdio.h>

typedef struct _Candidato Candidato;

struct _Candidato {
    int id_inscricao;
    char curso[20];
    char cpf[15];
    char dataNacimento[11];
    char sexo;
    char email[40];
    char opcaoQuadro;
};

int main() {
    FILE *candidatosA, *candidatosB;
    Candidato *a, *b;
    char *arquivoA = "candidatosA.dat";
    char *arquivoB = "candidatosB.dat";
    int cont = 0;

    candidatosA = fopen(arquivoA, "r");
    candidatosB = fopen(arquivoB, "r");

    if (candidatosA == NULL) {
        fprintf(stderr, "Erro ao abrir o %s.\n", arquivoA);
        return 1;
    }
    if (candidatosB == NULL) {
        fprintf(stderr, "Erro ao abrir o %s.\n", arquivoB);
        return 1;
    }

    while (!feof(candidatosA) && !feof(candidatosB)) {

        cont++;
        fread(&a, sizeof(Candidato), 1, candidatosA);
        fread(&b, sizeof(Candidato), 1, candidatosB);

        printf("Candidato %i do arquivo %s: email( %s ) \n",cont, arquivoA, a->email);
        printf("Candidato %i do arquivo %s: email( %s ) \n",cont, arquivoB, b->email);
    }

    while (!feof(candidatosA)) {

        cont++;
        fread(&a, sizeof(Candidato), 1, candidatosA);
        printf("Candidato %i do arquivo %s: email( %s ) \n",cont, arquivoA, a->email);
    }
    
    while (!feof(candidatosB)) {
        
        cont++;
        fread(&b, sizeof(Candidato), 1, candidatosB);
        printf("Candidato %i do arquivo %s: email( %s ) \n",cont, arquivoB, b->email);
    }

    fclose(candidatosA);
    fclose(candidatosB);
    return 0;
}