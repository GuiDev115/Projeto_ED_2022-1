#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Futuramente: transformar CSV em uma classe

struct CSV{
	
	int campo_1_id;
	char campo_2_name[50];
	char campo_3_team[50];
	char campo_4_game[50];
	int campo_5_year;
	char campo_6_season[6];
	
	CSV();
};

CSV::CSV(){
	
	campo_1_id = -1;
	memset(campo_2_name, 0, sizeof(campo_2_name));
	memset(campo_3_team, 0, sizeof(campo_3_team));
	memset(campo_4_game, 0, sizeof(campo_4_game));
	campo_5_year = -1;
	memset(campo_6_season, 0, sizeof(campo_6_season));
};

int main(){
	
	ifstream arq("data_athlete_game.csv");
	
	if(arq){
		
		arq.seekg(0, arq.end);
		int tam = arq.tellg();
		
		cout << tam << " bytes" << endl;
		
		arq.seekg(0, arq.beg);
		
		string palavras_comeco;
		
		// Lendo a linha 1
		arq >> palavras_comeco;
		cout << palavras_comeco << endl;
		
		// Teste: leitura e escrita das 10 primeiras linhas (linhas 2 até 11). Futuramente: criar funções que realizem o processo de leitura, em vez de 1 por 1 no main
		ofstream arq_binario("dados_convertidos.bin");
		
		// 271116 real tamanho, verificar depois se esse tamanho procede
		// Não é possível adicionar valores extremamente altos no tamanho do array
		CSV *linhas = new CSV[1000];
		
		int id, ano;
		char virgula, c[1];
		
		for(int cont = 0; cont < 1000; cont++){
			
			// id
			
			arq >> id;
			linhas[cont].campo_1_id = id;
			arq >> virgula;
			
			int i = 0;
			bool controle = true;
			
			// name
			
			do{
				
				arq.read(c, 1);
				
				if(c[0] != ','){
					
					linhas[cont].campo_2_name[i] = c[0];
					
					i++;
				}
				
				else
					controle = false;
				
			}while(controle);
			
			i = 0;
			controle = true;
			
			// team
			
			do{
				
				arq.read(c, 1);
				
				if(c[0] != ','){
					
					linhas[cont].campo_3_team[i] = c[0];
					
					i++;
				}
				
				else
					controle = false;
				
			}while(controle);
			
			i = 0;
			controle = true;
			
			// game
		
			do{
				
				arq.read(c, 1);
				
				if(c[0] != ','){
					
					linhas[cont].campo_4_game[i] = c[0];
					
					i++;
				}
				
				else
					controle = false;
				
			}while(controle);
			
			i = 0;
			controle = true;
			
			// year
			
			arq >> ano;
			linhas[cont].campo_5_year = ano;
			arq >> virgula;
			
			// season
			
			do{
				
				arq.read(c, 1);
				
				if(c[0] != '\n'){
					
					linhas[cont].campo_6_season[i] = c[0];
					
					i++;
				}
				
				else
					controle = false;
				
			}while(controle);
			
			i = 0;
			controle = true;
			
			arq_binario.write((char*)(&linhas[cont]), sizeof(linhas[cont]));
		}
		
		arq.close();
		arq_binario.close();
		delete[] linhas;
	}
	
	return 0;
}
