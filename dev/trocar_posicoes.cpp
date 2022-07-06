#include <iostream>
#include <fstream>
#include <cstring>

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

int main(){
	
	// O arquivo binário é aberto tanto para entrada quanto saída de dados
	fstream arq_binario("dados_convertidos.bin", ios::binary | ios::in | ios::out);
	
	// erro será o retorno do programa, que é tratado no programa principal
	// Se erro = 1, representa que ocorreu erro (o usuário digitou algo incorreto)
	// Se erro = 2, os valores das posições são iguais
	int erro = 0;
	
	if(arq_binario){
		
		// É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		arq_binario.seekg(0, arq_binario.end);
		int tamanho_arquivo_binario = arq_binario.tellg();
		
		// É criado uma variável do tipo classe Binario para acessar a função de trocar
		Binario dados_binario;
		
		// Variáveis para a execução das operações
		int pos_primeira = -1;
		int pos_segunda = -1;
		long aux;
		
		cout << "Escreva a primeira posição da troca: " << endl;
		cin >> pos_primeira;
		
		// Tamanho da pos_primeira em relação ao início do arquivo binário,
		// ou seja, representa o byte que a posição de pos_primeira começa
		aux = pos_primeira * sizeof(Binario);
		
		if((pos_primeira < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
			erro = 1;
			
		else{
			
			cout << "Escreva a segunda posição da troca: " << endl;
			cin >> pos_segunda;
			
			// Tamanho da pos_segunda em relação ao início do arquivo binário,
			// ou seja, representa o byte que a posição de pos_segunda começa
			aux = sizeof(Binario) * pos_segunda;
			
			if((pos_segunda < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
				erro = 1;
				
			else{
				
				if(pos_primeira == pos_segunda)
					erro = 2;
					
				else
					dados_binario.trocar(arq_binario, pos_primeira, pos_segunda);
			}
		}
		
		arq_binario.close();
	}
	
	else{
		
		cout << "Não há arquivo convertido" << endl;
	}
	
	return erro;
}
