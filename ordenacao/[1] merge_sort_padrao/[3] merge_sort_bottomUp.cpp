#include <iostream>

using namespace std;

// Outra maneira de escrever a intercalar (para o mergeSortIterativo)
void intercalar(int a[], int inicio, int meio, int fim){
	
	int i = inicio, j = meio;
	int tamanho = fim - inicio + 1;
	// vetor auxiliar
	int aux[tamanho];
	
	int k = 0;
	
	while((i < meio) and (j <= fim)){
		
		if(a[i] <= a[j])
			aux[k++] = a[i++];
			
		else
			aux[k++] = a[j++];
	}
	// terminou um do vetores, agora copia o outro
	while(i < meio)
		aux[k++] = a[i++];
		
	while(j <= fim)
		aux[k++] = a[j++];
		
	// agora copiamos do vetor aux em a[inicio:fim]
	for(int m = 0; m < tamanho ; m++)
		a[inicio + m] = aux[m];
}

// MergeSort Bottom-Up
// Nesse versão é considerado que o vetor já está inicialmente
// partido em pedaços de tamanho único, e assim ir aumentando seus pedaços (dobrando)
// até ser igual ou maior ao vetor original
// Algoritmo base para ordenação externa (em disco)
void mergeSortIterativo(int a[], int tam){
	
	int inicio, fim, num_blocos = 1;
	
	while(num_blocos < tam){
		
		inicio = 0;
		
		while(inicio + num_blocos < tam){
			
			fim = inicio + 2 * num_blocos - 1;
			
			if(fim >= tam)
				fim = tam - 1;
				
			intercalar(a, inicio, inicio + num_blocos, fim);
			
			inicio = inicio + 2 * num_blocos;
		}
		
		num_blocos *= 2;
	}
}

int main(){
	
	int vetor[10] = {12, 4, 6, 21, 18, 3, 9, 16, 25, 7};
	
	cout << "antes: " << flush;
	for(int i = 0; i < 10; i++)
		cout << vetor[i] << " ";
		
	cout << endl;
	
	mergeSortIterativo(vetor, 10);
	
	cout << "depois: " << flush;
	for(int i = 0; i < 10; i++)
		cout << vetor[i] << " ";
		
	cout << endl;
	
	return 0;
}
