#ifndef BELI_H
#define BELI_H

#include <string>
#include "produk.h"
#include "user.h"

using namespace std;

const int MAX_ITEM_KERANJANG = 10;

// ── Struct lama (dipakai checkout, invoice, kurir, mitra) ──
struct ItemKeranjang {
    string namaProduk = "";
    int    hargaSatuan = 0;
    int    banyakPembelian = 0;
    int    subTotal = 0;
};

// ── Node Double Linked List untuk keranjang belanja ──
struct NodeKeranjang {
    ItemKeranjang item;
    NodeKeranjang* prev = nullptr;
    NodeKeranjang* next = nullptr;
};

// ── Double Linked List keranjang per-user ──
struct KeranjangDLL {
    User         pemilik;
    NodeKeranjang* head = nullptr;
    NodeKeranjang* tail = nullptr;
    int            jumlahItem = 0;
    int            totalHarga = 0;
    bool           isCheckedOut = false;
    string         waktuCheckout = "";
};

// ── Struct lama Pembelian (tetap dipakai kurir/mitra/invoice) ──
struct Pembelian {
    User          daftarUser[MAX_USER];
    ItemKeranjang daftarBarang[MAX_ITEM_KERANJANG];
    int           jumlahBarang = 0;
    int           totalHargaSemua = 0;
    bool          isCheckedOut = false;
    string        waktuCheckout = "";
};

const int MAX_PEMBELIAN = 20;
extern Pembelian  daftarPembelian[MAX_PEMBELIAN];
extern int        jumlahPembelian;

// Keranjang DLL — satu slot per user (maks sama dengan MAX_PEMBELIAN)
extern KeranjangDLL daftarKeranjang[MAX_PEMBELIAN];
extern int          jumlahKeranjang;

#endif