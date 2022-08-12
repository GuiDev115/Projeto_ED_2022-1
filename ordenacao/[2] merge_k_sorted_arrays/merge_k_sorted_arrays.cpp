#include <iostream>

using namespace std;

#define N 4

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

void printArray(int vetor[], int size){
	
	for(int i = 0; i < size; i++)
		cout << vetor[i] << " ";
}

void mergeKArrays(int vetor[][N], int k, int output[]){
	
	for(int i = 0; i < k; i++)
		for(int j = 0; j < N; j++)
			output[(N * i) + j] = vetor[i][j];
			
	qsort(output, 0, N * k);
}

int main(){
	
	int vetor[][N] = {{2, 6, 12, 34}, {1, 9, 20, 1000}, {23, 34, 90, 2000}};
	
	cout << sizeof(vetor) << endl;
	cout << sizeof(vetor[0]) << endl;
	
	int k = sizeof(vetor) / sizeof(vetor[0]);
	
	cout << k << endl;
	
	int output[N * k];
	
	mergeKArrays(vetor, k, output);
	
	printArray(output, N * k);
	
	return 0;
}
