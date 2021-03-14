#include <stdio.h>
#include <string.h>

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

int main(int argc, char **argv)
{
	FILE *f;
	Endereco e;
	int cont = 0;
	long tamanhoArquivo;
	char *arquivoCepOrdenado = "cep_ordenado.dat";

	if (argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	f = fopen(arquivoCepOrdenado, "r"); // Abre o arquivo para leitura.
	if (f == NULL)
	{
		fprintf(stderr, "Erro ao abrir o %s.\n", arquivoCepOrdenado);
		return 1;
	}

	fseek(f, 0, SEEK_END); 		// "Aponta" para o final do arquivo
	tamanhoArquivo = ftell(f);
	rewind(f); 					// "Aponta" para o inicio do arquivo

	printf("Tamanho do Arquivo: %ld bytes\n", tamanhoArquivo);
	printf("Tamanho do Registro: %ld bytes\n", sizeof(Endereco));
	printf("Quantidade de Registro no Arquivo: %ld registros\n", tamanhoArquivo / sizeof(Endereco));
	printf("==========================================================\n");

	long primeiro = 0;									   // Posição do Primeiro registro do arquivo.
	long ultimo = (tamanhoArquivo / sizeof(Endereco)) - 1; // Posição do Último registro do arquivo.
	long meio;

	while (primeiro <= ultimo)
	{
		++cont;
		meio = (primeiro + ultimo) / 2;				 // Posição do Registro do meio.
		fseek(f, meio * sizeof(Endereco), SEEK_SET); // "Aponta" para o registro do meio.
		fread(&e, sizeof(Endereco), 1, f);			 // Lê o registo que está apontado.

		if (strncmp(argv[1], e.cep, 8) == 0)
		{
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
			printf("Total de Leituras: %d\n", cont);
			fclose(f);
			return 0;
		}
		if (strncmp(argv[1], e.cep, 8) < 0)
			ultimo = meio - 1;
		else
			primeiro = meio + 1;
	}

	fprintf(stderr, "CEP nao foi encontrado");
	return 1;
}
