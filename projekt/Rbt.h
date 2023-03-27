#include "projekt.h"

class Rbt
{
	struct Elem {
		int dane;
		Elem* rodzic, * lewy, * prawy;
		char kolor;	// B - czarne R - czerwone
	};

	Elem* root;

public:
	Rbt();
	~Rbt();
	void daneZPliku(string plik);
	Elem* czyZawiera(int wartosc);
	void dodaj(int wartosc);
	void rotacjaPrawo(Elem* A);
	void rotacjaLewo(Elem* A);
	void napraw(Elem* wstawiony);
	void naprawUsuniecie(Elem* wstawiony);
	Elem* minimum(Elem* buf);
	Elem* maksimum(Elem* buf);
	Elem* nastepnik(Elem* buf);
	Elem* poprzednik(Elem* buf);
	void usun(int wartosc);
	void wyswietl();
	void preorder(Elem* p);
	void inorder(Elem* p);
	void postorder(Elem* p);
	void P(Elem* p);
	void stworz(int size);
	void czas();

	void printRBT(string sp, string sn, Elem* v);
};