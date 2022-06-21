#include <iostream>
#include <fstream>

using namespace std;

struct aluno{
	
	char nome[20];
	int matricula;
	float notas[4];
	float media;
};

int main(){
	
	//cout << sizeof(aluno) << endl;
	
	ofstream arq("dados.bin");
	aluno alunos[3];
	
	for(int i = 0; i < 3; i++)
	{
		cout << "Matricula: ";
		cin >> alunos[i].matricula;
		
		cout << "Nome: ";
		cin >> alunos[i].nome;
		
		cout << "Notas: ";
		for(int j = 0; j < 4; j++)
			cin >> alunos[i].notas[j];
			
		alunos[i].media = (alunos[i].notas[0] + alunos[i].notas[1] + alunos[i].notas[2] + alunos[i].notas[3]) / 4;
		
		arq.write((char*)(&alunos[i]), sizeof(alunos[i]));
	}
	
	arq.close();
	
	return 0;
}
