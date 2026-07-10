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

// ── Definisi variabel global ──
Pembelian      daftarPembelian[MAX_PEMBELIAN];
int            jumlahPembelian = 0;

KeranjangDLL   daftarKeranjang[MAX_PEMBELIAN];
int            jumlahKeranjang = 0;

// ════════════════════════════════════════════════════════
//  HELPER DOUBLE LINKED LIST KERANJANG
// ════════════════════════════════════════════════════════

// Cari keranjang aktif milik userAktif, buat baru jika belum ada
KeranjangDLL* cariAtauBuatKeranjang() {
    for (int i = 0; i < jumlahKeranjang; i++) {
        if (daftarKeranjang[i].pemilik.username == userAktif->username
            && !daftarKeranjang[i].isCheckedOut) {
            return &daftarKeranjang[i];
        }
    }
    if (jumlahKeranjang >= MAX_PEMBELIAN) return nullptr;
    daftarKeranjang[jumlahKeranjang].pemilik = *userAktif;
    daftarKeranjang[jumlahKeranjang].head = nullptr;
    daftarKeranjang[jumlahKeranjang].tail = nullptr;
    daftarKeranjang[jumlahKeranjang].jumlahItem = 0;
    daftarKeranjang[jumlahKeranjang].totalHarga = 0;
    daftarKeranjang[jumlahKeranjang].isCheckedOut = false;
    daftarKeranjang[jumlahKeranjang].waktuCheckout = "";
    return &daftarKeranjang[jumlahKeranjang++];
}

// Tambah item ke tail DLL
void tambahKeKeranjang(KeranjangDLL* k, ItemKeranjang item) {
    NodeKeranjang* node = new NodeKeranjang();
    node->item = item;
    node->prev = k->tail;
    node->next = nullptr;
    if (k->tail) k->tail->next = node;
    else         k->head = node;
    k->tail = node;
    k->jumlahItem++;
    k->totalHarga += item.subTotal;
}

// Hapus node tertentu dari DLL (by pointer)
void hapusDariKeranjang(KeranjangDLL* k, NodeKeranjang* node) {
    if (!node) return;
    if (node->prev) node->prev->next = node->next;
    else            k->head = node->next;
    if (node->next) node->next->prev = node->prev;
    else            k->tail = node->prev;
    k->totalHarga -= node->item.subTotal;
    k->jumlahItem--;
    delete node;
}

// Kosongkan seluruh DLL (dipakai setelah checkout)
void kosongkanKeranjang(KeranjangDLL* k) {
    NodeKeranjang* cur = k->head;
    while (cur) {
        NodeKeranjang* next = cur->next;
        delete cur;
        cur = next;
    }
    k->head = nullptr;
    k->tail = nullptr;
    k->jumlahItem = 0;
    k->totalHarga = 0;
}

// Konversi KeranjangDLL → Pembelian (untuk kurir/mitra/invoice)
Pembelian keranjangKePembelian(KeranjangDLL* k) {
    Pembelian p;
    p.daftarUser[0] = k->pemilik;
    p.jumlahBarang = 0;
    p.totalHargaSemua = k->totalHarga;
    p.isCheckedOut = k->isCheckedOut;
    p.waktuCheckout = k->waktuCheckout;
    NodeKeranjang* cur = k->head;
    while (cur && p.jumlahBarang < MAX_ITEM_KERANJANG) {
        p.daftarBarang[p.jumlahBarang++] = cur->item;
        cur = cur->next;
    }
    return p;
}

// ════════════════════════════════════════════════════════
//  CARI & FILTER
// ════════════════════════════════════════════════════════

