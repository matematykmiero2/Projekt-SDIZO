#include "Rbt.h"

string crr, clr, cpr;

void Rbt::printRBT(string sp, string sn, Elem* v)		//GOTOWIEC
{
	string t;

	if (v != NULL)
	{
		t = sp;
		if (sn == crr) t[t.length() - 2] = ' ';
		printRBT(t + cpr, crr, v->prawy);

		t = t.substr(0, sp.length() - 2);
		cout << t << sn << v->kolor << ":" << v->dane << endl;

		t = sp;
		if (sn == clr) t[t.length() - 2] = ' ';
		printRBT(t + cpr, clr, v->lewy);
	}
}




Rbt::Rbt()
{
	root = nullptr;
}

Rbt::~Rbt()
{
	while (root)usun(root->dane);
}

void Rbt::daneZPliku(string plik)
{
	ifstream odczyt(plik);
	if (odczyt.is_open()) {
		root = nullptr;
		int il, x;
		odczyt >> il;
		for (int i = 0; i < il; i++) {
			odczyt >> x;
			dodaj(x);
		}
	}
	else {
		cout << "\nNie udalo sie otworzyc pliku\n";
	}
}

Rbt::Elem* Rbt::czyZawiera(int wartosc)
{
	Elem* temp = root;

	while (temp)
	{
		if (temp->dane == wartosc) return temp;
		if (wartosc > temp->dane) temp = temp->prawy;
		else temp = temp->lewy;
	}
	return NULL;
}

void Rbt::dodaj(int wartosc)
{
	Elem* nowy = new Elem();
	nowy->dane = wartosc;
	nowy->kolor = 'R';
	Elem* y = NULL;
	Elem* x = root;

	while (x != NULL) {
		y = x;
		if (nowy->dane < x->dane) {
			x = x->lewy;
		}
		else {
			x = x->prawy;
		}
	}
	nowy->rodzic = y;
	if (y == NULL) {
		root = nowy;
	}
		
	else {
		if (nowy->dane < y->dane) {
			y->lewy = nowy;
		}
		else {
			y->prawy = nowy;
		}

	}

	if (nowy == root) {
		nowy->kolor = 'B';
		return;
	}

	if (nowy->rodzic->rodzic == NULL) return;
	

	napraw(nowy);
}

void Rbt::rotacjaPrawo(Elem* A)
{
	if (A == NULL)return;
	if (A->lewy == NULL)return;
	Elem* P = A->rodzic;
	Elem* B = A->lewy;

	A->lewy = B->prawy;
	if (B->prawy) B->prawy->rodzic = A;
	B->prawy = A;
	A->rodzic = B;
	B->rodzic = P;
	if (P) {
		if (P->lewy == A)P->lewy = B;
		else P->prawy = B;
	}
	else root = B;

}

void Rbt::rotacjaLewo(Elem* A)
{

	if (A == NULL)return;
	if (A->prawy == NULL)return;
	Elem* P = A->rodzic;
	Elem* B = A->prawy;

	A->prawy = B->lewy;
	if (B->lewy) B->lewy->rodzic = A;
	B->lewy = A;
	A->rodzic = B;
	B->rodzic = P;
	if (P) {
		if (P->lewy == A)P->lewy = B;
		else P->prawy = B;
	}
	else root = B;

}

