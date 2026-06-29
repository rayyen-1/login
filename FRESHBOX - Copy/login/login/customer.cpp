#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include "produk.h"
#include "mitra.h"
#include "beli.h"
#include "customer.h"
#include "menu.h"
#include "user.h"
using namespace std;

Pembelian daftarPembelian[MAX_PEMBELIAN];
int jumlahPembelian;

void cari() { cout << "Coming soon" << endl; system("PAUSE"); }
void filter() { cout << "Coming soon" << endl; system("PAUSE"); }

void beli() {
    system("cls");
    char program;
    string namaProduk;
    int banyak = 0;
    cout << "========== Beli Produk ==========" << endl;
    cout << "Nama Produk: "; cin >> namaProduk;

    bool isKetemu = false;
    int i;

    for (i = queue.depan; i < queue.belakang; i++) {
        if (namaProduk == queue.data[i].namaProduk) {
            isKetemu = true;
            break;
        }
    }

    if (isKetemu) {
        cout << "Sisa Produk      : " << queue.data[i].stok << endl;
        cout << "Harga Produk Rp. : " << queue.data[i].harga << endl;
        cout << "Banyak Pembelian : "; cin >> banyak;

        if (banyak <= queue.data[i].stok) {
            cout << "Total Harga  : " << queue.data[i].harga * banyak << endl;
            queue.data[i].stok -= banyak;

            // =================================================================
            // PROSES BERUBAH DI SINI (LOGIKA OPSI 2)
            // =================================================================

            // 1. Cari apakah user aktif sudah memiliki nota transaksi di daftarPembelian
            // Ubah bagian pencarian user yang kemarin menjadi seperti ini:
            int idxUser = -1;
            for (int j = 0; j < jumlahPembelian; j++) {
                // TAMBAHKAN SYARAT: && !daftarPembelian[j].isCheckedOut
                if (daftarPembelian[j].user == userAktif->username && !daftarPembelian[j].isCheckedOut) {
                    idxUser = j;
                    break;
                }
            }

            // 2. Jika user belum punya nota transaksi, buat slot transaksi baru
            if (idxUser == -1) {
                if (jumlahPembelian < MAX_PEMBELIAN) {
                    idxUser = jumlahPembelian;
                    daftarPembelian[idxUser].user = userAktif->username;
                    daftarPembelian[idxUser].alamat = userAktif->alamat;
                    daftarPembelian[idxUser].jumlahBarang = 0;
                    daftarPembelian[idxUser].totalHargaSemua = 0;
                    jumlahPembelian++; // Naikkan jumlah total transaksi di sistem
                }
                else {
                    cout << "Maaf, kapasitas data transaksi pembelian sudah penuh!" << endl;
                    queue.data[i].stok += banyak; // Kembalikan stok karena gagal
                    system("PAUSE");
                    return menuCustomer();
                }
            }

            // 3. Masukkan produk ke dalam array barang milik user tersebut
            int idxBarang = daftarPembelian[idxUser].jumlahBarang;
            if (idxBarang < MAX_ITEM_KERANJANG) {
                daftarPembelian[idxUser].daftarBarang[idxBarang].namaProduk = queue.data[i].namaProduk;
                daftarPembelian[idxUser].daftarBarang[idxBarang].hargaSatuan = queue.data[i].harga;
                daftarPembelian[idxUser].daftarBarang[idxBarang].banyakPembelian = banyak;
                daftarPembelian[idxUser].daftarBarang[idxBarang].subTotal = queue.data[i].harga * banyak;

                // Update total harga keseluruhan di nota user tersebut
                daftarPembelian[idxUser].totalHargaSemua += daftarPembelian[idxUser].daftarBarang[idxBarang].subTotal;

                // Naikkan jumlah jenis barang di dalam nota user
                daftarPembelian[idxUser].jumlahBarang++;

                cout << "Pembelian berhasil dimasukkan ke keranjang!" << endl;
            }
            else {
                cout << "Maaf, keranjang Anda sudah penuh (Maksimal jenis barang tercapai)!" << endl;
                queue.data[i].stok += banyak; // Kembalikan stok
            }
            // =================================================================
        }
        else {
            cout << "Maaf, stok tidak mencukupi!" << endl;
        }
    }
    else {
        cout << "Maaf, produk tidak ditemukan di antrean mitra." << endl;
    }

    cout << "Kembali ke halaman menu? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return menuCustomer();
    }
    else {
        exit(0);
    }
}

