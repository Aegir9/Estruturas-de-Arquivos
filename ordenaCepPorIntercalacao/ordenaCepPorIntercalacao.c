#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#pragma pack(1)

typedef struct _Endereco Endereco;

struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int compara(const void *e1, const void *e2)
{
    return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, 8);
}

void intercala(char *arquivo1, char *arquivo2, char *arqSaida)
{
    FILE *a, *b, *saida;
    Endereco ea, eb;

    // printf("arquivo1 -> %s\n", arquivo1);
    // printf("arquivo2 -> %s\n", arquivo2);
    // printf("arqSaida -> %s\n\n", arqSaida);

    a = fopen(arquivo1, "r");
    b = fopen(arquivo2, "r");
    saida = fopen(arqSaida, "w");

    fread(&ea, sizeof(Endereco), 1, a);
    fread(&eb, sizeof(Endereco), 1, b);

    while (!feof(a) && !feof(b))
    {
        if (compara(&ea, &eb) < 0)
        {
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread(&ea, sizeof(Endereco), 1, a);
        }
        else
        {
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread(&eb, sizeof(Endereco), 1, b);
        }
    }

    while (!feof(a))
    {
        fwrite(&ea, sizeof(Endereco), 1, saida);
        fread(&ea, sizeof(Endereco), 1, a);
    }
    while (!feof(b))
    {
        fwrite(&eb, sizeof(Endereco), 1, saida);
        fread(&eb, sizeof(Endereco), 1, b);
    }

    fclose(a);
    fclose(b);
    fclose(saida);
}

int main(int argc, char **argv)
{
    FILE *f, *saida;
    Endereco *e;
    long posicao, qtdRegistros, qtdMaxRegPorBloco, qtdRegPorBloco, qtdBlocos;
    int ultimoArquivo = 0;

    qtdMaxRegPorBloco = 50000;

    f = fopen("cep.dat", "r"); // Abre o Arquivo Original Completo.

    fseek(f, 0, SEEK_END);
    posicao = ftell(f);
    qtdRegistros = posicao / sizeof(Endereco);

    // Define a quantidade de blocos que seja potência de 2 e que respeite a quantidade maxima de registros.
    qtdBlocos = pow(2, ceil(log2(qtdRegistros / qtdMaxRegPorBloco)));
    qtdRegPorBloco = ceil(qtdRegistros / qtdBlocos);

    rewind(f);
    e = (Endereco *)malloc(qtdRegPorBloco * sizeof(Endereco)); //Aloca memória RAM
    for (int i = 0; i < qtdBlocos; i++)
    {

        if (fread(e, sizeof(Endereco), qtdRegPorBloco, f) == qtdRegPorBloco)
        {
            printf("Bloco %d -> Lido\n", i);
        }

        qsort(e, qtdRegPorBloco, sizeof(Endereco), compara);
        printf("Bloco %d -> Ordenado\n", i);

        char nomeBloco[qtdBlocos];
        sprintf(nomeBloco, "cep_bloco_%d.dat", i);

        saida = fopen(nomeBloco, "w"); // Nomeia o Blocos

        fwrite(e, sizeof(Endereco), qtdRegPorBloco, saida);
        fclose(saida);
        printf("Bloco %d -> Escrito\n\n", i);
        ultimoArquivo++;
    }
    free(e);
    fclose(f); // Fecha o Arquivo Original Completo.

    int arqIndex1 = 0, aux;
    int etapa = log2(qtdBlocos);
    for (int etapa = log2(qtdBlocos); etapa > 0; etapa--)
    {
        printf("Etapa %d:\n", etapa);
        aux = ultimoArquivo;
        qtdBlocos = qtdBlocos / 2;
        for (int i = 0; i < qtdBlocos; i++)
        {
            char arquivo1[20], arquivo2[20], arqSaida[20];

            sprintf(arquivo1, "cep_bloco_%d.dat", arqIndex1++);
            sprintf(arquivo2, "cep_bloco_%d.dat", arqIndex1++);
            sprintf(arqSaida, "cep_bloco_%d.dat", ultimoArquivo++);

            printf("Intercalando: '%s' + '%s' ---> '%s'\n", arquivo1, arquivo2, arqSaida);

            intercala(arquivo1, arquivo2, arqSaida);
            remove(arquivo1);
            remove(arquivo2);
            if (i+1 >= qtdBlocos)
            {
                arqIndex1 = aux;
            }
        }
        printf("\n\n");
    }

    return 0;
}