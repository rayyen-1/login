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
// ════════════════════════════════════════════════════════
//  HELPER DOUBLE LINKED LIST KERANJANG
// ════════════════════════════════════════════════════════

// Cari keranjang AKTIF milik userAktif saja, TANPA membuat baru.
// Dipakai fungsi keranjang() untuk lihat/kelola isi keranjang.
KeranjangDLL* cariKeranjangAktif() {
    for (int i = 0; i < jumlahKeranjang; i++) {
        if (daftarKeranjang[i].pemilik.username == userAktif->username
            && !daftarKeranjang[i].isCheckedOut) {
            return &daftarKeranjang[i];
        }
    }
    return nullptr;
}

// Cari keranjang aktif milik userAktif, BUAT baru kalau belum ada.
// Dipakai fungsi beli() saat menambahkan item pertama ke keranjang.
KeranjangDLL* cariAtauBuatKeranjang() {
    KeranjangDLL* aktif = cariKeranjangAktif();
    if (aktif) return aktif;

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
        int colNo = 4, colNama = 25, colKat = 12, colStok = 8, colHarga = 20;
        int lebarKotak = 3 + colNo + 3 + colNama + 3 + colKat + 3 + colStok + 3 + colHarga + 3;

        // Judul dibuat dinamis mengikuti lebarKotak, bukan hardcode "=========="
        string judul = " Hasil Pencarian: \"" + kataKunci + "\" ";
        int sisaLebar = lebarKotak - (int)judul.length();
        if (sisaLebar < 0) sisaLebar = 0; // jaga-jaga kalau kataKunci sangat panjang
        int kiri = sisaLebar / 2;
        int kanan = sisaLebar - kiri;

        cout << string(kiri, '=') << judul << string(kanan, '=') << endl;
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "|| "
            << left << setw(colNo) << "No" << " | "
            << left << setw(colNama) << "Nama Produk" << " | "
            << left << setw(colKat) << "Kategori" << " | "
            << right << setw(colStok) << "Stok" << " | "
            << right << setw(colHarga) << "Harga Satuan per Kg" << " ||" << endl;
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
                    string stokStr = to_string(listMitra[m].data[i].stok) + " kg";
                    cout << "|| "
                        << left << setw(colNo) << nomor << " | "
                        << left << setw(colNama) << listMitra[m].data[i].namaProduk << " | "
                        << left << setw(colKat) << namaKategori(listMitra[m].data[i].kategori) << " | "
                        << right << setw(colStok) << stokStr << " | "
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
    if (program == 'n' || program == 'N')
    {
        return pembelian();
    }
}

