#ifndef MITRA_H
#define MITRA_H

#include <vector>
#include <string>
#include "menu.h"
#include "produk.h"
#include "user.h"
#include "beli.h" // Wajib di sini agar struct Pembelian terbaca

using namespace std;

const int MAX_QUEUE = 20;

enum Status {
    diproses = 1, diserahkan_ke_kurir = 2
};

struct Queue {
    int depan;
    int belakang;
    Produk data[MAX_QUEUE];
    Status statusMitra = diproses;
    User mitra;
    Pembelian beli;
};

extern Queue queue;

// listMitra      = katalog produk milik masing-masing mitra (dipakai customer utk belanja)
// listOrderMitra = daftar pesanan yang sudah masuk ke mitra (dipakai utk status pesanan)
extern vector<Queue> listMitra;
extern vector<Queue> listOrderMitra;
extern User daftarUser[MAX_USER];
extern int jumlahUser;
void login(User daftarUser[], int jumlahUser); // prototype login
string statusToString(Status statusMitra);

Queue listOrder(vector<Queue>& data, Pembelian beli);

void update(Queue& i, int newStatus);

void statusPengiriman();

void hapusProduk();
void invoice();
void inputProduk();
void tampilProduk();
void tampilProdukSaya();
void sortProdukAZ(Produk data[], int mulai, int akhir);
void informasi();
void updateProduk();
void inisialisasi();
bool isEmpty();
bool isFull();


#endif