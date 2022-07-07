#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

class Binario{
	
	private:
		int campo_1_id;
		char campo_2_name[40];
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
		void imprimir(Binario& umaLinha);
        void trocar(fstream& umArquivo, int p1, int p2);
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

// Função para impressão dos dados
void Binario::imprimir(Binario& umaLinha){
	
	cout << umaLinha.campo_1_id << '\n'
	<< umaLinha.campo_2_name << '\n'
	<< umaLinha.campo_3_job << '\n'
	<< umaLinha.campo_4_base_pay << '\n'
	<< umaLinha.campo_5_overtime_pay << '\n'
	<< umaLinha.campo_6_other_pay << '\n'
	<< umaLinha.campo_7_benefits << '\n'
	<< umaLinha.campo_8_total_pay << '\n'
	<< umaLinha.campo_9_total_pay_benefits << '\n'
	<< umaLinha.campo_10_year << '\n'
	<< umaLinha.campo_11_posicao << '\n' << endl;
	
	#warning retire o campo posicao antes de entregar!
}

// Função para trocar duas linhas (pacote/bloco classe Binario) de posição
void Binario::trocar(fstream& umArquivo, int p1, int p2){
	
	// Criação dos pacotes/blocos
	Binario bloco_1;
	Binario bloco_2;
	
	// Atribui-se à bloco_1 todos os elementos da 1ª posição
	umArquivo.seekg(p1 * sizeof(Binario), umArquivo.beg);
	umArquivo.read((char*)(&bloco_1), sizeof(Binario));
	
	// Atribui-se à bloco_2 todos os elementos da 2ª posição
	umArquivo.seekg(p2 * sizeof(Binario), umArquivo.beg);
	umArquivo.read((char*)(&bloco_2), sizeof(Binario));
	
	// Troca de posições
	int aux_pos = bloco_1.campo_11_posicao;
	bloco_1.campo_11_posicao = bloco_2.campo_11_posicao;
	bloco_2.campo_11_posicao = aux_pos;
	
	// Escrita dos blocos/pacotes com posições alteradas
	umArquivo.seekg(p1 * sizeof(Binario), umArquivo.beg);
	umArquivo.write((char*)(&bloco_2), sizeof(Binario));
	
	umArquivo.seekg(p2 * sizeof(Binario), umArquivo.beg);
	umArquivo.write((char*)(&bloco_1), sizeof(Binario));
}