void Rbt::napraw(Elem* wstawiony)
{
	Elem* stryj;
	while (wstawiony->rodzic->kolor == 'R')
	{
		if (wstawiony->rodzic == wstawiony->rodzic->rodzic->lewy)	//Rozpatrujemy przypadki gdy stryj jest prawym potomkiem
		{
			stryj = wstawiony->rodzic->rodzic->prawy;

			if (stryj && stryj->kolor == 'R')						//Przypadek A - stryj jest czerwony
			{
				wstawiony->rodzic->kolor = 'B';
				stryj->kolor = 'B';
				wstawiony->rodzic->rodzic->kolor = 'R';
				wstawiony = wstawiony->rodzic->rodzic;

			}
			else{ 
				if (wstawiony == wstawiony->rodzic->prawy)			//Przypadek C - stryj jest czarny i wstawiany wêze³ jest prawym potomkiem
			{
				wstawiony = wstawiony->rodzic;
				rotacjaLewo(wstawiony);
			}//po tej operacji mamy przypadek C sprowadzony do przypadku B

			//Rozpatrujemy przypadek B (czarny stryj,wstawiany jest lewym potomkiem)
			wstawiony->rodzic->kolor = 'B';
			wstawiony->rodzic->rodzic->kolor = 'R';
			rotacjaPrawo(wstawiony->rodzic->rodzic);
			wstawiony = root;
		}
		}
		else	//To samo (zamiana lewy i prawy) dla przypadku gdy stryj jest lewym potomkiem
		{                   
			stryj = wstawiony->rodzic->rodzic->lewy;

			if (stryj && stryj->kolor == 'R')						//Przypadek A - stryj jest czerwony
			{
				wstawiony->rodzic->kolor = 'B';
				stryj->kolor = 'B';
				wstawiony->rodzic->rodzic->kolor = 'R';
				wstawiony = wstawiony->rodzic->rodzic;

			}
			else {
				if (wstawiony == wstawiony->rodzic->lewy)			//Przypadek C - stryj jest czarny i wstawiany wêze³ jest prawym potomkiem
				{
					wstawiony = wstawiony->rodzic;
					rotacjaPrawo(wstawiony);
				}//po tej operacji mamy przypadek C sprowadzony do przypadku B

				//Rozpatrujemy przypadek B (czarny stryj,wstawiany jest lewym potomkiem)
				wstawiony->rodzic->kolor = 'B';
				wstawiony->rodzic->rodzic->kolor = 'R';
				rotacjaLewo(wstawiony->rodzic->rodzic);
				wstawiony = root;
			}
		}
		if (wstawiony == root)break;
	}
	root->kolor = 'B';

}

Rbt::Elem* Rbt::minimum(Elem* buf)
{
	while (buf->lewy != NULL)
		buf = buf->lewy;
	return buf;
}

Rbt::Elem* Rbt::maksimum(Elem* buf)
{
	while (buf->prawy != NULL)
		buf = buf->prawy;
	return buf;
}

Rbt::Elem* Rbt::nastepnik(Elem* buf)
{
	Elem* buft = new Elem();
	if (buf->prawy != NULL) return minimum(buf->prawy);
	buft = buf->rodzic;
	while (buft != NULL && buft->lewy != buf) {
		buf = buft;
		buft = buf->rodzic;
	}
	return buft;
}

Rbt::Elem* Rbt::poprzednik(Elem* buf)
{
	Elem* buft = new Elem();
	if (buf->lewy != NULL) return maksimum(buf->lewy);
	buft = buf->rodzic;
	while (buft != NULL && buft->prawy != buf) {
		buf = buft;
		buft = buf->rodzic;
	}
	return buft;
}

void Rbt::usun(int wartosc)	//jak dla bst
{
	Elem* y = NULL;
	Elem* x = root;
	Elem* id = czyZawiera(wartosc);
	if (id == NULL)return;
	if (id->lewy == NULL || id->prawy == NULL) y = id;
	else y = nastepnik(id);

	if (y->lewy != NULL) x = y->lewy;
	else x = y->prawy;

	if (x != NULL) x->rodzic = y->rodzic;

	if (y->rodzic == NULL) root = x;
	else {
		if (y == y->rodzic->lewy) y->rodzic->lewy = x;
		else y->rodzic->prawy = x;
	}
	if (y != id) id->dane = y->dane;

	delete y;
	naprawUsuniecie(id);
}

void Rbt::naprawUsuniecie(Elem* wstawiony) // Trzeba dorobiæ
{
	
}



void Rbt::wyswietl()
{
	
	crr = clr = cpr = "  ";
	crr[0] = 218; crr[1] = 196;
	clr[0] = 192; clr[1] = 196;
	cpr[0] = 179;

	printRBT("", "", root);
	
	if (root != NULL) {
		cout << "\nPreorder\n";
		preorder(root);
		cout << "\nInorder\n";
		inorder(root);
		cout << "\npostorder\n";
		postorder(root);
	}
	cout << endl << endl << endl << endl;
}

void Rbt::preorder(Elem* p)
{
	if (p == NULL) return;
	P(p);
	preorder(p->lewy);
	preorder(p->prawy);
}

void Rbt::inorder(Elem* p)
{
	if (p == NULL) return;
	inorder(p->lewy);
	P(p);
	inorder(p->prawy);
}

void Rbt::postorder(Elem* p)
{
	if (p == NULL) return;
	postorder(p->lewy);
	postorder(p->prawy);
	P(p);
}
void Rbt:: P(Elem* p) {
	cout <<p->kolor <<": " << p->dane << " ";
}

void Rbt::stworz(int size)
{
	srand(time(NULL));
	root = NULL;
	int liczba;
	for (int i = 0; i < size;i++) {
		liczba = rand() % 100;
		dodaj(liczba);
	}

}

void Rbt::czas()
{
}
