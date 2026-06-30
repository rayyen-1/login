#include <iostream>

using namespace std;

#include "user.h";

struct user {
	string username;
	string password;
	user_as as;
}user;

void registrasi(string username, string password, user_as as);
void login();

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


void registrasi(string username, string password, user_as as) {
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

	cout << "=== REGISTRASI ===" << endl << endl;
	cout << "Username : "; cin >> username;
	cout << "Password : "; cin >> password;
}