#include "kurir.h"

Pengiriman Jadwal(vector<Pengiriman>& dataStorage, Pembelian beli) {
    Pengiriman pengirimanBaru;

    pengirimanBaru.status = dalam_perjalanan;
    pengirimanBaru.beli = beli;

    User userkurir;
    userkurir.as = kurir;
    pengirimanBaru.kurir = userkurir;

    dataStorage.push_back(pengirimanBaru);
    
    return pengirimanBaru;
}

void updateStatus(Pengiriman& p, int StatusBaru) {
    p.status = static_cast<StatusPengiriman>(StatusBaru);
}

vector<Pengiriman> *listKurir;

// Diubah agar Mitra bisa melihat semua status pengiriman saat ini
void statusPengirim() {
    int pilih;
    char program;
    do
    {
        system("cls");
        cout << "1. Status pengiriman" << endl;
        cout << "2. Update status" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            system("cls");
            cout << "=== DAFTAR STATUS PENGIRIMAN (MITRA) ===" << endl;
            if (listKurir->empty()) {
                cout << "Belum ada data pengiriman saat ini." << endl;
            }
            else {
                for (size_t i = 0; i < listKurir->size(); i++) {
                    cout << i + 1 << ". Pembelian oleh: " << (*listKurir)[i].beli.user // sesuaikan struct Pembelian Anda
                        << " | Status: " << statusToString((*listKurir)[i].status) << endl;
                }
            }
            cout << "========================================" << endl;
            cout << "kembali ke halaman menu status? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y')
            {
                return;
            }
            break;

        case 2:
            system("cls");
            cout << "=== UPDATE STATUS PENGIRIMAN ===" << endl;

            if (listKurir->empty()) {
                cout << "Belum ada tugas pengiriman untuk Anda." << endl;
                system("PAUSE");
                return menuKurir();
            }

            // Tampilkan semua daftar pengiriman yang dipegang kurir
            for (size_t i = 0; i < listKurir->size(); i++) {
                cout << i + 1 << ". Tugas Pengiriman ke-" << i + 1
                    << " | Status Saat Ini: " << statusToString((*listKurir)[i].status) << endl;
            }

            int pilihan, statusBaru;
            cout << "\nPilih nomor pengiriman yang ingin di-update: ";
            cin >> pilihan;

            if (pilihan > 0 && pilihan <= (int)listKurir->size()) {
                cout << "Pilih Status Baru:\n1. Sedang dikirim (Dalam Perjalanan)\n2. Pengiriman selesai\nPilihan status (1/2): ";
                cin >> statusBaru;

                // Memanggil fungsi asli dari kurir.h (by reference menggunakan index vector)
               updateStatus((*listKurir)[pilihan - 1], statusBaru);

                cout << "\nStatus berhasil diperbarui menjadi: " << statusToString((*listKurir)[pilihan - 1].status) << endl;
            }
            else {
                cout << "Pilihan nomor pengiriman tidak valid!" << endl;
            }
            cout << "kembali ke halaman menu status? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y')
            {
                return;
            }
            break;

        case 3:
            return menuKurir();
            break;
        }
    } while (pilih != 3);
}

// Fungsi pembungkus jadwal pengiriman untuk Kurir (Case 1 di menuKurir)
void jadwalPengirim() {
    char program;
    system("cls");
    cout << "=== AMBIL JADWAL PENGIRIMAN ===" << endl;

    // 1. Validasi apakah ada data pembelian di sistem
    if (jumlahPembelian == 0) {
        cout << "Belum ada transaksi pembelian di dalam sistem saat ini." << endl;
        cout << "\nKembali ke halaman menu? (y/n): ";
        cin >> program;
        if (program == 'y' || program == 'Y') {
            return menuKurir();
        }
    }

    // 2. Tampilkan semua daftar pembelian yang SUDAH CHECKOUT secara dinamis
    cout << "Daftar Pembelian yang Siap Dikirim:" << endl;
    cout << "----------------------------------------------------" << endl;

    int nomorUrut = 1;
    int indeksMapping[MAX_PEMBELIAN]; // Untuk mencatat indeks asli dari daftarPembelian

    for (int i = 0; i < jumlahPembelian; i++) {
        // Hanya tampilkan jika customer sudah checkout dan belum diambil kurir lain
        if (daftarPembelian[i].isCheckedOut) {
            cout << nomorUrut << ". Customer: " << daftarPembelian[i].user
                << " | Total Item: " << daftarPembelian[i].jumlahBarang
                << " | Total Harga: Rp" << daftarPembelian[i].totalHargaSemua << endl;

            indeksMapping[nomorUrut - 1] = i; // Simpan posisi indeks aslinya
            nomorUrut++;
        }
    }

    // Jika setelah di-loop ternyata tidak ada yang isCheckedOut == true
    if (nomorUrut == 1) {
        cout << "Tidak ada antrean pengiriman barang saat ini." << endl;
        cout << "\nKembali ke halaman menu? (y/n): ";
        cin >> program;
        if (program == 'y' || program == 'Y') {
            return menuKurir();
        }
    }
    cout << "----------------------------------------------------" << endl;

    // 3. Kurir memilih nomor antrean pembelian
    int pilBeli;
    cout << "Pilih nomor pembelian untuk diambil: ";
    cin >> pilBeli;

    if (pilBeli > 0 && pilBeli < nomorUrut) {
        // Ambil data asli dari array berdasarkan mapping nomor urut
        int indeksAsli = indeksMapping[pilBeli - 1];
        Pembelian beliDipilih = daftarPembelian[indeksAsli];

        // 4. Masukkan ke dalam listKurir menggunakan fungsi Jadwal bawaanmu
        Pengiriman pBaru = Jadwal(*listKurir, beliDipilih);

        // Mencatat kurir penanggung jawab yang sedang aktif
        if (userAktif != nullptr) {
            listKurir->back().kurir = *userAktif;
        }

        // 5. TAMPILKAN DETAIL DATA CUSTOMER & BARANG SECARA DINAMIS
        system("cls");
        cout << "=== BERHASIL MENJADWALKAN PENGIRIMAN ===" << endl;
        cout << "Nama Customer : " << pBaru.beli.user << endl; // Langsung .user karena tipenya string
        cout << "Alamat Tujuan : " << pBaru.beli.alamat << endl;
        cout << "Waktu Checkout: " << pBaru.beli.waktuCheckout << endl;
        cout << "----------------------------------------" << endl;
        cout << "Daftar Barang yang Harus Dikirim:" << endl;

        // Looping untuk menampilkan item keranjang secara dinamis
        for (int j = 0; j < pBaru.beli.jumlahBarang; j++) {
            cout << " - " << pBaru.beli.daftarBarang[j].namaProduk
                << " (Jumlah: " << pBaru.beli.daftarBarang[j].banyakPembelian << ")"
                << " [Rp" << pBaru.beli.daftarBarang[j].subTotal << "]" << endl;
        }

        cout << "----------------------------------------" << endl;
        cout << "Total Tagihan : Rp" << pBaru.beli.totalHargaSemua << endl;
        cout << "Status Paket  : " << statusToString(pBaru.status) << endl;
        cout << "========================================" << endl;

    }
    else {
        cout << "Pilihan nomor tidak valid!" << endl;
    }

    cout << "\nKembali ke halaman menu? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return menuKurir();
    }
}
