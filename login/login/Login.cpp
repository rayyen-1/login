#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <ctime>
#include "menu.h"
#include "mitra.h"
#include "produk.h"
#include "kurir.h"
#include "user.h"


using namespace std;
User daftarUser[MAX_USER];
int jumlahUser = 5;

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

	// 2 user customer statis
	daftarUser[3] = { "customer1", "cust123", "10-02-1999", "budi.cust@email.com", "Depok, Yogyakarta", "081234567890", customer };
	daftarUser[4] = { "customer2", "cust456", "22-07-2001", "sinta.cust@email.com", "Sleman, Yogyakarta", "081298765432", customer };
}

// Membuat transaksi contoh: customer1 & customer2 belanja dari produk mitra1,
// lalu pesanannya masuk ke antrean mitra dan diteruskan ke kurir.
// Dipanggil SETELAH inisialisasiUser() dan inisialisasiProduk(),
// supaya daftarUser dan listMitra[0].data (produk mitra1) sudah terisi.
void inisialisasiTransaksi() {
	time_t sekarang = time(0);
	string waktuSekarang = ctime(&sekarang);
	waktuSekarang.pop_back(); // buang karakter '\n' di akhir // format: "Mon Jun 29 11:03:42 2026\n"

	// ---------- Transaksi 1: customer1 beli dari mitra1 ----------
	Pembelian p1;
	p1.daftarUser[0] = daftarUser[3];       // customer1
	p1.isCheckedOut = true;
	p1.waktuCheckout = waktuSekarang;
	p1.jumlahBarang = 2;

	p1.daftarBarang[0].namaProduk = listMitra[0].data[0].namaProduk; // "Bayam"
	p1.daftarBarang[0].banyakPembelian = 2;
	p1.daftarBarang[0].hargaSatuan = listMitra[0].data[0].harga;
	p1.daftarBarang[0].subTotal = p1.daftarBarang[0].banyakPembelian * p1.daftarBarang[0].hargaSatuan;

	p1.daftarBarang[1].namaProduk = listMitra[0].data[2].namaProduk; // "Wortel"
	p1.daftarBarang[1].banyakPembelian = 3;
	p1.daftarBarang[1].hargaSatuan = listMitra[0].data[2].harga;
	p1.daftarBarang[1].subTotal = p1.daftarBarang[1].banyakPembelian * p1.daftarBarang[1].hargaSatuan;

	p1.totalHargaSemua = p1.daftarBarang[0].subTotal + p1.daftarBarang[1].subTotal;

	daftarPembelian[jumlahPembelian++] = p1;

	// ---------- Transaksi 2: customer2 beli dari mitra1 ----------
	Pembelian p2;
	p2.daftarUser[0] = daftarUser[4];       // customer2
	p2.isCheckedOut = true;
	p2.waktuCheckout = waktuSekarang;
	p2.jumlahBarang = 1;

	p2.daftarBarang[0].namaProduk = listMitra[0].data[1].namaProduk; // "Apel"
	p2.daftarBarang[0].banyakPembelian = 4;
	p2.daftarBarang[0].hargaSatuan = listMitra[0].data[1].harga;
	p2.daftarBarang[0].subTotal = p2.daftarBarang[0].banyakPembelian * p2.daftarBarang[0].hargaSatuan;

	p2.totalHargaSemua = p2.daftarBarang[0].subTotal;

	daftarPembelian[jumlahPembelian++] = p2;

	// ---------- Masukkan kedua transaksi ke antrean order mitra ----------
	listOrder(listOrderMitra, p1);
	listOrder(listOrderMitra, p2);

	// ---------- Masukkan ke daftar kurir (kurir1 kebagian keduanya) ----------
	Pengiriman k1;
	k1.beli = p1;
	k1.kurir = daftarUser[1];   // kurir1
	k1.status = sedang_proses_packing;
	listKurir.push_back(k1);

	Pengiriman k2;
	k2.beli = p2;
	k2.kurir = daftarUser[1];   // kurir1
	k2.status = sedang_proses_packing;
	listKurir.push_back(k2);
}

// GANTI BARIS INI (Taruh di luar fungsi main / global)


void registrasi(User daftarUser[], int& jumlahUser);
void login(User daftarUser[], int jumlahUser);
void registerUser(User daftarUser[], int& jumlahUser);

