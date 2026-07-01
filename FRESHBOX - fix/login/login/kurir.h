#ifndef KURIR_H
#define KURIR_H

#include <iostream>
#include <string>
#include <vector>
#include "beli.h" 
#include "produk.h" 
#include "user.h"

using namespace std;

enum StatusPengiriman {
    dalam_perjalanan = 1, sedang_proses_packing = 2, selesai = 3
};

struct Pengiriman {
    StatusPengiriman status = sedang_proses_packing;
    Pembelian beli;
    User kurir;
};

extern vector<Pengiriman> listKurir;

string statusToString(StatusPengiriman status);

Pengiriman Jadwal(vector<Pengiriman>& dataStorage, Pembelian beli);

// Fungsi update langsung mengubah objek pengiriman yang dituju (tanpa nyari ID)
void updateStatus(Pengiriman& p, int StatusBaru);

void jadwalPengirim();
void statusPengirim();

#endif