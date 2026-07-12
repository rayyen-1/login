#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <vector>

using namespace std;

#include "user.h"       
#include "produk.h"     
#include "beli.h"       
#include "mitra.h"      
#include "customer.h"   
#include "kurir.h"
#include "menu.h"       

Queue queue;

vector<Queue> listOrderMitra;

// Mencari index milik mitra yang sedang login di dalam listMitra (katalog produk).
// Jika mitra ini belum pernah punya katalog (baru registrasi), buatkan entri baru
// supaya produk yang ditambahkannya langsung tersambung ke listMitra yang dipakai
// customer untuk belanja (sebelumnya semua fungsi produk memakai variabel global
// "queue" yang terpisah total dari listMitra, jadi produk yang diinput mitra
// tidak pernah bisa dibeli oleh customer).
int cariAtauBuatIndexMitraAktif() {
    for (size_t i = 0; i < listMitra.size(); i++) {
        if (listMitra[i].mitra.username == userAktif->username) {
            return (int)i;
        }
    }

    Queue queueBaru;
    queueBaru.depan = 0;
    queueBaru.belakang = 0; // 0 = belum ada produk (konsisten dgn konvensi di Login.cpp & beli())
    queueBaru.statusMitra = diproses;
    queueBaru.mitra = *userAktif;
    listMitra.push_back(queueBaru);
    return (int)listMitra.size() - 1;
}

string statusToString(Status statusMitra) {
    if (statusMitra == diproses) {
        return "Sedang diproses (Dalam proses pemaketan)";
    }
    else if (statusMitra == diserahkan_ke_kurir) {
        return "Pesanan diberikan ke kurir";
    }
    return "Status Tidak Diketahui";
}

// 2. Implementasi fungsi update
void update(Queue& i, int newStatus) {
    if (newStatus == 1) {
        i.statusMitra = diproses;
    }
    else if (newStatus == 2) {
        i.statusMitra = diserahkan_ke_kurir;
    }
}

Queue listOrder(vector<Queue>& data, Pembelian beli) {
    Queue orderBaru;

    orderBaru.depan = -1;
    orderBaru.belakang = -1;
    orderBaru.statusMitra = diproses;
    orderBaru.beli = beli;

    data.push_back(orderBaru);

    return orderBaru;
}

bool isEmpty() {
    int idx = cariAtauBuatIndexMitraAktif();
    return (listMitra[idx].belakang == listMitra[idx].depan);
}

bool isFull() {
    int idx = cariAtauBuatIndexMitraAktif();
    return (listMitra[idx].belakang >= MAX_QUEUE);
}

void inisialisasi() {
    queue.depan = queue.belakang = -1;
    int idx = cariAtauBuatIndexMitraAktif();
    listMitra[idx].depan = 0;
    listMitra[idx].belakang = 0;
}

// Mengurutkan array produk (dari index "mulai" sampai sebelum "akhir") secara
// A-Z berdasarkan nama produk, tidak peduli huruf besar/kecil. Pakai selection
// sort: cari produk dengan nama "terkecil" secara alfabet di sisa data, lalu
// tukar ke posisi depan. Diulang sampai semua bagian terurut.
void sortProdukAZ(Produk data[], int mulai, int akhir) {
    for (int i = mulai; i < akhir - 1; i++) {
        int idxTerkecil = i;

        for (int j = i + 1; j < akhir; j++) {
            string namaJ = data[j].namaProduk;
            string namaTerkecil = data[idxTerkecil].namaProduk;

            for (size_t k = 0; k < namaJ.size(); k++) namaJ[k] = tolower(namaJ[k]);
            for (size_t k = 0; k < namaTerkecil.size(); k++) namaTerkecil[k] = tolower(namaTerkecil[k]);

            if (namaJ < namaTerkecil) {
                idxTerkecil = j;
            }
        }

        if (idxTerkecil != i) {
            Produk temp = data[i];
            data[i] = data[idxTerkecil];
            data[idxTerkecil] = temp;
        }
    }
}

