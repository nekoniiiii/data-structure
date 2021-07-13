// Nama: Neisa Hibatillah Alif
// NRP: 5025201170
// Judul soal: Terpendek ke-K
#include<bits/stdc++.h>
using namespace std;

int main(){
    int jumlah, urutan;
    cin >> jumlah >> urutan;
 
    int arr[jumlah];
 
    for(int i=0; i<jumlah; i++) cin >> arr[i];
	int n = sizeof(arr) / sizeof(arr[0]);
	
	sort(arr, arr+n);
    cout << arr[urutan-1];
    
    return 0;
}
