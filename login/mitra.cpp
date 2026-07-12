#include <iostream>
#include <string>
#include "produk.h"

using namespace std;

const int MAX_QUEUE = 20;

struct Queue {
    int depan;
    int belakang;
    Produk data[MAX_QUEUE];
};

Queue queue;

bool isEmpty() {
    return (queue.belakang == -1);
}

bool isFull() {
    return (queue.belakang >= (MAX_QUEUE - 1));
}

void inisialisasi() {
    queue.depan = queue.belakang = -1;
}

void tampilProduk() {
    system("cls");
    cout << "=== DAFTAR PRODUK FRESHBOX ===" << endl << endl;

    if (isEmpty()) {
        cout << "Queue masih kosong!" << endl << endl;
        system("PAUSE");
        return;
    }

    for (int i = queue.depan; i <= queue.belakang; i++) {
        cout << i + 1 << ". " << queue.data[i].namaProduk << endl;
        cout << "   Kategori : " << namaKategori(queue.data[i].kategori) << endl;
        cout << "   Stok     : " << queue.data[i].stok << endl;
        cout << "   Harga    : Rp " << queue.data[i].harga << endl;
        cout << endl;
    }

    char program;
    cout << "Kembali ke halaman menu? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return;
    }
    else {
        exit(0);
    }
}

void updateProduk() {
    system("cls");
    cout << "=== UPDATE PRODUK ===" << endl << endl;

    if (isEmpty()) {
        cout << "Queue masih kosong!" << endl << endl;
        system("PAUSE");
        return;
    }

    for (int i = queue.depan; i <= queue.belakang; i++) {
        cout << i + 1 << ". " << queue.data[i].namaProduk
            << " | Stok: " << queue.data[i].stok
            << " | Harga: Rp " << queue.data[i].harga << endl;
    }
    cout << endl;

    int nomor;
    cout << "Masukkan nomor produk yang ingin diupdate: ";
    cin >> nomor;
    nomor--;

    if (nomor < queue.depan || nomor > queue.belakang) {
        cout << "Nomor tidak valid!" << endl << endl;
        system("PAUSE");
        return;
    }

    cout << endl;
    cout << "Produk : " << queue.data[nomor].namaProduk << endl;
    cout << "Stok sekarang  : " << queue.data[nomor].stok << endl;
    cout << "Harga sekarang : Rp " << queue.data[nomor].harga << endl;
    cout << endl;

    cout << "Stok baru  : "; cin >> queue.data[nomor].stok;
    cout << "Harga baru : "; cin >> queue.data[nomor].harga;

    cout << endl;
    cout << "Produk berhasil diupdate!" << endl << endl;

    cout << endl;
}

//izin tes min