// Menampilkan gabungan katalog produk dari SEMUA mitra. Dipakai customer saat
// belanja (pembelian() di customer.cpp) supaya produk yang diinput oleh mitra
// manapun bisa langsung terlihat dan dibeli.
void tampilProduk() {
    system("cls");

    int colNo = 4;
    int colNama = 25;
    int colKat = 12;
    int colStok = 8;
    int colHarga = 20; // diperbesar dari 8 -> 20 supaya muat "Harga Satuan per Kg"

    // lebarKotak dihitung otomatis dari total lebar kolom + separator,
    // supaya tidak perlu dihitung manual tiap kali kolom berubah.
    // Rumus: "|| " (3) + colNo + " | "(3) + colNama + " | "(3) + colKat + " | "(3) + colStok + " | "(3) + colHarga + " ||"(3)
    int lebarKotak = 3 + colNo + 3 + colNama + 3 + colKat + 3 + colStok + 3 + colHarga + 3;

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << "|| "
        << left << setw(colNo) << "No" << " | "
        << left << setw(colNama) << "Nama Produk" << " | "
        << left << setw(colKat) << "Kategori" << " | "
        << right << setw(colStok) << "Stok" << " | "
        << right << setw(colHarga) << "Harga Satuan per Kg" << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    vector<Produk> gabungan;
    for (size_t m = 0; m < listMitra.size(); m++) {
        for (int i = listMitra[m].depan; i < listMitra[m].belakang; i++) {
            gabungan.push_back(listMitra[m].data[i]);
        }
    }

    sortProdukAZ(gabungan.data(), 0, (int)gabungan.size());

    if (gabungan.empty()) {
        cout << "|| " << left << setw(lebarKotak - 6) << "Belum ada produk tersedia." << " ||" << endl;
    }
    else {
        for (size_t n = 0; n < gabungan.size(); n++) {
            string hargaStr = "Rp " + to_string(gabungan[n].harga);
            string stokStr = to_string(gabungan[n].stok) + " kg";
            cout << "|| "
                << left << setw(colNo) << n + 1 << " | "
                << left << setw(colNama) << gabungan[n].namaProduk << " | "
                << left << setw(colKat) << namaKategori(gabungan[n].kategori) << " | "
                << right << setw(colStok) << stokStr << " | "
                << right << setw(colHarga) << hargaStr << " ||" << endl;
        }
    }

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << endl;
}

// Menampilkan HANYA produk milik mitra yang sedang login. Dipakai untuk
// input/update/hapus produk supaya nomor yang ditampilkan sesuai dengan
// katalog milik mitra itu sendiri.
void tampilProdukSaya() {
    system("cls");

    // Pengaman: potong teks yang lebih panjang dari lebar kolomnya
    auto potong = [](string teks, int lebarKolom) {
        if ((int)teks.length() > lebarKolom) {
            if (lebarKolom > 3) return teks.substr(0, lebarKolom - 3) + "...";
            return teks.substr(0, lebarKolom);
        }
        return teks;
        };

    int colNo = 4;
    int colNama = 25;
    int colKat = 12;
    int colStok = 8;
    int colHarga = 20; // diperbesar supaya muat header "Harga per Satuan Kg"

    // lebarKotak dihitung otomatis dari kolom, jadi selalu konsisten
    int lebarKotak = 3 + colNo + 3 + colNama + 3 + colKat + 3 + colStok + 3 + colHarga + 3;

    int idx = cariAtauBuatIndexMitraAktif();

    // Urutkan produk milik mitra ini A-Z berdasarkan nama sebelum ditampilkan
    sortProdukAZ(listMitra[idx].data, listMitra[idx].depan, listMitra[idx].belakang);

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << "|| "
        << left << setw(colNo) << "No" << " | "
        << left << setw(colNama) << "Nama Produk" << " | "
        << left << setw(colKat) << "Kategori" << " | "
        << right << setw(colStok) << "Stok" << " | "
        << right << setw(colHarga) << "Harga per Satuan Kg" << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    if (isEmpty()) {
        cout << "|| " << left << setw(lebarKotak - 6) << "Belum ada produk tersedia." << " ||" << endl;
    }
    else {
        for (int i = listMitra[idx].depan; i < listMitra[idx].belakang; i++) {
            string hargaStr = "Rp " + to_string(listMitra[idx].data[i].harga);
            string stokStr = to_string(listMitra[idx].data[i].stok) + " kg";
            cout << "|| "
                << left << setw(colNo) << potong(to_string(i + 1), colNo) << " | "
                << left << setw(colNama) << potong(listMitra[idx].data[i].namaProduk, colNama) << " | "
                << left << setw(colKat) << potong(namaKategori(listMitra[idx].data[i].kategori), colKat) << " | "
                << right << setw(colStok) << potong(stokStr, colStok) << " | "
                << right << setw(colHarga) << potong(hargaStr, colHarga) << " ||" << endl;
        }
    }

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << endl;
}

