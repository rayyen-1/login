#include <iostream>
#include <string>
#include  <iomanip>
#include "produk.h"
#include "menu.h"
#include "mitra.h"


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

    int lebarKotak = 75;
    int colNo    = 4;
    int colNama  = 25;
    int colKat   = 12;
    int colStok  = 8;
    int colHarga = 15;

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << "|| "
         << left  << setw(colNo)    << "No"          << " | "
         << left  << setw(colNama)  << "Nama Produk" << " | "
         << left  << setw(colKat)   << "Kategori"    << " | "
         << right << setw(colStok)  << "Stok"        << " | "
         << right << setw(colHarga) << "Harga"       << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    if (isEmpty()) {
        cout << "|| " << left << setw(lebarKotak - 6) << "Belum ada produk tersedia." << " ||" << endl;
    } else {
        for (int i = queue.depan; i <= queue.belakang; i++) {
            string hargaStr = "Rp " + to_string(queue.data[i].harga);
            cout << "|| "
                 << left  << setw(colNo)    << i + 1                                << " | "
                 << left  << setw(colNama)  << queue.data[i].namaProduk             << " | "
                 << left  << setw(colKat)   << namaKategori(queue.data[i].kategori) << " | "
                 << right << setw(colStok)  << queue.data[i].stok                   << " | "
                 << right << setw(colHarga) << hargaStr                             << " ||" << endl;
        }
    }

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << endl;
}

void updateProduk() {
    system("cls");
    cout << "=== UPDATE PRODUK ===" << endl << endl;

    if (isEmpty()) {
        cout << "Queue masih kosong!" << endl << endl;
        system("PAUSE");
        return;
    }

    tampilProduk();
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

    char program;
    cout << "Kembali ke halaman menu? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return menuMitra();
    }
    else {
        exit(0);
    }
}

void hapusProduk()
{
    system("cls");
    cout << "============= HAPUS PRODUK =============" << endl << endl;
    if (isEmpty())
    {
        cout << "=== Daftar produk masih kosong! ===" << endl << endl;
        system("pause");
        return;
    }
    for (int i = 1; i <= queue.belakang; i++)
    {
        cout << i  << ". " << queue.data[i].namaProduk << " | Stok: " << queue.data[i].stok << " | Harga: Rp " << queue.data[i].harga << endl;
    }
    cout << endl;
    int nomor;
    cout << "Masukkan nomor produk yang ingin dihapus: ";
    cin >> nomor;
    nomor--;

    if (nomor < queue.depan || nomor > queue.belakang)
    {
        cout << "Nomor tidak valid!" << endl << endl;
        system("pause");
        return;
    }

    for (int i = nomor; i < queue.belakang; i++)
    {
        queue.data[i] = queue.data[i + 1];
    }
    queue.belakang--;

    if (queue.belakang < queue.depan)
    {
        queue.depan = -1;
        queue.belakang = -1;
    }

    cout << endl;
    cout << "=== Produk berhasil dihapus! ===" << endl << endl;
    cout << "Kembali ke halaman menu? (y/n): ";
    char program;
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return menuMitra();
    }
    else {
        exit(0);
    }
}

void inputProduk() { 
    system("cls");
    char program;
        string namaProduk;
        int stock, harga, kategori;
        cout << "===INPUT PRODUK===" << endl;
        cout << "Nama Produk: "; cin >> namaProduk;
        cout << "Harga: "; cin >> harga;
        cout << "Stock: "; cin >> stock;
        cout << "===List Kategori==" << endl;
        cout << "1. Sayur" << endl;
        cout << "2. Buah" << endl;
        cout << "3. Bumbu" << endl;
        cout << "Masukkan pilihan: "; cin >> kategori;

        if (queue.belakang >= MAX_QUEUE - 1) {
            cout << "Gagal menambahkan! Produk sudah penuh!" << endl;
            return;
        }

        Produk produkBaru;
        produkBaru.namaProduk = namaProduk;
        produkBaru.harga = harga;
        produkBaru.stok = stock;

        produkBaru.kategori = static_cast<KategoriProduk>(kategori);

        queue.belakang++; // Naikkan indeks belakang
        queue.data[queue.belakang] = produkBaru; // Masukkan data ke array dalam queue

        cout << "Produk berhasil ditambahkan!" << endl;


        cout << "Kembali ke halaman menu? (y/n): ";
        cin >> program;
        if (program == 'y' || program == 'Y') {
            return menuMitra();
        }
        else {
            exit(0);
        }
}
