#include <iostream>
#include <iomanip>
#include <cstring>
#include "menu.h"
#include "mitra.h"
#include "produk.h"
#include "kurir.h"
#include "user.h"


using namespace std;
User daftarUser[MAX_USER];
int jumlahUser = 3;

User* userAktif = nullptr;

void inisialisasiProduk() {
	// 1. Buat satu objek Queue baru
	Queue antreanMitra1;
	antreanMitra1.depan = 0;
	antreanMitra1.belakang = 5; // Meng-cover 5 produk (indeks 0 sampai 4)

	// 2. Masukkan data akun mitra dari daftarUser[0] ke dalam struct Queue
	// Pastikan inisialisasiUser() dipanggil duluan sebelum fungsi ini ya!
	antreanMitra1.mitra = daftarUser[0];

	// 3. Masukkan data produknya
	antreanMitra1.data[0] = { "P001", "Bayam", 5000, 20, SAYUR };
	antreanMitra1.data[1] = { "P002", "Apel", 25000, 15, BUAH };
	antreanMitra1.data[2] = { "P003", "Wortel", 7000, 30, SAYUR };
	antreanMitra1.data[3] = { "P004", "Mangga", 18000, 10, BUAH };
	antreanMitra1.data[4] = { "P005", "Jeruk", 15000, 25, BUAH };

	// Status bawaan (default) mitra
	antreanMitra1.statusMitra = diproses;

	// 4. Dorong objek Queue tersebut ke dalam vector listMitra
	listMitra.push_back(antreanMitra1);
}

void inisialisasiUser() {
	daftarUser[0] = { "mitra1", "mitra123", "12-04-1995", "mitra.utama@email.com", "Sleman, Yogyakarta", "123456789", mitra };
	daftarUser[1] = { "kurir1", "kurir123", "25-08-1998", "kurir.anton@email.com", "Depok, Sleman", "234556788", kurir };
	daftarUser[2] = { "kurir2", "kurir456", "03-11-2000", "kurir.budi@email.com", "Bantul, Yogyakarta", "12345578975", kurir };

}

// GANTI BARIS INI (Taruh di luar fungsi main / global)


void registrasi(User daftarUser[], int& jumlahUser);
void login(User daftarUser[], int jumlahUser);

int main() {
	// inisialisasiProduk() membaca daftarUser[0], jadi inisialisasiUser() wajib
	// dipanggil lebih dulu (sesuai catatan di komentar inisialisasiProduk()).
	inisialisasiUser();
	inisialisasiProduk();

	int pil;
	do {
		system("cls");
		cout << "  +-----------------------------------+" << endl;
		cout << "  |                                   |" << endl;
		cout << "  | F R E S H B O X  ~  S A Y U R G O |" << endl;
		cout << "  |                                   |" << endl;
		cout << "  +-----------------------------------+" << endl;
		cout << "  +-----------------------------------+" << endl;
		cout << "  |   1  |  Registrasi                |" << endl;
		cout << "  |   2  |  Login                     |" << endl;
		cout << "  |   3  |  Keluar                    |" << endl;
		cout << "  +------+----------------------------+" << endl;
		cout << "Pilih menu : ";
		cin >> pil;

		switch (pil)
		{
		case 1:
			registrasi(daftarUser, jumlahUser);
			break;
		case 2:
			login(daftarUser, jumlahUser);
			break;
		case 3:
			break;
		}
	} while (pil != 3);

	return 0;
}