void updateProduk() {
    system("cls");
    char program;
    cout << "=== UPDATE PRODUK ===" << endl << endl;

    if (isEmpty()) {
        cout << "Daftar produk masih kosong!" << endl << endl;
        
    }

    int idx = cariAtauBuatIndexMitraAktif();

    tampilProdukSaya();
    cout << endl;

    int nomor;
    cout << "Masukkan nomor produk yang ingin diupdate: ";
    cin >> nomor;
    nomor--;

    if (nomor < listMitra[idx].depan || nomor >= listMitra[idx].belakang) {
        cout << "Nomor tidak valid!" << endl << endl;
        system("PAUSE");
        return;
    }

    cout << endl;
    cout << "Produk : " << listMitra[idx].data[nomor].namaProduk << endl;
    cout << "Stok sekarang  : " << listMitra[idx].data[nomor].stok << " Kg" << endl;
    cout << "Harga sekarang : Rp " << listMitra[idx].data[nomor].harga << endl;
    cout << endl;

    cout << "Stok baru  : "; cin >> listMitra[idx].data[nomor].stok;
    cout << "\033[A\033[2K";  // naik 1 baris, hapus isinya
    cout << "Stok baru  : " << listMitra[idx].data[nomor].stok << " Kg" << endl;

    cout << "Harga baru : "; cin >> listMitra[idx].data[nomor].harga;

    cout << endl;
    cout << "Produk berhasil diupdate!" << endl << endl;

    cout << "kembali ke halaman menu? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return menuMitra();
    }
    else
    {
		return updateProduk();
    }
}

void hapusProduk()
{
    system("cls");
    cout << "============= HAPUS PRODUK =============" << endl << endl;
    if (isEmpty())
    {
        cout << "=== Daftar produk masih kosong! ===" << endl << endl;
        system("pause");
        return;
    }

    int idx = cariAtauBuatIndexMitraAktif();
    char program;
    tampilProdukSaya();
    cout << endl;
    int nomor;
    cout << "Masukkan nomor produk yang ingin dihapus: ";
    cin >> nomor;
    nomor--;

    if (nomor < listMitra[idx].depan || nomor >= listMitra[idx].belakang)
    {
        cout << "Nomor tidak valid!" << endl << endl;
        cout << "kembali ke halaman menu? (y/n): ";
        cin >> program;
        if (program == 'y' || program == 'Y') {
            return menuMitra();
        }
        else {
            return hapusProduk();
        }
    }

    for (int i = nomor; i < listMitra[idx].belakang - 1; i++)
    {
        listMitra[idx].data[i] = listMitra[idx].data[i + 1];
    }
    listMitra[idx].belakang--;

    cout << endl;
    cout << "=== Produk berhasil dihapus! ===" << endl << endl;
    cout << "Kembali ke halaman menu? (y/n): ";
    
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return menuMitra();
    }
    else {
        return hapusProduk();
    }
}

