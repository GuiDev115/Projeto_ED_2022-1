#include <iostream>

using namespace std;

struct dado{
	
	int valor;
};

class MinHeap{
	
	private:
		dado *dados;
		int capacidade;
		int tamanho;
		// Funções auxiliares, para o heap começando na posição 0
		// Se o heap começasse na posição 1 seria respectivamente:
		// pai(i) = i/2
		// esquerdo(i) = 2 * i
		// direito(i) = 2 * i + 1
		int pai(int i){ return (i - 1)/2; }
		int esquerdo(int i){ return 2 * i + 1; }
		int direito(int i){ return 2 * i + 2; }
		// Funções essenciais para o heap
		void corrigeDescendo(int i);
		void corrigeSubindo(int i);
		void arruma();	// heapify() ou constroi-heap()
		
	public:
		MinHeap(int cap);
		MinHeap(int vetor[], int tam, int cap);
		~MinHeap();
		dado retirarRaiz();
		void inserirDado(dado d);
		void depuracao();
};

MinHeap::MinHeap(int cap){
	
	capacidade = cap;
	tamanho = 0;
	dados = new dado[capacidade];
	
	for(int i = 0; i < capacidade; i++)
		dados[i].valor = 0;
}

MinHeap::MinHeap(int vetor[], int tam, int cap){
	
	capacidade = cap;
	tamanho = tam;
	
	dados = new dado[capacidade];
	
	for(int i = 0; i < tam; i++)
		dados[i].valor = vetor[i];
	
	arruma();
}

MinHeap::~MinHeap(){
	
	delete[] dados;
}

void MinHeap::corrigeDescendo(int i){
	
	int esq = esquerdo(i);
	int dir = direito(i);
	
	int menor = i;
	
	// tamanho -1 representa o FINAL/último elemento do heap que começa na posição 0
	// caso o heap começasse na posição 1, FINAL seria apenas tamanho
	if((esq <= tamanho - 1) and (dados[esq].valor < dados[i].valor))
		menor = esq;
		
	if((dir <= tamanho - 1) and (dados[dir].valor < dados[menor].valor))
		menor = dir;
		
	if(menor != i){
		
		dado aux = dados[i];
		dados[i] = dados[menor];
		dados[menor] = aux;
		
		corrigeDescendo(menor);
	}
}

void MinHeap::corrigeSubindo(int i){
	// i = 1, p = 0
	int p = pai(i);
	
	// 0 = Inicio
	if((p >= 0) and (dados[i].valor < dados[p].valor)){
		
		dado aux = dados[i];
		dados[i] = dados[p];
		dados[p] = aux;
		
		corrigeSubindo(p);
	}
}

void MinHeap::arruma(){
	
	// metade = final/2 ou tamanho / 2 (heaps começando em 1)
	// metade = (final - 1) / 2 ou (tamanho - 2) / 2 (heaps começando em 0)
	for(int metade = (tamanho - 2) / 2; metade >= 0; metade--)
		corrigeDescendo(metade);
}

dado MinHeap::retirarRaiz(){
	
	dado aux;
	aux.valor = -1;
	
	if(tamanho < 1){
		
		cout << "erro" << endl;
	}
	
	else{
		// 0 = Inicio
		// tamanho - 1 = Final
		aux = dados[0];
		dados[0] = dados[tamanho - 1];
		dados[tamanho - 1] = aux;
		
		tamanho--;
		corrigeDescendo(0);
	}
	
	return aux;
}

void MinHeap::inserirDado(dado d){
	
	if(tamanho == capacidade)
		cout << "erro" << endl;
		
	else{
		// tamanho = Final + 1
		dados[tamanho] = d;
		corrigeSubindo(tamanho);
		tamanho++;
	}
}

void MinHeap::depuracao(){
	
	cout << "Capacidade: " << capacidade << '\n'
	<< "Tamanho: " << tamanho << endl
	<< "Dados: ";
	
	for(int i = 0; i < capacidade; i++)
		cout << dados[i].valor << " ";
		
	cout << endl;
}

int main(){
	
	int tam, cap;
	cin >> cap;
	cin >> tam;
	int vetor[tam];
	
	for(int i = 0; i < tam; i++)
		cin >> vetor[i];
	
	MinHeap heap(vetor, tam, cap);
	
	heap.depuracao();
	
	char c;
	cin >> c;
	dado retirado;
	
	while(c != 'q'){
		
		if(c == 'i'){
			
			dado num;
			cin >> num.valor;
			
			heap.inserirDado(num);
			
			heap.depuracao();
		}
		
		if(c == 'r'){
			
			retirado = heap.retirarRaiz();
			
			cout << retirado.valor << endl;
			
			heap.depuracao();
		}
		
		cin >> c;
	}
	
	return 0;
}
