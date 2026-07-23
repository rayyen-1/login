#ifndef MITRA_PRODUK_H
#define MITRA_PRODUK_H

#include <string>
using namespace std;

enum KategoriProduk {
    SAYUR = 1,
    BUAH = 2,
    LAINNYA = 4
};

// 1. Struct Produk dasar
struct Produk {
    string idProduk;
    string namaProduk;
    int harga = 0;
    int stok = 0;
    KategoriProduk kategori;
};

const int MAX_PRODUK_PER_MITRA = 10;

// 2. Struct Mitra yang membawahi langsung produknya
struct Mitra {
    string idMitra;
    string namaMitra;
    string alamat;

    // Setiap mitra punya daftar produknya sendiri
    Produk daftarProdukMitra[MAX_PRODUK_PER_MITRA];
    int jumlahProdukMitra = 0;
};

const int MAX_MITRA = 10;
extern Mitra daftarMitra[MAX_MITRA];
extern int jumlahMitra;

// Dipakai oleh mitra.cpp (tampilProduk/tampilProdukSaya) untuk menampilkan
// nama kategori produk. Sebelumnya fungsi ini dipanggil tapi tidak pernah
// dideklarasikan/didefinisikan di mana pun, sehingga project gagal di-compile.
inline string namaKategori(KategoriProduk kategori) {
    if (kategori == SAYUR) return "Sayur";
    if (kategori == BUAH) return "Buah";
    if (kategori == LAINNYA) return "Bumbu";
    return "Lainnya";
}

#endif