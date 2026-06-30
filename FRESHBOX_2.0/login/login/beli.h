#ifndef BELI_H
#define BELI_H

#include <string>
#include "produk.h"
using namespace std;


struct Pembelian {
    string namaProduk = "";
    int    totalHarga = 0;
    int    banyakPembelian = 0;
    string user;
    string alamat;
};

const int MAX_PEMBELIAN = 20;
extern Pembelian daftarPembelian[MAX_PEMBELIAN];
extern int jumlahPembelian;

#endif
