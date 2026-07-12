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

        string judul = "MENU MITRA";
        int panjangJudul = (int)judul.length();
        int spasiKiri = (lebarKotak - panjangJudul) / 2;
        int spasiKanan = lebarKotak - panjangJudul - spasiKiri;

        cout << "++" << string(lebarKotak, '-') << "++" << endl;
        cout << "||" << string(spasiKiri, ' ') << judul << string(spasiKanan, ' ') << "||" << endl;
        cout << "++" << string(lebarKotak, '-') << "++" << endl;

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
            tampilProdukSaya();
            cout << string(lebarKotak, '=') << endl;
            int pilihan;
            char program;
            cout << "kembali ke halaman menu? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y') {
                return menuMitra();
            }
            else
            {
				return tampilProdukSaya();
            }
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
            return login(daftarUser, jumlahUser);
            break;
        default:
            cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            break;
        }

        char program;
        cout << "Kembali ke halaman menu login? (y/n): ";
        cin >> program;
        if (program == 'y' || program == 'Y') {
            return login(daftarUser, jumlahUser);
        }
        else {
            return menuMitra();
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

        string judul = "MENU CUSTOMER";
        int panjangJudul = (int)judul.length();
        int spasiKiri = (lebarKotak - panjangJudul) / 2;
        int spasiKanan = lebarKotak - panjangJudul - spasiKiri;

        cout << "++" << string(lebarKotak, '-') << "++" << endl;
        cout << "||" << string(spasiKiri, ' ') << judul << string(spasiKanan, ' ') << "||" << endl;
        cout << "++" << string(lebarKotak, '-') << "++" << endl;

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

        string judul = "MENU KURIR";
        int panjangJudul = (int)judul.length();
        int spasiKiri = (lebarKotak - panjangJudul) / 2;
        int spasiKanan = lebarKotak - panjangJudul - spasiKiri;

        cout << "++" << string(lebarKotak, '-') << "++" << endl;
        cout << "||" << string(spasiKiri, ' ') << judul << string(spasiKanan, ' ') << "||" << endl;
        cout << "++" << string(lebarKotak, '-') << "++" << endl;

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
            statusPengirim();
            break;
        case 3:
            return login(daftarUser, jumlahUser);
            break;
        default:
            cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
            break;
        }
    } while (plh != 3);
}