void cari() {
    char program;
    do {
        system("cls");
        string kataKunci;
        cout << "========== Cari Produk ==========" << endl;
        cout << "Masukkan nama produk yang dicari: ";
        cin >> kataKunci;

        string kataKunciLower = kataKunci;
        for (size_t k = 0; k < kataKunciLower.size(); k++)
            kataKunciLower[k] = tolower(kataKunciLower[k]);

        system("cls");
        int lebarKotak = 75, colNo = 4, colNama = 25, colKat = 12, colStok = 8, colHarga = 8;

        cout << "========== Hasil Pencarian: \"" << kataKunci << "\" ==========" << endl;
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "|| "
            << left << setw(colNo) << "No" << " | "
            << left << setw(colNama) << "Nama Produk" << " | "
            << left << setw(colKat) << "Kategori" << " | "
            << right << setw(colStok) << "Stok" << " | "
            << right << setw(colHarga) << "Harga" << " ||" << endl;
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

        bool adaHasil = false;
        int nomor = 1;
        for (size_t m = 0; m < listMitra.size(); m++) {
            for (int i = listMitra[m].depan; i < listMitra[m].belakang; i++) {
                string namaLower = listMitra[m].data[i].namaProduk;
                for (size_t k = 0; k < namaLower.size(); k++)
                    namaLower[k] = tolower(namaLower[k]);
                if (namaLower.find(kataKunciLower) != string::npos) {
                    adaHasil = true;
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
        }
        if (!adaHasil)
            cout << "|| " << left << setw(lebarKotak - 6) << "Produk tidak ditemukan." << " ||" << endl;

        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl << endl;
        cout << "\nLanjutkan pencarian? (y/n): ";
        cin >> program;
    } while (program == 'y' || program == 'Y');
}

void filter() {
    int lebarKotak = 75, colNo = 4, colNama = 25, colKat = 12, colStok = 8, colHarga = 8;
    char program;
    do {
        int q;
        cout << "1. Sayur" << endl;
        cout << "2. Buah" << endl;
        cout << "3. Lainnya" << endl;
        cout << "masukkan pilihan: "; cin >> q;

        KategoriProduk kategoriDipilih;
        if (q == 1) kategoriDipilih = SAYUR;
        else if (q == 2) kategoriDipilih = BUAH;
        else             kategoriDipilih = LAINNYA;

        system("cls");
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
                if (listMitra[m].data[i].kategori != kategoriDipilih) continue;
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
        if (!adaProduk)
            cout << "|| " << left << setw(lebarKotak - 6) << "Tidak ada produk untuk kategori ini." << " ||" << endl;

        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "\nLanjutkan pemfilteran? (y/n): ";
        cin >> program;
    } while (program == 'y' || program == 'Y');
}

vector<Pengiriman> listKurir;
vector<Queue>      listMitra;

// ════════════════════════════════════════════════════════
//  BELI — tambah item ke DLL keranjang
// ════════════════════════════════════════════════════════

void beli() {
    system("cls");
    char program;
    string namaProduk;
    int banyak = 0;

    cout << "========== Beli Produk ==========" << endl;
    cout << "Nama Produk: "; cin >> namaProduk;

    bool   isKetemu = false;
    size_t idxMitra = 0;
    int    idxProduk = -1;

    for (size_t m = 0; m < listMitra.size(); m++) {
        for (int i = listMitra[m].depan; i < listMitra[m].belakang; i++) {
            if (namaProduk == listMitra[m].data[i].namaProduk) {
                isKetemu = true; idxMitra = m; idxProduk = i; break;
            }
        }
        if (isKetemu) break;
    }

    if (isKetemu) {
        Produk& produkPilihan = listMitra[idxMitra].data[idxProduk];
        cout << "Sisa Produk      : " << produkPilihan.stok << endl;
        cout << "Harga Produk Rp. : " << produkPilihan.harga << endl;
        cout << "Banyak Pembelian : "; cin >> banyak;

        if (banyak <= produkPilihan.stok) {
            cout << "Total Harga  : " << produkPilihan.harga * banyak << endl;
            produkPilihan.stok -= banyak;

            KeranjangDLL* keranjang = cariAtauBuatKeranjang();
            if (!keranjang) {
                cout << "Maaf, kapasitas keranjang sudah penuh!" << endl;
                produkPilihan.stok += banyak;
                system("PAUSE");
                return;
            }
            if (keranjang->jumlahItem >= MAX_ITEM_KERANJANG) {
                cout << "Maaf, keranjang Anda sudah penuh!" << endl;
                produkPilihan.stok += banyak;
            }
            else {
                ItemKeranjang item;
                item.namaProduk = produkPilihan.namaProduk;
                item.hargaSatuan = produkPilihan.harga;
                item.banyakPembelian = banyak;
                item.subTotal = produkPilihan.harga * banyak;
                tambahKeKeranjang(keranjang, item);
                cout << "Pembelian berhasil dimasukkan ke keranjang!" << endl;
            }
        }
        else {
            cout << "Maaf, stok tidak mencukupi!" << endl;
        }
    }
    else {
        cout << "Maaf, produk tidak ditemukan di antrean mitra mana pun." << endl;
    }

    cout << "\nLanjutkan pembelian? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') return beli();
}

void pembelian() {
    tampilProduk();
    cout << "============================" << endl;
    cout << "1. Cari" << endl;
    cout << "2. Filter" << endl;
    cout << "3. Beli" << endl;
    cout << "4. Keluar" << endl;
    int pil;
    cout << "masukkan pilihan : "; cin >> pil;
    switch (pil) {
    case 1: cari();   break;
    case 2: filter(); break;
    case 3: beli();   break;
    case 4: return;
    default: cout << "\nPilihan tidak valid! Silakan coba lagi." << endl; break;
    }
}

// ════════════════════════════════════════════════════════
//  KERANJANG — tampil & hapus item dari DLL
// ════════════════════════════════════════════════════════

void keranjang() {
    int pil;
    int lebarKotak = 85;
    do {
        system("cls");
        int colNo = 4;
        int colNama = 30;
        int colJumlah = 20;
        int colHarga = 15;

        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "|| "
            << left << setw(colNo) << "No" << " | "
            << left << setw(colNama) << "Nama Produk" << " | "
            << right << setw(colJumlah) << "Jumlah Pembelian" << " | "
            << right << setw(colHarga) << "Total Harga" << " ||" << endl;
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

        // Cari keranjang aktif milik user
        KeranjangDLL* keranjang = nullptr;
        for (int i = 0; i < jumlahKeranjang; i++) {
            if (daftarKeranjang[i].pemilik.username == userAktif->username
                && !daftarKeranjang[i].isCheckedOut) {
                keranjang = &daftarKeranjang[i];
                break;
            }
        }

        // Traversal DLL dari head ke tail
        if (keranjang && keranjang->head) {
            int nomor = 1;
            NodeKeranjang* cur = keranjang->head;
            while (cur) {
                cout << "|| "
                    << left << setw(colNo) << nomor << " | "
                    << left << setw(colNama) << cur->item.namaProduk << " | "
                    << right << setw(colJumlah) << cur->item.banyakPembelian << " | "
                    << right << setw(colHarga) << cur->item.subTotal << " ||" << endl;
                cur = cur->next;
                nomor++;
            }
            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
            int sisaGrandTotal = lebarKotak - 4 - colNo - colNama - colJumlah - 9;
            cout << "|| " << left << setw(colNo + colNama + colJumlah + 9) << "GRAND TOTAL:"
                << right << setw(sisaGrandTotal) << keranjang->totalHarga << " ||" << endl;
        }
        else {
            cout << "|| " << left << setw(lebarKotak - 6) << "Keranjang belanja Anda masih kosong." << " ||" << endl;
        }

        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

        string menu[] = { "1. Checkout", "2. Hapus Item", "3. Keluar" };
        int jumlahMenu = 3;
        for (int i = 0; i < jumlahMenu; i++) {
            int sisa = lebarKotak - (int)menu[i].length() - 6;
            cout << "|| " << menu[i] << right << setw(sisa + 3) << " ||" << endl;
        }
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "|| Pilih menu: " << left << setw(lebarKotak - 18) << "" << " ||" << endl;
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "\033[2A\033[15C";
        cin >> pil;
        cout << "\033[2B";

        switch (pil) {
        case 1: // ── CHECKOUT ──
        {
            if (!keranjang || !keranjang->head) {
                cout << "\n[!] Keranjang belanja Anda masih kosong!" << endl;
                system("PAUSE"); break;
            }

            time_t waktuSekarang = time(0);
            string teksWaktu = ctime(&waktuSekarang);
            if (!teksWaktu.empty() && teksWaktu.back() == '\n') teksWaktu.pop_back();

            keranjang->isCheckedOut = true;
            keranjang->waktuCheckout = teksWaktu;

            // Konversi DLL → Pembelian supaya kurir & mitra tetap bisa pakai
            Pembelian p = keranjangKePembelian(keranjang);
            if (jumlahPembelian < MAX_PEMBELIAN) {
                daftarPembelian[jumlahPembelian++] = p;
            }

            Jadwal(listKurir, p);
            listOrder(listOrderMitra, p);

            cout << "\nCheckout berhasil! Pesanan Anda sedang diproses." << endl;
            system("PAUSE");
            return;
        }
        case 2: // ── HAPUS ITEM dari DLL ──
        {
            if (!keranjang || !keranjang->head) {
                cout << "\n[!] Keranjang kosong, tidak ada yang bisa dihapus." << endl;
                system("PAUSE"); break;
            }
            int nomorHapus;
            cout << "\nMasukkan nomor item yang ingin dihapus: ";
            cin >> nomorHapus;

            // Traversal DLL untuk cari node ke-nomorHapus
            NodeKeranjang* target = keranjang->head;
            for (int i = 1; i < nomorHapus && target; i++)
                target = target->next;

            if (!target) {
                cout << "Nomor item tidak valid!" << endl;
            }
            else {
                // Kembalikan stok produk ke mitra
                for (size_t m = 0; m < listMitra.size(); m++) {
                    for (int i = listMitra[m].depan; i < listMitra[m].belakang; i++) {
                        if (listMitra[m].data[i].namaProduk == target->item.namaProduk) {
                            listMitra[m].data[i].stok += target->item.banyakPembelian;
                            break;
                        }
                    }
                }
                cout << "Item \"" << target->item.namaProduk << "\" dihapus dari keranjang." << endl;
                hapusDariKeranjang(keranjang, target);
            }
            system("PAUSE"); break;
        }
        case 3:
            return;
        default:
            cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
            system("PAUSE"); break;
        }
    } while (pil != 3);
}

// ════════════════════════════════════════════════════════
//  EXPORT CSV & INVOICE — baca dari daftarPembelian
// ════════════════════════════════════════════════════════

void exportcsv() {
    int indexDitemukan = -1;
    for (int i = jumlahPembelian - 1; i >= 0; i--) {
        if (daftarPembelian[i].daftarUser[0].username == userAktif->username
            && daftarPembelian[i].isCheckedOut) {
            indexDitemukan = i; break;
        }
    }

    string lokasi_file = "laporan_customer.csv";
    ofstream file(lokasi_file);
    if (file.is_open()) {
        Pembelian p = daftarPembelian[indexDitemukan];
        file << "Tanggal,Nama Mitra,Nama Pembeli,No HP,Alamat,Item,Jumlah Beli,Harga\n";
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
        cout << "Gagal membuat file!" << endl;
    }
    system("PAUSE");
}

void invo() {
    int indexDitemukan = -1;
    for (int i = jumlahPembelian - 1; i >= 0; i--) {
        if (daftarPembelian[i].daftarUser[0].username == userAktif->username
            && daftarPembelian[i].isCheckedOut) {
            indexDitemukan = i; break;
        }
    }

    if (indexDitemukan == -1) {
        system("cls");
        cout << "======================================================" << endl;
        cout << " Belum ada riwayat transaksi/checkout untuk user: " << userAktif->username << endl;
        cout << "======================================================" << endl;
        cout << "\nKembali ke menu (Enter)...";
        cin.get(); cin.get();
        return;
    }

    system("cls");
    int lebarKotak = 85;
    Pembelian p = daftarPembelian[indexDitemukan];
    int    idTransaksi = indexDitemukan + 1;
    string namaMitra = "Toko Mitra Resmi";

    cout << "++" << string(lebarKotak, '-') << "++" << endl;
    cout << "|| " << left << setw(lebarKotak - 2) << " INVOICE" << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl;
    cout << "|| Tanggal : " << left << setw(20) << p.waktuCheckout
        << "|| ID Transaksi : " << left << setw(lebarKotak - 50) << idTransaksi << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl;
    cout << "|| Nama Mitra   : " << left << setw(20) << namaMitra
        << "|| Nama Pembeli : " << left << setw(lebarKotak - 55) << p.daftarUser[0].username << " ||" << endl;
    cout << "|| Alamat       : " << left << setw(20) << p.daftarUser[0].alamat
        << "|| No HP        : " << left << setw(lebarKotak - 55) << p.daftarUser[0].nohp << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl;
    cout << "|| " << left << setw(7) << "QTY"
        << "|| " << left << setw(lebarKotak - 30) << "ITEM"
        << "|| " << right << setw(15) << "PRICE" << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl;
    for (int i = 0; i < p.jumlahBarang; i++) {
        cout << "|| " << left << setw(7) << p.daftarBarang[i].banyakPembelian
            << "|| " << left << setw(lebarKotak - 30) << p.daftarBarang[i].namaProduk
            << "|| " << right << setw(15) << p.daftarBarang[i].subTotal << " ||" << endl;
    }
    cout << "++" << string(lebarKotak, '-') << "++" << endl;
    cout << "|| Item Count : " << left << setw(15) << p.jumlahBarang
        << "|| Total      : " << right << setw(lebarKotak - 46) << p.totalHargaSemua << " ||" << endl;
    cout << "++" << string(lebarKotak, '-') << "++" << endl << endl;

    cout << "1. Export CSV" << endl;
    cout << "2. Kembali" << endl;
    int pilihan;
    cout << "Masukkan pilihan : "; cin >> pilihan;
    switch (pilihan) {
    case 1: exportcsv(); break;
    case 2: return;
    }
}

// ════════════════════════════════════════════════════════
//  LACAK KURIR
// ════════════════════════════════════════════════════════

void lacakKurir() {
    system("cls");
    int lebarKotak = 85;
    int colNo = 4;
    int colAlamat = 30;
    int colStatus = 25;
    int colCustomer = lebarKotak - 5 - 9 - colNo - colAlamat - colStatus - 2;

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << "|| " << left << setw(lebarKotak - 6) << "LACAK KURIR - STATUS PENGIRIMAN" << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << "|| "
        << left << setw(colNo) << "No" << " | "
        << left << setw(colCustomer) << "Customer" << " | "
        << left << setw(colAlamat) << "Alamat" << " | "
        << left << setw(colStatus) << "Status" << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    bool adaData = false;
    int  nomor = 1;
    for (size_t i = 0; i < listKurir.size(); i++) {
        if (listKurir[i].beli.daftarUser->username == userAktif->username) {
            adaData = true;
            cout << "|| "
                << left << setw(colNo) << nomor << " | "
                << left << setw(colCustomer) << listKurir[i].beli.daftarUser->username << " | "
                << left << setw(colAlamat) << listKurir[i].beli.daftarUser->alamat << " | "
                << left << setw(colStatus) << statusToString(listKurir[i].status) << " ||" << endl;
            nomor++;
        }
    }
    if (!adaData)
        cout << "|| " << left << setw(lebarKotak - 6) << "Belum ada data pengiriman untuk akun Anda." << " ||" << endl;

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl << endl;
    cout << "Tekan Enter untuk kembali...";
    cin.get(); cin.get();
}