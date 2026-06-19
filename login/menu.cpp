#include <iostream>
#include "menu.h"

using namespace std;

void menuMitra();
void menuCustomer();
void menuKurir();

void menuMitra()
{
    cout << "\n\n === MENU UTAMA ===" << endl;
    cout << "1. Input Produk" << endl;
    cout << "2. Update Produk" << endl;
    cout << "3. Hapus Produk" << endl;
    cout << "4. Invoice" << endl;
    cout << "5. Update Status Pengiriman" << endl;
    cout << "6. Informasi Pelanggan" << endl;
    cout << "Pilih menu: "<< endl;
};
void menuCustomer()
{
    cout << "\n\n === MENU UTAMA ===" << endl;
    cout << "1. Pembelian" << endl;
    cout << "2. Keranjang" << endl;
    cout << "3. Lacak Kurir" << endl;
    cout << "4. Invoice" << endl;
    cout << "Pilih menu: " << endl;
};
void menuKurir()
{
    cout << "\n\n === MENU UTAMA ===" << endl;
    cout << "1. Jadwal Pengiriman" << endl;
    cout << "2. Update Status" << endl;
    cout << "Pilih menu: " << endl;
}