#ifndef MITRA_H
#define MITRA_H

#include <vector>
#include "produk.h"
#include "mitra.h"
#include "beli.h"
#include "customer.h"
#include "menu.h"
#include "user.h"

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

extern vector<Queue> listMitra;
string statusToString(Status statusMitra);

Queue listOrder(vector<Queue>& data, Pembelian beli);

void update(Queue& i, int newStatus);

void statusPengiriman();

void hapusProduk();
void invoice();
void inputProduk();
void tampilProduk();
void informasi();
void updateProduk();
void inisialisasi();
bool isEmpty();
bool isFull();

#endif
