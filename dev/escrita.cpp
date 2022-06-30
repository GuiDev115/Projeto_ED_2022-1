#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

// Classe que representa cada linha do arquivo CSV, tamanho : 140 bytes
class arquivo_CSV{
	
	private:
		int campo_1_id;
		// Feito um teste prévio, sabe-se que a maior string que o arquivo CSV possui é de 52 caracteres
		// Logo cada campo tem 52 + 1 (caractere fim da string: \0) = 53, mas arredonda-se para 54
		char campo_2_name[54];
		char campo_3_job[54];
		float campo_4_base_pay;
		float campo_5_overtime_pay;
		float campo_6_other_pay;
		float campo_7_benefits;
		float campo_8_total_pay;
		float campo_9_total_pay_benefits;
		int campo_10_year;
		
	public:
		arquivo_CSV();
		void escrita_id(ifstream& arq, arquivo_CSV& umaLinha);
		void escrita_char(ifstream& umArquivo, arquivo_CSV& umaLinha, int seletor);
		void escrita_pagamentos(ifstream& umArquivo, arquivo_CSV& umaLinha, int seletor);
		void escrita_ano(ifstream& umArquivo, arquivo_CSV& umaLinha);
};

// Construtor
arquivo_CSV::arquivo_CSV(){
	
	// A função memset foi vista pelo link: https://stackoverflow.com/questions/1559487/how-to-empty-a-char-array
	// Nesse caso, basicamente o memset coloca um ponteiro na primeira posição do vetor de caracteres e vai percorrendo-o até seu término
	// e imprime o valor, em cada caractere, que representa um número da tabela ascii (0 é o nulo)
	
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
}

// Função para ler e escrever o id (campo 1) em binário
void arquivo_CSV::escrita_id(ifstream& umArquivo, arquivo_CSV& umaLinha){
	
	char virgula;
	int id;
	
	umArquivo >> id;
	umArquivo >> virgula;
	
	umaLinha.campo_1_id = id;
}

// Função para ler e escrever o nome e trabalho (campos 2 e 3) em binário
void arquivo_CSV::escrita_char(ifstream& umArquivo, arquivo_CSV& umaLinha, int seletor){
	
	// Pega a posição atual (em bytes) no arquivo CSV
	umArquivo.seekg(0, umArquivo.cur);
	int posicao_inicial = umArquivo.tellg();
	
	char c[1];
	string texto;
	getline(umArquivo, texto);
	
	// No arquivo CSV uma frase dentro de " " pode conter uma vírgula, logo a lógica a partir daqui cuida dessa operação
	// Procura o primeiro caractere " dentro da string texto e retorna sua posição, se não for encontrado, retorna a última posição da string texto
	size_t found_primeira_aspas = texto.find("\"");
	
	// A primeira " não foi encontrada
	if(found_primeira_aspas == string::npos){
		
		// Retorna à posição inicial
		umArquivo.seekg(posicao_inicial, umArquivo.beg);
		
		getline(umArquivo, texto, ',');
		
		switch(seletor){
			
			case 1:
				for(unsigned int i = 0; i < texto.length(); i++)
					umaLinha.campo_2_name[i] = texto[i];
				break;
				
			case 2:
				for(unsigned int i = 0; i < texto.length(); i++)
					umaLinha.campo_3_job[i] = texto[i];
				break;
		}
	}
	
	// A primeira " foi encontrada
	else{
		
		// Procura a posição da vírgula
		size_t found_virgula = texto.find(",");
		
		// Procura a segunda " dentro da string texto
		size_t found_segunda_aspas = texto.find("\"", found_primeira_aspas + 1);
		
		// Se está condição for true, representa que há uma virgula antes da primeira ", ou seja, tal " pertence à outro campo (campo_3_job)
		// Quando o campo_3_job estiver sendo analisado, ele não entra nessa condicional
		if(found_virgula < found_primeira_aspas){
			
			umArquivo.seekg(posicao_inicial, umArquivo.beg);
			
			getline(umArquivo, texto, ',');
			
			for(unsigned int i = 0; i < texto.length(); i++)
				umaLinha.campo_2_name[i] = texto[i];
		}
		
		// A segunda " foi encontrada
		else if(found_segunda_aspas != string::npos){
			
			umArquivo.seekg(posicao_inicial, umArquivo.beg);
			unsigned int j = 0;
			
			// A variável j tem o papel de preencher o campo analisado, caractere a caractere, até a vírgula (último caractere " + 1)
			while(j < found_segunda_aspas + 1){
				
				umArquivo.read(c, 1);
				
				switch(seletor){
					
					case 1:
						umaLinha.campo_2_name[j] = c[0];
						break;
						
					case 2:
						umaLinha.campo_3_job[j] = c[0];
						break;
				}
				
				j++;
			}
			
			// Remove a vírgula
			umArquivo.read(c, 1);
		}
	}
}

