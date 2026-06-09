#include <iostream>

using namespace std;

enum user_as {
	customer = 1, kurir = 2, mitra = 3
};

struct user {
	string username;
	string password;
	user_as as;
}user;

void registrasi(string username, string password, user_as as);
void login();

int main() {

}


void registrasi(string username, string password, user_as as) {
	system("cls");
	cout << "Registrasi sebagai apa?" << endl << endl;
	cout << "1. Customer" << endl;

	cout << "=== REGISTRASI ===" << endl << endl;
	cout << "Username : "; cin >> username;
	cout << "Password : "; cin >> password;
}