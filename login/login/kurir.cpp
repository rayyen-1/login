#include "kurir.h"
#include "user.h"   // Wajib di-include supaya bisa baca daftarUser dan jumlahUser
#include <cstdlib>  // Untuk rand()
#include <iomanip>  // Untuk setw, left (dipakai tampilan tabel)
#include <vector>

string statusToString(StatusPengiriman status) {
    if (status == dalam_perjalanan) return "Dalam Perjalanan";
    if (status == sedang_proses_packing) return "Sedang proses packing";
    if (status == selesai) return "Selesai";
    return "Tidak Diketahui";
}

// Diubah agar Mitra bisa melihat semua status pengiriman saat ini
void statusPengirim() {
    // Pengaman: potong teks yang lebih panjang dari lebar kolomnya
    auto potong = [](string teks, int lebarKolom) {
        if ((int)teks.length() > lebarKolom) {
            if (lebarKolom > 3) return teks.substr(0, lebarKolom - 3) + "...";
            return teks.substr(0, lebarKolom);
        }
        return teks;
        };

    int pilih;
    char program;
    do
    {
        system("cls");
        int lebarKotak = 85;
        string menu[] = {
            "1. Status Pengiriman",
            "2. Update Status Pengiriman",
            "3. Keluar"
        };

        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        cout << "|| " << left << setw(lebarKotak - 6) << "STATUS PENGIRIMAN" << " ||" << endl;
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
        {
            system("cls");
            int lebarKotak = 85;
            int colNo = 4;
            int colCustomer = 18;
            int colAlamat = 28;
            int colStatus = lebarKotak - 15 - colNo - colCustomer - colAlamat; // = 20, dihitung otomatis
           
            vector<int> indeksMilikSaya;
            for (size_t i = 0; i < listKurir.size(); i++) {
                if (listKurir[i].kurir.username == userAktif->username) {
                    indeksMilikSaya.push_back((int)i);
                }
            }

            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
            cout << "|| " << left << setw(lebarKotak - 6) << "DAFTAR STATUS PENGIRIMAN SAYA" << " ||" << endl;
            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
            cout << "|| "
                << left << setw(colNo) << "No" << " | "
                << left << setw(colCustomer) << "Customer" << " | "
                << left << setw(colAlamat) << "Alamat" << " | "
                << left << setw(colStatus) << "Status" << " ||" << endl;
            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

            if (indeksMilikSaya.empty()) {
                cout << "|| " << left << setw(lebarKotak - 6) << "Belum ada data pengiriman untuk Anda saat ini." << " ||" << endl;
            }
            else {
                for (size_t n = 0; n < indeksMilikSaya.size(); n++) {
                    int i = indeksMilikSaya[n];
                    cout << "|| "
                        << left << setw(colNo) << potong(to_string(n + 1), colNo) << " | "
                        << left << setw(colCustomer) << potong((listKurir)[i].beli.daftarUser->username, colCustomer) << " | "
                        << left << setw(colAlamat) << potong((listKurir)[i].beli.daftarUser->alamat, colAlamat) << " | "
                        << left << setw(colStatus) << potong(statusToString((listKurir)[i].status), colStatus) << " ||" << endl;
                }
            }
            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
            cout << endl;
            cout << "kembali ke halaman menu status? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y')
            {
                return statusPengirim();
            }
            else
            {
				return menuKurir();
            }
            break;
        }

        case 2:
        {
            system("cls");
            int lebarKotak = 85;
            int colNo = 4;
            int colStatus = lebarKotak - 9 - colNo; // = 72, sebelumnya salah hardcode 76

            vector<int> indeksMilikSaya;
            for (size_t i = 0; i < listKurir.size(); i++) {
                if (listKurir[i].kurir.username == userAktif->username) {
                    indeksMilikSaya.push_back((int)i);
                }
            }

            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
            cout << "|| " << left << setw(lebarKotak - 6) << "UPDATE STATUS PENGIRIMAN SAYA" << " ||" << endl;
            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

            if (indeksMilikSaya.empty()) {
                cout << "|| " << left << setw(lebarKotak - 6) << "Belum ada tugas pengiriman untuk Anda." << " ||" << endl;
                cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
                cout << "\nkembali ke halaman menu status? (y/n): ";
                cin >> program;
                if (program == 'y' || program == 'Y')
                {
                    return statusPengirim();
                }
                else continue;
            }

            cout << "|| "
                << left << setw(colNo) << "No" << " | "
                << left << setw(colStatus) << "Status Saat Ini" << " ||" << endl;
            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

            for (size_t n = 0; n < indeksMilikSaya.size(); n++) {
                int i = indeksMilikSaya[n];
                cout << "|| "
                    << left << setw(colNo) << potong(to_string(n + 1), colNo) << " | "
                    << left << setw(colStatus) << potong(statusToString((listKurir)[i].status), colStatus) << " ||" << endl;
            }
            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
            cout << endl;

            int pilihan;
            cout << "Pilih nomor pengiriman yang ingin di-update: ";
            cin >> pilihan;

            if (pilihan > 0 && pilihan <= (int)indeksMilikSaya.size()) {
                int idxAsli = indeksMilikSaya[pilihan - 1];

                if (listKurir[idxAsli].status == sedang_proses_packing) {
                    cout << "\nPaket ini masih dalam proses packing oleh mitra." << endl;
                    cout << "Anda belum bisa mengubah statusnya. Silakan tunggu sampai" << endl;
                    cout << "mitra menyerahkan paket ini ke kurir." << endl;
                }
                else if (listKurir[idxAsli].status == selesai) {
                    cout << "\nPengiriman ini sudah selesai, tidak ada lagi yang perlu diupdate." << endl;
                }
                else {
                    char konfirmasi;
                    cout << "\nTandai pengiriman ini sebagai SELESAI? (y/n): ";
                    cin >> konfirmasi;

                    if (konfirmasi == 'y' || konfirmasi == 'Y') {
                        updateStatus((listKurir)[idxAsli], selesai);
                        cout << "\nStatus berhasil diperbarui menjadi: " << statusToString((listKurir)[idxAsli].status) << endl;
                    }
                }
            }
            else {
                cout << "Pilihan nomor pengiriman tidak valid!" << endl;
            }
            cout << "\nkembali ke halaman menu status? (y/n): ";
            cin >> program;
            if (program == 'y' || program == 'Y')
            {
                return;
            }
            break;
        }

        case 3:
            return menuKurir();
            break;
        }
    } while (pilih != 3);
}