void pembelian() {
    tampilProduk();
    cout << "============================" << endl;
    cout << "1. Cari" << endl;
    cout << "2. Filter" << endl;
    cout << "3. Beli" << endl;
    cout << "4. Keluar" << endl;
    int pil;
    cin >> pil;
    switch (pil)
    {
    case 1:
        cari();
        break;
    case 2:
        filter();
        break;
    case 3:
        beli();
        break;
    case 4:
        return menuCustomer();
    default:
        cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
        break;
    }
}


void keranjang() {
    char program;
    int pil; // Deklarasi variabel pilihan menu
    int lebarKotak = 85;
    do {
        system("cls");

        // Total lebar konten di dalam harus 79 agar ditambah pembatas "|| " dan " ||" (6 karakter) pas menjadi 85.
        // 30 + 3 + 23 + 3 + 20 = 79. Pas!
        int colNama = 30;
        int colJumlah = 23;
        int colHarga = 20;

        // Garis Atas
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

        // Header Tabel
        cout << "|| "
            << left << setw(colNama) << "Nama Produk" << " | "
            << right << setw(colJumlah) << "Jumlah Pembelian" << " | "
            << right << setw(colHarga) << "Total Harga" << " ||" << endl;

        // Garis Pembatas Header
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

        // Cari index milik user yang sedang aktif
        int idxUser = -1;
        for (int j = 0; j < jumlahPembelian; j++) {
            // SEKARANG DITAMBAH SYARAT: && !daftarPembelian[j].isCheckedOut
            if (daftarPembelian[j].user == userAktif->username && !daftarPembelian[j].isCheckedOut) {
                idxUser = j;
                break;
            }
        }

        // Isi Tabel (Looping berdasarkan item di keranjang milik user aktif)
        if (idxUser != -1 && daftarPembelian[idxUser].jumlahBarang > 0) {
            for (int i = 0; i < daftarPembelian[idxUser].jumlahBarang; i++) {
                cout << "|| "
                    << left << setw(colNama) << daftarPembelian[idxUser].daftarBarang[i].namaProduk << " | "
                    << right << setw(colJumlah) << daftarPembelian[idxUser].daftarBarang[i].banyakPembelian << " | "
                    << right << setw(colHarga) << daftarPembelian[idxUser].daftarBarang[i].subTotal << " ||" << endl;
            }

            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
            cout << "|| " << left << setw(colNama + colJumlah + 3) << "GRAND TOTAL:"
                << right << setw(colHarga+3) << daftarPembelian[idxUser].totalHargaSemua << " ||" << endl;
        }
        else {
            // Jika tidak ketemu keranjang yang aktif (atau sudah dicheckout semua)
            cout << "|| " << left << setw(lebarKotak - 6) << "Keranjang belanja Anda masih kosong." << " ||" << endl;
        }

        // Bagian Menu Cetak
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

        string menu[] = {
            "1. Checkout",
            "2. Keluar"
        };
        int jumlahMenu = sizeof(menu) / sizeof(menu[0]); // Mengurangi risiko hardcode angka 5

        for (int i = 0; i < jumlahMenu; i++) {
            // "|| " memakan 3 karakter, " ||" memakan 3 karakter. Total 6 karakter frame.
            int sisaLebarMenu = lebarKotak - menu[i].length() - 6;
            cout << "|| " << menu[i] << right << setw(sisaLebarMenu + 3) << " ||" << endl;
        }

        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "|| Pilih menu: " << left << setw(lebarKotak - 18) << "" << " ||" << endl; // Membuat baris input tetap punya penutup kanan
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

        // Mengarahkan kursor kembali ke baris "Pilih menu: "
        cout << "\033[2A\033[15C";
        cin >> pil;
        cout << "\033[2B";

        switch (pil)
        {
        case 1:
        {
            time_t waktuSekarang = time(0);

            // 3. Konversi waktu menjadi bentuk teks/string (ctim_t otomatis memberi karakter newline di ujungnya)
            string teksWaktu = ctime(&waktuSekarang);

            // Hapus karakter 'enter/newline' di akhir teksWaktu agar tidak merusak format tabel/layout
            if (!teksWaktu.empty() && teksWaktu.back() == '\n') {
                teksWaktu.pop_back();
            }

            // 4. Simpan ke dalam struct user tersebut
            daftarPembelian[idxUser].isCheckedOut = true;
            daftarPembelian[idxUser].waktuCheckout = teksWaktu;
            return menuCustomer();
        }
        case 2:
            return menuCustomer();
        default:
            cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
            system("PAUSE");
            break;
        }
    } while (pil != 2); // Karena menunya hanya sampai 2, loop keluar jika pil == 2

}