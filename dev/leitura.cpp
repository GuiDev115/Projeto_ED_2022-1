#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct CSV{
	
	int campo_1_id;
	char campo_2_name[50];
	char campo_3_team[50];
	char campo_4_game[50];
	int campo_5_year;
	char campo_6_season[6];
	
	CSV();
};

CSV::CSV(){
	
	campo_1_id = -1;
	memset(campo_2_name, 0, sizeof(campo_2_name));
	memset(campo_3_team, 0, sizeof(campo_3_team));
	memset(campo_4_game, 0, sizeof(campo_4_game));
	campo_5_year = -1;
	memset(campo_6_season, 0, sizeof(campo_6_season));
};

int main(){
	
	ifstream arq("dados_convertidos.bin");
	
	if(arq){
		
		cout << sizeof(CSV) << " bytes" << endl;
		
		arq.seekg(0, arq.end);
		int tam = arq.tellg();
		
		cout << tam << " bytes" << endl << endl;
		
		CSV leitura[1000];
		
		arq.seekg(0, arq.beg);
		
		arq.read((char*)(&leitura), 1000*sizeof(CSV));
		// ou arq.read((char*)(&leitura), sizeof(leitura));
		
		for(int i = 0; i < 1000; i++){
			
			cout << leitura[i].campo_1_id << " " 
			<< leitura[i].campo_2_name << " " 
			<< leitura[i].campo_3_team << " " 
			<< leitura[i].campo_4_game << " " 
			<< leitura[i].campo_5_year << " " 
			<< leitura[i].campo_6_season << endl << endl;
		}
		
		arq.close();
	}
	
	return 0;
}
