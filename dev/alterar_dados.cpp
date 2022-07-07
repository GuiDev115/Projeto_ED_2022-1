#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Binario{
	
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
		void alterar_campo(fstream& umArquivo, int pos, int opcao);
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

// Função para alterar algum campo de escolha de uma posição específica
void Binario::alterar_campo(fstream& umArquivo, int pos, int opcao){
	
	// Variáveis para a execução das operações
	string name_or_job;
	name_or_job.clear();
	int id_or_year = 0;
	float pay = 0;
	
	// Em cada caso, a posição se altera pela soma dos posições anteriores (exceto a primeira);
	// Nos casos dos tipos int e float, pega-se o novo valor e se sobrescreve no campo desejado;
	// Nos casos do tipo char, limpa-se o campo e se insere o novo escrito.
	switch(opcao){
		
		case 0:
			umArquivo.seekg(pos * sizeof(Binario), umArquivo.beg);
			
			cout << "Digite o novo id: ";
			cin >> id_or_year;
			
			umArquivo.write((char*)(&id_or_year), sizeof(campo_1_id));
			break;
			
		case 1:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id);
			umArquivo.seekg(pos, umArquivo.beg);
			
			char nome[sizeof(campo_2_name)];
			memset(nome, 0, sizeof(nome));
			
			cin.ignore();
			cout << "Digite o novo nome (máx. 41 caracteres): ";
			getline(cin, name_or_job);
			
			if(name_or_job.size() >= sizeof(campo_2_name))
				cout << "Passou do limite" << endl;
				
			else{
				
				for(unsigned int i = 0; i < name_or_job.size(); i++)
					nome[i] = name_or_job[i];
					
				memset(campo_2_name, 0, sizeof(campo_2_name));
				umArquivo.write((char*)(&nome), sizeof(campo_2_name));
			}
			break;
			
		case 2:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name);
			umArquivo.seekg(pos, umArquivo.beg);
			
			char trabalho[sizeof(campo_3_job)];
			memset(trabalho, 0, sizeof(trabalho));
			
			cin.ignore();
			cout << "Digite o novo trabalho(máx. 53 caracteres): ";
			getline(cin, name_or_job);
			
			if(name_or_job.size() >= sizeof(campo_3_job))
				cout << "Passou do limite" << endl;
				
			else{
				
				for(unsigned int i = 0; i < name_or_job.size(); i++)
					trabalho[i] = name_or_job[i];
					
				memset(campo_2_name, 0, sizeof(campo_3_job));
				umArquivo.write((char*)(&trabalho), sizeof(campo_3_job));
			}
			break;
			
		case 3:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job) ;
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: ";
			cin >> pay;
			
			umArquivo.write((char*)(&pay), sizeof(campo_4_base_pay));
			
			break;
			
		case 4:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: ";
			cin >> pay;
			
			umArquivo.write((char*)(&pay), sizeof(campo_5_overtime_pay));
			break;
			
		case 5:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay) + sizeof(campo_5_overtime_pay);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: ";
			cin >> pay;
			
			umArquivo.write((char*)(&pay), sizeof(campo_6_other_pay));
			break;
			
		case 6:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay) + sizeof(campo_5_overtime_pay) + sizeof(campo_6_other_pay);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: ";
			cin >> pay;
			
			umArquivo.write((char*)(&pay), sizeof(campo_7_benefits));
			break;
			
		case 7:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay) + sizeof(campo_5_overtime_pay) + sizeof(campo_6_other_pay) + sizeof(campo_7_benefits);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: ";
			cin >> pay;
			
			umArquivo.write((char*)(&pay), sizeof(campo_8_total_pay));
			break;
			
		case 8:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay) + sizeof(campo_5_overtime_pay) + sizeof(campo_6_other_pay) + sizeof(campo_7_benefits)
			+ sizeof(campo_8_total_pay);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: ";
			cin >> pay;
			
			umArquivo.write((char*)(&pay), sizeof(campo_9_total_pay_benefits));
			break;
			
		case 9:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay) + sizeof(campo_5_overtime_pay) + sizeof(campo_6_other_pay) + sizeof(campo_7_benefits)
			+ sizeof(campo_8_total_pay) + sizeof(campo_9_total_pay_benefits);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo ano: ";
			cin >> id_or_year;
			
			umArquivo.write((char*)(&id_or_year), sizeof(campo_10_year));
			break;
			
		default:
			break;
	}
}

int main(){
	
	// O arquivo binário é aberto tanto para entrada quanto saída de dados
	fstream arq_binario("dados_convertidos.bin", ios::binary | ios::in | ios::out);
	
	// erro será o retorno do programa, que é tratado no programa principal
	// Se erro = 1, representa que ocorreu erro (o usuário digitou algo incorreto)
	int erro = 0;
	
	if(arq_binario){
		
		// É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		arq_binario.seekg(0, arq_binario.end);
		int tamanho_arquivo_binario = arq_binario.tellg();
		
		// É criado uma variável do tipo classe Binario para acessar a função de trocar
		Binario dados_binario;
		
		// Variáveis para a execução das operações
		int pos;
		long aux;
		
		cout << "Escreva a posição que se deseja alterar algum dado: " << endl;
		cin >> pos;
		
		// Tamanho da pos em relação ao início do arquivo binário,
		// ou seja, representa o byte que a posição de pos começa
		aux = pos * sizeof(Binario);
		
		if((pos < 0) or (aux > tamanho_arquivo_binario) or (cin.fail()))
			erro = 1;
			
		else{
			
			int opcao;
			
			cout << "Digite o número que representa o campo que se deseja alterar: " << '\n'
			<< "0. Id" << '\n'
			<< "1. Nome" << '\n'
			<< "2. Trabalho" << '\n'
			<< "3. Pagamento base" << '\n'
			<< "4. Pagamento extra" << '\n'
			<< "5. Outros pagamentos" << '\n'
			<< "6. Pagamento de benefícios" << '\n'
			<< "7. Pagamento total" << '\n'
			<< "8. Pagamento total dos benefícios" << '\n'
			<< "9. Ano" << endl;
			cin >> opcao;
			
			if((cin.fail()) or (!((opcao >= 0) and (opcao <= 9))))
				erro = 2;
			
			if(erro == 0)
				dados_binario.alterar_campo(arq_binario, pos, opcao);
		}
		
		arq_binario.close();
	}
	
	else{
		
		cout << "Não há arquivo convertido" << endl;
	}
	
	return erro;
}
