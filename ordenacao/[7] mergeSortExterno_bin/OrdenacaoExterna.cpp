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

void juntarArquivos(string nome_arq_input,string nome_arq_output, int n, int k){
	
	// Cria-se a quantidade de nós heap igual ao número de arquivos temporários
	MinHeapNoh *nohs = new MinHeapNoh[k];
	Binario *leitura = new Binario[1];
	
	stringstream nome_arquivo;
	
	// Para cada nó heap é lhe atribuído o primeiro pacote da classe Binario do arquivo temporário i
	for(int i = 0; i < k; i++){
		
		nome_arquivo.str("");
		nome_arquivo.clear();
		nome_arquivo << "dados_temp";
		nome_arquivo << to_string(i + 1);
		nome_arquivo << ".bin";
		
		ifstream arq_leitura(nome_arquivo.str(), ios::binary);
		
		arq_leitura.read((char*)(&leitura[0]), sizeof(Binario));
		
		nohs[i].bin = leitura[0];
		nohs[i].i = i;
		nohs[i].j = 1;
		
		arq_leitura.close();
	}
	
	// Criação do MinHeap com k nohs
	MinHeap hp(nohs, k);
	
	// cont representa quantos arquivos já foram tratados/chegaram ao fim
	int cont = 0;
	
	// pos representa a posição que um pacote Binario será inserida no arquivo final
	// também será usada para avançar na barra de progresso
	int pos = 0;
	
	ifstream arq_entrada(nome_arq_input, ios::binary);
	
	// Variáveis para para preencher a barra de progresso
	float progresso = 0, porcento = 1;
	int qtd_linhas_input = quantidadeLinhasArq(arq_entrada);
	int divisor = qtd_linhas_input / 100;
	if(divisor == 0)
		divisor = 1;
	
	arq_entrada.close();
	
	ofstream arq_result(nome_arq_output, ios::binary);
	
	progressbar(progresso);
	
	while(cont != k){
		
		// Cria-se um nó heap que representa a raiz do heap principal
		MinHeapNoh raiz = hp.getMin();
		
		raiz.alterarCampoPosicao(pos);
		
		// Insere-se a raiz (menor nome ou id {atual} de todos os arquivos temporários) no arquivo final
		arq_result.write((char*)(&raiz.bin), sizeof(Binario));
		
		nome_arquivo.str("");
		nome_arquivo.clear();
		nome_arquivo << "dados_temp";
		nome_arquivo << to_string(raiz.i + 1);
		nome_arquivo << ".bin";
		
		ifstream arq_leitura(nome_arquivo.str(), ios::binary);
		int quantidade_linhas = quantidadeLinhasArq(arq_leitura);
		
		// Tal condicional pega o próximo pacote Binario do atual arquivo temporário aberto
		// Caso TRUE, representa que ainda há pacotes a serem tratados
		// Caso FALSE, representa que se chegou no final do atual arquivo temporário aberto
		if(raiz.j < quantidade_linhas){
			
			arq_leitura.seekg(raiz.j * sizeof(Binario), arq_leitura.beg);
			
			arq_leitura.read((char*)(&leitura[0]), sizeof(Binario));
			
			raiz.bin = leitura[0];
			raiz.j++;
		}
		
		else{
			
			// O atual arquivo temporário aberto chegou no seu fim e não há mais pacotes para serem comparados
			// logo, ele é desconsiderado (ficando nos nós mais baixos do MinHeap principal)
			raiz.alterarCampoNome();
			
			cont++;
		}
		
		arq_leitura.close();
		
		// A raiz atual do MinHeap principal é substituída pelo próximo pacote Binario do atual arquivo temporário "aberto"
		// O MinHeap é rearranjado (aplica-se o corrige descendo) para que o menor nome ou id esteja no topo
		hp.inserirMin(raiz);
		
		// Progressão da barra
		if(porcento == (pos / divisor)){
			
			progressbar(progresso);
			porcento++;
		}
	}
	
	progresso = 100.0;
	progressbar(progresso);
	
	arq_result.close();
	delete[] leitura;
}

void salvarArquivo(string nome, Binario v[], int tam){
	
	ofstream arq(nome, ios::binary);
	
	for(int i = 0; i < tam; i++)
		arq.write((char*)(&v[i]), sizeof(Binario));
	
	arq.close();
}

