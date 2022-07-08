#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

#include "classes.hpp"
//Chamada do arquivo auxiliar .hpp na onde escontra-se maior parte do algoritmo do projeto. Desde inserir até a alteração.
//Construtores e classe estão colocados tambem no .hpp

using namespace std;

int main(){

    int dado;

    Binario *bin = new Binario[1];

    cout << "Seja Bem vindo !!!" << endl;
    cout << "Por Favor faca sua escolha para progredir no programa" << endl << endl;

    cout << "1 - Inserir || 2 - Leitura Geral || 3 - Leitura em determinado espaco || 4 - Trocar Posicao || 5 - Alterar Dados || 0 - Sair" << endl;

    cin >> dado;

    switch(dado){

        case 1:
            cout << "Fazer";
        break;

        case 2:{
			
			cin.ignore();
            bin->leitura_geral();
            break;
        }

        case 3:{

            int erro03 = 0;
            bin -> leitura_por_espaco(erro03);

        break;
        }

        case 4:{

            int erro04 = 0;
            bin -> troca_pos(erro04);

        break;
        }

        case 5:{
            int erro05 = 0;
            bin -> alterar(erro05);

        break;
        }

        default:{
            cout << endl <<"Ate mais !!!! Fechando programa...";

            break;
        }
    }
    return 0;
}
