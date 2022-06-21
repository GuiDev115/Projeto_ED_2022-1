#include <iostream>
#include <fstream>

using namespace std;

int main(){
	
	string nome_arquivo;
	cin >> nome_arquivo;
	
	ifstream arq(nome_arquivo);
	
	if(arq){
		
		int inteiro;
		float decimal;
		char ponto_virgula;
		char c[1];
		bool inicio = false, fim = false, controle = true;
		
		while(arq >> decimal){
			
			cout << decimal << " ";
			
			arq >> ponto_virgula;
			arq >> inteiro;
			
			cout << inteiro;
			
			arq >> ponto_virgula;
			do{
				
				arq.read(c, 1);
				
				if(c[0] != ';'){
					
					cout << c;
					
					if((c[0] == '"') or (c[0] == '\'')){
						
						if(inicio == true)
							fim = true;
							
						inicio = true;
					}
				}
				
				else{
					
					if((inicio == true) and (fim == false))
						cout << c;
						
					else if(fim == true){
						
						inicio = false;
						fim = false;
						controle = false;
						
						cout << ' ';
					}
					
					else{
						
						controle = false;
						
						cout << ' ';
					}
				}
				
			}while(controle);
			
			controle = true;
			
			arq >> decimal;
			
			cout << decimal;
			
			arq >> ponto_virgula;
			do{
				
				arq.read(c, 1);
				
				if(c[0] != ';'){
					
					cout << c;
					
					if((c[0] == '"') or (c[0] == '\'')){
						
						if(inicio == true)
							fim = true;
							
						inicio = true;
					}
				}
				
				else{
					
					if((inicio == true) and (fim == false))
						cout << c;
						
					else if(fim == true){
						
						inicio = false;
						fim = false;
						controle = false;
						
						cout << ' ';
					}
					
					else{
						
						controle = false;
						
						cout << ' ';
					}
				}
				
			}while(controle);
			
			controle = true;
			
			arq >> decimal;
			
			cout << decimal << endl;
		}
		
		arq.close();
	}
	
	return 0;
}
