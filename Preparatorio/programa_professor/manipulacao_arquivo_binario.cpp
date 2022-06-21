/* 
 * arqBin.cpp -> exemplo de manipulação de arquivo binário
 * 
 * GCC216 - Estruturas de Dados
 * by Joukim, 2020
 * 
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

// nome do arquivo usado para armazenar dados
const char NOMEARQUIVO[20] = "teste.dat";

// geração de dados aleatórios
static const char alpha[] = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

const int alphaLength = sizeof(alpha) - 1;

// gera uma letra do alfabeto aleatoriamente
char geraAlpha(){
	return alpha[rand() % alphaLength];
}

// estrutura a ser lida do arquivo
class dado {
	friend ostream& operator<<(ostream& saida, const dado& d); 
	private: 
		int chave;
		float valor;
		char codigo[4]; // 3 caracteres (4o é para término de string \0)
		char nome[11]; // 10 caracteres (11o é para \0)
	public:
		dado (int k=0); 
};

dado::dado(int k) {
	chave = k;

	// preenchendo outros dados aleatoriamente
	// gera um número entre 0 e 1
	// RAND_MAX - macro da cstdlib que gera um valor inteiro grande
	// (pelo menos 32767, depende do compilador)
	valor = ((float) rand()) / ((float) RAND_MAX);
	// gerando as strings, com caracteres aleatórios 
	for (int i = 0; i < 3; i++) {
		codigo[i] = geraAlpha();
	}
	for (int i = 0; i < 10; i++) {
		nome[i] = geraAlpha();
	}
	// garantindo caracter de término na última posição 
	// do vetor de caracteres
	codigo[3] = '\0';
	nome[10] = '\0';
}

// sobrecarga de operadores para facilitar visualização dos dados
// ex => 0: (eNr / OLMmZxxuko / 0.943612)

ostream& operator<<(ostream& saida, const dado& d) {
	saida << d.chave << ": (" << d.codigo << " / " 
		  << d.nome << " / " << d.valor << ")";
	return saida;
}


int main() {  
	// inicializa a semente a ser utilizada pelo gerador de números aleatórios    
	srand(time(NULL));

	// o arquivo tem um pequeno cabeçalho com a quantidade de dados no arquivo 
	unsigned cabecalho;

	// 1. Verifica se arquivo existe, se não existe, cria
	// se existe lê a quantidade de elementos no arquivo

	// verificando inicialmente se o arquivo existe
	ifstream arqIN(NOMEARQUIVO);

	// se existe lê o número de dados no arquivo
	if (arqIN) {
		arqIN.read((char*) &cabecalho, sizeof(cabecalho));
	}
	// se não existe, cria o arquivo e grava o cabeçalho com 0 elementos
	else {
		cabecalho = 0;
		ofstream arqOUT(NOMEARQUIVO);
		arqOUT.write((char *) &cabecalho, sizeof(cabecalho));
		arqOUT.close();
	}
	arqIN.close();

	// 2. Abre arquivo para ler e escrever
	fstream arquivo(NOMEARQUIVO);

	// 3. opções de manipulação do arquivo
	char opcao;

	cin >> opcao;

	// switch case não permite declaração de variáveis em seu interior...
	// declaramos variáveis auxiares do switch antes dele então
	unsigned posRelativa;
	unsigned posAbsoluta;
	dado* ptrDado;

	do {
		switch (opcao) {
			case 'i':
				// gera um novo dado para inserir no final do arquivo
				// primeiro elemento tem chave 0 e assim por diante
				// assim, podemos usar a quantidade atual de elementos
				// para gerar um novo dado
				ptrDado = new dado(cabecalho);
				// posicao relativa do novo dado
				// ex: se arquivo tinha 2 dados, eles estavam na posicao 0 e 1,
				// o novo vai ser inserido na posição 2
				posRelativa = cabecalho;

				cout << "posRelativa: " << posRelativa << endl;
				// atualiza o cabecalho para refletir a nova quantidade de dados
				cabecalho++;
				// posiciona cabeca de escrita no início do arquivo
				arquivo.seekp(0);
				// atualiza cabecalho no arquivo
				arquivo.write((char *) &cabecalho, sizeof(cabecalho));

				// encontra a posicao absoluta para armazenar o novo dado
				// precisa pular o cabecalho 
				// e os dados anteriores
				posAbsoluta = sizeof(cabecalho) + sizeof(dado)*posRelativa;

				cout << "posAbsoluta: " << posAbsoluta << endl;
				// escreve o dado
				arquivo.seekp(posAbsoluta);
				arquivo.write((char *) ptrDado, sizeof(dado));    

				// desaloca memória alocada dinamicamente
				delete ptrDado;  

				break;

			case 'a': // altera o conteúdo de um dado específico
				ptrDado = new dado;

				// verifica qual a posição a ser alterada
				cin >> posRelativa;
				if (posRelativa < cabecalho) {
					// encontra posição absoluta no disco
					posAbsoluta = sizeof(cabecalho) + sizeof(dado)*posRelativa;
					// posiciona cabeça de leitura
					arquivo.seekg(posAbsoluta);
					// lê o dado e o imprime
					arquivo.read((char*) ptrDado, sizeof(dado));
					cout << "Antes: " << *ptrDado << endl; 

					// gera novo dado com mesma chave
					delete ptrDado;
					ptrDado = new dado(posRelativa);
					arquivo.seekp(posAbsoluta);
					// altera o dado e o imprime
					arquivo.write((char*) ptrDado, sizeof(dado));
					cout << "Depois: " << *ptrDado << endl;
				}
				else {
					cout << "Posição inválida!" << endl;
				}

				delete ptrDado;
				break;

			case 'p': // imprime um dado específico
				ptrDado = new dado;

				// verifica qual a posição a ser impressa
				cin >> posRelativa;
				if (posRelativa < cabecalho) {
					// encontra posição absoluta no disco
					posAbsoluta = sizeof(cabecalho) + sizeof(dado)*posRelativa;
					// posiciona cabeça de leitura
					arquivo.seekg(posAbsoluta);
					// lê o dado e o imprime
					arquivo.read((char*) ptrDado, sizeof(dado));
					cout << *ptrDado << endl; 
				}
				else {
					cout << "Posição inválida!" << endl;
				}

				delete ptrDado;
				break;

			case 't': // imprime todos os dados
				ptrDado = new dado;

				// pula o cabecalho
				arquivo.seekg(sizeof(cabecalho));

				// lê todos os dados usando uma única variável
				for (unsigned i = 0; i < cabecalho; i++) {
					arquivo.read((char*) ptrDado, sizeof(dado));
					cout << *ptrDado << endl;
				}
			
				delete ptrDado;
				break;

			case 'f': // encerra aplicação
				break;
			
			default:
				cout << "Opção inválida!" << endl;
				break;
		}

		cin >> opcao;

	} while (opcao != 'f');

	return 0;
}
