#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <limits>
#include <limits.h>
#include <exception>

using namespace std;

// Função para simular uma barra de progresso da junção dos arquivos
void progressbar(float &progresso){
	
	int tamanhoBarra = 70;
	
	cout << "[";
	
	// Desenha cada caractere da barra, baseado no valor de progresso
	int pos = tamanhoBarra * progresso;
	for(int i = 0; i < tamanhoBarra; i++){
		
		if(i < pos) 
			cout << '=';
		else if(i == pos) 
			cout << '>';
		else 
			cout << " ";
	}
	
	int porcento = int(progresso * 100.0);
	
	// \r move o cursor para o começo da linha, permitindo a reestruturação da barra
	// cout.flush() libera um fluxo de saída (nesse caso, a barra de progresso)
	if(porcento >= 99){
		
		cout << "] " << 100 << " %\r";
		cout.flush();
	}
	
	else{
		
		cout << "] " << porcento << " %\r";
		cout.flush();
	}
	
	progresso += 0.01;
}

class Binario{
	
	friend class MinHeap;
	friend class MinHeapNoh;
	
	private:
		int campo_1_id;
		char campo_2_name[42];
		char campo_3_job[54];
		float campo_4_base_pay;
		float campo_5_overtime_pay;
		float campo_6_other_pay;
		float campo_7_benefits;
		float campo_8_total_pay;
		float campo_9_total_pay_benefits;
		int campo_10_year;
		int campo_11_posicao;
	
	public:
		Binario();
		int particao(int menor, int maior);
		void qsort(int menor, int maior);
};

Binario::Binario(){
	
	campo_1_id = -1;
	memset(campo_2_name, 0, sizeof(campo_2_name));
	memset(campo_3_job, 0, sizeof(campo_3_job));
	campo_4_base_pay = 0;
	campo_5_overtime_pay = 0;
	campo_6_other_pay = 0;
	campo_7_benefits = 0;
	campo_8_total_pay = 0;
	campo_9_total_pay_benefits = 0;
	campo_10_year = 0;
	campo_11_posicao = -1;
}

int Binario::particao(int menor, int maior){
	
	Binario pivo = this[maior];
	
	int i = (menor - 1);
	
	for(int j = menor; j <= maior; j++){
		
		// Se o primeiro nome é menor que o segundo nome, trocam
		if((strcasecmp(this[j].campo_2_name, pivo.campo_2_name)) < 0){
			
			i++;
			swap(this[i], this[j]);
		}
		
		// Se os dois nomes são iguais, ordena-se pelo id
		else if(((strcasecmp(this[j].campo_2_name, pivo.campo_2_name)) == 0) and (this[j].campo_1_id < pivo.campo_1_id)){
			
			i++;
			swap(this[i], this[j]);
		}
	}
	
	swap(this[i + 1], this[maior]);
	
	return (i + 1);
}

void Binario::qsort(int menor, int maior){
	
	if(menor < maior){
		
		int pi = particao(menor, maior);
		
		qsort(menor, pi - 1);
		qsort(pi + 1, maior);
	}
}

class MinHeapNoh{
	
	public:
		Binario bin;	// pacote da classe Binario de certo arquivo temporário i a ser armazenado
		int i;	// posicão/id dentre os arquivos temporários
		int j;	// posicão/id do próximo pacote que será pego do arquivo temporário i
		void alterarCampoNome(){ bin.campo_2_name[0] = std::numeric_limits<char>::max(); }
		void alterarCampoPosicao(int& pos){ bin.campo_11_posicao = pos++; }
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
		int esquerdo(int i){ return 2 * i + 1; }
		int direito(int i){ return 2 * i + 2; }
		void corrigeDescendo(int i);
		
	public:
		MinHeap(MinHeapNoh vetor[], int tam);
		~MinHeap();
		MinHeapNoh getMin(){ return dados[0]; }
		void inserirMin(MinHeapNoh x){ dados[0] = x; corrigeDescendo(0); }
};

MinHeap::MinHeap(MinHeapNoh vetor[], int tam){
	
	tamanho = tam;
	dados = vetor;
	
	int i = (tamanho - 1) / 2;
	while(i >= 0){
		
		corrigeDescendo(i);
		
		i--;
	}
}

MinHeap::~MinHeap(){
	
	delete[] dados;
}

// Corrige descendo considerando preferencialmente a ordenação pelo nome, o id é considerado se os nomes forem iguais
void MinHeap::corrigeDescendo(int i){
	
	int esq = esquerdo(i);
	int dir = direito(i);
	
	int menor = i;
	
	if((esq < tamanho) and ((strcasecmp(dados[esq].bin.campo_2_name, dados[i].bin.campo_2_name)) < 0))
		menor = esq;
		
	else if((esq < tamanho) and ((strcasecmp(dados[esq].bin.campo_2_name, dados[i].bin.campo_2_name)) == 0) and (dados[esq].bin.campo_1_id < dados[i].bin.campo_1_id))
		menor = esq;
	
	if((dir < tamanho) and ((strcasecmp(dados[dir].bin.campo_2_name, dados[menor].bin.campo_2_name)) < 0))
		menor = dir;
		
	else if((dir < tamanho) and ((strcasecmp(dados[dir].bin.campo_2_name, dados[menor].bin.campo_2_name)) == 0) and (dados[dir].bin.campo_1_id < dados[menor].bin.campo_1_id))
		menor = dir;
		
	if(menor != i){
		
		swap(&dados[i], &dados[menor]);
		
		corrigeDescendo(menor);
	}
}

int quantidadeLinhasArq(ifstream& nome_arq){
	
	nome_arq.seekg(0, nome_arq.end);
	int tamanho_arquivo_binario = nome_arq.tellg();
	
	int quantidade_linhas = tamanho_arquivo_binario / sizeof(Binario);
	
	return quantidade_linhas;
}

void salvarArquivo(string nome, Binario v[], int tam){
	
	ofstream arq(nome, ios::binary);
	
	for(int i = 0; i < tam; i++)
		arq.write((char*)(&v[i]), sizeof(Binario));
	
	arq.close();
}
