#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include "produk.h"
#include "mitra.h"
#include "beli.h"
#include "customer.h"
#include "menu.h"
#include "user.h"
#include "kurir.h"
using namespace std;

Pembelian daftarPembelian[MAX_PEMBELIAN];
int jumlahPembelian;


void cari() { 
    string nama_produk;
    cout << "Masukkan nama produk yang ingin dicari : "; cin >> nama_produk;



}
void filter() {
    Mitra produk[MAX_PRODUK_PER_MITRA];
    
    int lebarKotak = 75;
    int colNo = 4;
    int colNama = 25;
    int colKat = 12;
    int colStok = 8;
    int colHarga = 8;

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << "|| "
        << left << setw(colNo) << "No" << " | "
        << left << setw(colNama) << "Nama Produk" << " | "
        << left << setw(colKat) << "Kategori" << " | "
        << right << setw(colStok) << "Stok" << " | "
        << right << setw(colHarga) << "Harga" << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    bool adaProduk = false;
    int nomor = 1;
    for (size_t m = 0; m < listMitra.size(); m++) {
        for (int i = listMitra[m].depan; i < listMitra[m].belakang; i++) {
            adaProduk = true;
            string hargaStr = "Rp " + to_string(listMitra[m].data[i].harga);
            cout << "|| "
                << left << setw(colNo) << nomor << " | "
                << left << setw(colNama) << listMitra[m].data[i].namaProduk << " | "
                << left << setw(colKat) << namaKategori(listMitra[m].data[i].kategori) << " | "
                << right << setw(colStok) << listMitra[m].data[i].stok << " | "
                << right << setw(colHarga) << hargaStr << " ||" << endl;
            nomor++;
        }
    }

    int q;
    cout << "1. Sayur" << endl;
    cout << "2. Buah" << endl;
    cout << "masukkan pilihan: "; cin >> q;
    for (int i = 1; i < produk->jumlahProdukMitra ; i++)
    {
        cout << "|";
        if (q == produk[i].daftarProdukMitra[i].kategori) {
            cout << i << produk[i].daftarProdukMitra[i].namaProduk << produk[i].daftarProdukMitra[i].kategori << produk[i].daftarProdukMitra[i].stok << produk[i].daftarProdukMitra[i].harga;
        }
    }
}

vector<Pengiriman> listKurir;
vector<Queue> listMitra;
// listOrderMitra didefinisikan bersama listMitra di sini karena keduanya
// diinisialisasi sebelum dipakai oleh customer.cpp maupun mitra.cpp

