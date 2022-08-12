#include <iostream>

using namespace std;

#define N 4

void printArray(int vetor[], int size){
	
	for(int i = 0; i < size; i++)
		cout << vetor[i] << " ";
}

void mergeArrays(int vetor1[], int vetor2[], int n1, int n2, int vetor3[]){
	
	int i = 0, j = 0, k = 0;
	
	while(i < n1 and j < n2){
		
		if(vetor1[i] < vetor2[j])
			vetor3[k++] = vetor1[i++];
			
		else
			vetor3[k++] = vetor2[j++];
	}
	
	while(i < n1)
		vetor3[k++] = vetor1[i++];
		
	while(j < n2)
		vetor3[k++] = vetor2[j++];
}

void mergeKArrays(int vetor[][N], int i, int j, int output[]){
	
	if(i == j){
		
		for(int p = 0; p < N; p++)
			output[p] = vetor[i][p];
			
		return;
	}
	
	if(j - i == 1){
		
		mergeArrays(vetor[i], vetor[j], N, N, output);
		
		return;
	}
	
	int out1[N * (((i + j) / 2) - i + 1)], out2[N * (j - ((i + j) / 2))];
	
	mergeKArrays(vetor, i, (i + j) / 2, out1);
	mergeKArrays(vetor, (i + j) / 2 + 1, j, out2);
	
	mergeArrays(out1, out2, N * (((i + j) / 2) - i + 1), N * (j - ((i + j) / 2)), output);
}

int main(){
	
	int vetor[][N] = {{2, 6, 12, 34}, {1, 9, 20, 1000}, {23, 34, 90, 2000}, {14, 19, 22, 37}};
	
	cout << sizeof(vetor) << endl;
	cout << sizeof(vetor[0]) << endl;
	
	int k = sizeof(vetor) / sizeof(vetor[0]);
	
	cout << k << endl;
	
	int output[N * k];
	
	mergeKArrays(vetor, 0, k - 1, output);
	
	printArray(output, N * k);
	
	return 0;
}