void filter() {
    int colNo = 4, colNama = 25, colKat = 12, colStok = 8, colHarga = 20; // colHarga disamakan
    int lebarKotak = 3 + colNo + 3 + colNama + 3 + colKat + 3 + colStok + 3 + colHarga + 3;
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
            << right << setw(colHarga) << "Harga Satuan per Kg" << " ||" << endl;
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

        bool adaProduk = false;
        int nomor = 1;
        for (size_t m = 0; m < listMitra.size(); m++) {
            for (int i = listMitra[m].depan; i < listMitra[m].belakang; i++) {
                if (listMitra[m].data[i].kategori != kategoriDipilih) continue;
                adaProduk = true;
                string hargaStr = "Rp " + to_string(listMitra[m].data[i].harga);
                string stokStr = to_string(listMitra[m].data[i].stok) + " kg";
                cout << "|| "
                    << left << setw(colNo) << nomor << " | "
                    << left << setw(colNama) << listMitra[m].data[i].namaProduk << " | "
                    << left << setw(colKat) << namaKategori(listMitra[m].data[i].kategori) << " | "
                    << right << setw(colStok) << stokStr << " | "
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
	if (program == 'n' || program == 'N')
	{
		return pembelian();
	}
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

    for (size_t m = 0; m < listMitra.size(); m++)
    {
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
        Produk& produkPilihan = listMitra[idxMitra].data[idxProduk];
         cout << "Sisa Produk      : " << produkPilihan.stok << " kg" << endl;
        cout << "Harga Produk Rp. : " << produkPilihan.harga << endl;
        cout << "Banyak Pembelian : ";
        string inputBanyak;
        cin >> inputBanyak;
        banyak = stoi(inputBanyak); // konversi manual ke int, karena kita baca sebagai string dulu

        // Pindahkan kursor: naik 1 baris (balik ke baris "Banyak Pembelian : "),
        // lalu geser ke kanan sejauh panjang teks label + angka yang tadi diketik,
        // baru cetak " kg" supaya nempel di ujung angka
        int panjangLabel = strlen("Banyak Pembelian : ");
        cout << "\033[1A" << "\033[" << (panjangLabel + inputBanyak.length()) << "C" << " kg" << endl;

        if (banyak <= produkPilihan.stok) {
            cout << "Total Harga  : Rp. " << produkPilihan.harga * banyak << endl;
            produkPilihan.stok -= banyak;

            KeranjangDLL* keranjang = cariAtauBuatKeranjang();
            if (!keranjang) {
                cout << "\nMaaf, kapasitas keranjang sudah penuh!" << endl;
                produkPilihan.stok += banyak;
                system("PAUSE");
                return;
            }
            if (keranjang->jumlahItem >= MAX_ITEM_KERANJANG) {
                cout << "\nMaaf, keranjang Anda sudah penuh!" << endl;
                produkPilihan.stok += banyak;
            }
            else {
                ItemKeranjang item;
                item.namaProduk = produkPilihan.namaProduk;
                item.hargaSatuan = produkPilihan.harga;
                item.banyakPembelian = banyak;
                item.subTotal = produkPilihan.harga * banyak;
                tambahKeKeranjang(keranjang, item);
                cout << "\nPembelian berhasil dimasukkan ke keranjang!" << endl;
            }
        }
        else {
            cout << "\nMaaf, stok tidak mencukupi!" << endl;
        }
    }
    else {
        cout << "\nMaaf, produk tidak ditemukan di antrean mitra mana pun." << endl;
    }

    cout << "\nLanjutkan pembelian? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') return beli();
}

void pembelian() {
    tampilProduk();
    int colNo = 4;
    int colNama = 25;
    int colKat = 12;
    int colStok = 8;
    int colHarga = 20;
    int lebarKotak = 3 + colNo + 3 + colNama + 3 + colKat + 3 + colStok + 3 + colHarga + 3;
    cout << string(lebarKotak, '=') << endl;
    cout << "1. Cari" << endl;
    cout << "2. Filter" << endl;
    cout << "3. Beli" << endl;
    cout << "4. Keluar" << endl;
    cout << string(lebarKotak, '=') << endl;
    int pil;
    cout << "Pilih Menu yang Anda Inginkan : ";
    cin >> pil;
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
    char program;
    do {
        system("cls");
        int colNo = 4;
        int colNama = 30;
        int colJumlah = 15;
        int colHargaSatuan = 18;
        int colTotal = 15;

        int lebarKotak = 3 + colNo + 3 + colNama + 3 + colJumlah + 3 + colHargaSatuan + 3 + colTotal + 3;

        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "|| "
            << left << setw(colNo) << "No" << " | "
            << left << setw(colNama) << "Nama Produk" << " | "
            << right << setw(colJumlah) << "Jumlah" << " | "
            << right << setw(colHargaSatuan) << "Harga per Kg" << " | "
            << right << setw(colTotal) << "Total Harga" << " ||" << endl;
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

        KeranjangDLL* isiKeranjang = cariKeranjangAktif();

        if (isiKeranjang && isiKeranjang->head) {
            int nomor = 1;
            NodeKeranjang* cur = isiKeranjang->head;
            while (cur) {
                string jumlahStr = to_string(cur->item.banyakPembelian) + " kg";
                string hargaSatuanStr = "Rp " + to_string(cur->item.hargaSatuan);
                string totalStr = "Rp " + to_string(cur->item.subTotal);
                cout << "|| "
                    << left << setw(colNo) << nomor << " | "
                    << left << setw(colNama) << cur->item.namaProduk << " | "
                    << right << setw(colJumlah) << jumlahStr << " | "
                    << right << setw(colHargaSatuan) << hargaSatuanStr << " | "
                    << right << setw(colTotal) << totalStr << " ||" << endl;
                cur = cur->next;
                nomor++;
            }
            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

            string grandTotalStr = "Rp " + to_string(isiKeranjang->totalHarga);
            int lebarKiri = colNo + 3 + colNama + 3 + colJumlah + 3 + colHargaSatuan;
            cout << "|| " << left << setw(lebarKiri) << "GRAND TOTAL:"
                << " | " << right << setw(colTotal) << grandTotalStr << " ||" << endl;
        }
        else {
            cout << "|| " << left << setw(lebarKotak - 6) << "Keranjang belanja Anda masih kosong." << " ||" << endl;
        }

        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

        string menu[] = { "1. Checkout", "2. Tambah Produk", "3. Hapus Produk", "4. Keluar" };
        int jumlahMenu = 4;
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
            if (!isiKeranjang || !isiKeranjang->head) {
                cout << "\n[!] Keranjang belanja Anda masih kosong!" << endl;
                cout << "Kembali ke halaman menu? (y/n): ";
                cin >> program;
                if (program == 'y' || program == 'Y') return menuCustomer();
                else continue; // <-- diperbaiki dari "return keranjang();"
            }

            time_t waktuSekarang = time(0);
            string teksWaktu = ctime(&waktuSekarang);
            if (!teksWaktu.empty() && teksWaktu.back() == '\n') teksWaktu.pop_back();

            isiKeranjang->isCheckedOut = true;
            isiKeranjang->waktuCheckout = teksWaktu;

            Pembelian p = keranjangKePembelian(isiKeranjang);
            if (jumlahPembelian < MAX_PEMBELIAN) {
                daftarPembelian[jumlahPembelian++] = p;
            }

            Jadwal(listKurir, p);
            listOrder(listOrderMitra, p);

            kosongkanKeranjang(isiKeranjang);
            cout << "\nCheckout berhasil! Pesanan Anda sedang diproses." << endl;
            cout << "Kembali ke halaman menu? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y') return menuCustomer();
            else continue; // <-- diperbaiki
        }
        case 2: // ── TAMBAH PRODUK ──
            beli();
            break;

        case 3: // ── HAPUS ITEM ──
        {
            if (!isiKeranjang || !isiKeranjang->head) {
                cout << "\n[!] Keranjang kosong, tidak ada yang bisa dihapus." << endl;
                system("PAUSE"); break;
            }
            int nomorHapus;
            cout << "\nMasukkan nomor item yang ingin dihapus: ";
            cin >> nomorHapus;

            NodeKeranjang* target = isiKeranjang->head;
            for (int i = 1; i < nomorHapus && target; i++)
                target = target->next;

            if (!target) {
                cout << "Nomor item tidak valid!" << endl;
            }
            else {
                for (size_t m = 0; m < listMitra.size(); m++) {
                    for (int i = listMitra[m].depan; i < listMitra[m].belakang; i++) {
                        if (listMitra[m].data[i].namaProduk == target->item.namaProduk) {
                            listMitra[m].data[i].stok += target->item.banyakPembelian;
                            break;
                        }
                    }
                }
                cout << "Item \"" << target->item.namaProduk << "\" dihapus dari keranjang." << endl;
                hapusDariKeranjang(isiKeranjang, target);
            }
            cout << "Kembali ke halaman menu? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y') return menuCustomer();
            else continue; // <-- diperbaiki, ini yang tadinya bikin glitch/crash saat hapus produk
        }

        case 4:
            return;

        default:
            cout << "\nPilihan tidak valid! Silakan coba lagi." << endl;
            cout << "Kembali ke halaman menu? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y') return menuCustomer();
            else continue; // <-- diperbaiki
        }
    } while (pil != 4);
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
        cout << "\nFile CSV berhasil disimpan di: " << lokasi_file << endl;
    }
    else {
        cout << "\nGagal membuat file!" << endl;
    }

    char program; // <-- FIX: variabel ini tadinya belum dideklarasikan
    cout << "Kembali ke halaman menu? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y')
    {
        return;
    }
    else
    {
        return invo();
    }
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
    Pembelian p = daftarPembelian[indexDitemukan];
    int    idTransaksi = indexDitemukan + 1;
    string namaMitra = "Toko Mitra Resmi";

    // Pengaman: potong teks yang lebih panjang dari lebar kolomnya,
    // supaya tabel tidak pernah rusak walau data (alamat/username/angka) panjang
    auto potong = [](string teks, int lebarKolom) {
        if ((int)teks.length() > lebarKolom) {
            if (lebarKolom > 3) return teks.substr(0, lebarKolom - 3) + "...";
            return teks.substr(0, lebarKolom);
        }
        return teks;
        };

    // ── Kolom tabel item (4 kolom): Qty, Item, Harga Satuan, Total.
    int colQty = 7;
    int colItem = 25;
    int colHargaSatuan = 18;
    int colTotal = 15;
    int lebarKotak = 3 + colQty + 3 + colItem + 3 + colHargaSatuan + 3 + colTotal + 3; // = 80

    // ── Kolom baris info (Tanggal/ID, Nama Mitra/Pembeli, Alamat/No HP).
    //    Baris info sekarang pakai separator tengah " || " (simetris dengan " | " di tabel item),
    //    jadi total barisnya = 3(kiri) + label1 + value1 + 4(tengah) + label2 + value2 + 3(kanan) = lebarKotak
    int colLabel1 = 15;
    int colValue1 = 20;
    int colLabel2 = 16;
    int colValue2 = lebarKotak - 10 - colLabel1 - colValue1 - colLabel2;

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << "|| " << left << setw(lebarKotak - 6) << " INVOICE" << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    cout << "|| " << left << setw(colLabel1) << "Tanggal :" << setw(colValue1) << potong(p.waktuCheckout, colValue1)
        << " || " << left << setw(colLabel2) << "ID Transaksi :" << setw(colValue2) << potong(to_string(idTransaksi), colValue2) << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    cout << "|| " << left << setw(colLabel1) << "Nama Mitra :" << setw(colValue1) << potong(namaMitra, colValue1)
        << " || " << left << setw(colLabel2) << "Nama Pembeli :" << setw(colValue2) << potong(p.daftarUser[0].username, colValue2) << " ||" << endl;
    cout << "|| " << left << setw(colLabel1) << "Alamat :" << setw(colValue1) << potong(p.daftarUser[0].alamat, colValue1)
        << " || " << left << setw(colLabel2) << "No HP :" << setw(colValue2) << potong(p.daftarUser[0].nohp, colValue2) << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    // ── Header tabel item
    cout << "|| "
        << left << setw(colQty) << "QTY" << " | "
        << left << setw(colItem) << "ITEM" << " | "
        << right << setw(colHargaSatuan) << "Harga per Kg" << " | "
        << right << setw(colTotal) << "Total Harga" << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    for (int i = 0; i < p.jumlahBarang; i++) {
        string qtyStr = to_string(p.daftarBarang[i].banyakPembelian) + " kg";
        string hargaSatuanStr = "Rp " + to_string(p.daftarBarang[i].hargaSatuan);
        string totalStr = "Rp " + to_string(p.daftarBarang[i].subTotal);
        cout << "|| "
            << left << setw(colQty) << potong(qtyStr, colQty) << " | "
            << left << setw(colItem) << potong(p.daftarBarang[i].namaProduk, colItem) << " | "
            << right << setw(colHargaSatuan) << potong(hargaSatuanStr, colHargaSatuan) << " | "
            << right << setw(colTotal) << potong(totalStr, colTotal) << " ||" << endl;
    }
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    // Baris footer: label "Item Count" menempati 3 kolom kiri, total di kolom paling kanan
    string totalStr = "Rp " + to_string(p.totalHargaSemua);
    int lebarKiri = colQty + 3 + colItem + 3 + colHargaSatuan;
    string itemCountStr = "Item Count : " + to_string(p.jumlahBarang) + " produk";
    cout << "|| " << left << setw(lebarKiri) << potong(itemCountStr, lebarKiri)
        << " | " << right << setw(colTotal) << potong(totalStr, colTotal) << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl << endl;

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
    int colNo = 4;
    int colCustomer = 15;
    int colAlamat = 25;
    int colStatus = 42; // diperbesar supaya cukup untuk teks status terpanjang

    int lebarKotak = 3 + colNo + 3 + colCustomer + 3 + colAlamat + 3 + colStatus + 3;

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

            // Pengaman: potong teks yang lebih panjang dari lebar kolomnya,
            // supaya tabel TIDAK PERNAH rusak walau datanya (username, alamat,
            // atau status) ternyata lebih panjang dari yang diperkirakan
            auto potong = [](string teks, int lebarKolom) {
                if ((int)teks.length() > lebarKolom) {
                    return teks.substr(0, lebarKolom - 3) + "...";
                }
                return teks;
                };

            string customerStr = potong(listKurir[i].beli.daftarUser->username, colCustomer);
            string alamatStr = potong(listKurir[i].beli.daftarUser->alamat, colAlamat);
            string statusStr = potong(statusToString(listKurir[i].status), colStatus);

            cout << "|| "
                << left << setw(colNo) << nomor << " | "
                << left << setw(colCustomer) << customerStr << " | "
                << left << setw(colAlamat) << alamatStr << " | "
                << left << setw(colStatus) << statusStr << " ||" << endl;
            nomor++;
        }
    }
    if (!adaData)
        cout << "|| " << left << setw(lebarKotak - 6) << "Belum ada data pengiriman untuk akun Anda." << " ||" << endl;

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl << endl;
    cout << "Tekan Enter untuk kembali ke halaman menu...";
    cin.get(); cin.get();
}