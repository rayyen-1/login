#ifndef MITRA_H
#define MITRA_H

#include "produk.h"

const int MAX_QUEUE = 20;

struct Queue {
    int depan;
    int belakang;
    Produk data[MAX_QUEUE];
};
extern Queue queue;

void hapusProduk();
void inputProduk();
void tampilProduk();
void updateProduk();
void inisialisasi();
bool isEmpty();
bool isFull();

#endif // MITRA_H
