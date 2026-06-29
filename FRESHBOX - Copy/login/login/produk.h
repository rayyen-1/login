#ifndef PRODUK_H
#define PRODUK_H

#include <string>

using namespace std;

enum KategoriProduk {
    SAYUR = 1,
    BUAH = 2,
    LAINNYA = 4
};

struct Produk {
    string namaProduk = "";
    int    harga = 0;
    int    stok = 0;
    KategoriProduk kategori;
};

const int MAX_PRODUK = 20;
extern Produk daftarProduk[MAX_PRODUK];
extern int jumlahProduk;


inline string namaKategori(KategoriProduk k) {
    switch (k) {
    case SAYUR:   return "Sayur";
    case BUAH:    return "Buah";
    default:      return "Lainnya";
    }
}

#endif
