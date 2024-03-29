#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <limits>

using namespace std;

class Binario{
	
	private:
		// Atributos/campos privados
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
		// Funções privadas da classe Binario
		void imprimir(Binario& umaLinha);
		void preencher_campo(fstream& umArquivo, int pos);
		void trocar(fstream& umArquivo, int p1, int p2);
		void alterar_campo(fstream& umArquivo, int pos, int opcao);
	
	public:
		// Funções públicas acessadas pelo main
		Binario();
		int inserir(int erro01);
		void leitura_geral();
		int leitura_por_espaco(int erro03);
		int troca_pos(int erro04);
		int alterar(int erro05);
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
	<< "posição: " << umaLinha.campo_11_posicao << "\n" << endl;
}

// Função para criar um novo bloco/pacote da classe Binario em uma posição específica
void Binario::preencher_campo(fstream& umArquivo, int pos){
	
	string name_or_job;
	name_or_job.clear();
	int tamanho_pos = sizeof(Binario) * pos;
	
	umArquivo.seekg(0, umArquivo.end);
	int tamanho_arquivo_binario_inicial = umArquivo.tellg();
	
	Binario *escrita = new Binario[1];
	Binario *leitura = new Binario[1];
	int pos_atual = tamanho_arquivo_binario_inicial;
	int subtrator = sizeof(Binario);
	
	// Cada bloco/pacote Binario é movido uma posição para frente até a posição desejada
	while(tamanho_pos != pos_atual){
		
		umArquivo.seekg(pos_atual - subtrator, umArquivo.beg);
		umArquivo.read((char*)(&leitura[0]), sizeof(Binario));
		
		escrita[0] = leitura[0];
		escrita[0].campo_11_posicao++;
		
		umArquivo.seekg(pos_atual, umArquivo.beg);
		umArquivo.write((char*)(&escrita[0]), sizeof(Binario));
		
		pos_atual -= subtrator;
	}
	
	cout << endl;
	
	// Preenchimento no novo bloco/pacote Binario
	Binario aux;
	
	// ID
	
	cout << "Digite o id: " << flush;
	cin >> aux.campo_1_id;
	
	while(cin.fail()){
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "Digite o id: " << flush;
		cin >> aux.campo_1_id;
	}
	
	// Nome
	
	cin.ignore();
	cout << "Digite o nome (máx. 41 letras): " << flush;
	getline(cin, name_or_job);
	
	while(name_or_job.size() >= sizeof(campo_2_name)){
		
		cout << "Passou do limite" << '\n';
		cout << "Digite o nome (máx. 41 letras): " << flush;
		getline(cin, name_or_job);
	}
	
	for(unsigned int i = 0; i < name_or_job.size(); i++)
		aux.campo_2_name[i] = name_or_job[i];
		
	name_or_job.clear();
	
	// Trabalho
	
	cout << "Digite o trabalho (máx. 53 letras): " << flush;
	getline(cin, name_or_job);
	
	while(name_or_job.size() >= sizeof(campo_3_job)){
		
		cout << "Passou do limite" << '\n';
		cout << "Digite o trabalho (máx. 53 letras): " << flush;
		getline(cin, name_or_job);
	}
	
	for(unsigned int i = 0; i < name_or_job.size(); i++)
		aux.campo_3_job[i] = name_or_job[i];
		
	// Pagamento base
	
	cout << "Digite o valor do pagamento base: " << flush;
	cin >> aux.campo_4_base_pay;
	
	while(cin.fail()){
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "Digite o valor do pagamento base: " << flush;
		cin >> aux.campo_4_base_pay;
	}
	
	// Pagamento extra
	
	cout << "Digite o valor do pagamento extra: " << flush;
	cin >> aux.campo_5_overtime_pay;
	
	while(cin.fail()){
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "Digite o valor do pagamento extra: " << flush;
		cin >> aux.campo_5_overtime_pay;
	}
	
	// Outros pagamentos
	
	cout << "Digite o valor dos outros pagamento: " << flush;
	cin >> aux.campo_6_other_pay;
	
	while(cin.fail()){
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "Digite o valor dos outros pagamento: " << flush;
		cin >> aux.campo_6_other_pay;
	}
	
	// Pagamento de benefícios
	
	cout << "Digite o valor dos pagamentos de benefícios: " << flush;
	cin >> aux.campo_7_benefits;
	
	while(cin.fail()){
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "Digite o valor dos pagamentos de benefícios: " << flush;
		cin >> aux.campo_7_benefits;
	}
	
	// Pagamento total
	
	cout << "Digite o valor total dos pagamentos: " << flush;
	cin >> aux.campo_8_total_pay;
	
	while(cin.fail()){
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "Digite o valor total dos pagamentos: " << flush;
		cin >> aux.campo_8_total_pay;
	}
	
	// Pagamento total dos benefícios
	
	cout << "Digite o valor total dos pagamentos de benefícios: " << flush;
	cin >> aux.campo_9_total_pay_benefits;
	
	while(cin.fail()){
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "Digite o valor total dos pagamentos de benefícios: " << flush;
		cin >> aux.campo_9_total_pay_benefits;
	}
	
	// ANO
	
	cout << "Digite o ano: " << flush;
	cin >> aux.campo_10_year;
	
	while(cin.fail()){
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "Digite o ano: " << flush;
		cin >> aux.campo_10_year;
	}
	
	aux.campo_11_posicao = pos;
	
	umArquivo.seekg(tamanho_pos, umArquivo.beg);
	umArquivo.write((char*)(&aux), sizeof(Binario));
	
	delete[] leitura;
	delete[] escrita;
	
	cout << "Pressione enter para retornar. . . " << flush;
	cin.get();
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

// Função para alterar algum campo de escolha de uma posição específica
void Binario::alterar_campo(fstream& umArquivo, int pos, int opcao){
	
	system("clear");
	
	// Variáveis para a execução das operações
	string name_or_job;
	name_or_job.clear();
	int id_or_year = 0;
	float pay = 0;
	
	// Em cada caso, a posição se altera pela soma dos posições anteriores (exceto a primeira);
	// Nos casos dos tipos int e float, pega-se o novo valor e se sobrescreve no campo desejado;
	// Nos casos do tipo char, limpa-se o campo e se insere o novo escrito.
	// Fonte para validação dos dados: https://www.hackerearth.com/practice/notes/validating-user-input-in-c/#:~:text=these%20methods%20are%20%3A-,cin.,kept%20in%20an%20error%20state.
	switch(opcao){
		
		case 0:
			umArquivo.seekg(pos * sizeof(Binario), umArquivo.beg);
			
			cout << "Digite o novo id: " << flush;
			cin >> id_or_year;
			
			while(cin.fail()){
				
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				cout << "Digite o novo id: " << flush;
				cin >> id_or_year;
			}
			
			umArquivo.write((char*)(&id_or_year), sizeof(campo_1_id));
			break;
			
		case 1:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id);
			umArquivo.seekg(pos, umArquivo.beg);
			
			char nome[sizeof(campo_2_name)];
			memset(nome, 0, sizeof(nome));
			
			cout << "Digite o novo nome (máx. 41 caracteres): " << flush;
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
			
			cout << "Digite o novo trabalho(máx. 53 caracteres): " << flush;
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
			
			cout << "Digite o novo pagamento: " << flush;
			cin >> pay;
			
			while(cin.fail()){
				
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				cout << "Digite o novo pagamento: " << flush;
				cin >> pay;
			}
			
			umArquivo.write((char*)(&pay), sizeof(campo_4_base_pay));
			
			break;
			
		case 4:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: " << flush;
			cin >> pay;
			
			while(cin.fail()){
				
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				cout << "Digite o novo pagamento: " << flush;
				cin >> pay;
			}
			
			umArquivo.write((char*)(&pay), sizeof(campo_5_overtime_pay));
			break;
			
		case 5:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay) + sizeof(campo_5_overtime_pay);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: " << flush;
			cin >> pay;
			
			while(cin.fail()){
				
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				cout << "Digite o novo pagamento: " << flush;
				cin >> pay;
			}
			
			umArquivo.write((char*)(&pay), sizeof(campo_6_other_pay));
			break;
			
		case 6:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay) + sizeof(campo_5_overtime_pay) + sizeof(campo_6_other_pay);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: " << flush;
			cin >> pay;
			
			while(cin.fail()){
				
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				cout << "Digite o novo pagamento: " << flush;
				cin >> pay;
			}
			
			umArquivo.write((char*)(&pay), sizeof(campo_7_benefits));
			break;
			
		case 7:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay) + sizeof(campo_5_overtime_pay) + sizeof(campo_6_other_pay) + sizeof(campo_7_benefits);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: " << flush;
			cin >> pay;
			
			while(cin.fail()){
				
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				cout << "Digite o novo pagamento: " << flush;
				cin >> pay;
			}
			
			umArquivo.write((char*)(&pay), sizeof(campo_8_total_pay));
			break;
			
		case 8:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay) + sizeof(campo_5_overtime_pay) + sizeof(campo_6_other_pay) + sizeof(campo_7_benefits)
			+ sizeof(campo_8_total_pay);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo pagamento: " << flush;
			cin >> pay;
			
			while(cin.fail()){
				
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				cout << "Digite o novo pagamento: " << flush;
				cin >> pay;
			}
			
			umArquivo.write((char*)(&pay), sizeof(campo_9_total_pay_benefits));
			break;
			
		case 9:
			pos = pos * sizeof(Binario) + sizeof(campo_1_id) + sizeof(campo_2_name) + sizeof(campo_3_job)
			+ sizeof(campo_4_base_pay) + sizeof(campo_5_overtime_pay) + sizeof(campo_6_other_pay) + sizeof(campo_7_benefits)
			+ sizeof(campo_8_total_pay) + sizeof(campo_9_total_pay_benefits);
			umArquivo.seekg(pos, umArquivo.beg);
			
			cout << "Digite o novo ano: " << flush;
			cin >> id_or_year;
			
			while(cin.fail()){
				
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				cout << "Digite o novo ano: " << flush;
				cin >> id_or_year;
			}
			
			umArquivo.write((char*)(&id_or_year), sizeof(campo_10_year));
			break;
			
		default:
			break;
	}
}

