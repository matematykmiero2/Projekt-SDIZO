#include "projekt.h"

class Lista
{
	struct Elemlist {
		int dane;
		Elemlist *next, * prev;
	};

	Elemlist* head;
	Elemlist* tail;

	
public:
	Lista();
	~Lista();
	void daneZPliku(string plik);
	Elemlist* czyZawiera(int wartosc);
	void dodaj(int index, int wartosc);
	void dodajp(int wartosc);
	void dodajk(int wartosc);
	void usun(int wartosc);
	void usunp();
	void usunk();
	void wyswietl();
	void wyswietlOdTylu();
	void stworz(int size);
	int rozmiar();
	void czas(int ilosc_wyk, int wielkosc, int ilosc_op);
};