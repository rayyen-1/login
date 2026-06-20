#include <iostream>
#include "menu.h"

using namespace std;

void menuMitra();
void menuCustomer();
void menuKurir();

void menuMitra()
{
    int pilih;
    do
    {
        system("cls");
        cout << "=== MENU UTAMA ===" << endl;
        cout << "1. Input Produk" << endl;
        cout << "2. Update Produk" << endl;
        cout << "3. Hapus Produk" << endl;
        cout << "4. Invoice" << endl;
        cout << "5. Update Status Pengiriman" << endl;
        cout << "6. Informasi Pelanggan" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;
        switch(pilih)
        {
        case 1:
            inputProduk();
            break;
        case 2:
            updateProduk();
            break;
        case 3:
            hapusProduk();
            break;
        case 4:
            invoice();
            break;
        case 5:
            statusPengiriman();
            break;
        case 6:
            informasi();
            break;
        default:
            cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            break;
        }
    } while (pilih != 7);
};
void inputProduk();
void updateProduk();
void hapusProduk();
void invoice();
void statusPengiriman();
void informasi();

void menuCustomer()
{
    int pil;
    do
    {
        system("cls");
        cout << "=== MENU UTAMA ===" << endl;
        cout << "1. Pembelian" << endl;
        cout << "2. Keranjang" << endl;
        cout << "3. Lacak Kurir" << endl;
        cout << "4. Invoice" << endl;
        cout << "Pilih menu: ";
        cin >> pil;
        switch (pil)
        {
        case 1:
            pembelian();
            break;
        case 2:
            keranjang();
            break;
        case 3:
            lacakKurir();
            break;
        case 4:
            invo();
            break;
        default:
            cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
            break;
        }
    } while (pil != 5);
};
void pembelian();
void keranjang();
void lacakKurir();
void invo();

void menuKurir()
{
    int plh;
    do
    {
        system("cls");
        cout << "=== MENU UTAMA ===" << endl;
        cout << "1. Jadwal Pengiriman" << endl;
        cout << "2. Update Status" << endl;
        cout << "Pilih menu: ";
        cin >> plh;
        switch (plh)
        {
        case 1:
            jadwalPengirim();
            break;
        case 2:
            updateStatus();
            break;
        default:
            cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
            break;
        }
    } while (plh != 3);
};
void jadwalPengirim();
void updateStatus();