void exportcsv_m() {

    string tanggalDiproses[MAX_PEMBELIAN];
    int jumlahTanggalDiproses = 0;

    for (int i = 0; i < jumlahPembelian; i++) {
        if (!daftarPembelian[i].isCheckedOut) continue;

        // Ambil bagian tanggalnya saja dari ctime (Format asli: "Mon Jun 29 11:03:42 2026")
        string fullWaktu = daftarPembelian[i].waktuCheckout;
        string tanggalSaja = "";
        if (fullWaktu.length() >= 24) {
            tanggalSaja = fullWaktu.substr(0, 10) + fullWaktu.substr(19, 5); // Hasil: "Mon Jun 29 2026"
        }
        else {
            tanggalSaja = fullWaktu;
        }

        // Cek apakah tanggal ini sudah pernah digambar kotaknya

        bool sudahAda = false;
        for (int d = 0; d < jumlahTanggalDiproses; d++) {
            if (tanggalDiproses[d] == tanggalSaja) {
                sudahAda = true;
                break;
            }
        }
        if (sudahAda) continue; // Kalau sudah, skip ke transaksi berikutnya

        // Catat tanggal baru yang siap diproses
        tanggalDiproses[jumlahTanggalDiproses++] = tanggalSaja;

        int totalHargaTanggal = 0;

        string lokasi_file = "laporan_mitra.csv";
        ofstream file(lokasi_file);

        // 2. Cek apakah file benar-benar berhasil dibuka/dibuat
        if (file.is_open()) {

            // Header CSV
            file << "Tanggal,Item,Jumlah Produk,Harga\n";

            for (int j = 0; j < jumlahPembelian; j++) {
                if (!daftarPembelian[j].isCheckedOut) continue;

                string fullWaktuJ = daftarPembelian[j].waktuCheckout;
                string tanggalSajaJ = (fullWaktuJ.length() >= 24) ? (fullWaktuJ.substr(0, 10) + fullWaktuJ.substr(19, 5)) : fullWaktuJ;

                // Jika tanggal cocok, bongkar isi keranjang belanjaannya ke tabel ini
                if (tanggalSajaJ == tanggalSaja) {
                    for (int b = 0; b < daftarPembelian[j].jumlahBarang; b++) {
                        file << tanggalSaja << ","
                            << daftarPembelian[j].daftarBarang[b].namaProduk << ","
                            << daftarPembelian[j].daftarBarang[b].banyakPembelian << ","
                            << daftarPembelian[j].daftarBarang[b].subTotal << "\n";
                    }
                }
            }

            file.close();
            cout << "File CSV berhasil disimpan " << endl;
        }
        else {
            cout << "Gagal membuat file!" << endl;
        }
        char program;
        cout << "kembali ke halaman menu? (y/n): ";
        cin >> program;
        if (program == 'y' || program == 'Y') {
            return menuMitra();
        }
        else {
            return exportcsv_m();
        }
    }
}

void inputProduk() {
    system("cls");
    char program;
    string namaProduk;
    int stock, harga, kategori;
    cout << "===INPUT PRODUK===" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // buang sisa newline di buffer
    cout << "Nama Produk: ";
    getline(cin, namaProduk);

    cout << "Harga per satuan Kg: "; cin >> harga;
    cout << "Stock (Kg): "; cin >> stock;
    cout << "===List Kategori==" << endl;
    cout << "1. Sayur" << endl;
    cout << "2. Buah" << endl;
    cout << "3. Bumbu" << endl;
    cout << "Masukkan pilihan: "; cin >> kategori;

    // ... sisanya tetap sama

    int idx = cariAtauBuatIndexMitraAktif();

    if (listMitra[idx].belakang >= MAX_QUEUE) {
        cout << "Gagal menambahkan! Produk sudah penuh!" << endl;
        return;
    }

    Produk produkBaru;
    produkBaru.namaProduk = namaProduk;
    produkBaru.harga = harga;
    produkBaru.stok = stock;

    // Pilihan menu: 1. Sayur, 2. Buah, 3. Bumbu -> KategoriProduk: SAYUR=1, BUAH=2, LAINNYA=4
    // static_cast langsung ke KategoriProduk salah untuk pilihan 3 (nilai 3 tidak
    // punya enumerator), sehingga produk "Bumbu" tersimpan dengan kategori tak valid.
    if (kategori == 1) {
        produkBaru.kategori = SAYUR;
    }
    else if (kategori == 2) {
        produkBaru.kategori = BUAH;
    }
    else {
        produkBaru.kategori = LAINNYA;
    }

    listMitra[idx].data[listMitra[idx].belakang] = produkBaru; // Masukkan data produk ke katalog mitra ini
    listMitra[idx].belakang++; // Naikkan jumlah produk

    cout << "Produk berhasil ditambahkan!" << endl;


    cout << "Mau menambahkan produk lain? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return inputProduk();
    }
    else {
        return menuMitra();
    }
}