// Função para inserir um novo bloco/pacote da classe Binario em uma posição específica, chama a função preencher_campo
int Binario::inserir(int erro01){
	
	system("clear");
	
	fstream arq_binario01("dados_convertidos.bin", ios::binary | ios::in | ios::out);
	
	if(arq_binario01){
		
		// É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		arq_binario01.seekg(0, arq_binario01.end);
		int tamanho_arquivo_binario = arq_binario01.tellg();
		
		cout << "Posições: 0 até " << tamanho_arquivo_binario / sizeof(Binario) << endl;
		
		int pos;
		
		cout << "Escreva a posição que se deseja inserir os dados: " << flush;
		cin >> pos;
		
		if(cin.fail()){
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			erro01 = 1;
		}
		
		else{
			
			// Tamanho da inicial_pos em relação ao início do arquivo binário,
			// ou seja, representa o byte que a posição de inicial_pos começa
			long aux = sizeof(Binario) * pos;
			
			if((pos < 0) or (aux > tamanho_arquivo_binario))
				erro01 = 1;
			
			else
				preencher_campo(arq_binario01, pos);
				
			cin.ignore();
		}
		
		arq_binario01.close();
	}
	
	else{
		cout << "Não há arquivo convertido" << '\n';
		cout << "Pressione enter para retornar. . . " << flush;
		cin.get();
		erro01 = -1;
	}
	
	// erro será o retorno do programa, que é tratado no programa principal
	// Se erro = -1, representa que o arquivo binário não existe
	// Se erro = 1, representa que ocorreu erro (o usuário digitou algo incorreto)
	return erro01;
}

