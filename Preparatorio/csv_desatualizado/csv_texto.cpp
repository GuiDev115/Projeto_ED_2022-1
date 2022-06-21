#include <iostream>
#include <fstream>

using namespace std;

struct CSV{
	
	float campo1, campo4, campo6;
	int campo2;
	string campo3, campo5;
};

int main(){
	
	string nome_arquivo;
	cin >> nome_arquivo;
	
	ifstream arq(nome_arquivo);
	
	if(arq){
		
		int inteiro;
		float decimal;
		char ponto_virgula;
		char c[1];
		bool inicio = false, fim = false, controle = true, primeiro_espaco = false;
		
		ofstream arq_texto("dados_texto.txt");
		
		while(arq >> decimal){
			
			arq_texto << decimal << " ";
			
			arq >> ponto_virgula;
			arq >> inteiro;
			
			arq_texto << inteiro << " ";
			
			arq >> ponto_virgula;
			string texto1;
			do{
				
				arq.read(c, 1);
				
				if(c[0] != ';'){
					
					if(primeiro_espaco){
						
						texto1 = texto1 + c;
					}
					
					if((c[0] == '"') or (c[0] == '\'')){
						
						if(inicio == true)
							fim = true;
							
						inicio = true;
					}
				}
				
				else{
					
					if((inicio == true) and (fim == false))
						texto1 = texto1 + c;
						
					else if(fim == true){
						
						inicio = false;
						fim = false;
						controle = false;
					}
					
					else
						controle = false;
				}
				
				primeiro_espaco = true;
				
			}while(controle);
			
			arq_texto << texto1 << " ";
			
			controle = true;
			primeiro_espaco = false;
			
			arq >> decimal;
			
			arq_texto << decimal << " ";
			
			arq >> ponto_virgula;
			string texto2;
			do{
				
				arq.read(c, 1);
				
				if(c[0] != ';'){
					
					if(primeiro_espaco){
						
						texto2 = texto2 + c;
					}
					
					if((c[0] == '"') or (c[0] == '\'')){
						
						if(inicio == true)
							fim = true;
							
						inicio = true;
					}
				}
				
				else{
					
					if((inicio == true) and (fim == false))
						texto2 = texto2 + c;
						
					else if(fim == true){
						
						inicio = false;
						fim = false;
						controle = false;
					}
					
					else
						controle = false;
				}
				
				primeiro_espaco = true;
				
			}while(controle);
			
			arq_texto << texto2 << " ";
			
			controle = true;
			primeiro_espaco = false;
			
			arq >> decimal;
			
			arq_texto << decimal << endl;
		}
		
		arq.close();
	}
	
	return 0;
}