void beli() {
    system("cls");
    char program;
    string namaProduk;
    int banyak = 0;
    cout << "========== Beli Produk ==========" << endl;
    cout << "Nama Produk: "; cin >> namaProduk;

    bool isKetemu = false;
    size_t idxMitra = -1;
    int idxProduk = -1;

    // Cari produk di dalam antrean (Queue) milik setiap mitra di listMitra
    for (size_t m = 0; m < listMitra.size(); m++) {
        for (int i = listMitra[m].depan; i < listMitra[m].belakang; i++) {
            // listMitra[m].data[i] mengakses struct Produk asli kamu yang ada di dalam queue
            if (namaProduk == listMitra[m].data[i].namaProduk) {
                isKetemu = true;
                idxMitra = m;
                idxProduk = i;
                break;
            }
        }
        if (isKetemu) break;
    }

    if (isKetemu) {
        // Ambil referensi ke produk asli kamu tanpa mengubah definisi struct-nya
        Produk& produkPilihan = listMitra[idxMitra].data[idxProduk];

        cout << "Sisa Produk      : " << produkPilihan.stok << endl;
        cout << "Harga Produk Rp. : " << produkPilihan.harga << endl;
        cout << "Banyak Pembelian : "; cin >> banyak;

        if (banyak <= produkPilihan.stok) {
            cout << "Total Harga  : " << produkPilihan.harga * banyak << endl;
            produkPilihan.stok -= banyak; // Stok di struct asli langsung terpotong

            int idxUser = -1;
            // Cari keranjang belanja aktif milik user saat ini
            for (int j = 0; j < jumlahPembelian; j++) {
                if (daftarPembelian[j].daftarUser[0].username == userAktif->username && !daftarPembelian[j].isCheckedOut) {
                    idxUser = j;
                    break;
                }
            }

            // Jika belum punya keranjang, buat baru
            if (idxUser == -1) {
                if (jumlahPembelian < MAX_PEMBELIAN) {
                    idxUser = jumlahPembelian;
                    daftarPembelian[idxUser].daftarUser[0] = *userAktif;
                    daftarPembelian[idxUser].jumlahBarang = 0;
                    daftarPembelian[idxUser].totalHargaSemua = 0;
                    daftarPembelian[idxUser].isCheckedOut = false;
                    jumlahPembelian++;
                }
                else {
                    cout << "Maaf, kapasitas data transaksi pembelian sudah penuh!" << endl;
                    produkPilihan.stok += banyak;
                    system("PAUSE");
                    return menuCustomer();
                }
            }

            // Masukkan data barang ke keranjang pembeli
            int idxBarang = daftarPembelian[idxUser].jumlahBarang;
            if (idxBarang < MAX_ITEM_KERANJANG) {
                daftarPembelian[idxUser].daftarBarang[idxBarang].namaProduk = produkPilihan.namaProduk;
                daftarPembelian[idxUser].daftarBarang[idxBarang].hargaSatuan = produkPilihan.harga;
                daftarPembelian[idxUser].daftarBarang[idxBarang].banyakPembelian = banyak;
                daftarPembelian[idxUser].daftarBarang[idxBarang].subTotal = produkPilihan.harga * banyak;

                daftarPembelian[idxUser].totalHargaSemua += daftarPembelian[idxUser].daftarBarang[idxBarang].subTotal;
                daftarPembelian[idxUser].jumlahBarang++;

                cout << "Pembelian berhasil dimasukkan ke keranjang!" << endl;
            }
            else {
                cout << "Maaf, keranjang Anda sudah penuh!" << endl;
                produkPilihan.stok += banyak;
            }
        }
        else {
            cout << "Maaf, stok tidak mencukupi!" << endl;
        }
    }
    else {
        cout << "Maaf, produk tidak ditemukan di antrean mitra mana pun." << endl;
    }

    cout << "\nKembali ke halaman menu? (y/n): ";
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
        for (int j = 0; j < jumlahPembelian && idxUser == -1; j++) {
            for (int u = 0; u < jumlahUser; u++) {
                if (daftarPembelian[j].daftarUser[u].username == userAktif->username && !daftarPembelian[j].isCheckedOut) {
                    idxUser = j;
                    break;
                }
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
                << right << setw(colHarga + 3) << daftarPembelian[idxUser].totalHargaSemua << " ||" << endl;
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
            if (idxUser == -1) {
                cout << "\n[!] Sesi pengguna tidak valid. Gagal checkout!" << endl;
                system("PAUSE");
                break;
            }
            if (daftarPembelian[idxUser].jumlahBarang == 0) {
                cout << "\n[!] Keranjang belanja Anda masih kosong!" << endl;
                system("PAUSE");
                break;
            }

            time_t waktuSekarang = time(0);
            string teksWaktu = ctime(&waktuSekarang);
            if (!teksWaktu.empty() && teksWaktu.back() == '\n') {
                teksWaktu.pop_back();
            }

            daftarPembelian[idxUser].isCheckedOut = true;
            daftarPembelian[idxUser].waktuCheckout = teksWaktu;

            // FIX: Hapus tanda bintang (*) di depan listKurir saat memanggil fungsi
            Pengiriman hasilPengiriman = Jadwal(listKurir, daftarPembelian[idxUser]);
            // Daftarkan juga pesanan ini ke Mitra supaya muncul di menu "Update Status Pengiriman"-nya
            Queue hasilOrder = listOrder(listOrderMitra, daftarPembelian[idxUser]);

            // ... kode cetak struk kamu ke bawah tetap sama ...
            system("PAUSE");
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

void exportcsv() {
    // 1. Cari data pembelian milik user yang sedang aktif
    int indexDitemukan = -1;

    // Kita melakukan loop mundur (dari yang terbaru) 
    // untuk mendapatkan invoice terakhir dari user aktif tersebut
    for (int i = jumlahPembelian - 1; i >= 0; i--) {
        // Catatan: Mengasumsikan daftarUser[0] adalah user yang melakukan pembelian
        // dan 'userAktif' adalah variabel global/extern untuk sesi yang sedang login
        if (daftarPembelian[i].daftarUser[0].username == userAktif->username && daftarPembelian[i].isCheckedOut) {
            indexDitemukan = i;
            break; // Hentikan pencarian jika sudah ketemu yang terbaru
        }
    }

    string lokasi_file = "laporan_customer.csv";
    ofstream file(lokasi_file);

    // 2. Cek apakah file benar-benar berhasil dibuka/dibuat
    if (file.is_open()) {
        Pembelian p = daftarPembelian[indexDitemukan];

        // Header CSV
        file << "Tanggal,Nama Mitra,Nama Pembeli,No HP,Alamat,Item,Jumlah Beli,Harga\n";

        // Isi CSV (Sudah ditambah koma pemisah kolom)
        for (int i = 0; i < p.jumlahBarang; i++) {
            file << p.waktuCheckout << ",Toko Mitra Resmi,"
                << p.daftarUser[0].username << ","
                << p.daftarUser[0].nohp << ","
                << p.daftarUser[0].alamat << ","
                << p.daftarBarang[i].namaProduk << ","
                << p.daftarBarang[i].banyakPembelian << ","
                << p.daftarBarang[i].subTotal << "\n";
        }

        file.close();
        cout << "File CSV berhasil disimpan di: " << lokasi_file << endl;
    }
    else {
        cout << "Gagal membuat file! Pastikan folder 'Downloads' sudah ada." << endl;
    }
    system("PAUSE");
}

void invo() {
    // 1. Cari data pembelian milik user yang sedang aktif
    int indexDitemukan = -1;

    // Kita melakukan loop mundur (dari yang terbaru) 
    // untuk mendapatkan invoice terakhir dari user aktif tersebut
    for (int i = jumlahPembelian - 1; i >= 0; i--) {
        // Catatan: Mengasumsikan daftarUser[0] adalah user yang melakukan pembelian
        // dan 'userAktif' adalah variabel global/extern untuk sesi yang sedang login
        if (daftarPembelian[i].daftarUser[0].username == userAktif->username && daftarPembelian[i].isCheckedOut) {
            indexDitemukan = i;
            break; // Hentikan pencarian jika sudah ketemu yang terbaru
        }
    }

    // 2. Validasi jika data tidak ditemukan
    if (indexDitemukan == -1) {
        system("cls");
        cout << "======================================================" << endl;
        cout << " Belum ada riwayat transaksi/checkout untuk user: " << userAktif->username << endl;
        cout << "======================================================" << endl;
        cout << "\nKembali ke menu (Enter)...";
        cin.get(); cin.get();
        return;
    }

    // 3. Jika ditemukan, ambil datanya
    system("cls");
    int lebarKotak = 85;
    Pembelian p = daftarPembelian[indexDitemukan];

    // Placeholder karena idTransaksi & namaMitra tidak ada di struct Pembelian Anda
    int idTransaksiPlaceholder = indexDitemukan + 1;
    string namaMitraPlaceholder = "Toko Mitra Resmi";

    // --- CETAK INVOICE ---
    cout << "++" << string(lebarKotak, '-') << "++" << endl;
    cout << "|| " << left << setw(lebarKotak - 2) << " INVOICE" << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl;

    // Baris Tanggal & ID Transaksi
    cout << "|| Tanggal : " << left << setw(20) << p.waktuCheckout
        << "|| ID Transaksi : " << left << setw(lebarKotak - 50) << idTransaksiPlaceholder << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl;

    // Baris Profil Pembeli & Mitra
    cout << "|| Nama Mitra   : " << left << setw(20) << namaMitraPlaceholder
        << "|| Nama Pembeli : " << left << setw(lebarKotak - 55) << p.daftarUser[0].username << " ||" << endl;
    cout << "|| Alamat       : " << left << setw(20) << p.daftarUser[0].alamat
        << "|| No HP        : " << left << setw(lebarKotak - 55) << p.daftarUser[0].nohp << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl;

    // Header Tabel Barang
    cout << "|| " << left << setw(7) << "QTY"
        << "|| " << left << setw(lebarKotak - 30) << "ITEM"
        << "|| " << right << setw(15) << "PRICE" << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl;

    // Loop menampilkan item keranjang
    for (int i = 0; i < p.jumlahBarang; i++) {
        cout << "|| " << left << setw(7) << p.daftarBarang[i].banyakPembelian
            << "|| " << left << setw(lebarKotak - 30) << p.daftarBarang[i].namaProduk
            << "|| " << right << setw(15) << p.daftarBarang[i].subTotal << " ||" << endl;
    }
    cout << "++" << string(lebarKotak, '-') << "++" << endl;

    // Footer Total
    cout << "|| Item Count : " << left << setw(15) << p.jumlahBarang
        << "|| Total      : " << right << setw(lebarKotak - 46) << p.totalHargaSemua << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl;
    cout << endl;

    cout << "1. Export CSV " << endl;
    cout << "2. Kembali " << endl;
    int pilihan;
    cout << "Masukkan pilihan : "; cin >> pilihan;
    switch (pilihan) {
    case 1:
        exportcsv();
        break;
    case 2:
        return menuCustomer();
    }
}



void lacakKurir() {
    system("cls");
    int lebarKotak = 85;

    cout << "++" << string(lebarKotak, '-') << "++" << endl;
    cout << "|| " << left << setw(lebarKotak - 4) << " STATUS PENGIRIMAN" << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl;

    cout << "== Status Pengiriman Saat Ini ==" << endl;
    cout << "-----------------------------------" << endl;
    cout
        << setw(20) << left << "Customer"
        << setw(20) << left << "Alamat"
        << setw(20) << left << "Status" << endl;
    cout << "-----------------------------------" << endl;



    for (size_t i = 0; i < listKurir.size(); i++) {

        if (listKurir[i].beli.daftarUser->username == userAktif->username) {
            cout
                << setw(20) << left << listKurir[i].beli.daftarUser->username
                << setw(20) << left << listKurir[i].beli.daftarUser->alamat
                << setw(20) << left << statusToString(listKurir[i].status) << endl;
        }
    }

    cout << "-----------------------------------" << endl;

    cout << "\nTekan Enter untuk kembali...";
    cin.get(); cin.get();
}