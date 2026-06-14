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

void registrasi(User &pengguna);

int main() {
	
	string usn, pass;
	registrasi(pengguna);
	cout << "---- Registrasi Berhasil ----" << endl << endl;
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
}


void registrasi(User &pengguna) {
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
}
