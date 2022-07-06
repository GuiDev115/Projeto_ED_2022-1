#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

class Binario{
	
	private:
		int campo_1_id;
		char campo_2_name[40];
		char campo_3_job[54];
		float campo_4_base_pay;
		float campo_5_overtime_pay;
		float campo_6_other_pay;
		float campo_7_benefits;
		float campo_8_total_pay;
		float campo_9_total_pay_benefits;
		int campo_10_year;
		int campo_11_posicao;
	
	public:
		Binario();
		void imprimir(Binario& umaLinha);
};

Binario::Binario(){
	
	campo_1_id = -1;
	memset(campo_2_name, 0, sizeof(campo_2_name));
	memset(campo_3_job, 0, sizeof(campo_3_job));
	campo_4_base_pay = 0;
	campo_5_overtime_pay = 0;
	campo_6_other_pay = 0;
	campo_7_benefits = 0;
	campo_8_total_pay = 0;
	campo_9_total_pay_benefits = 0;
	campo_10_year = 0;
	campo_11_posicao = -1;
}

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
	
	ifstream arq_binario("dados_convertidos.bin", ios::binary);
	
	if(arq_binario){
		
		// É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		arq_binario.seekg(0, arq_binario.end);
		int tamanho_arquivo_binario = arq_binario.tellg();
		
		// É atribuído para quantidade_linhas o total de linhas do arquivo binário
		int quantidade_linhas = tamanho_arquivo_binario / sizeof(Binario);
		
		// Um ponteiro do tipo classe Binario é criado para ler cada linha do arquivo binário
		Binario *leitura = new Binario[1];
		
		arq_binario.seekg(0, arq_binario.beg);
		
		// Variáveis para a execução das operações
		char opcao;
		bool controle = true, primeiro = false;
		int aux_quant = quantidade_linhas;
		
		do{
			// É mostrado ao usuário 100 linhas por vez
			int cont = 100;
			
			// Ou menos que 100 linhas, caso a quantidade de linhas restantes seja < cont
			if(aux_quant >= 1 and aux_quant < cont)
				cont = aux_quant;
			
			// É lido uma linha de informações (um pacote da classe Binario) de cada vez
			// Tal pacote é "inserido" no ponteiro leitura para vizualização
			for(int i = 0; i < cont; i++, aux_quant--){
				
				arq_binario.read((char*)(&leitura[0]), sizeof(Binario));
				
				leitura[0].imprimir(leitura[0]);
			}
			
			cout << "Linhas restantes: " << aux_quant << '\n';
			cout << "Se desejar ver os resultados do ponto anterior até esse ponto, rode para cima" << endl;
			
			if(aux_quant == 0){
				
				cout << "Fim da aplicação, pressione enter para retornar. . . ";
				
				controle = false;
				
				cin.get();
			}
			
			else{
				
				cout << "Se deseja sair da aplicação, pressione q e enter, se não aperte enter para continuar. . . ";
				
				// O programa somente irá fechar se o 1º caractere (de uma sequência ou não) for 'q'
				// Obs: essa é a função do bool primeiro
				// Teoricamente, para qualquer outro caso o programa continuará 
				while(opcao != '\n'){
					
					opcao = getchar();
					
					if((!primeiro) and (opcao == 'q'))
						controle = false;
						
					primeiro = true;
				}
				
				// É atribuído nulo à opcao para o programa não continuar rodando sozinho
				opcao = 0;
				primeiro = false;
			}
			
			// No linux apenas um clear não basta, tal razão de ter dois comandos iguais
			system("clear");
			system("clear");
			
		}while(controle);
		
		arq_binario.close();
		delete[] leitura;
	}
	
	else{
		
		cout << "Não há arquivo convertido." << endl;
	}
	
	return 0;
}