// Função para ler todo o arquivo binário. Pode ser interrompida
void Binario::leitura_geral(){
	
	system("clear");
	
	ifstream arq_binario02("dados_convertidos.bin", ios::binary);
	
	if(arq_binario02){
		
		// É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		arq_binario02.seekg(0, arq_binario02.end);
		int tamanho_arquivo_binario = arq_binario02.tellg();
		
		// É atribuído para quantidade_linhas o total de linhas do arquivo binário
		int quantidade_linhas = tamanho_arquivo_binario / sizeof(Binario);
		
		// Um ponteiro do tipo classe Binario é criado para ler cada linha do arquivo binário
		Binario *leitura = new Binario[1];
		
		arq_binario02.seekg(0, arq_binario02.beg);
		
		// Variáveis para a execução das operações
		char opcao;
		bool controle = true;
		int aux_quant = quantidade_linhas;
		
		do{
			// É mostrado ao usuário 100 linhas por vez
			int cont = 100;
			
			// Ou menos que 100 linhas, caso a quantidade de linhas restantes seja < cont
			if(aux_quant >= 1 and aux_quant < cont)
				cont = aux_quant;
				
			// É lido uma linha de informações (um pacote da classe Binario) de cada vez
			// Tal pacote é "inserido" no ponteiro leitura para vizualização
			for(int i = 0; i < cont; i++, aux_quant--){
				
				arq_binario02.read((char*)(&leitura[0]), sizeof(Binario));
				
				imprimir(leitura[0]);
			}
			
			cout << "Linhas restantes: " << aux_quant << '\n';
			cout << "Se desejar ver os resultados do ponto anterior até esse ponto, rode para cima" << endl;
			
			if(aux_quant == 0)
			{
				cout << "Fim da aplicação, pressione enter para retornar. . . " << flush;
				cin.get();
				
				controle = false;
			}
			
			else{
				
				cout << "Se deseja sair da aplicação, pressione q e enter, se não aperte enter para continuar. . . " << flush;
				
				// Lógica para parar o programa somente quando o 'q' e enter são pressionados
				int cont = 0;
				while(opcao != '\n'){
					
					opcao = getchar();
					
					if(cont == 0)
						if(opcao == 'q')
							controle = false;
					
					cont++;
					
					if(cont > 2)
						controle = true;
				}
				
				// É atribuído nulo à opcao para o programa não continuar rodando sozinho
				opcao = 0;
			}
			
			// No linux apenas um clear não basta, tal razão de ter dois comandos iguais
			system("clear");
			system("clear");
		}while(controle);
		
		arq_binario02.close();
		delete[] leitura;
	}
	
	else{
		cout << "Não há arquivo convertido." << '\n';
		cout << "Pressione enter para retornar. . . " << flush;
		cin.get();
		
		system("clear");
	}
}

