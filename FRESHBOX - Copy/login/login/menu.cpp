#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>
using namespace std;

#include "mitra.h"
#include "menu.h"
#include "customer.h"
#include "user.h"
#include "beli.h"
#include "kurir.h"


void invoice() { cout << "Coming soon" << endl; system("PAUSE"); }
void statusPengiriman() { cout << "Coming soon" << endl; system("PAUSE"); }
void informasi() { cout << "Coming soon" << endl; system("PAUSE"); }

void lacakKurir() { cout << "Coming soon" << endl; system("PAUSE"); }
void invo() { cout << "Coming soon" << endl; system("PAUSE"); }

void menuMitra()
{
    int pilih;
    do
    {
        time_t timestamp;
        time(&timestamp);
        struct tm waktuLokal;
        localtime_s(&waktuLokal, &timestamp);

        char bufferTanggal[50];
        strftime(bufferTanggal, sizeof(bufferTanggal), "%A, %d %B %Y", &waktuLokal);
        int lebarKotak = 85;
        system("cls");

        cout << "++" << string(lebarKotak, '-') << "++" << endl;

        int panjangTanggal = strlen(bufferTanggal);
        int sisaLebarHeader = lebarKotak - panjangTanggal - 2;

        cout << "|| " << bufferTanggal << right << setw(sisaLebarHeader) << userAktif->username << " ||" << endl;

        cout << "++" << string(lebarKotak, '-') << "++" << endl;

        string menu[] = {
            "1. Input Produk",
            "2. Tampilkan Produk",
            "3. Update Produk",
            "4. Hapus Produk",
            "5. Invoice",
            "6. Update Status Pengiriman",
            "7. Informasi Pelanggan",
            "8. Keluar"
        };

        for (int i = 0; i < 8; i++) {
            int sisaLebarMenu = lebarKotak - menu[i].length() + 1;
            cout << "|| " << menu[i] << right << setw(sisaLebarMenu) << " ||" << endl;
        }

        cout << "++" << string(lebarKotak, '-') << "++" << endl;

        cout << "|| Pilih menu: " << endl;
        cout << "++" << string(lebarKotak, '-') << "++" << endl;
        cout << "\033[2A\033[15C";

        cin >> pilih;
        cout << "\033[2B"; 

        switch (pilih)
        {
        case 1:
            inputProduk();
            break;
        case 2:
            tampilProduk();
            cout << "===========================================" << endl;
            int pilihan;
            cout << "1. kembali" << endl;
            cout << "2. Masukkan Pilihan: "; cin >> pilihan;

            if (pilihan == 1)
                return menuMitra();
            break;
        case 3:
            updateProduk();
            break;
        case 4:
            hapusProduk();
            break;
        case 5:
            invoice();
            break;
        case 6:
            statusPengiriman();
            break;
        case 7:
            informasi();
            break;
        case 8:
            return;
            break;
        default:
            cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            break;
        }

        char program;
        cout << "Kembali ke halaman menu? (y/n): ";
        cin >> program;
        if (program == 'y' || program == 'Y') {
            return;
        }
        else {
            exit(0);
        }
    } while (pilih != 8);
};


void menuCustomer()
{
    int pil;
    do
    {
        time_t timestamp;
        time(&timestamp);
        struct tm waktuLokal;
        localtime_s(&waktuLokal, &timestamp);

        char bufferTanggal[50];

        strftime(bufferTanggal, sizeof(bufferTanggal), "%A, %d %B %Y", &waktuLokal);
        int lebarKotak = 85;
        system("cls");

        cout << "++" << string(lebarKotak, '-') << "++" << endl;

        int panjangTanggal = strlen(bufferTanggal);
        int sisaLebarHeader = lebarKotak - panjangTanggal - 2;

        cout << "|| " << bufferTanggal << right << setw(sisaLebarHeader) << userAktif->username << " ||" << endl;

        cout << "++" << string(lebarKotak, '-') << "++" << endl;

        string menu[] = {
            "1. Pembelian",
            "2. Keranjang",
            "3. Lacak Kurir",
            "4. Invoice",
            "5. Keluar"
        };

        for (int i = 0; i < 5; i++) {
            int sisaLebarMenu = lebarKotak - menu[i].length() + 1;
            cout << "|| " << menu[i] << right << setw(sisaLebarMenu) << " ||" << endl;
        }

        cout << "++" << string(lebarKotak, '-') << "++" << endl;

        cout << "|| Pilih menu: " << endl;
        cout << "++" << string(lebarKotak, '-') << "++" << endl;
        cout << "\033[2A\033[15C";

        cin >> pil;

        cout << "\033[2B";

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
        case 5:
            return;
            break;
        default:
            cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
            break;
        }
    } while (pil != 5);
};


void menuKurir()
{
    int plh;
    do
    {
        time_t timestamp;
        time(&timestamp);
        struct tm waktuLokal;
        localtime_s(&waktuLokal, &timestamp);

        char bufferTanggal[50];
        strftime(bufferTanggal, sizeof(bufferTanggal), "%A, %d %B %Y", &waktuLokal);
        int lebarKotak = 85;
        system("cls");

        cout << "++" << string(lebarKotak, '-') << "++" << endl;

        int panjangTanggal = strlen(bufferTanggal);
        int sisaLebarHeader = lebarKotak - panjangTanggal - 2;
        cout << "|| " << bufferTanggal << right << setw(sisaLebarHeader) << userAktif->username << " ||" << endl;

        cout << "++" << string(lebarKotak, '-') << "++" << endl;

        string menu[] = {
            "1. Jadwal Pengiriman",
            "2. Update Status",
            "3. Keluar"
        };

        for (int i = 0; i < 3; i++) {
            int sisaLebarMenu = lebarKotak - menu[i].length() + 1;
            cout << "|| " << menu[i] << right << setw(sisaLebarMenu) << " ||" << endl;
        }

        cout << "++" << string(lebarKotak, '-') << "++" << endl;

        cout << "|| Pilih menu: " << endl;
        cout << "++" << string(lebarKotak, '-') << "++" << endl;
        cout << "\033[2A\033[15C"; 

        cin >> plh;
        cout << "\033[2B"; 

        switch (plh)
        {
        case 1:
            jadwalPengirim();
            break;
        case 2:
            updateStatus();
            break;
        case 3:
            return;
            break;
        default:
            cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
            break;
        }
    } while (plh != 3);
};


