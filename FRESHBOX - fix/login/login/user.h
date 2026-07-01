#ifndef USER_H
#define USER_H

#include "produk.h"

enum user_as {
	customer = 1, kurir = 2, mitra = 3
};

struct User {
	string username = "";
	string password = "";
	string tanggalLahir;
	string email;
	string alamat;
	string nohp;
	user_as as;
};

const int MAX_USER = 10;
extern User daftarUser[MAX_USER];
extern int jumlahUser;
extern User *userAktif;



#endif 