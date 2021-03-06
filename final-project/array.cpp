#include <bits/stdc++.h>
#define MAX 1000
using namespace std;

struct employee{
    string name;
    string nip;
};
employee Employee[MAX];
int i, loop=0;

int menu();		// menampilkan menu
void readFile();	// membaca file kemudian memasukkan data ke dalam array
void insert();		// memasukkan data baru 
void remove();		// menghapus data
void swap();		// mengganti data
void readArr();		// membaca array kemudian memasukkan data ke dalam file
bool compName(employee str1, employee str2);	// membandingkan nama
bool compNip(employee str1, employee str2);	// membandingkan nip
void removeName(string data);	// menghapus data nama
void removeNip(string data);	// menghapus data nip

void readArr(){
	ofstream myfile;
	myfile.open ("nip.txt");
    
    	for(int i=0; i<loop; i++){
    		myfile << Employee[i].name << "\n" << Employee[i].nip << "\n";
	}
	myfile.close();
	
	// delete blank lines
	ifstream fin("nip.txt");    
	ofstream fout;
	string str;
	
	fout.open("temp.txt", ios::out);
	while(getline(fin, str)){ 
    		while(str.length()==0) getline(fin, str);   
		fout << str << endl;
	}
	
	fout.close();  
	fin.close();  
	remove("nip.txt");        
	rename("temp.txt", "nip.txt");
}

void swap(){
	char opsi;
	string data1, data2;
	cout << "Apakah anda ingin merubah data berdasarkan nama? y/n\n";
	cin >> opsi;
	
	if(opsi == 'y'){
		cout << "Silakan masukkan nama lama beserta nama yang baru:\n";
		cin >> data1 >> data2;
		for(i=0; i<loop; i++){
			if(Employee[i].name == data1){
				Employee[i].name = data2;
				break;
			}
		}
		if(i>=loop){
			cout << "Maaf, data tidak ditemukan.\n";
			menu();
		}
		readArr();
	}
	else if(opsi == 'n'){
		cout << "Silakan masukkan nip lama beserta nip yang baru:\n";
		cin >> data1 >> data2;
		for(i=0; i<loop; i++){
			if(Employee[i].nip == data1){
				Employee[i].nip = data2;
				break;
			}
		}
		if(i>=loop){
			cout << "Maaf, data tidak ditemukan.\n";
			menu();
		}
		readArr();
	}
	else cout << "Maaf, perintah tidak dikenali.\n";
	menu();
}

void removeNip(string data){
	int i;
	for(i=0; i<loop; i++){
		if(Employee[i].nip == data) break;
	}
    
	if(i<loop){
    		loop--;
    		for(int j=i; j<loop; j++){
    			Employee[j].name = Employee[j+1].name;
    			Employee[j].nip = Employee[j+1].nip;
		}
	} else{
		cout << "Maaf, data tidak ditemukan.\n";
		menu();
	}	
	readArr();
}

void removeName(string data){
	string name, nip;
	int i;
	for(i=0; i<loop; i++){
		if(Employee[i].name == data) break;
	}
    
	if(i<loop){
    		loop--;
    		for(int j=i; j<loop; j++){
    			Employee[j].name = Employee[j+1].name;
    			Employee[j].nip = Employee[j+1].nip;
		}
	} else{
		cout << "Maaf, data tidak ditemukan.\n";
		menu();
	}
	readArr();
}

void remove(){
	char opsi;
	string data;
	
	cout << "Apakah anda ingin menghapus data berdasarkan nama? y/n\n";
	cin >> opsi;
	if(opsi == 'y'){
		cout << "Silakan masukkan nama yang datanya ingin anda hapus:\n";
		cin >> data;
		removeName(data);
	}
	else if(opsi == 'n'){
		cout << "Silakan masukkan NIP yang datanya ingin anda hapus:\n";
		cin >> data;
		removeNip(data);
	}
	else cout << "Maaf, perintah tidak dikenali.\n";
	menu();
}

void insert(){
	cout << "Silakan masukkan nama dan NIP pegawai baru:\n";
	cin >> Employee[loop].name >> Employee[loop].nip;
	loop++;
	
	ofstream fout; 
	ifstream fin;
	fin.open ("nip.txt");
	fout.open ("nip.txt", ios::app); 

	if(fin.is_open()){
		fout << Employee[loop-1].name << "\n" << Employee[loop-1].nip << "\n";
	}
	else cout << "Maaf, file tidak dapat dibuka\n";

	fin.close();
	fout.close();
	menu();
}

bool compNip(employee str1, employee str2){
	if(str1.nip.length() == str2.nip.length()){
		return (str1.nip < str2.nip);
	}
	return (str1.nip.length() < str2.nip.length());
}

bool compName(employee str1, employee str2){
    return (str1.name < str2.name);
}

void printData(){
	for(int i=0; i<loop; i++){
    		cout << Employee[i].name << "\t" << Employee[i].nip << endl;
	}
	menu();
}

void readFile(){ 
    	string line;
	ifstream myfile("nip.txt");
	
	if(myfile.is_open()){
        while (!myfile.eof()){
            	getline(myfile, line);
            	Employee[loop].name = line;
            
            	getline(myfile, line);
            	Employee[loop].nip = line;
            	loop++;
        }
        myfile.close();
    }
    else cout << "File tidak dapat dibuka\n";
    
    sort(Employee, Employee+loop, compNip);
}

int menu(){
	int option;
	cout << "====== Layanan Data Pegawai ======\n";
    	cout << "Pilih opsi:\n";
    	cout << "(1) Daftar pegawai dalam urut nama\n";
    	cout << "(2) Daftar pegawai dalam urut NIP\n";
    	cout << "(3) Masukkan data baru\n";
    	cout << "(4) Hapus data\n";
    	cout << "(5) Ubah data\n";
    	cout << "(6) Keluar dari layanan\n";

    	cin >> option;
	cout << "==================================\n";
    	switch (option){
    		case 1:
    			sort(Employee, Employee+loop, compName);
			printData();
    			break;
    		case 2:
    			sort(Employee, Employee+loop, compNip);
			printData();
    			break;
    		case 3:
    			insert();
    			break;
    		case 4:
    			remove();
    			break;
    		case 5:
    			swap();
    			break;
    		case 6:
    			cout << "Terima kasih telah menggunakan layanan ini ^ ^";
    			return 0;
    		default:
        		cout << "Mohon maaf, menu tidak tersedia. Mohon ulangi kembali\n";
        		menu();
    }
}

int main(){
	readFile();
	menu();
	return 0;
}
