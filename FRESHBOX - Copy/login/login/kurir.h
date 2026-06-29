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
    dalam_perjalanan=1, selesai=2
};

struct Pengiriman {
    StatusPengiriman status;
    Pembelian beli;
    User kurir;
};

string statusToString(StatusPengiriman status) {
    switch (status) {
    case dalam_perjalanan: return "Sedang dikirim";
    case selesai: return "Pengiriman selesai";
    default: return "Pending";
    }
}

Pengiriman Jadwal(vector<Pengiriman>& dataStorage, Pembelian beli);

// Fungsi update langsung mengubah objek pengiriman yang dituju (tanpa nyari ID)
void Status(Pengiriman& p, int StatusBaru);

void jadwalPengirim();
void updateStatus();
void statusPengirim();

#endif