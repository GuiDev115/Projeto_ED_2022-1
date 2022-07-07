#include <iostream>
#include <fstream>
#include <cstring>

#include "classes.hpp"

using namespace std;



int main(){
	
	// O arquivo binário é aberto tanto para entrada quanto saída de dados
	fstream arq_binario("dados_convertidos.bin", ios::binary | ios::in | ios::out);
	
	// erro será o retorno do programa, que é tratado no programa principal
	// Se erro = 1, representa que ocorreu erro (o usuário digitou algo incorreto)
	// Se erro = 2, os valores das posições são iguais
	int erro = 0;
	
	if(arq_binario){
		
		// É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		arq_binario.seekg(0, arq_binario.end);
		int tamanho_arquivo_binario = arq_binario.tellg();
		
		// É criado uma variável do tipo classe Binario para acessar a função de trocar
		Binario dados_binario;
		
		// Variáveis para a execução das operações
		int pos_primeira = -1;
		int pos_segunda = -1;
		long aux;
		
		cout << "Escreva a primeira posição da troca: " << endl;
		cin >> pos_primeira;
		
		// Tamanho da pos_primeira em relação ao início do arquivo binário,
		// ou seja, representa o byte que a posição de pos_primeira começa
		aux = pos_primeira * sizeof(Binario);
		
		if((pos_primeira < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
			erro = 1;
			
		else{
			
			cout << "Escreva a segunda posição da troca: " << endl;
			cin >> pos_segunda;
			
			// Tamanho da pos_segunda em relação ao início do arquivo binário,
			// ou seja, representa o byte que a posição de pos_segunda começa
			aux = sizeof(Binario) * pos_segunda;
			
			if((pos_segunda < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
				erro = 1;
				
			else{
				
				if(pos_primeira == pos_segunda)
					erro = 2;
					
				else
					dados_binario.trocar(arq_binario, pos_primeira, pos_segunda);
			}
		}
		
		arq_binario.close();
	}
	
	else{
		
		cout << "Não há arquivo convertido" << endl;
	}
	
	return erro;
}
