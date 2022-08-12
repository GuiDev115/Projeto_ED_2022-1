#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

void criarArquivoTeste(string nome, int tam){
	
	ofstream arq(nome);
	
	// Inicializando gerador de n. aleat.
	srand(time(NULL));
	
	int valor = 0;
	
	for(int i = 0; i < tam; i++){
		
		valor = rand() % 1000;
		
		arq << valor << " ";
	}
	
	arq.close();
}

int main(){
	
	int tamanho;
	cin >> tamanho;
	
	criarArquivoTeste("dados.txt", tamanho);
	
	return 0;
}