void invoice() {
    system("cls");
    cout << "=== INVOICE PESANAN MASUK ===" << endl << endl;
    char program;

    // Pengaman: potong teks yang lebih panjang dari lebar kolomnya
    auto potong = [](string teks, int lebarKolom) {
        if ((int)teks.length() > lebarKolom) {
            if (lebarKolom > 3) return teks.substr(0, lebarKolom - 3) + "...";
            return teks.substr(0, lebarKolom);
        }
        return teks;
        };

    // 1. Cek apakah sudah ada transaksi yang masuk
    if (jumlahPembelian == 0) {
        cout << "Belum ada pesanan masuk!" << endl << endl;
        cout << "kembali ke halaman menu? (y/n): ";
        cin >> program;
        if (program == 'y' || program == 'Y') {
            return menuMitra();
        }
        else {
            return invoice();
        }
    }

    // Array bantuan untuk mencatat tanggal yang sudah diproses agar tidak double
    string tanggalDiproses[MAX_PEMBELIAN];
    int jumlahTanggalDiproses = 0;

    for (int i = 0; i < jumlahPembelian; i++) {
        if (!daftarPembelian[i].isCheckedOut) continue;

        // Ambil bagian tanggalnya saja dari ctime (Format asli: "Mon Jun 29 11:03:42 2026")
        string fullWaktu = daftarPembelian[i].waktuCheckout;
        string tanggalSaja = "";
        if (fullWaktu.length() >= 24) {
            tanggalSaja = fullWaktu.substr(0, 10) + fullWaktu.substr(19, 5); // Hasil: "Mon Jun 29 2026"
        }
        else {
            tanggalSaja = fullWaktu;
        }

        // Cek apakah tanggal ini sudah pernah digambar kotaknya
        bool sudahAda = false;
        for (int d = 0; d < jumlahTanggalDiproses; d++) {
            if (tanggalDiproses[d] == tanggalSaja) {
                sudahAda = true;
                break;
            }
        }
        if (sudahAda) continue; // Kalau sudah, skip ke transaksi berikutnya

        // Catat tanggal baru yang siap diproses
        tanggalDiproses[jumlahTanggalDiproses++] = tanggalSaja;

        int totalHargaTanggal = 0;

        // 3. Cetak Header Atas sesuai gaya desain minimalismu
        cout << "+--------------------------------------------------+" << endl;
        cout << "| Tanggal : " << left << setw(38) << tanggalSaja << " |" << endl;
        cout << "+--------------------------------------------------+" << endl;
        cout << "| Qty    | Item             | Harga                |" << endl;
        cout << "+--------+------------------+----------------------+" << endl;

        // 4. Looping Kedua: Ambil semua barang yang dibeli di tanggal yang sama
        for (int j = 0; j < jumlahPembelian; j++) {
            if (!daftarPembelian[j].isCheckedOut) continue;

            string fullWaktuJ = daftarPembelian[j].waktuCheckout;
            string tanggalSajaJ = (fullWaktuJ.length() >= 24) ? (fullWaktuJ.substr(0, 10) + fullWaktuJ.substr(19, 5)) : fullWaktuJ;

            // Jika tanggal cocok, bongkar isi keranjang belanjaannya ke tabel ini
            if (tanggalSajaJ == tanggalSaja) {
                for (int b = 0; b < daftarPembelian[j].jumlahBarang; b++) {
                    cout << "| " << left << setw(7) << daftarPembelian[j].daftarBarang[b].banyakPembelian
                        << "| " << left << setw(17) << potong(daftarPembelian[j].daftarBarang[b].namaProduk, 17)
                        << "| Rp " << left << setw(17) << daftarPembelian[j].daftarBarang[b].subTotal << " |" << endl;
                }
                // Jumlahkan total harga semua keranjang di tanggal ini
                totalHargaTanggal += daftarPembelian[j].totalHargaSemua;
            }
        }

        // 5. Cetak Footer Total Harga per tanggal tersebut
        cout << "+--------+------------------+----------------------+" << endl;
        cout << "| Total  |                  | Rp " << left << setw(17) << totalHargaTanggal << " |" << endl;
        cout << "+--------+------------------+----------------------+" << endl << endl;
    }
    cout << "1. Export CSV " << endl;
    cout << "2. Kembali " << endl;
    int pilihan;
    cout << "Masukkan pilihan : "; cin >> pilihan;
    switch (pilihan) {
    case 1:
        exportcsv_m();
        break;
    case 2:
        return menuMitra();
        break;
    }
    cout << "kembali ke halaman menu? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return menuMitra();
    }
    else {
       return invoice();
    }
}



