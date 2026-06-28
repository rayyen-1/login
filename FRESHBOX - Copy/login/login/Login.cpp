#include <iostream>
#include "menu.h"
#include "mitra.h"
#include "produk.h"
#include "user.h";

using namespace std;

User daftarUser[MAX_USER];
int jumlahUser = 0;
User* userAktif = nullptr;

void registrasi(User daftarUser[], int &jumlahUser);
void login(User daftarUser[], int jumlahUser);

int main() {
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

	for (int i = 0; i <= jumlahUser; i++) {

		if (usn == daftarUser[i].username && pass == daftarUser[i].password)
		{
			cout << "---- Login berhasil ----" << endl << endl;
			if (daftarUser[i].as == 1)

		if (usn == daftarUser[i].username && pass == daftarUser[i].password)
		{
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
			loginSuccess = true;

			userAktif = &daftarUser[i];


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

}

