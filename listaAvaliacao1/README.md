### Questão 2: 
Considere um arquivo com registros de tamanho fixo, conforme a estrutura
definida abaixo. 
Considere também que o arquivo está ordenado por cpf. 
Por uma falha no sistema de inscrição o mesmo candidato pode se inscrever mais de uma vez.
Decidiu-se que a inscrição válida será a última, ou seja, aquela com o maior número de id inscricao. 
Faça um programa que copie o arquivo “candidatos.dat” original em um novo arquivo “candidatos2.dat”, com os registros válidos. Escreva de forma eficiente.
Qual é a complexidade desse método?

~~~C
struct Registro {
    int id_inscricao;
    char curso[20];
    char cpf[15];
    char dataNacimento[11];
    char sexo;
    char email[40];
    char opcaoQuadro;
};
~~~