void informasi() {
    char program;
    system("cls");
    cout << "=== INFORMASI PELANGGAN ===" << endl << endl;

    // Pengaman: potong teks yang lebih panjang dari lebar kolomnya
    auto potong = [](string teks, int lebarKolom) {
        if ((int)teks.length() > lebarKolom) {
            if (lebarKolom > 3) return teks.substr(0, lebarKolom - 3) + "...";
            return teks.substr(0, lebarKolom);
        }
        return teks;
        };

    if (jumlahPembelian == 0) {
        cout << "Belum ada data pelanggan!" << endl << endl;
        cout << "kembali ke halaman menu? (y/n): ";
        cin >> program;
        if (program == 'y' || program == 'Y') {
            return menuMitra();
        }
        else {
            return informasi();
        }
    }
    else
    {
        cout << "+----+------------+-----------------+-----------+--------+--------------+" << endl;
        cout << "| No | Nama       | Alamat          | Barang    | Jumlah | Total        |" << endl;
        cout << "+----+------------+-----------------+-----------+--------+--------------+" << endl;

        int no = 0;
        for (int i = 0; i < jumlahPembelian; i++) {
            if (!daftarPembelian[i].isCheckedOut) continue;
            no++;
            cout << "| " << left << setw(3) << no
                << "| " << left << setw(11) << potong(daftarPembelian[i].daftarUser->username, 10)
                << "| " << left << setw(16) << potong(daftarPembelian[i].daftarUser->alamat, 15)
                << "| " << left << setw(10) << potong(daftarPembelian[i].daftarBarang->namaProduk, 9)
                << "| " << left << setw(7) << daftarPembelian[i].daftarBarang->banyakPembelian
                << "| Rp " << left << setw(9) << daftarPembelian[i].daftarBarang->subTotal
                << "|" << endl;
        }

        cout << "+----+------------+-----------------+-----------+--------+--------------+" << endl;
        cout << endl;

        cout << "Kembali ke halaman menu? (y/n): ";
        cin >> program;
        if (program == 'y' || program == 'Y') {
            return menuMitra();
        }
        else {
            return informasi();
        }
    }
}