// Fungsi pembungkus jadwal pengiriman untuk Kurir (Case 1 di menuKurir)
Pengiriman Jadwal(vector<Pengiriman>& dataStorage, Pembelian beli) {
    Pengiriman pengirimanBaru;

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

    int lebarKotak = 85;

    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    cout << "|| " << left << setw(lebarKotak - 6) << "DAFTAR JADWAL PENGIRIMAN SAYA" << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    // 1. Validasi apakah ada kurir yang login
    if (userAktif == nullptr) {
        cout << "|| " << left << setw(lebarKotak - 6) << "[!] Error: Tidak ada sesi kurir yang aktif." << " ||" << endl;
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
        system("PAUSE");
        return;
    }

    cout << "|| " << left << setw(lebarKotak - 6) << ("Nama Kurir : " + userAktif->username) << " ||" << endl;
    cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;

    int nomorUrut = 1;

    // 2. Tampilkan paket yang HANYA ditugaskan ke kurir aktif
    for (size_t i = 0; i < listKurir.size(); i++) {

        if (listKurir[i].kurir.username == userAktif->username) {
            cout << "|| " << left << setw(lebarKotak - 6) << ("Paket #" + to_string(nomorUrut)) << " ||" << endl;
            cout << "|| " << left << setw(lebarKotak - 6) << ("  Customer      : " + listKurir[i].beli.daftarUser->username) << " ||" << endl;
            cout << "|| " << left << setw(lebarKotak - 6) << ("  Alamat Tujuan : " + listKurir[i].beli.daftarUser->alamat) << " ||" << endl;
            cout << "|| " << left << setw(lebarKotak - 6) << ("  Waktu Order   : " + listKurir[i].beli.waktuCheckout) << " ||" << endl;
            cout << "|| " << left << setw(lebarKotak - 6) << ("  Status Paket  : " + statusToString(listKurir[i].status)) << " ||" << endl;
            cout << "|| " << left << setw(lebarKotak - 6) << "  Daftar Barang :" << " ||" << endl;

            for (int j = 0; j < listKurir[i].beli.jumlahBarang; j++) {
                string baris = "    - " + listKurir[i].beli.daftarBarang[j].namaProduk
                    + " (" + to_string(listKurir[i].beli.daftarBarang[j].banyakPembelian) + " Kg)";
                cout << "|| " << left << setw(lebarKotak - 6) << baris << " ||" << endl;
            }
            cout << "|| " << left << setw(lebarKotak - 6) << ("  Total Tagihan : Rp" + to_string(listKurir[i].beli.totalHargaSemua)) << " ||" << endl;
            cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
            nomorUrut++;
        }
    }

    // 3. Jika setelah di-loop ternyata tidak ada paket yang cocok untuk kurir ini
    if (nomorUrut == 1) {
        cout << "|| " << left << setw(lebarKotak - 6) << "Tidak ada antrean tugas pengiriman untuk Anda saat ini." << " ||" << endl;
        cout << "++" << string(lebarKotak - 4, '-') << "++" << endl;
    }

    cout << endl;
    cout << "Kembali ke halaman menu? (y/n): ";
    cin >> program;
    if (program == 'y' || program == 'Y') {
        return menuKurir();
    }
    else
    {
        return jadwalPengirim();
    }
}