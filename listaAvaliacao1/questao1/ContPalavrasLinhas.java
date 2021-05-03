import java.io.*;

public class ContPalavrasLinhas {
	public static void main(String[] args) {

		if (args.length != 1) {
			System.err.println("Erro na chamada do comando.\n");
			System.err.println("Uso: java ContPalavrasLinhas [ARQUIVO].");
			System.exit(1);
		}

		try {
			RandomAccessFile entrada = new RandomAccessFile(args[0], "r");
			int contLinhas = 0, contPalavras = 0;

			while (entrada.getFilePointer() < entrada.length()) // Detectar o fim do arquivo.
			{
				String texto = entrada.readLine();
				++contLinhas;
				contPalavras += (texto.split(" ")).length;
			}
			entrada.close();

			System.out.println("O arquivo" + args[0] + " possui " + contLinhas + " linhas e "+ contPalavras +" palavras.");

		} catch (IOException ex) {
			System.err.println("Arquivo " + args[0] + " nao pode ser aberto para leitura.\n");
			System.exit(1);
		}

	}
}