// Função para ler e escrever os pagamentos (campos 4 a 9) em binário
void arquivo_CSV::escrita_pagamentos(ifstream& umArquivo, arquivo_CSV& umaLinha, int seletor){
	
	char c[1], virgula;
	string texto;
	float pagamento;
	
	umArquivo.seekg(0, umArquivo.cur);
	int posicao_inicial = umArquivo.tellg();
	
	umArquivo.read(c, 1);
	
	// No arquivo CSV, certos campos que deveriam ser para float na verdade possuem a informação: "Not Provided"
	// Para não romper com a lógica dos pagamentos serem float, caso o primeiro caractere lido não seja um algarismo
	// o devido pagamento terá valor igual a 0.
	if(not(c[0] >= 48 and c[0] <= 57)){
		
		getline(umArquivo, texto, ',');
		
		pagamento = 0;
		
		switch(seletor){
			
			case 1:
				umaLinha.campo_4_base_pay = pagamento;
				break;
				
			case 2:
				umaLinha.campo_5_overtime_pay = pagamento;
				break;
				
			case 3:
				umaLinha.campo_6_other_pay = pagamento;
				break;
				
			case 4:
				umaLinha.campo_7_benefits = pagamento;
				break;
				
			case 5:
				umaLinha.campo_8_total_pay = pagamento;
				break;
				
			case 6:
				umaLinha.campo_9_total_pay_benefits = pagamento;
				break;
		}
	}
	
	else{
		
		umArquivo.seekg(posicao_inicial, umArquivo.beg);
		
		umArquivo >> pagamento;
		
		umArquivo >> virgula;
		
		switch(seletor){
			
			case 1:
				umaLinha.campo_4_base_pay = pagamento;
				break;
				
			case 2:
				umaLinha.campo_5_overtime_pay = pagamento;
				break;
				
			case 3:
				umaLinha.campo_6_other_pay = pagamento;
				break;
				
			case 4:
				umaLinha.campo_7_benefits = pagamento;
				break;
				
			case 5:
				umaLinha.campo_8_total_pay = pagamento;
				break;
				
			case 6:
				umaLinha.campo_9_total_pay_benefits = pagamento;
				break;
		}
	}
}

// Função para ler escrever o ano (campo 10) em binário
void arquivo_CSV::escrita_ano(ifstream& umArquivo, arquivo_CSV& umaLinha){
	
	int ano;
	
	umArquivo >> ano;
	
	umaLinha.campo_10_year = ano;
}

// Função para simular uma barra de progresso da conversão em CSV para binário. 
// Fonte: https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
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
	if(porcento == 98){
		
		cout << "] " << 100 << " %\r";
		cout.flush();
	}
	
	else{
		
		cout << "] " << porcento << " %\r";
		cout.flush();
	}
	
	progresso += 0.01;
}

int main(){
	
	ifstream arq("san_francisco_payroll_dataset.csv");
	
	if(arq){
		
		arquivo_CSV dados_csv;
		string palavras_comeco;
		
		// Dá a certeza que o arquivo CSV será lido na linha 1
		arq.seekg(0, arq.beg);
		
		// Lê a linha 1 do arquivo CSV que será descartada
		getline(arq, palavras_comeco);
		
		// Cria ou sobrescreve o arquivo: dados_convertidos.bin
		ofstream arq_binario("dados_convertidos.bin", ios::binary);
		
		// Um ponteiro é criado para ler cada linha do arquivo CSV
		// O tamanho do ponteiro foi determinado previamente, olhando o número de total de Ids do arquivo CSV + 1
		arquivo_CSV *linhas = new arquivo_CSV[357407];
		
		// Variáveis para para preencher a barra de progresso
		float progresso = 0;
		int divisor = 3574, porcento = 1;
		
		// Conversão dos dados
		for(int i = 0; i < 357407; i++){
			
			int cont = 1;
			
			dados_csv.escrita_id(arq, linhas[i]);
			
			for(int j = 0; j < 2; j++){
				
				dados_csv.escrita_char(arq, linhas[i], cont);
				
				cont++;
			}
			
			cont = 1;
			
			for(int j = 0; j < 6; j++){
				
				dados_csv.escrita_pagamentos(arq, linhas[i], cont);
				
				cont++;
			}
			
			dados_csv.escrita_ano(arq, linhas[i]);
			
			// Progressão da barra
			if(porcento == (i / divisor)){
				
				progressbar(progresso);
				porcento++;
			}
			
			// Escrita de uma linha do arquivo CSV em binário
			arq_binario.write((char*)(&linhas[i]), sizeof(linhas[i]));
		}
		
		arq.close();
		arq_binario.close();
		delete[] linhas;
	}
	
	else
		cout << "Por favor, insira o arquivo escolhido ao grupo (san_francisco_payroll_dataset.csv) e reabra o programa." << endl;
	
	return 0;
}
