#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

#include "classes.hpp"

using namespace std;

int main(){

    int n1;

    cout << "Seja Bem vindo !!!" << endl;
    cout << "Por Favor faca sua escolha para progredir no programa" << endl << endl;

    cout << "1 - Inserir || 2 - Leitura Geral || 3 - Leitura em determinado espaco || 4 - Trocar Posicao" << endl;

    cin >> n1;

    switch(n1){
        case 1:
            cout << "Fazer";
        break;

        case 2:{
			
			cin.ignore();

            ifstream arq_binario02("dados_convertidos.bin", ios::binary);
	
	        if(arq_binario02){
		
            // É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
            arq_binario02.seekg(0, arq_binario02.end);
            int tamanho_arquivo_binario = arq_binario02.tellg();
            
            // É atribuído para quantidade_linhas o total de linhas do arquivo binário
            int quantidade_linhas = tamanho_arquivo_binario / sizeof(Binario);
            
            // Um ponteiro do tipo classe Binario é criado para ler cada linha do arquivo binário
            Binario *leitura = new Binario[1];
            
            arq_binario02.seekg(0, arq_binario02.beg);
            
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
                    
                    arq_binario02.read((char*)(&leitura[0]), sizeof(Binario));
                    
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
            
            arq_binario02.close();
            delete[] leitura;
        }
        
        else
            cout << "Não há arquivo convertido." << endl;
        break;
    }

        case 3:{
            // erro será o retorno do programa, que é tratado no programa principal
	        // Se erro = 1, representa que ocorreu erro (o usuário digitou algo incorreto)
	        int erro03 = 0;
	
	        ifstream arq_binario03("dados_convertidos.bin", ios::binary);
	
	        if(arq_binario03){
		
		        // É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		        arq_binario03.seekg(0, arq_binario03.end);
		        int tamanho_arquivo_binario = arq_binario03.tellg();
		
		        // Um ponteiro do tipo classe Binario é criado para ler as linhas desejadas do arquivo binário
                Binario *leitura = new Binario[1];
                
                arq_binario03.seekg(0, arq_binario03.beg);
                
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
                    erro03 = 1;
		
                else{
                    
                    cout << "Escreva a posição final: " << endl;
                    
                    cin >> final_pos;
                    
                    // Tamanho da final_pos em relação ao início do arquivo binário,
                    // ou seja, representa o byte que a posição de final_pos começa
                    aux = sizeof(Binario) * final_pos;
                    
                    if((final_pos < inicial_pos) or (final_pos < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
                        erro03 = 1;
                    
                    else{
                        
                        // Intervalo de leitura
                        int intervalo = final_pos - inicial_pos + 1;
                        
                        arq_binario03.seekg(inicial_pos * sizeof(Binario), arq_binario03.beg);
                        
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
                                
                                arq_binario03.read((char*)(&leitura[0]), sizeof(Binario));
                                
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
                arq_binario03.close();
                delete[] leitura;
            }
            else
                cout << "Não há arquivo convertido" << endl;
            return erro03;
        break;
        }

        case 4:{
            // O arquivo binário é aberto tanto para entrada quanto saída de dados
	        fstream arq_binario04("dados_convertidos.bin", ios::binary | ios::in | ios::out);
	
            // erro será o retorno do programa, que é tratado no programa principal
            // Se erro = 1, representa que ocorreu erro (o usuário digitou algo incorreto)
            // Se erro = 2, os valores das posições são iguais
            int erro04 = 0;
            
            if(arq_binario04){
                
                // É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
                arq_binario04.seekg(0, arq_binario04.end);
                int tamanho_arquivo_binario = arq_binario04.tellg();
                
                // É criado uma variável do tipo classe Binario para acessar a função de trocar
                Binario dados_binario;
                
                // Variáveis para a execução das operações
                int pos_primeira = -1;
                int pos_segunda = -1;
                long aux;
                
                cout << "Escreva a primeira posição da troca: " << endl;
                cin >> pos_primeira;
                
                // Tamanho da pos_primeira em relação ao início do arquivo binário,
                // ou seja, representa o byte que a posição de pos_primeira começa
                aux = pos_primeira * sizeof(Binario);
                
                if((pos_primeira < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
                    erro04 = 1;
                    
                else{
                    
                    cout << "Escreva a segunda posição da troca: " << endl;
                    cin >> pos_segunda;
                    
                    // Tamanho da pos_segunda em relação ao início do arquivo binário,
                    // ou seja, representa o byte que a posição de pos_segunda começa
                    aux = sizeof(Binario) * pos_segunda;
                    
                    if((pos_segunda < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
                        erro04 = 1;
                        
                    else{
                        
                        if(pos_primeira == pos_segunda)
                            erro04 = 2;
                            
                        else
                            dados_binario.trocar(arq_binario04, pos_primeira, pos_segunda);
                    }
                }
                
                arq_binario04.close();
            }
            
            else{
                
                cout << "Não há arquivo convertido" << endl;
            }
            
            return erro04;
        break;
        }
    }
}