void statusPengiriman() {
    int pilih;
    char program;
    do
    {
        system("cls");
        int lebarKotak = 85;
        string menu[] = {
            "1. Status Pesanan",
            "2. Update Status Pesanan",
            "3. Keluar"
        };

        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "|| " << left << setw(lebarKotak - 6) << "STATUS PESANAN" << " ||" << endl;
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "|| " << left << setw(lebarKotak - 6) << menu[i] << " ||" << endl;
        }
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            system("cls");
            cout << "=== DAFTAR STATUS PESANAN PRODUK ===" << endl;
            if (listOrderMitra.empty()) {
                cout << "Belum ada data pesanan saat ini." << endl;
            }
            else {
                for (size_t i = 0; i < listOrderMitra.size(); i++) {
                    cout << i + 1 << ". Pembelian oleh: " << (listOrderMitra)[i].beli.daftarUser->username// sesuaikan struct Pembelian Anda
                        << " | Status: " << statusToString((listOrderMitra)[i].statusMitra) << endl;
                }
            }
            cout << "========================================" << endl;
            cout << "kembali ke halaman menu status? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y')
            {
                return statusPengiriman();
            }
            else
            {
                return menuMitra();
            }

        case 2:
            system("cls");
            cout << "=== UPDATE STATUS PESANAN PRODUK ===" << endl;

            if (listOrderMitra.empty()) {
                cout << "Belum ada pesanan untuk produk Anda." << endl;
                cout << "kembali ke halaman menu status? (y/n): ";
                cin >> program;
                if (program == 'y' || program == 'Y') {
                    return statusPengiriman();
                }
                else
                {
                    return menuMitra();
                }
            }

            // Tampilkan semua daftar pengiriman yang dipegang kurir
            for (size_t i = 0; i < listOrderMitra.size(); i++) {
                cout << i + 1 << ". Pesanan ke-" << i + 1
                    << " | Status Saat Ini: " << statusToString((listOrderMitra)[i].statusMitra) << endl;
            }

            int pilihan, statusBaru;
            cout << "\nPilih nomor pesanan yang ingin di-update: ";
            cin >> pilihan;

            if (pilihan > 0 && pilihan <= (int)listOrderMitra.size()) {
                cout << "Pilih Status Baru:\n1. Sedang diproses (Dalam proses pemaketan)\n2. Pesanan diberikan ke kurir\nPilihan status (1/2): ";
                cin >> statusBaru;

                // Memanggil fungsi asli dari kurir.h (by reference menggunakan index vector)
                update((listOrderMitra)[pilihan - 1], statusBaru);

                cout << "\nStatus berhasil diperbarui menjadi: " << statusToString((listOrderMitra)[pilihan - 1].statusMitra) << endl;

                // Begitu mitra menyerahkan pesanan ke kurir, cocokkan pesanan ini dengan
                // entri pengiriman miliknya di listKurir (dicocokkan lewat username &
                // waktu checkout, karena keduanya berasal dari Pembelian yang sama),
                // lalu ubah statusnya dari "Sedang proses packing" jadi "Dalam Perjalanan".
                // Tanpa ini, kurir tidak akan pernah tahu paketnya sudah boleh diproses.
                if ((listOrderMitra)[pilihan - 1].statusMitra == diserahkan_ke_kurir) {
                    for (size_t k = 0; k < listKurir.size(); k++) {
                        if (listKurir[k].beli.daftarUser->username == (listOrderMitra)[pilihan - 1].beli.daftarUser->username
                            && listKurir[k].beli.waktuCheckout == (listOrderMitra)[pilihan - 1].beli.waktuCheckout
                            && listKurir[k].status == sedang_proses_packing) {
                            listKurir[k].status = dalam_perjalanan;
                            break;
                        }
                    }
                }
            }
            else {
                cout << "Pilihan nomor pesanan tidak valid!" << endl;
            }
            cout << "kembali ke halaman menu status? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y')
            {
                return statusPengiriman();
            }
            else
            {
				return menuMitra();
            }
            break;

        case 3:
            return menuMitra();
            break;
        }
    } while (pilih != 3);
}