void registrasi(User daftarUser[], int& jumlahUser) {

	system("cls");

	char program;
	if (jumlahUser >= MAX_USER) {
		cout << "Maaf, jumlah pengguna sudah mencapai batas maksimum." << endl;
		system("PAUSE");
		return;
	}

	int pilih;
	int lebarKotak = 50;
	int panjangJudul1 = strlen(" Registrasi sebagai apa? ");
	cout << "++" << string(lebarKotak, '-') << "++" << endl;
	cout << "++" << string((lebarKotak - panjangJudul1) / 2, '-') << " Registrasi sebagai apa? " << string((lebarKotak - panjangJudul1) / 2, '-') << "-++" << endl;
	cout << "++" << string(lebarKotak, '-') << "++" << endl;
	string menu_role[] = {
		   "1. Customer",
		   "2. Kurir",
		   "3. Mitra Tani"
	};

	for (int i = 0; i < 3; i++) {
		int sisaLebarMenu = lebarKotak - menu_role[i].length() + 1;
		cout << "|| " << menu_role[i] << right << setw(sisaLebarMenu) << " ||" << endl;
	}
	cout << "++" << string(lebarKotak, '-') << "++" << endl;
	int panjangPilih = strlen("Pilih: ");
	cout << "|| Pilih: " << string((lebarKotak - panjangPilih - 1), ' ') << "||" << endl;
	cout << "++" << string(lebarKotak, '-') << "++" << endl;
	cout << "\033[2A\033[10C";
	cin >> pilih;
	cout << "\033[1B";
	daftarUser[jumlahUser].as = user_as(pilih);

	int panjangJudul2 = strlen(" REGISTRASI ");
	cout << "++" << string(((lebarKotak - panjangJudul2) / 2) - 1, '-') << " REGISTRASI " << string((lebarKotak - panjangJudul2) / 2, '-') << "-++" << endl;
	cout << "++" << string(lebarKotak, '-') << "++" << endl;

	string menu_registrasi[] = {
		   "Username : ",
		   "Password : ",
		   "Tanggal Lahir : ",
		   "No Handphone : ",
		   "Email : ",
		   "Alamat : "
	};


	for (int i = 0; i < 6; i++) {
		int sisaLebarMenu = lebarKotak - menu_registrasi[i].length() + 1;
		cout << "|| " << menu_registrasi[i] << right << setw(sisaLebarMenu) << " ||" << endl;
	}
	cout << "++" << string(lebarKotak, '-') << "++" << endl;
	cout << "\033[7A\033[14C";
	cin >> daftarUser[jumlahUser].username;
	cout << "\033[14C";
	cin >> daftarUser[jumlahUser].password;
	cout << "\033[19C";
	cin >> daftarUser[jumlahUser].tanggalLahir;
	cout << "\033[18C";
	cin >> daftarUser[jumlahUser].nohp;
	cout << "\033[11C";
	cin >> daftarUser[jumlahUser].email;
	cout << "\033[12C";
	cin >> daftarUser[jumlahUser].alamat;
	cout << "\033[1B";
	int panjangJudul3 = strlen(" Registrasi Berhasil ");
	cout << "++" << string((lebarKotak - panjangJudul3) / 2, '-') << " Registrasi Berhasil " << string((lebarKotak - panjangJudul3) / 2, '-') << "-++" << endl;
	cout << "++" << string(lebarKotak, '-') << "++" << endl << endl;

	jumlahUser++;
	cout << "kembali ke halaman menu? (y/n): ";
	cin >> program;
	if (program == 'y' || program == 'Y')
	{
		return;
	}
	else
	{
		exit(0);
	}
}


void login(User daftarUser[], int jumlahUser) {
	system("cls");
	string usn, pass;
	char program;
	int lebarKotak = 50;
	int panjangJudul1 = strlen(" LOGIN ");
	cout << "++" << string(lebarKotak, '-') << "++" << endl;
	cout << "++" << string((lebarKotak - panjangJudul1) / 2, ' ') << " LOGIN " << string((lebarKotak - panjangJudul1) / 2, ' ') << "-++" << endl;
	cout << "++" << string(lebarKotak, '-') << "++" << endl;

	string menu_login[] = {
		   "Username : ",
		   "Password : "
	};

	for (int i = 0; i < 2; i++) {
		int sisaLebarMenu = lebarKotak - menu_login[i].length() + 1;
		cout << "|| " << menu_login[i] << right << setw(sisaLebarMenu) << " ||" << endl;
	}
	cout << "++" << string(lebarKotak, '-') << "++" << endl;
	cout << "\033[3A\033[14C";
	cin >> usn;
	cout << "\033[14C";
	cin >> pass;


	bool loginSuccess = false;

	for (int i = 0; i < jumlahUser; i++) {

		if (usn == daftarUser[i].username && pass == daftarUser[i].password)
		{
			loginSuccess = true;
			userAktif = &daftarUser[i];
			cout << "---- Login berhasil ----" << endl << endl;
			if (daftarUser[i].as == 1)

			{
				menuCustomer();
			}

			else if (daftarUser[i].as == 2)

			{
				menuKurir();
			}

			else if (daftarUser[i].as == 3)

			{
				menuMitra();
			}

			break;
		}
	}

	if (!loginSuccess) {
		cout << "Login gagal, username atau password Anda salah." << endl;
	}

	cout << "kembali ke halaman menu? (y/n): ";
	cin >> program;
	if (program == 'y' || program == 'Y')
	{
		return;
	}
	else
	{
		exit(0);
	}

}



