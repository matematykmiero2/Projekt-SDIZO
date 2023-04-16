#include "projekt.h"

class Kopiec
{
	int* kopiec;
	int ilosc;
public:
	Kopiec();
	~Kopiec();
	void daneZPliku(string plik);
	int czyZawiera(int wartosc);
	void dodaj(int wartosc);
	void wyswietl();
	void usunW(int i);
	void usunKorzen();
	void gotowiec(string sp, string sn, int v);
	void stworz(int size);
	void naprawianieg(int rozmiar);
	void naprawianied(int id);
	void naprawienieOdId(int id);
	void floyd();
	void czas(int ilosc_wyk, int wielkosc, int ilosc_op);
};