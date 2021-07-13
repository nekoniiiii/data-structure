#include <bits/stdc++.h>
#define MAX 1000
using namespace std;

struct employee{
    string name;
    string nip;
};

list<employee> mylist;
list<employee>::iterator it;
employee Employee;
ifstream fin;
ofstream fout;

int menu();		// menampilkan menu
void readFile();	// membaca file kemudian memasukkan data ke dalam list
void printData();	// menampilkan data
void insert();		// memasukkan data baru
void remove();		// menghapus data
void swap();		// mengganti data
void readList();	// membaca list kemudian memasukkan data ke dalam file
bool compName(employee str1, employee str2);	// membandingkan nama
bool compNip(employee str1, employee str2);	// membandingkan nip

void readList(){
	// overwrite data ke dalam file dari list
	ofstream myfile;
	myfile.open("nip.txt");
    
    	it = mylist.begin();
	while(it != mylist.end()){
		myfile << it->name << "\n" << it->nip << "\n";
		it++;
	}
	myfile.close();
	
	// menghapus garis kosong (blank lines)
	fin.open("nip.txt");
	fout.open("temp.txt");                
	string line;

	while(getline(fin, line)){ 
    	while(line.length()==0) getline(fin, line);   
		fout << line << endl;
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
		
	// mengiterasi list
	it = mylist.begin();
	while(it != mylist.end()){
		if(it->name == data1){
			// mengganti nama yang diinginkan setelah ditemukan
			it->name = data2;
			break;
		}
		it++;
		}
		if(it == mylist.end()){
			cout << "Maaf, data tidak ditemukan.\n";
			menu();
		}
		readList();
	}
	else if(opsi == 'n'){
		cout << "Silakan masukkan nip lama beserta nip yang baru:\n";
		cin >> data1 >> data2;
		
		// mengiterasi list
		it = mylist.begin();
		while(it != mylist.end()){
			if(it->nip == data1){
				// mengganti nip yang diinginkan setelah ditemukan
				it->nip = data2;
				break;
			}
			it++;
		}
		if(it == mylist.end()){
			cout << "Maaf, data tidak ditemukan.\n";
			menu();
		}
		readList();
	}
	else cout << "Maaf, perintah tidak dikenali.\n";
	menu();
}

void remove(){
	string name, nip, line;
	cout << "Silakan masukkan nama dan NIP yang datanya ingin anda hapus:\n";
	cin >> name >> nip;
	
	// menghapus data dalam file
	fin.open("nip.txt");
	fout.open("temp.txt");

	while(getline(fin, line)){
    		if(line != name && line != nip) fout << line << endl;
	}
	
	fout.close();
	fin.close();
	remove("nip.txt");
	rename("temp.txt", "nip.txt");
	
	// menghapus semua isi list
	mylist.clear();
	readFile();
	menu();
}

void insert(){
	cout << "Silakan masukkan nama dan NIP pegawai baru:\n";
	cin >> Employee.name >> Employee.nip;
	
	// memasukkan data baru ke dalam list
	mylist.push_back(Employee);
	
	// menambahkan data baru dalam file
	fin.open("nip.txt");
	fout.open("nip.txt", ios::app);

	if(fin.is_open()){
		fout << Employee.name << "\n" << Employee.nip << "\n";
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
	// mengiterasi list kemudian di-output
	it = mylist.begin();
	while(it != mylist.end()){
		cout << it->name << "\t" << it->nip << endl;
		it++;
	}
	menu();
}

void readFile(){
    	string line;
	ifstream myfile("nip.txt");
	
	// memasukkan data dari file ke dalam list
	if(myfile.is_open()){
        while(!myfile.eof()){
            	getline(myfile, line);
            	Employee.name = line;
            
            	getline(myfile, line);
            	Employee.nip = line;

		mylist.push_back(Employee);
        }
        myfile.close();
    }
    else cout << "File tidak dapat dibuka\n";
    
    mylist.sort(compNip);
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
    	switch(option){
    		case 1:
    			mylist.sort(compName);
    			printData();
    			break;
    		case 2:
    			mylist.sort(compNip);
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
