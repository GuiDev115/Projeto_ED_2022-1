#include <iostream>

using namespace std;

// Consiste em dividir um vetor em 2 trechos ordenados
// e comparar os valores um a um, os inserindo em um novo vetor
void intercalar(int a[], int inicio, int meio, int fim){
	
	int i = inicio, j = meio + 1;
	int tamanho = fim - inicio + 1;
	// vetor auxiliar
	int aux[tamanho];
	
	for(int k = 0; k < tamanho; k++){
		
		if((i <= meio) and (j <= fim)){
			
			if(a[i] <= a[j]){
				
				// copia trecho1 em aux[] e avança em trecho1
				aux[k] = a[i];
				i++;
			}
			
			else{
				
				// copia trecho2 em aux[] e avança em trecho2
				aux[k] = a[j];
				j++;
			}
		}
		// terminou o trecho1
		else if(i > meio){
			
			aux[k] = a[j];
			j++;
		}
		// terminou o trecho2 (j > final)
		else{
			
			aux[k] = a[i];
			i++;
		}
	}
	
	// terminando: copiar de aux[] em a[inicio:fim]
	for(int k = 0; k < tamanho; k++){
		
		a[inicio + k] = aux[k];
	}
}

int main(){
	
	int vetor[5] = {13, 17, 64, 29, 35};
	
	cout << "antes: " << flush;
	for(int i = 0; i < 5; i++)
		cout << vetor[i] << " ";
		
	cout << endl;
	
	intercalar(vetor, 0, 2, 4);
	
	cout << "depois: " << flush;
	for(int i = 0; i < 5; i++)
		cout << vetor[i] << " ";
		
	cout << endl;
	
	return 0;
}
