#include <iostream>
#include "menu.h"

using namespace std;

void inputProduk();
void updateProduk();
void hapusProduk();
void invoice();
void statusPengiriman();
void informasi();
void pembelian();
void tampilProduk();
void lacakKurir();
void invo();
void jadwalPengirim();
void updateStatus();

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

            char program;
            cout << "Kembali ke halaman menu? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y') {
                return;
            }
            else {
                exit(0);
            }
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
void inputProduk() { cout << "Coming soon" << endl; system("PAUSE"); }
/*void updateProduk() { cout << "Coming soon" << endl; system("PAUSE"); }*/
void hapusProduk() { cout << "Coming soon" << endl; system("PAUSE"); } 
void invoice() { cout << "Coming soon" << endl; system("PAUSE"); }
void statusPengiriman() { cout << "Coming soon" << endl; system("PAUSE"); }
void informasi() { cout << "Coming soon" << endl; system("PAUSE"); }

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
            tampilProduk();

            char program;
            cout << "Kembali ke halaman menu? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y') {
                return;
            }
            else {
                exit(0);
            }
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
void pembelian() { cout << "Coming soon" << endl; system("PAUSE"); }
/*void keranjang() { cout << "Coming soon" << endl; system("PAUSE"); }*/
void lacakKurir() { cout << "Coming soon" << endl; system("PAUSE"); }
void invo() { cout << "Coming soon" << endl; system("PAUSE"); }

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
void jadwalPengirim() { cout << "Coming soon" << endl; system("PAUSE"); }
void updateStatus() { cout << "Coming soon" << endl; system("PAUSE"); }
