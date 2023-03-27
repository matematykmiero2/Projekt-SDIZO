#include "projekt.h"

class Tablica
{
	int* tablica;
	int ilosc;
public:
	Tablica();
	~Tablica();
	Tablica(int l);
	void daneZPliku(string plik);
	int czyZawiera(int wartosc);
	void dodaj(int index, int wartosc);
	void usun(int index);
	void wyswietl();
	void stworz(int size);
	void czas(int ilosc_wyk, int wielkosc, int ilosc_op);
};