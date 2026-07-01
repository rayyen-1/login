#include "kurir.h"
#include "user.h"   // Wajib di-include supaya bisa baca daftarUser dan jumlahUser
#include <cstdlib>  // Untuk rand()
#include <vector>

string statusToString(StatusPengiriman status) {
    if (status == dalam_perjalanan) return "Dalam Perjalanan";
    if (status == sedang_proses_packing) return "Sedang proses packing";
    if (status == selesai) return "Selesai";
    return "Tidak Diketahui";
}

Pengiriman Jadwal(vector<Pengiriman>& dataStorage, Pembelian beli, User kurirSkg) {
    Pengiriman pengirimanBaru;

    pengirimanBaru.status;
    pengirimanBaru.beli = beli;
    pengirimanBaru.kurir = kurirSkg; // Menggunakan kurir hasil acakan

    dataStorage.push_back(pengirimanBaru);

    return pengirimanBaru;
}



// Diubah agar Mitra bisa melihat semua status pengiriman saat ini
void statusPengirim() {
    int pilih;
    char program;
    do
    {
        system("cls");
        cout << "1. Status pengiriman" << endl;
        cout << "2. Update status pengiriman" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            system("cls");
            cout << "=== DAFTAR STATUS PENGIRIMAN ===" << endl;
            if (listKurir.empty()) {
                cout << "Belum ada data pengiriman saat ini." << endl;
            }
            else {
                for (size_t i = 0; i < listKurir.size(); i++) {
                    cout << i + 1 << ". Pembelian oleh: " << (listKurir)[i].beli.daftarUser->username// sesuaikan struct Pembelian Anda
                        << " | Status: " << statusToString((listKurir)[i].status) << endl;
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

            if (listKurir.empty()) {
                cout << "Belum ada tugas pengiriman untuk Anda." << endl;
                system("PAUSE");
                return menuKurir();
            }

            // Tampilkan semua daftar pengiriman yang dipegang kurir
            for (size_t i = 0; i < listKurir.size(); i++) {
                cout << i + 1 << ". Tugas Pengiriman ke-" << i + 1
                    << " | Status Saat Ini: " << statusToString((listKurir)[i].status) << endl;
            }

            int pilihan, statusBaru;
            cout << "\nPilih nomor pengiriman yang ingin di-update: ";
            cin >> pilihan;

            if (pilihan > 0 && pilihan <= (int)listKurir.size()) {
                cout << "Pilih Status Baru:\n1. Sedang dikirim (Dalam Perjalanan)\n2. Pengiriman selesai\nPilihan status (1/2): ";
                cin >> statusBaru;

                // Memanggil fungsi asli dari kurir.h (by reference menggunakan index vector)
                updateStatus((listKurir)[pilihan - 1], statusBaru);

                cout << "\nStatus berhasil diperbarui menjadi: " << statusToString((listKurir)[pilihan - 1].status) << endl;
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
Pengiriman Jadwal(vector<Pengiriman>& dataStorage, Pembelian beli) {
    Pengiriman pengirimanBaru;

    pengirimanBaru.status;
    pengirimanBaru.beli = beli;

    // 1. Cari semua indeks user yang rolenya kurir
    vector<int> indeksKurirTersedia;
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].as == kurir) { // Ngecek berdasarkan enum user_as milikmu
            indeksKurirTersedia.push_back(i);
        }
    }

    // 2. Acak kurir dari daftar yang tersedia
    if (!indeksKurirTersedia.empty()) {
        int acak = rand() % indeksKurirTersedia.size();
        int indeksTerpilih = indeksKurirTersedia[acak];

        // Pasang data kurir asli hasil acakan ke data pengiriman
        pengirimanBaru.kurir = daftarUser[indeksTerpilih];
    }
    else {
        // Cadangan kalau di data pembobotan sistem belum ada akun kurir sama sekali
        User userkurir;
        userkurir.username = "Kurir Toko (Default)";
        userkurir.as = kurir;
        pengirimanBaru.kurir = userkurir;
    }

    // 3. Masukkan ke database vector pengiriman
    dataStorage.push_back(pengirimanBaru);

    return pengirimanBaru;
}

void updateStatus(Pengiriman& p, int StatusBaru) {
    p.status = static_cast<StatusPengiriman>(StatusBaru);
}

void jadwalPengirim() {
    char program;
    system("cls");
    cout << "=== DAFTAR JADWAL PENGIRIMAN SAYA ===" << endl;

    // 1. Validasi apakah ada kurir yang login
    if (userAktif == nullptr) {
        cout << "[!] Error: Tidak ada sesi kurir yang aktif." << endl;
        system("PAUSE");
        return menuKurir();
    }

    cout << "Nama Kurir: " << userAktif->username << endl;
    cout << "----------------------------------------------------" << endl;

    int nomorUrut = 1;

    // 2. Tampilkan paket yang HANYA ditugaskan ke kurir aktif
    // listKurir berbentuk pointer vector (vector<Pengiriman>*)
    for (size_t i = 0; i < listKurir.size(); i++) {

        if (listKurir[i].kurir.username == userAktif->username) {
            cout << nomorUrut << ". [Paket #" << i + 1 << "]" << endl;
            cout << "   Customer      : " << listKurir[i].beli.daftarUser->username << endl;
            cout << "   Alamat Tujuan : " << listKurir[i].beli.daftarUser->alamat << endl;
            cout << "   Waktu Order   : " << listKurir[i].beli.waktuCheckout << endl;
            cout << "   Status Paket  : " << statusToString(listKurir[i].status) << endl;
            cout << "   Daftar Barang : " << endl;

            for (int j = 0; j < listKurir[i].beli.jumlahBarang; j++) {
                cout << "     - " << listKurir[i].beli.daftarBarang[j].namaProduk
                    << " (" << listKurir[i].beli.daftarBarang[j].banyakPembelian << " pcs)" << endl;
            }
            cout << "   Total Tagihan : Rp" << listKurir[i].beli.totalHargaSemua << endl;
            cout << "----------------------------------------------------" << endl;
            nomorUrut++;
        }
    }

    // 3. Jika setelah di-loop ternyata tidak ada paket yang cocok untuk kurir ini
    if (nomorUrut == 1) {
        cout << "Tidak ada antrean tugas pengiriman untuk Anda saat ini." << endl;
        cout << "----------------------------------------------------" << endl;
    }

    cout << "\nKembali ke halaman menu? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return menuKurir();
    }
}