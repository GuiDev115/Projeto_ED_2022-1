#include <iostream>
#include <fstream>

using namespace std;

struct CSV{
	
	float campo1, campo4, campo6;
	int campo2;
	char campo3[150] = "", campo5[150] = "";
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
		int cont = 0;
		
		ofstream arq_binario("dados_convertidos.bin");
		CSV aux[10];
		
		while(cont != 10){
			
			arq >> decimal;
			
			aux[cont].campo1 = decimal;
			
			arq >> ponto_virgula;
			arq >> inteiro;
			
			aux[cont].campo2 = inteiro;
			
			int i = 0;
			
			arq >> ponto_virgula;
			do{
				arq.read(c, 1);
				
				if(c[0] != ';'){
					
					if(primeiro_espaco){
						
						aux[cont].campo3[i] = c[0];
						
						i++;
					}
					
					if((c[0] == '"') or (c[0] == '\'')){
						
						if(inicio == true)
							fim = true;
							
						inicio = true;
					}
				}
				
				else{
					
					if((inicio == true) and (fim == false))
					{
						aux[cont].campo3[i] = c[0];
						
						i++;
					}
					
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
			
			i = 0;
			
			controle = true;
			primeiro_espaco = false;
			
			arq >> decimal;
			
			aux[cont].campo4 = decimal;
			
			arq >> ponto_virgula;
			do{
				arq.read(c, 1);
				
				if(c[0] != ';'){
					
					if(primeiro_espaco){
						
						aux[cont].campo5[i] = c[0];
						
						i++;
					}
					
					if((c[0] == '"') or (c[0] == '\'')){
						
						if(inicio == true)
							fim = true;
							
						inicio = true;
					}
				}
				
				else{
					
					if((inicio == true) and (fim == false))
					{
						aux[cont].campo5[i] = c[0];
						
						i++;
					}
						
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
			
			i = 0;
			
			controle = true;
			primeiro_espaco = false;
			
			arq >> decimal;
			
			aux[cont].campo6 = decimal;
			
			arq_binario.write((char*)(&aux[cont]), sizeof(aux[cont]));
			
			cont++;
		}
		
		arq.close();
	}
	
	return 0;
}
