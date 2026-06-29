#ifndef BELI_H
#define BELI_H

#include <string>
#include "produk.h"
#include "mitra.h"
#include "beli.h"
#include "customer.h"
#include "menu.h"
#include "user.h"
using namespace std;

const int MAX_ITEM_KERANJANG = 10; 

struct ItemKeranjang {
    string namaProduk = "";
    int    hargaSatuan = 0;   
    int    banyakPembelian = 0; 
    int    subTotal = 0;        
};

struct Pembelian {
    string user;
    string alamat;
    ItemKeranjang daftarBarang[MAX_ITEM_KERANJANG];
    int    jumlahBarang = 0;
    int    totalHargaSemua = 0;

    bool   isCheckedOut = false;
    string waktuCheckout = "";
};

const int MAX_PEMBELIAN = 20;
extern Pembelian daftarPembelian[MAX_PEMBELIAN];
extern int jumlahPembelian;

#endif