// Função para ler de uma posição até outra, escolhidas pelo usuário
int Binario::leitura_por_espaco(int erro03){
	
	system("clear");
	
	ifstream arq_binario03("dados_convertidos.bin", ios::binary);
	
	if(arq_binario03){
		
		// É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		arq_binario03.seekg(0, arq_binario03.end);
		int tamanho_arquivo_binario = arq_binario03.tellg();
		
		cout << "Posições: 0 até " << tamanho_arquivo_binario / sizeof(Binario) - 1 << endl;
		
		// Um ponteiro do tipo classe Binario é criado para ler as linhas desejadas do arquivo binário
		Binario *leitura = new Binario[1];
		
		arq_binario03.seekg(0, arq_binario03.beg);
		
		// Variáveis para a execução das operações
		int inicial_pos = -1;
		int final_pos = -1;
		long aux;
		bool segunda_posicao = false, entrou_leitura = false;
		
		cout << "Escreva a posição inicial: " << flush;
		cin >> inicial_pos;
		
		if(cin.fail()){
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			erro03 = 1;
		}
		
		else{
			
			// Tamanho da inicial_pos em relação ao início do arquivo binário,
			// ou seja, representa o byte que a posição de inicial_pos começa
			aux = sizeof(Binario) * inicial_pos;
			
			if((inicial_pos < 0) or (aux >= tamanho_arquivo_binario) or (cin.fail()))
				erro03 = 1;
				
			else{
				
				cout << "Escreva a posição final: " << flush;
				cin >> final_pos;
				
				if(cin.fail()){
					
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					
					erro03 = 1;
					
					segunda_posicao = true;
				}
				
				else{
					
					// Tamanho da final_pos em relação ao início do arquivo binário,
					// ou seja, representa o byte que a posição de final_pos começa
					aux = sizeof(Binario) * final_pos;
					
					if((final_pos < inicial_pos) or (final_pos < 0) or (aux >= tamanho_arquivo_binario) or (cin.fail()))
						erro03 = 1;
						
					else{
						
						entrou_leitura = true;
						
						// Intervalo de leitura
						int intervalo = final_pos - inicial_pos + 1;
						
						arq_binario03.seekg(inicial_pos * sizeof(Binario), arq_binario03.beg);
						
						cout << '\n' << "Resultado: " << '\n' << endl;
						
						bool primeiro = false;
						
						do{
							// É mostrado ao usuário 100 linhas por vez
							int cont = 100;
							
							// Ou menos que 100 linhas, caso o intervalo restante seja < cont
							if(intervalo >= 1 and intervalo < cont)
								cont = intervalo;
								
							// É lido uma linha de informações (um pacote da classe Binario) de cada vez
							// Tal pacote é "inserido" no ponteiro leitura para vizualização
							for(int i = 0; i < cont; i++, intervalo--){
								
								arq_binario03.read((char*)(&leitura[0]), sizeof(Binario));
								
								imprimir(leitura[0]);
							}
							
							cout << "Linhas restantes: " << intervalo << '\n';
							cout << "Se desejar ver os resultados do ponto anterior até esse ponto, rode para cima" << endl;
							
							if(intervalo != 0)
								cout << "Pressione enter para continuar. . . " << flush;
								
							else
								cout << "Pressione enter para sair. . . " << flush;
							
							// Ignora o primeiro enter
							if(!primeiro){
								
								cin.ignore();
								
								primeiro = true;
							}
							
							// O programa apenas irá continuar/parar após o usuário pressionar enter.
							// Tal laço é feito para impedir que a cada caractere que o usuário digite, 
							// o programa rode uma vez + quantidade de caracteres inseridos
							bool controle = true;
							while(controle){
								
								if(cin.get() == '\n')
									controle = false;
							}
							
							// No linux apenas um clear não basta, tal razão de ter dois comandos iguais
							system("clear");
							system("clear");
						}while(intervalo != 0);
					}
					
					if(!entrou_leitura)
						cin.ignore();
						
					segunda_posicao = true;
				}
			}
			
			if(!segunda_posicao)
				cin.ignore();
		}
		
		arq_binario03.close();
		delete[] leitura;
	}
	
	else{
		cout << "Não há arquivo convertido" << '\n';
		cout << "Pressione enter para retornar. . . " << flush;
		cin.get();
		erro03 = -1;
	}
	
	// erro será o retorno do programa, que é tratado no programa principal
	// Se erro = -1, representa que o arquivo binário não existe
	// Se erro = 1, representa que ocorreu erro (o usuário digitou algo incorreto)
	return erro03;
}

