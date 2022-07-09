#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

#include "classes.hpp"
// Chamada do arquivo auxiliar .hpp na onde escontra-se maior parte do algoritmo do projeto. Desde inserir até a alteração.
// Construtores e classe estão colocados tambem no .hpp

using namespace std;

int main(){
	
	string dado = " ";
	bool controle = true;
	
	Binario *bin = new Binario[1];
	
	cout << "||||                   Seja Bem vindo !!!                  ||||" << '\n';
    cout << "|||| Por Favor faca sua escolha para progredir no programa ||||" << '\n' << '\n';

    do{

        cout << "|| 1 - Inserir || 2 - Leitura Geral || 3 - Leitura em determinado espaco || 4 - Trocar Posicao || 5 - Alterar Dados || 0 - Sair ||" << '\n';
		getline(cin, dado);
		
		if((dado.size() > 1) or (!((dado[0] >= 48) and (dado[0] <= 53))) or (cin.fail()))
			dado = " ";
			
		else
		
		switch(int(dado[0] - 48)){
			
			case 1:
                bin->inserir();

            break;
			
			case 2:{
				bin -> leitura_geral();
				
				break;
			}
			
			case 3:{
				int erro03 = 0, result = 0;
				result = bin -> leitura_por_espaco(erro03);
				
				if(result == 1)
					cout << "Posição inválida" << endl;
				
				break;
			}
			
			case 4:{
				int erro04 = 0, result = 0;
				
				result = bin -> troca_pos(erro04);
				
				if(result == 1)
					cout << "Posição inválida" << endl;
					
				else if(result == 2)
					cout << "As posições são iguais, não há porque trocar" << endl;
					
				cin.ignore();
				cin.get();
				
				break;
			}
			
			case 5:{
				int erro05 = 0, result = 0;
				
				result = bin -> alterar(erro05);
				
				if(result == 1)
					cout << "Posição inválida" << endl;
					
				else if(result == 2)
					cout << "O que foi digitado não corresponde com nenhum item da lista" << endl;
				
				cin.get();
				
				break;
			}
			
			case 0:{
				cout << endl << "Ate mais !!!! Fechando programa...";
				controle = false;
				break;
			}
		}
		
		if(dado[0] != '0')
			system("clear");
	}while(controle);
	
	return 0;
}