int criarArquivosOrdenados(string nome_arq_input, int tam_particao){
	
	ifstream arq_entrada(nome_arq_input, ios::binary);
	
	if(arq_entrada){
		
		int quantidade_linhas = quantidadeLinhasArq(arq_entrada);
		
		arq_entrada.seekg(0, arq_entrada.beg);
		
		stringstream nome_arquivo;
		
		Binario *vetor_bin = new Binario[tam_particao];
		Binario *leitura = new Binario[1];
		
		int ate_linha = quantidade_linhas - (quantidade_linhas % tam_particao);
		int linha_atual = 0, cont = 0, total = 0;
		
		// Lê-se os dados do arquivo original e os insere em arquivos temporários
		while(linha_atual < ate_linha){
			
			arq_entrada.read((char*)(&leitura[0]), sizeof(Binario));
			
			vetor_bin[total] = leitura[0];
			
			total++;
			
			// vetor_bin está cheio
			if(total == tam_particao){
				
				cont++;
				
				nome_arquivo.str("");
				nome_arquivo.clear();
				nome_arquivo << "dados_temp";
				nome_arquivo << to_string(cont);
				nome_arquivo << ".bin";
				
				cout << nome_arquivo.str() << " criado com sucesso!" << endl;
				
				// QuickSort foi usado como algoritmo de ordenação interno
				vetor_bin->qsort(0, total - 1);
				
				// Salva o arquivo temporário
				salvarArquivo(nome_arquivo.str(), vetor_bin, tam_particao);
				
				total = 0;
			}
			
			linha_atual++;
		}
		
		// sobraram dados
		if(linha_atual != quantidade_linhas){
			
			Binario *vetor_resto_bin = new Binario[quantidade_linhas - linha_atual];
			
			while(linha_atual < quantidade_linhas){
				
				arq_entrada.read((char*)(&leitura[0]), sizeof(Binario));
				
				vetor_resto_bin[total] = leitura[0];
				
				total++;
				linha_atual++;
			}
			
			cont++;
			
			nome_arquivo.str("");
			nome_arquivo.clear();
			nome_arquivo << "dados_temp";
			nome_arquivo << to_string(cont);
			nome_arquivo << ".bin";
			
			cout << nome_arquivo.str() << " criado com sucesso!" << endl;
			
			vetor_resto_bin->qsort(0, total - 1);
			
			salvarArquivo(nome_arquivo.str(), vetor_resto_bin, total);
			
			delete[] vetor_resto_bin;
		}
		
		arq_entrada.close();
		delete[] leitura;
		delete[] vetor_bin;
		
		return cont;
	}
	
	else
		throw runtime_error("ERRO: arquivo não encontrado");
}

void externalSort(string nome_arq_input, string nome_arq_output, int tam_particao){
	
	int k = -1;
	
	try{
		
		// k é o número de arquivos ordenados
		k = criarArquivosOrdenados(nome_arq_input, tam_particao);
		
		cout << "quantidade arquivos temporários: " << k << endl;
		
		juntarArquivos(nome_arq_input ,nome_arq_output, tam_particao, k);
	}
	catch(exception& e){
		cout << e.what() << endl;
	}
	
	if(k != -1){
		
		cout << endl << endl << "Processo ocorreu corretamente!! Aperte Enter para apagar os arquivos temporários. . . " << flush;
		cin.get();
		
		stringstream nome_arquivo;
		
		// deleta os arquivos temporários
		for(int i = 0; i < k; i++){
			
			nome_arquivo.str("");
			nome_arquivo.clear();
			nome_arquivo << "dados_temp";
			nome_arquivo << to_string(i + 1);
			nome_arquivo << ".bin";
			
			remove(nome_arquivo.str().c_str());
		}
		
		cout << endl << "Por favor, caso queria averiguar o resultado, utilize os programas fornecidos do grupo pela etapa 1. . . " << flush;
		cin.get();
	}
}

int main(){
	
	string nome_arq_input = "dados_convertidos.bin";
	string nome_arq_output = "dados_convertidos.bin";
	
	ifstream arq_original(nome_arq_input, ios::binary);
	
	if(arq_original){
		
		int quantidade_linhas = quantidadeLinhasArq(arq_original);
		// tam_particao é o número de pacotes da classe Binario que um arquivo temporário terá
		int tam_particao = quantidade_linhas / 1000;
		
		if(tam_particao == 0)
			tam_particao = 999;
		
		arq_original.close();
		
		externalSort(nome_arq_input, nome_arq_output, tam_particao);
	}
	
	else
		cout << "Sem arquivo!! Por favor, insira o dados_convertidos.bin gerado pela etapa 1 do grupo." << endl;
	
	return 0;
}
