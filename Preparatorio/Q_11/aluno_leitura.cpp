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
	
	ifstream arq("dados.bin");
	
	if(arq)
	{
		aluno alunos[3];
		
		arq.read((char*)(&alunos), 3*sizeof(aluno));
		// ou arq.read((char*)(&alunos), sizeof(alunos));
		
		for(int i = 0; i < 3; i++)
			cout << alunos[i].nome << " " << alunos[i].media << endl;
		
		arq.close();
	}
	
	return 0;
}
