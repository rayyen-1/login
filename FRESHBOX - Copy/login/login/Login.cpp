#include <iostream>
#include "menu.h"
#include "mitra.h"
#include "produk.h"
#include "user.h";


using namespace std;


User* userAktif = nullptr;

void inisialisasiProduk() {
	queue.depan = 0;
	queue.belakang = 0;
	queue.data[0] = { "Bayam", 5000, 20, SAYUR };
	queue.data[1] = { "Apel", 25000, 15, BUAH };
	queue.data[2] = { "Wortel", 7000, 30, SAYUR };
	queue.data[3] = { "Mangga", 18000, 10, BUAH };
	queue.data[4] = { "Jeruk", 15000, 25, BUAH };
}

void inisialisasiUser() {
	daftarUser[0] = { "admin1", "admin123", "12-04-1995", "admin.utama@email.com", "Sleman, Yogyakarta" };
	daftarUser[1] = { "kurir1", "kurir123", "25-08-1998", "kurir.anton@email.com", "Depok, Sleman" };
	daftarUser[2] = { "kurir2", "kurir456", "03-11-2000", "kurir.budi@email.com", "Bantul, Yogyakarta" };

}

void registrasi(User daftarUser[], int &jumlahUser);
void login(User daftarUser[], int jumlahUser);

int main() {
	inisialisasiProduk();
	inisialisasiUser();
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

void registrasi(User daftarUser[], int &jumlahUser) {

	system("cls");

	char program;
	if (jumlahUser >= MAX_USER) {
		cout << "Maaf, jumlah pengguna sudah mencapai batas maksimum." << endl;
		system("PAUSE");
		return;
	}

	int pilih;
	cout << "---- Registrasi sebagai apa? ----" << endl << endl;
	cout << "1. Customer" << endl;
	cout << "2. Kurir" << endl;
	cout << "3. Mitra Tani" << endl;
	cout << "Pilih: ";
	cin >> pilih;
	daftarUser[jumlahUser].as = user_as(pilih);
	cout << "\n=== REGISTRASI ===" << endl << endl;
	cout << "Username : "; cin >> daftarUser[jumlahUser].username;
	cout << "Password : "; cin >> daftarUser[jumlahUser].password;
	cout << "Tanggal Lahir : "; cin >> daftarUser[jumlahUser].tanggalLahir;
	cout << "Email : "; cin >> daftarUser[jumlahUser].email;
	cout << "Alamat : "; cin >> daftarUser[jumlahUser].alamat;
	cout << "---- Registrasi Berhasil ----" << endl << endl;


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
	cout << "=== LOGIN ===" << endl;
	cout << "Username: ";
	cin >> usn;
	cout << "Password: ";
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
				cout << "Selamat datang customer" << endl;
				menuCustomer();
			}

			else if (daftarUser[i].as == 2)

			{
				cout << "Selamat datang kurir" << endl;
				menuKurir();
			}

			else if (daftarUser[i].as == 3)

			{
				cout << "Selamat datang mitra tani" << endl;
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



