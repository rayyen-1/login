#include <iostream>
using namespace std;

#include "mitra.h"
#include "produk.h"
#include "menu.h"
#include "customer.h"
#include "beli.h"


void cari() { cout << "Coming soon" << endl; system("PAUSE"); }
void filter() { cout << "Coming soon" << endl; system("PAUSE"); }

void beli() {
    system("cls");
    string namaProduk;
    int banyak;
    cout << "========= Beli Produk ==========" << endl;
    cout << "Nama Produk: "; cin >> namaProduk;
    bool isKetemu = false;
    int i;
    Queue queue;
    for (i = 0; i < queue.belakang; i++) {
        if (namaProduk == queue.data[i].namaProduk) {
            isKetemu = true;
            break;
        }
    }
    

    cout << "Sisa Produk " << queue.data[i].stok << endl;
    cout << "Harga Produk Rp." << queue.data[i].harga << endl;
    cout << "Banyak Pembelian : "; cin >> banyak;
    cout << "Total Harga " << queue.data[i].harga * banyak << endl;

}



void pembelian() {
	tampilProduk();
	cout << "============================" << endl;
	cout << "1. Cari" << endl;
	cout << "2. Filter" << endl;
	cout << "3. Beli" << endl;
    cout << "4. Keluar" << endl;
    int pil;
    cin >> pil;
    switch (pil)
    {
    case 1:
        cari();
        break;
    case 2:
        filter();
        break;
    case 3:
        beli();
        break;
    case 4:
        return menuCustomer();
    default:
        cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
        break;
    }
}

