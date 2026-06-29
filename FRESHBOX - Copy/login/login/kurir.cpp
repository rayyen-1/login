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

vector<Pengiriman> listKurir;

// Diubah agar Mitra bisa melihat semua status pengiriman saat ini
void statusPengirim() {
    int pilih;
    char program;
    do
    {
        cout << "1. Status pengiriman" << endl;
        cout << "2. Update status" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih menu: ";

        switch (pilih)
        {
        case 1:
            system("cls");
            cout << "=== DAFTAR STATUS PENGIRIMAN (MITRA) ===" << endl;
            if (listKurir.empty()) {
                cout << "Belum ada data pengiriman saat ini." << endl;
            }
            else {
                for (size_t i = 0; i < listKurir.size(); i++) {
                    cout << i + 1 << ". Pembelian oleh: " << listKurir[i].beli.user // sesuaikan struct Pembelian Anda
                        << " | Status: " << statusToString(listKurir[i].status) << endl;
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
                    << " | Status Saat Ini: " << statusToString(listKurir[i].status) << endl;
            }

            int pilihan, statusBaru;
            cout << "\nPilih nomor pengiriman yang ingin di-update: ";
            cin >> pilihan;

            if (pilihan > 0 && pilihan <= (int)listKurir.size()) {
                cout << "Pilih Status Baru:\n1. Sedang dikirim (Dalam Perjalanan)\n2. Pengiriman selesai\nPilihan status (1/2): ";
                cin >> statusBaru;

                // Memanggil fungsi asli dari kurir.h (by reference menggunakan index vector)
                updateStatus(listKurir[pilihan - 1], statusBaru);

                cout << "\nStatus berhasil diperbarui menjadi: " << statusToString(listKurir[pilihan - 1].status) << endl;
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

    Pembelian beliDummy; // Simulasi data pembelian yang mau diambil kurir
    // Di dunia nyata, di sini biasanya ada proses memilih ID Pembelian yang belum dikirim.

    // Memanggil fungsi asli dari kurir.h
    Pengiriman pBaru = Jadwal(listKurir, beliDummy);

    // Mencatat siapa kurir yang mengambil tugas ini (menggunakan global pointer userAktif)
    if (userAktif != nullptr) {
        listKurir.back().kurir = *userAktif;
    }

    cout << "\nPengiriman baru berhasil dijadwalkan!" << endl;
    cout << "Status otomatis: " << statusToString(pBaru.status) << endl;
    cout << "kembali ke halaman menu? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y')
    {
        return menuKurir();
    }
}
