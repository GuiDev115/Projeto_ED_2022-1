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
	<< umaLinha.campo_10_year << '\n' << endl;
}

int main(){
	
	int erro = 0;
	
	ifstream arq("dados_convertidos.bin", ios::binary);
	
	if(arq){
		
		arq.seekg(0, arq.end);
		int tamanho_arquivo_binario = arq.tellg();
		
		Binario dados_binario;
		Binario *leitura = new Binario[1];
		
		arq.seekg(0, arq.beg);
		
		int inicial_pos = -1;
		int fim_pos = -1;
		long aux;
		
		cout << "Escreva a posição inicial: " << endl;
		
		cin >> inicial_pos;
		
		aux = sizeof(Binario)*inicial_pos;
		
		if((inicial_pos < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
			erro = 1;
		
		else{
			
			cout << "Escreva a posição final: " << endl;
			
			cin >> fim_pos;
			
			aux = sizeof(Binario)*fim_pos;
			
			if((fim_pos < inicial_pos) or (fim_pos < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
				erro = 1;
			
			else{
				
				int intervalo = fim_pos - inicial_pos + 1;
				
				arq.seekg(sizeof(Binario)*inicial_pos, arq.beg);
				
				cout << '\n' << "Resultado: " << '\n' << '\n';
				
				int aux_intervalo = intervalo;
				bool primeiro = false;
				
				do{
					
					int cont = 100;
					
					if(aux_intervalo >= 1 and aux_intervalo <= cont)
						cont = aux_intervalo;
						
					for(int i = 0; i < cont; i++){
						
						arq.read((char*)(&leitura[0]), sizeof(Binario));
						
						dados_binario.imprimir(leitura[0]);
						
						aux_intervalo--;
					}
					
					cout << "Linhas restantes: " << aux_intervalo << '\n';
					
					cout << "Se desejar ver os resultados do ponto anterior até esse ponto, rode para cima" << '\n';
					
					if(aux_intervalo != 0)
						cout << "Pressione enter para continuar" << endl;
						
					else
						cout << "Pressione enter para sair" << endl;
					
					if(!primeiro){
						
						cin.ignore();
						
						primeiro = true;
					}
					
					bool controle = true;
					while(controle){
						
						if(cin.get() == '\n')
							controle = false;
					}
					
					system("clear");
					system("clear");
					
				}while(aux_intervalo != 0);
			}
		}
		
		arq.close();
		delete[] leitura;
	}
	
	else{
		
		cout << "Não há arquivo convertido" << endl;
	}
	
	return erro;
}
