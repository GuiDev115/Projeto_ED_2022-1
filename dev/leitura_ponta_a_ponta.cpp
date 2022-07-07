#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

#include "classes.hpp"

using namespace std;

// Função para impressão dos dados
void Binario::imprimir(Binario& umaLinha){
	
	cout << umaLinha.campo_1_id << '\n'
	<< umaLinha.campo_2_name << '\n'
	<< umaLinha.campo_3_job << '\n'
	<< umaLinha.campo_4_base_pay << '\n'
	<< umaLinha.campo_5_overtime_pay << '\n'
	<< umaLinha.campo_6_other_pay << '\n'
	<< umaLinha.campo_7_benefits << '\n'
	<< umaLinha.campo_8_total_pay << '\n'
	<< umaLinha.campo_9_total_pay_benefits << '\n'
	<< umaLinha.campo_10_year << '\n'
	<< umaLinha.campo_11_posicao << '\n' << endl;
	
	#warning retire o campo posicao antes de entregar!
}

int main(){
	
	// erro será o retorno do programa, que é tratado no programa principal
	// Se erro = 1, representa que ocorreu erro (o usuário digitou algo incorreto)
	int erro = 0;
	
	ifstream arq_binario("dados_convertidos.bin", ios::binary);
	
	if(arq_binario){
		
		// É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		arq_binario.seekg(0, arq_binario.end);
		int tamanho_arquivo_binario = arq_binario.tellg();
		
		// Um ponteiro do tipo classe Binario é criado para ler as linhas desejadas do arquivo binário
		Binario *leitura = new Binario[1];
		
		arq_binario.seekg(0, arq_binario.beg);
		
		// Variáveis para a execução das operações
		int inicial_pos = -1;
		int final_pos = -1;
		long aux;
		
		cout << "Escreva a posição inicial: " << endl;
		cin >> inicial_pos;
		
		// Tamanho da inicial_pos em relação ao início do arquivo binário,
		// ou seja, representa o byte que a posição de inicial_pos começa
		aux = sizeof(Binario) * inicial_pos;
		
		if((inicial_pos < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
			erro = 1;
		
		else{
			
			cout << "Escreva a posição final: " << endl;
			
			cin >> final_pos;
			
			// Tamanho da final_pos em relação ao início do arquivo binário,
			// ou seja, representa o byte que a posição de final_pos começa
			aux = sizeof(Binario) * final_pos;
			
			if((final_pos < inicial_pos) or (final_pos < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
				erro = 1;
			
			else{
				
				// Intervalo de leitura
				int intervalo = final_pos - inicial_pos + 1;
				
				arq_binario.seekg(inicial_pos * sizeof(Binario), arq_binario.beg);
				
				cout << '\n' << "Resultado: " << '\n' << '\n';
				
				bool primeiro = false;
				
				do{
					// É mostrado ao usuário 100 linhas por vez
					int cont = 100;
					
					// Ou menos que 100 linhas, caso o intervalo restante seja < cont
					if(intervalo >= 1 and intervalo < cont)
						cont = intervalo;
						
					// É lido uma linha de informações (um pacote da classe Binario) de cada vez
					// Tal pacote é "inserido" no ponteiro leitura para vizualização
					for(int i = 0; i < cont; i++, intervalo--){
						
						arq_binario.read((char*)(&leitura[0]), sizeof(Binario));
						
						leitura[0].imprimir(leitura[0]);
					}
					
					cout << "Linhas restantes: " << intervalo << '\n';
					cout << "Se desejar ver os resultados do ponto anterior até esse ponto, rode para cima" << endl;
					
					if(intervalo != 0)
						cout << "Pressione enter para continuar. . . ";
						
					else
						cout << "Pressione enter para sair. . . ";
					
					// Ignora o primeiro enter
					if(!primeiro){
						
						cin.ignore();
						
						primeiro = true;
					}
					
					// O programa apenas irá continuar/parar após o usuário pressionar enter.
					// Tal laço é feito para impedir que a cada caractere que o usuário digite, 
					// o programa rode uma vez + quantidade de caracteres inseridos
					bool controle = true;
					while(controle){
						
						if(cin.get() == '\n')
							controle = false;
					}
					
					// No linux apenas um clear não basta, tal razão de ter dois comandos iguais
					system("clear");
					system("clear");
					
				}while(intervalo != 0);
			}
		}
		
		arq_binario.close();
		delete[] leitura;
	}
	
	else{
		
		cout << "Não há arquivo convertido" << endl;
	}
	
	return erro;
}
