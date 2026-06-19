#include <iostream>
#include "menu.h"
using namespace std;

enum user_as {
	  customer = 1, kurir = 2, mitra = 3
};

const int MAX_USER = 10;
int jumlahUser = 0;

struct User {
	string username = "";
	string password = "";
	string tanggalLahir;
	string email;
	string alamat;
	user_as as;
};

User pengguna[MAX_USER];

void registrasi(User pengguna[], int &jumlahUser);
void login(User pengguna[], int jumlahUser);

int main() {
	int pil;
	do {
		system("cls");
		cout << "=== FRESHBOX / SAYURGO ===" << endl;
		cout << "1. Registrasi" << endl;
		cout << "2. Login" << endl;
		cout << "3. Keluar" << endl;
		cout << "Pilih menu : ";
		cin >> pil;

		switch (pil)
		{
		case 1:
			registrasi(pengguna, jumlahUser);
			break;
		case 2:
			login(pengguna, jumlahUser);
			break;
		case 3:
			break;
		}
	} while (pil != 3);

	return 0;
}


void registrasi(User pengguna[], int &jumlahUser) {
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

	pengguna[jumlahUser].as = user_as(pilih);
	cout << "\n=== REGISTRASI ===" << endl << endl;
	cout << "Username : "; cin >> pengguna[jumlahUser].username;
	cout << "Password : "; cin >> pengguna[jumlahUser].password;
	cout << "Tanggal Lahir : "; cin >> pengguna[jumlahUser].tanggalLahir;
	cout << "Email : "; cin >> pengguna[jumlahUser].email;
	cout << "Alamat : "; cin >> pengguna[jumlahUser].alamat;
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

void login(User pengguna[], int jumlahUser) {
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
		if (usn == pengguna[i].username && pass == pengguna[i].password)
		{
			cout << "---- Login berhasil ----" << endl << endl;
			if (pengguna[i].as == 1)
			{
				cout << "Selamat datang customer" << endl;
				menuCustomer();
			}
			else if (pengguna[i].as == 2)
			{
				cout << "Selamat datang kurir" << endl;
				menuKurir();
			}
			else if (pengguna[i].as == 3)
			{
				cout << "Selamat datang mitra tani" << endl;
				menuMitra();
			}
			loginSuccess = true;
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
