#include <stdio.h>
#include <string.h>

typedef struct _Registro Registro;

struct _Registro
{
    int id_inscricao;
    char curso[20];
    char cpf[15];
    char dataNacimento[11];
    char sexo;
    char email[40];
    char opcaoQuadro;
};

int main()
{
    FILE *entrada, *saida;
    Registro *r, *rAux;
    char *arquivoLeitura = "candidatos.dat";
    char *arquivoSaidaValido = "candidatos2.dat";

    entrada = fopen(arquivoLeitura, "r"); // Abre o Arquivo Original com CPF repetido.
    saida = fopen(arquivoSaidaValido, "w");

    if (entrada == NULL)
    {
        fprintf(stderr, "Erro ao abrir o %s.\n", arquivoLeitura);
        return 1;
    }

    fread(&rAux, sizeof(Registro), 1, entrada); // Lê o primeiro registro.

    long posicaoSaida = sizeof(Registro);
    int primeiroLoop = 1; // true
    while (!feof(entrada))
    {
        fread(&r, sizeof(Registro), 1, entrada);

        if (strncmp(r->cpf, rAux->cpf, 15) == 0) // Verifica se os CPFs são iguais.
        {
            if (r->id_inscricao > rAux->id_inscricao)
            {
                fseek(saida, posicaoSaida - sizeof(Registro), SEEK_SET); // Aponta para o início do último registro escrito no arquivo de saída.
                fwrite(r, sizeof(Registro), 1, saida);                   // Sobrescreve o último registro salvo no arquivo de saída.
                rAux = r;
            }
            else if (primeiroLoop) // Caso seja o primeiro loop.
            {
                fwrite(rAux, sizeof(Registro), 1, saida);
            }
        }
        else
        {
            fwrite(r, sizeof(Registro), 1, saida);
            rAux = r;
        }

        posicaoSaida = ftell(saida);
        
        if (primeiroLoop)
            primeiroLoop = 0; //false
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}