int main() {
	// inisialisasiProduk() membaca daftarUser[0], jadi inisialisasiUser() wajib
	// dipanggil lebih dulu (sesuai catatan di komentar inisialisasiProduk()).
	inisialisasiUser();
	inisialisasiProduk();
	inisialisasiTransaksi();

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
			cout << "\n=== Terima kasih telah menggunakan FreshBox! Sampai jumpa! ===\n" << endl;
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

	int panjangJudul2;
	int panjangJudul3;
	int panjangJudul4;
	switch (pilih)
	{
	case 1:
		system("cls");
		daftarUser[jumlahUser].as = customer;
		panjangJudul2 = strlen(" REGISTRASI SEBAGAI CUSTOMER ");
		cout << "++" << string(lebarKotak, '-') << "++" << endl;
		cout << "++" << string(((lebarKotak - panjangJudul2) / 2), '-') << " REGISTRASI SEBAGAI CUSTOMER " << string((lebarKotak - panjangJudul2) / 2, '-') << "-++" << endl;
		cout << "++" << string(lebarKotak, '-') << "++" << endl;
	
		registerUser(daftarUser, jumlahUser);
		break;

	case 2:
		system("cls");
		daftarUser[jumlahUser].as = kurir;
		 panjangJudul3 = strlen(" REGISTRASI SEBAGAI KURIR ");
		 cout << "++" << string(lebarKotak, '-') << "++" << endl;
		cout << "++" << string(((lebarKotak - panjangJudul3) / 2) - 1, '-') << " REGISTRASI SEBAGAI KURIR " << string((lebarKotak - panjangJudul3) / 2, '-') << "-++" << endl;
		cout << "++" << string(lebarKotak, '-') << "++" << endl;
		
		registerUser(daftarUser, jumlahUser);
		break;

	case 3:
		system("cls");
		daftarUser[jumlahUser].as = mitra;
		panjangJudul4 = strlen(" REGISTRASI SEBAGAI MITRA TANI ");
		cout << "++" << string(lebarKotak, '-') << "++" << endl;
		cout << "++" << string(((lebarKotak - panjangJudul4) / 2), '-') << " REGISTRASI SEBAGAI MITRA TANI " << string((lebarKotak - panjangJudul4) / 2, '-') << "-++" << endl;
		cout << "++" << string(lebarKotak, '-') << "++" << endl;
		
		registerUser(daftarUser, jumlahUser);
		break;
	}

	cout << "Beralih ke halaman login? (y/n): ";
	cin >> program;
	if (program == 'y' || program == 'Y')
	{
		login(daftarUser, jumlahUser);
	}
	else
	{
		return;
	}
}


void login(User daftarUser[], int jumlahUser) {
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // buang sisa newline dari menu sebelumnya (cin >> pil / cin >> program)

	char program;
	bool ulangi = true;

	while (ulangi) {
		system("cls");
		string usn, pass;
		int lebarKotak = 50;
		int panjangJudul1 = strlen(" LOGIN ");
		cout << "++" << string(lebarKotak, '-') << "++" << endl;
		cout << "++" << string((lebarKotak - panjangJudul1) / 2, ' ') << " LOGIN " << string((lebarKotak - panjangJudul1) / 2, ' ') << " ++" << endl;
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
		getline(cin, usn);   // <-- HAPUS "cin >> usn;" yang tadinya ada di atas baris ini
		cout << "\033[14C";
		cin >> pass;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\033[1B\r" << endl;

		bool loginSuccess = false;

		for (int i = 0; i < jumlahUser; i++)
		{
			if (usn == daftarUser[i].username && pass == daftarUser[i].password)
			{
				loginSuccess = true;
				userAktif = &daftarUser[i];

				int panjangPesanSukses = strlen(" LOGIN BERHASIL ");
				cout << "++" << string(lebarKotak, '-') << "++" << endl;
				cout << "++" << string((lebarKotak - panjangPesanSukses) / 2, '-') << " LOGIN BERHASIL " << string((lebarKotak - panjangPesanSukses) / 2, '-') << "-++" << endl;
				cout << "++" << string(lebarKotak, '-') << "++" << endl << endl;

				if (daftarUser[i].as == 1) {
					menuCustomer();
				}
				else if (daftarUser[i].as == 2) {
					menuKurir();
				}
				else if (daftarUser[i].as == 3) {
					menuMitra();
				}

				break;
			}
		}

		if (!loginSuccess)
		{
			int panjangPesanGagal = strlen(" USERNAME ATAU PASSWORD SALAH ");
			cout << "++" << string(lebarKotak, '-') << "++" << endl;
			cout << "++" << string((lebarKotak - panjangPesanGagal) / 2 - 1, '-') << " USERNAME ATAU PASSWORD SALAH " << string((lebarKotak - panjangPesanGagal) / 2, '-') << "-++" << endl;
			cout << "++" << string(lebarKotak, '-') << "++" << endl << endl;
		}

		cout << "Coba login kembali? (y/n): ";
		cin >> program;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		ulangi = (program == 'y' || program == 'Y');
	}
}

void registerUser(User daftarUser[], int& jumlahUser)
{
	int lebarKotak = 50;
	string menu_registrasi[] = {
		   "Username : ",
		   "Password : ",
		   "Tanggal Lahir : ",
		   "No Handphone : ",
		   "Email : ",
		   "Alamat : "
	};

	// jaga-jaga kalau sebelum fungsi ini ada cin >> (misal input menu)
	// yang meninggalkan sisa newline di buffer
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < 6; i++) {
		int sisaLebarMenu = lebarKotak - menu_registrasi[i].length() + 1;
		cout << "|| " << menu_registrasi[i] << right << setw(sisaLebarMenu) << " ||" << endl;
	}
	cout << "++" << string(lebarKotak, '-') << "++" << endl;
	cout << "\033[7A\033[14C";

	getline(cin, daftarUser[jumlahUser].username);

	cout << "\033[14C";
	cin >> daftarUser[jumlahUser].password;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // <-- penting

	cout << "\033[19C";
	getline(cin, daftarUser[jumlahUser].tanggalLahir);

	cout << "\033[18C";
	cin >> daftarUser[jumlahUser].nohp;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // <-- penting

	cout << "\033[11C";
	cin >> daftarUser[jumlahUser].email;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // <-- penting

	cout << "\033[12C";
	getline(cin, daftarUser[jumlahUser].alamat);

	cout << "\033[1B";
	int panjangJudul3 = strlen(" Registrasi Berhasil ");
	cout << "++" << string((lebarKotak - panjangJudul3) / 2, '-') << " Registrasi Berhasil " << string((lebarKotak - panjangJudul3) / 2, '-') << "-++" << endl;
	cout << "++" << string(lebarKotak, '-') << "++" << endl << endl;

	jumlahUser++;
}