// Função para trocas dois pacotes/blocos da classe Binario, chama a função trocar
int Binario::troca_pos(int erro04){
	
	system("clear");
	
	// O arquivo binário é aberto tanto para entrada quanto saída de dados
	fstream arq_binario04("dados_convertidos.bin", ios::binary | ios::in | ios::out);
	
	if(arq_binario04){
		
		// É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		arq_binario04.seekg(0, arq_binario04.end);
		int tamanho_arquivo_binario = arq_binario04.tellg();
		
		cout << "Posições: 0 até " << tamanho_arquivo_binario / sizeof(Binario) - 1 << endl;
		
		// Variáveis para a execução das operações
		int pos_primeira = -1;
		int pos_segunda = -1;
		long aux;
		bool segunda_posicao = false;
		
		cout << "Escreva a primeira posição da troca: " << flush;
		cin >> pos_primeira;
		
		if(cin.fail()){
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			erro04 = 1;
		}
		
		else{
			
			// Tamanho da pos_primeira em relação ao início do arquivo binário,
			// ou seja, representa o byte que a posição de pos_primeira começa
			aux = pos_primeira * sizeof(Binario);
			
			if((pos_primeira < 0) or (aux >= tamanho_arquivo_binario) or (cin.fail()))
				erro04 = 1;
				
			else{
				
				cout << "Escreva a segunda posição da troca: " << flush;
				cin >> pos_segunda;
				
				if(cin.fail()){
					
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					
					erro04 = 1;
					
					segunda_posicao = true;
				}
				
				else{
					
					// Tamanho da pos_segunda em relação ao início do arquivo binário,
					// ou seja, representa o byte que a posição de pos_segunda começa
					aux = sizeof(Binario) * pos_segunda;
					
					if((pos_segunda < 0) or (aux >= tamanho_arquivo_binario) or (cin.fail()))
						erro04 = 1;
						
					else{
						
						if(pos_primeira == pos_segunda)
							erro04 = 2;
							
						else
							trocar(arq_binario04, pos_primeira, pos_segunda);
					}
					
					cin.ignore();
					segunda_posicao = true;
				}
			}
			
			if(!segunda_posicao)
			cin.ignore();
		}
		
		arq_binario04.close();
	}
	
	else{
		
		cout << "Não há arquivo convertido" << '\n';
		cout << "Pressione enter para retornar. . ." << flush;
		cin.get();
		erro04 = -1;
	}
	
	// erro será o retorno do programa, que é tratado no programa principal
	// Se erro = -1, representa que o arquivo binário não existe
	// Se erro = 1, representa que ocorreu erro (o usuário digitou algo incorreto)
	// Se erro = 2, os valores das posições são iguais
	return erro04;
}

