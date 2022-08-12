#include <iostream>
#include <limits.h>

using namespace std;

#define N 4

struct dado{
	
	int valor;	// valo a ser armazenado
	int i;	// index do vetor que esse dado é pego
	int j;	// index do próximo dado que será pego do vetor
};

void swap(dado *x, dado *y){
	
	dado temp = *x;
	*x = *y;
	*y = temp;
}

void printArray(int vetor[], int size){
	
	for(int i = 0; i < size; i++)
		cout << vetor[i] << " ";
}

class MinHeap{
	
	private:
		dado *dados;
		int tamanho;
		
	public:
		//int pai(int i){ return (i - 1)/2; }
		int esquerdo(int i){ return 2 * i + 1; }
		int direito(int i){ return 2 * i + 2; }
		dado getMin(){ return dados[0]; }
		void corrigeDescendo(int i);
		//void corrigeSubindo(int i);
		void inserirMin(dado x){ dados[0] = x; corrigeDescendo(0); }
		//MinHeap(int cap);
		MinHeap(dado vetor[], int tam);
		~MinHeap();
		//dado retirarRaiz();
		//void inserirDado(dado d);
};

MinHeap::MinHeap(dado vetor[], int tam){
	
	tamanho = tam;
	
	dados = vetor;	// armazena o endereço do vetor
	
	int metade = (tamanho - 1) / 2;
	while(metade >= 0){
		
		corrigeDescendo(metade);
		metade--;
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

int* mergeKArrays(int vetor[][N], int k){
	
	// Armazena o vetor de saída (será retornado no final)
	int *output = new int[N * k];
	
	// Criação de k nós heap
	// Todo nó heap tem o primeiro (menor) elemento de um vetor
	dado *vet = new dado[k];
	
	for(int i = 0; i < k; i++){
		
		// Armazena o primeiro (menor) elemento do vetor i no nó heap i
		vet[i].valor = vetor[i][0];
		
		// Index do nó heap
		vet[i].i = i;
		
		// Index do próximo elemento que será armazenado pelo nó heap
		vet[i].j = 1;
	}
	
	// Cria o heap
	MinHeap hp(vet, k);
	
	// Agora, pega-se todos os mínimos, um por um
	// e os repoe com o próximo elemento do seu devido vetor
	for(int cont = 0; cont < N * k; cont++){
		
		// Pega o menor elemento (raiz do heap) e o armazena no output
		dado raiz = hp.getMin();
		output[cont] = raiz.valor;
		
		// Acha o próximo elemento que irá entrar do lugar da atual raiz do heap
		// O próximo elemento pertence ao mesmo vetor da raiz atual
		if(raiz.j < N){
			
			raiz.valor = vetor[raiz.i][raiz.j];
			raiz.j++;
		}
		
		// Se for o último elemento, INT_MAX seria o infinito
		else
			raiz.valor = INT_MAX;
			
		hp.inserirMin(raiz);
	}
	
	return output;
}

int main(){
	
	// Suponhe-se que todos os vetores já estejam ordenados
	int vetor[][N] = {{2, 6, 12, 34}, {1, 9, 20, 1000}, {23, 34, 90, 2000}};
	
	cout << sizeof(vetor) << endl;
	cout << sizeof(vetor[0]) << endl;
	
	int k = sizeof(vetor) / sizeof(vetor[0]);
	
	cout << k << endl;
	
	int *output = mergeKArrays(vetor, k);
	
	printArray(output, N * k);
	
	delete[] output;
	
	return 0;
}
