#include <iostream>

using namespace std;

// Utilizando o mergeSort não é necessário os 2 trechos estarem previamente ordenados
// pois cada trecho nesse caso tem tamanho único 
void intercalar(int a[], int inicio, int meio, int fim){
	
	int i = inicio, j = meio + 1;
	int tamanho = fim - inicio + 1;
	// vetor auxiliar
	int aux[tamanho];
	
	for(int k = 0; k < tamanho; k++){
		
		if((i <= meio) and (j <= fim)){
			
			if(a[i] <= a[j])
				aux[k] = a[i++];	// aux[k] = a[i]; i++;
				
			else
				aux[k] = a[j++];
		}
		// terminou o trecho1
		else if(i > meio)
			aux[k] = a[j++];
			
		// terminou o trecho2 (j > final)
		else
			aux[k] = a[i++];
	}
	
	// terminando: copiar de aux[] em a[inicio:fim]
	for(int k = 0; k < tamanho; k++)
		a[inicio + k] = aux[k];
}

// MergeSort Top-Down
// Consiste em aplicar, recursivamente, o processo da divisão de vetor
// original em metades, até que cada metade tenha 1 único elemento
// intercalando as metades ordenadas após isso
void mergeSort(int a[], int inicio, int fim){
	
	int meio;
	
	if(inicio < fim){
		
		meio = (inicio + fim) / 2;
		
		mergeSort(a, inicio, meio);
		mergeSort(a, meio + 1, fim);
		
		intercalar(a, inicio, meio, fim);
	}
}

int main(){
	
	int vetor[5] = {17, 13, 64, 35, 29};
	
	cout << "antes: " << flush;
	for(int i = 0; i < 5; i++)
		cout << vetor[i] << " ";
		
	cout << endl;
	
	mergeSort(vetor, 0, 4);
	
	cout << "depois: " << flush;
	for(int i = 0; i < 5; i++)
		cout << vetor[i] << " ";
		
	cout << endl;
	
	return 0;
}