// Função para alterar algum campo específico escolhido pelo usuário, chama a função alterar_campo
int Binario::alterar(int erro05){
	
	system("clear");
	
	// O arquivo binário é aberto tanto para entrada quanto saída de dados
	fstream arq_binario05("dados_convertidos.bin", ios::binary | ios::in | ios::out);
	
	if(arq_binario05){
		
		// É atribuído para tamanho_arquivo_binario quantos bytes há no arquivo binário
		arq_binario05.seekg(0, arq_binario05.end);
		int tamanho_arquivo_binario = arq_binario05.tellg();
		
		cout << "Posições: 0 até " << tamanho_arquivo_binario / sizeof(Binario) - 1 << endl;
		
		// Variáveis para a execução das operações
		int pos;
		long aux;
		bool pos_correta = false;
		
		cout << "Escreva a posição que se deseja alterar algum dado: " << flush;
		cin >> pos;
		
		if(cin.fail()){
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			erro05 = 1;
		}
		
		else{
			
			// Tamanho da pos em relação ao início do arquivo binário,
			// ou seja, representa o byte que a posição de pos começa
			aux = pos * sizeof(Binario);
			
			if((pos < 0) or (aux >= tamanho_arquivo_binario) or (cin.fail()))
				erro05 = 1;
				
			else{
				
				cin.ignore();
				pos_correta = true;
				
				string opcao;
				
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
				getline(cin, opcao);
				
				if((cin.fail()) or (opcao.size() > 1) or (!((opcao[0] >= 48) and (opcao[0] <= 57))))
					erro05 = 2;
				
				if(erro05 == 0)
					alterar_campo(arq_binario05, pos, int(opcao[0] - 48));
			}
			
			if(!pos_correta)
				cin.ignore();
		}
		
		arq_binario05.close();
	}
	
	else{
		cout << "Não há arquivo convertido" << '\n';
		cout << "Pressione enter para continuar. . . " << flush;
		cin.get();
		
		erro05 = -1;
	}
	
	// erro será o retorno do programa, que é tratado no programa principal
	// Se erro = -1, representa que o arquivo binário não existe
	// Se erro = 1, representa que ocorreu erro (o usuário digitou algo incorreto)
	return erro05;
}
