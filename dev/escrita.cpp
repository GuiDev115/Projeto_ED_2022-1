#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Futuramente: transformar CSV em uma classe

struct CSV{
	
	int campo_1_id;
	char campo_2_name[50];
	char campo_3_job[50];
	float campo_4_base_pay;
	float campo_5_overtime_pay;
	float campo_6_other_pay;
	float campo_7_benefits;
	float campo_8_total_pay;
	float campo_9_total_pay_benefits;
	int campo_10_year;
	
	CSV();
};

CSV::CSV(){
	
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
};

int main(){
	
	ifstream arq("san_francisco_payroll_dataset.csv");
	
	if(arq){
		
		cout << sizeof(CSV) << endl;
		
		cout << 2*sizeof(int) << " " << 6*sizeof(float) << " " << 50*sizeof(char) << " " << 50*sizeof(char) << endl;
		
		arq.seekg(0, arq.end);
		int tam = arq.tellg();
		
		cout << tam << " bytes" << endl;
		
		arq.seekg(0, arq.beg);
		
		string palavras_comeco;
		
		// Lendo a linha 1
		getline(arq, palavras_comeco);
		cout << palavras_comeco << endl;
		
		// Teste: leitura e escrita das 10 primeiras linhas (linhas 2 até 11). Futuramente: criar funções que realizem o processo de leitura, em vez de 1 por 1 no main
		ofstream arq_binario("dados_convertidos.bin", ios::binary);
		
		// 357407 real tamanho, verificar depois se esse tamanho procede
		CSV *linhas = new CSV[10];	// 5263
		
		int id, ano;
		float pagamentos;
		char virgula_leitura, c[1];
		string texto;
		
		for(int cont = 0; cont < 10; cont++){
			
			// id
			
			arq >> id;
			linhas[cont].campo_1_id = id;
			arq >> virgula_leitura;
			
			// name
			
			int k = 1;
			unsigned int j = 0;
			bool controle = true;
			
			while(controle){
				
				arq.seekg(0, arq.cur);
				int posicao_inicial = arq.tellg();
				
				getline(arq, texto);
				
				// procura o caractere " dentro da string texto e caso ache, retorna sua posição
				size_t found = texto.find("\"");
				
				// " não foi achado
				if(found == string::npos){
					
					arq.seekg(posicao_inicial, arq.beg);
					
					getline(arq, texto, ',');
					
					for(unsigned int i = 0; i < texto.length(); i++)
						linhas[cont].campo_2_name[i] = texto[i];
						
					controle = false;
				}
				
				// " foi achado
				else{
					
					size_t found_virgula = texto.find(",");
					
					// procura a segunda aparição do caractere " dentro da string texto
					found = texto.find("\"", found + k);
					k++;
					
					if(found_virgula < found){
						
						arq.seekg(posicao_inicial, arq.beg);
						
						getline(arq, texto, ',');
						
						for(unsigned int i = 0; i < texto.length(); i++)
							linhas[cont].campo_2_name[i] = texto[i];
							
						controle = false;
					}
					
					// a segunda aparição foi encontrada
					else if(found != string::npos){
						
						arq.seekg(posicao_inicial, arq.beg);
						
						while(j < found + 1){
							
							arq.read(c, 1);
							
							linhas[cont].campo_2_name[j] = c[0];
							
							j++;
						}
					}
				}
			}
			
			// job
			
			k = 1;
			j = 0;
			controle = true;
			
			while(controle){
				
				arq.seekg(0, arq.cur);
				int posicao_inicial = arq.tellg();
				
				getline(arq, texto);
				
				// procura o caractere " dentro da string texto e caso ache, retorna sua posição
				size_t found = texto.find("\"");
				
				// " não foi achado
				if(found == string::npos){
					
					arq.seekg(posicao_inicial, arq.beg);
					
					getline(arq, texto, ',');
					
					for(unsigned int i = 0; i < texto.length(); i++)
						linhas[cont].campo_3_job[i] = texto[i];
						
					controle = false;
				}
				
				// " foi achado
				else{
					
					// procura a segunda aparição do caractere " dentro da string texto
					found = texto.find("\"", found + k);
					k++;
					
					// a segunda aparição foi encontrada
					if(found != string::npos){
						
						arq.seekg(posicao_inicial, arq.beg);
						
						while(j < found + 1){
							
							arq.read(c, 1);
							
							linhas[cont].campo_3_job[j] = c[0];
							
							j++;
						}
					}
				}
			}
			
			// base pay
			
			arq >> pagamentos;
			linhas[cont].campo_4_base_pay = pagamentos;
			
			// overtime pay
			
			arq >> virgula_leitura;
			arq >> pagamentos;
			linhas[cont].campo_5_overtime_pay = pagamentos;
			
			// other pay
			
			arq >> virgula_leitura;
			arq >> pagamentos;
			linhas[cont].campo_6_other_pay = pagamentos;
			
			// benefits
			
			arq >> virgula_leitura;
			arq >> pagamentos;
			linhas[cont].campo_7_benefits = pagamentos;
			
			// total pay
			
			arq >> virgula_leitura;
			arq >> pagamentos;
			linhas[cont].campo_8_total_pay = pagamentos;
			
			// total pay & benefits
			
			arq >> virgula_leitura;
			arq >> pagamentos;
			linhas[cont].campo_9_total_pay_benefits = pagamentos;
			
			// year
			
			arq >> virgula_leitura;
			arq >> ano;
			linhas[cont].campo_10_year = ano;
			
			arq_binario.write((char*)(&linhas[cont]), sizeof(linhas[cont]));
		}
		
		delete[] linhas;
		arq.close();
		arq_binario.close();
	}
	
	return 0;
}
