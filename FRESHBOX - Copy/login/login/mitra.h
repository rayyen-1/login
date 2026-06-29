#ifndef MITRA_H
#define MITRA_H

#include "produk.h"
#include "mitra.h"
#include "beli.h"
#include "customer.h"
#include "menu.h"
#include "user.h"

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

#endif
