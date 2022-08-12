#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>

using namespace std;

int particao(int v[], int menor, int maior){
	
	int pivo = v[maior];
	
	int i = (menor - 1);
	
	for(int j = menor; j <= maior; j++)
	{
		if(v[j] < pivo)
		{
			i++;
			swap(v[i], v[j]);
		}
	}
	
	swap(v[i + 1], v[maior]);
	
	return (i + 1);
}

void qsort(int v[], int menor, int maior){
	
	if(menor < maior){
		
		int pi = particao(v, menor, maior);
		
		qsort(v, menor, pi - 1);
		qsort(v, pi + 1, maior);
	}
}

struct MinHeapNoh{
	
	int valor;	// valor a ser armazenado
	int i;	// número/id do arquivo que tal valor é pego
	int j;	// número/id do próximo valor que será pego do arquivo i
};

void swap(MinHeapNoh *x, MinHeapNoh *y){
	
	MinHeapNoh temp = *x;
	*x = *y;
	*y = temp;
}

class MinHeap{
	
	private:
		MinHeapNoh *dados;
		int tamanho;
		
	public:
		MinHeap(MinHeapNoh vetor[], int tam);
		~MinHeap();
		int esquerdo(int i){ return 2 * i + 1; }
		int direito(int i){ return 2 * i + 2; }
		MinHeapNoh getMin(){ return dados[0]; }
		void corrigeDescendo(int i);
		void inserirMin(MinHeapNoh x){ dados[0] = x; corrigeDescendo(0); }
};

MinHeap::MinHeap(MinHeapNoh vetor[], int tam){
	
	tamanho = tam;
	
	dados = vetor;	// armazena o endereço do vetor
	
	// O primeiro valor de i representa a metade do MinHeap
	int i = (tamanho - 1) / 2;
	while(i >= 0){
		
		corrigeDescendo(i);
		i--;
	}
}

MinHeap::~MinHeap(){
	
	delete[] dados;
}

void MinHeap::corrigeDescendo(int i){
	
	int esq = esquerdo(i);
	int dir = direito(i);
	
	int menor = i;
	
	if((esq < tamanho) and (dados[esq].valor < dados[i].valor))
		menor = esq;
		
	if((dir < tamanho) and (dados[dir].valor < dados[menor].valor))
		menor = dir;
		
	if(menor != i){
		
		swap(&dados[i], &dados[menor]);
		
		corrigeDescendo(menor);
	}
}

void mergeFiles(string nome_arq_output, int n, int k){
	
	stringstream nome_arquivo;
	
	ofstream arq_result(nome_arq_output);
	
	// Cria-se a quantidade de nós igual ao número de partições
	// Cada nó heap tem o primeiro elemento de seu devido arquivo
	MinHeapNoh *nohs = new MinHeapNoh[k];
	
	int valor;
	int i;
	
	for(i = 0; i < k; i++){
		
		nome_arquivo.str("");
		nome_arquivo.clear();
		nome_arquivo << "dados_temp";
		nome_arquivo << to_string(i + 1);
		nome_arquivo << ".txt";
		
		ifstream arq_leitura(nome_arquivo.str());
		
		arq_leitura >> valor;
		
		nohs[i].valor = valor;
		nohs[i].i = i;
		nohs[i].j = 1;
		
		arq_leitura.close();
	}
	
	MinHeap hp(nohs, i);
	
	int cont = 0;
	int z = -1;
	
	while(cont != i){
		
		MinHeapNoh raiz = hp.getMin();
		arq_result << raiz.valor << '\n';
		
		if(raiz.j < n){
			
			nome_arquivo.str("");
			nome_arquivo.clear();
			nome_arquivo << "dados_temp";
			nome_arquivo << to_string(raiz.i + 1);
			nome_arquivo << ".txt";
			
			ifstream arq_leitura(nome_arquivo.str());
			
			// Seria mais eficiente tentar usar seekg
			// O problema é que um arquivo txt é separado por char
			while(z < raiz.j){
				
				arq_leitura >> valor;
				
				z++;
			}
			
			z = -1;
			
			raiz.valor = valor;
			raiz.j++;
			
			arq_leitura.close();
		}
		
		else{
			
			raiz.valor = INT_MAX;
			cont++;
		}
		
		hp.inserirMin(raiz);
	}
	
	arq_result.close();
}

void salvarArquivo(string nome, int v[], int tam){
	
	ofstream arq(nome);
	
	for(int i = 0; i < tam; i++)
		arq << v[i] << " ";
	
	arq.close();
}

int criarArquivosOrdenados(string nome_arq_input, int tam_particao){
	
	fstream arq_entrada(nome_arq_input);
	
	if(arq_entrada){
		
		int vetor[tam_particao];
		int cont = 0, total = 0, valor;
		
		stringstream nome_arquivo;
		
		while(arq_entrada >> valor){
			
			vetor[total] = valor;
			total++;
			
			// vetor está cheio
			if(total == tam_particao){
				
				cont++;
				
				nome_arquivo.str("");
				nome_arquivo.clear();
				nome_arquivo << "dados_temp";
				nome_arquivo << to_string(cont);
				nome_arquivo << ".txt";
				
				cout << nome_arquivo.str() << endl;
				
				qsort(vetor, 0, total);
				salvarArquivo(nome_arquivo.str(), vetor, tam_particao);
				
				total = 0;
			}
		}
		
		// sobraram dados
		if(total > 0){
			
			cont++;
			
			nome_arquivo.str("");
			nome_arquivo.clear();
			nome_arquivo << "dados_temp";
			nome_arquivo << to_string(cont);
			nome_arquivo << ".txt";
			
			cout << nome_arquivo.str() << endl;
			
			qsort(vetor, 0, total);
			salvarArquivo(nome_arquivo.str(), vetor, total);
		}
		
		arq_entrada.close();
		
		return cont;
	}
	
	else{
		
		cout << "Sem arquivo" << endl;
		
		return -1;
	}
}

void externalSort(string nome_arq_input, string nome_arq_output, int tam_particao){
	
	// k é o número de arquivos ordenados
	int k = criarArquivosOrdenados(nome_arq_input, tam_particao);
	
	if(k != -1){
		
		mergeFiles(nome_arq_output, tam_particao, k);
		
		stringstream nome_arquivo;
		
		// deleta o arquivo original e os arquivos temporarios
		remove(nome_arq_input.c_str());
		
		for(int i = 0; i < k; i++){
			
			nome_arquivo.str("");
			nome_arquivo.clear();
			nome_arquivo << "dados_temp";
			nome_arquivo << to_string(i + 1);
			nome_arquivo << ".txt";
			
			remove(nome_arquivo.str().c_str());
		}
	}
}

int main(){
	
	// Tamanho de cada partição
	int tam_particao = 4;
	
	string nome_arq_input = "dados.txt";
	string nome_arq_output = "resultado.txt";
	
	externalSort(nome_arq_input, nome_arq_output, tam_particao);
	
	return 0;
}
