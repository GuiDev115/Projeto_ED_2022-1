#include <iostream>
#include <fstream>

using namespace std;

struct CSV{
	
	float campo1, campo4, campo6;
	int campo2;
	char campo3[150], campo5[150];
};

int main(){
	
	ifstream arq("dados_convertidos.bin");
	
	if(arq){
		
		arq.seekg(0, arq.end);
		int tam = arq.tellg();
		
		cout << tam << endl << endl;
		
		CSV aux[10];
		
		arq.seekg(0, arq.beg);
		
		arq.read((char*)(&aux), 10*sizeof(CSV));
		
		for(int i = 0; i < 10; i++)
			cout << aux[i].campo1 << " " << aux[i].campo2 << " " << aux[i].campo3 << " " << aux[i].campo4 << " " << aux[i].campo5 << " " << aux[i].campo6 << endl << endl;
		
		arq.close();
	}
	
	return 0;
}
