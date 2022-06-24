#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct CSV{
	
	int campo_1_id;
	char campo_2_name[50];
	char campo_3_job[50];
	float campo_4_base_pay;
	float campo_5_overtime_pay;
	float campo_6_other_pay;
	float campo_7_benefits;
	float campo_8_total_pay;
	float campo_9_total_pay_benefits;
	int campo_10_year;
	
	CSV();
};

CSV::CSV(){
	
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
};

int main(){
	
	ifstream arq("dados_convertidos.bin", ios::binary);
	
	if(arq){
		
		CSV leitura[10];
		
		arq.seekg(0, arq.beg);
		
		//arq.read((char*)(&leitura), n*sizeof(CSV));
		arq.read((char*)(&leitura), sizeof(leitura));
		
		for(int i = 0; i < 10; i++){
			
			cout << leitura[i].campo_1_id << endl 
			<< leitura[i].campo_2_name << endl 
			<< leitura[i].campo_3_job << endl 
			<< leitura[i].campo_4_base_pay << endl 
			<< leitura[i].campo_5_overtime_pay << endl 
			<< leitura[i].campo_6_other_pay << endl
			<< leitura[i].campo_7_benefits << endl
			<< leitura[i].campo_8_total_pay << endl
			<< leitura[i].campo_9_total_pay_benefits << endl
			<< leitura[i].campo_10_year << endl << endl;
		}
		
		cout << sizeof(CSV) << " bytes" << endl;
		
		arq.clear();
		arq.seekg(0, arq.end);
		int tam = arq.tellg();
		
		cout << tam << " bytes" << endl << endl;
		
		arq.close();
	}
	
	return 0;
}
