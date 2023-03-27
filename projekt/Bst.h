#include "projekt.h"

class Bst
{
	struct Elemheap {
		int dane;
		Elemheap* rodzic, * lewy,*prawy;
	};

	Elemheap* root;

public:
	Bst();
	~Bst();
	void daneZPliku(string plik);
	Elemheap* czyZawiera(int wartosc);
	Elemheap* czyZawiera2(Elemheap* buf,int wartosc);
	void rotacjaPrawo(Elemheap* A);
	void rotacjaLewo(Elemheap* A);
	void prostowanie();
	void balansowanie();
	void dodaj(int wartosc);
	void usun(int wartosc);
	Elemheap* minimum(Elemheap* buf);
	Elemheap* maksimum(Elemheap* buf);
	Elemheap* nastepnik(Elemheap* buf);
	Elemheap* poprzednik(Elemheap* buf);
	void wyswietl();
	void P(Elemheap* p);
	void preorder(Elemheap* p);
	void inorder(Elemheap* p);
	void postorder(Elemheap* p);
	void stworz(int size);
	void czas(int ilosc_wyk, int wielkosc, int ilosc_op);

	void printBT(string sp, string sn, Elemheap* v);
};