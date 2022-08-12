#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

// Máximo de números inteiros do arquivo na memória secundária
// que se pode ter carregado na memória primária
#define RAM 10

using namespace std;

struct arquivo{
	
	fstream *arq;
	int pos, MAX;
	int *buffer;
};

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

void salvarArquivo(string nome, int v[], int tam){
	
	ofstream arq(nome);
	
	for(int i = 0; i < tam; i++)
		arq << v[i] << " ";
	
	arq.close();
}

int criarArquivosOrdenados(ifstream& arqOriginal){
	
	int vetor[RAM];
	int cont = 0, total = 0, valor;
	
	stringstream nome_arquivo;
	
	if(arqOriginal){
		
		while(arqOriginal >> valor){
			
			vetor[total] = valor;
			total++;
			
			// vetor está cheio
			if(total == RAM){
				
				cont++;
				
				nome_arquivo.str("");
				nome_arquivo.clear();
				nome_arquivo << "dados_temp";
				nome_arquivo << to_string(cont);
				nome_arquivo << ".txt";
				
				cout << nome_arquivo.str() << endl;
				
				qsort(vetor, 0, total);
				salvarArquivo(nome_arquivo.str(), vetor, RAM);
				
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
		
		return cont;
	}
	
	else
		return -1;
}

void preencherBuffer(arquivo *umArquivo, int k){
	
	cout << "preencher_buffer" << endl;
	
	if(umArquivo->arq){
		
		umArquivo->pos = 0;
		umArquivo->MAX = 0;
		
		int valor;
		
		for(int i = 0; i < k; i++){
			
			if(*umArquivo->arq >> valor){
				
				umArquivo->buffer[umArquivo->MAX] = valor;
				umArquivo->MAX++;
			}
			
			else{
				umArquivo->arq->close();
				umArquivo->arq = NULL;
				break;
			}
		}
	}
}

int procurarMenor(arquivo *umArquivo, int numArqs, int k, int *menor){
	
	cout << "procura_menor" << endl;
	
	int index = -1;
	
	// procura o menor valor na primeira posição de cada buffer
	for(int i = 0; i < numArqs; i++){
		
		if(umArquivo[i].pos < umArquivo[i].MAX){
			
			if(index == -1)
				index = i;
				
			else{
				
				if(umArquivo[i].buffer[umArquivo[i].pos] < umArquivo[index].buffer[umArquivo[index].pos])
					index = i;
			}
		}
	}
	
	// achou menor. Atualiza a posição do buffer. Encher se estiver vazio
	if(index != -1){
		
		*menor = umArquivo[index].buffer[umArquivo[index].pos];
		umArquivo[index].pos++;
		
		if(umArquivo[index].pos == umArquivo[index].MAX)
			preencherBuffer(&umArquivo[index], k);
		
		return 1;
	}
	
	else
		return 0;
}

void mergeSort(int numArqs, int k){
	
	cout << "mergeSort" << endl;
	
	stringstream nome_arquivo;
	// buffer de saida
	int *buffer = new int[k * sizeof(int)];
	
	arquivo *arquivos = new arquivo[numArqs * sizeof(arquivo)];
	
	for(int i = 0; i < numArqs; i++){
		
		nome_arquivo.str("");
		nome_arquivo.clear();
		nome_arquivo << "dados_temp";
		nome_arquivo << to_string(i);
		nome_arquivo << ".txt";
		
		arquivos[i].arq->open(nome_arquivo.str());
		arquivos[i].MAX = 0;
		arquivos[i].pos = 0;
		arquivos[i].buffer = new int[k * sizeof(int)];
		preencherBuffer(&arquivos[i], k);
	}
	
	// enquanto houver arquivos para processar
	int menor, qtdBuffer = 0;
	
	while(procurarMenor(arquivos, numArqs, k, &menor) == 1){
		
		buffer[qtdBuffer] = menor;
		qtdBuffer++;
		
		if(qtdBuffer == k){
			
			salvarArquivo(nome_arquivo.str(), buffer, k);
			qtdBuffer = 0;
		}
	}
	
	// salva dados ainda no buffer
	if(qtdBuffer != 0)
		salvarArquivo(nome_arquivo.str(), buffer, qtdBuffer);
		
	for(int i = 0; i < numArqs; i++)
		delete[] arquivos[i].buffer;
		
	delete[] arquivos;
	delete[] buffer;
}

void mergeSortExterno(ifstream& arqOriginal){
	
	int numArqs = criarArquivosOrdenados(arqOriginal);
	// k é o tamanho dos buffers
	// 1 de saída e k de entradas
	int k = RAM / (numArqs + 1);
	if(k == 0)
		k = 1;
	cout << "numero de arquivos: " << numArqs << endl;
	cout << "k: " << k << endl;
	
	arqOriginal.close();
	// deleta o arquivo original
	remove("dados.txt");
	
	mergeSort(numArqs, k);
	
	stringstream nome_arquivo;
	
	// deleta os arquivos temporarios
	for(int i = 0; i < numArqs; i++){
		
		nome_arquivo.str("");
		nome_arquivo.clear();
		nome_arquivo << "dados_temp";
		nome_arquivo << to_string(i);
		nome_arquivo << ".txt";
		
		remove(nome_arquivo.str().c_str());
	}
	
	cout << "Fim." << endl;
}

int main(){
	
	ifstream arq("dados.txt");
	
	if(arq)
		mergeSortExterno(arq);
	
	else
		cout << "sem arquivo" << endl;
	
	return 0;
}
