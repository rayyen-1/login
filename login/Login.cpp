#include <iostream>

using namespace std;

enum user_as {
	customer = 1, kurir = 2, mitra = 3
};

struct User {
	string username;
	string password;
	user_as as;
}pengguna;

void registrasi(User& pengguna);
void login(User pengguna);

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
			registrasi(pengguna);
			break;
		case 2:
			login(pengguna);
			break;
		case 3:
			break;
		}
	} while (pil != 0);

	return 0;
}


void registrasi(User& pengguna) {
	system("cls");
	int pilih;
	cout << "---- Registrasi sebagai apa? ----" << endl << endl;
	cout << "1. Customer" << endl;
	cout << "2. Kurir" << endl;
	cout << "3. Mitra Tani" << endl;
	cout << "Pilih: ";
	cin >> pilih;

	pengguna.as = user_as(pilih);
	cout << "\n=== REGISTRASI ===" << endl << endl;
	cout << "Username : "; cin >> pengguna.username;
	cout << "Password : "; cin >> pengguna.password;
	cout << "---- Registrasi Berhasil ----" << endl << endl;
	system("PAUSE");
}

void login(User pengguna) {
	system("cls");
	string usn, pass;
	cout << "=== LOGIN ===" << endl;
	cout << "Username: ";
	cin >> usn;
	cout << "Password: ";
	cin >> pass;

	if (usn == pengguna.username && pass == pengguna.password)
	{
		cout << "---- Login berhasil ----" << endl << endl;
		if (pengguna.as == 1)
		{
			cout << "Selamat datang customer" << endl;
		}
		else if (pengguna.as == 2)
		{
			cout << "Selamat datang kurir" << endl;
		}
		else if (pengguna.as == 3)
		{
			cout << "Selamat datang mitra tani" << endl;
		}
	}
	else
	{
		cout << "Login gagal, username atau password Anda salah." << endl;
	}
	system("PAUSE");
}
