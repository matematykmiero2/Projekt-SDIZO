#include "Lista.h"
#include "chrono"
#include "Bst.h"
using namespace std;
int X = 10, Y = 100, Z = 5;
string cR, cL, cP;
int wezly = 0;


void Bst:: printBT(string sp, string sn, Elemheap* v)			//GOTOWIEC
{
	string s;

	if (v)
	{
		s = sp;
		if (sn == cR) s[s.length() - 2] = ' ';
		printBT(s + cP, cR, v->prawy);

		s = s.substr(0, sp.length() - 2);
		cout << s << sn << v->dane << endl;

		s = sp;
		if (sn == cL) s[s.length() - 2] = ' ';
		printBT(s + cP, cL, v->lewy);
	}
}


Bst::Bst()
{
	root = nullptr;
}

Bst::~Bst()
{
	while (root) (usun(root->dane));
}

void Bst::daneZPliku(string plik)
{
	ifstream odczyt(plik);
	if (odczyt.is_open()) {
		wezly = 0;
		root = nullptr;
		int il, x;
		odczyt >> il;
		for (int i = 0; i < il; i++) {
			odczyt >> x;
			dodaj(x);
		}
	//	wyswietl();
		
		balansowanie();

	}
	else {
		cout << "\nNie udalo sie otworzyc pliku\n";
	}
}

Bst::Elemheap* Bst::czyZawiera(int wartosc)			//OK
{
	return czyZawiera2(root, wartosc);
}
Bst::Elemheap* Bst::czyZawiera2(Elemheap* buf, int wartosc)			//OK
{
	if (buf == NULL || buf->dane == wartosc)return buf;
	if (wartosc < buf->dane)return(czyZawiera2(buf->lewy, wartosc));
	else return(czyZawiera2(buf->prawy, wartosc));
}

void Bst::rotacjaPrawo(Elemheap* A)		//wygl¹da git
{
	if (A == NULL)return;
	if (A->lewy == NULL)return;
	Elemheap* P = A->rodzic;
	Elemheap* B = A->lewy;

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

void Bst::rotacjaLewo(Elemheap* A)	// jak w prawo tylko w lewo
{
	if (A == NULL)return;
	if (A->prawy == NULL)return;
	Elemheap* P = A->rodzic;
	Elemheap* B = A->prawy;

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

void Bst::prostowanie()	//jak rostacja dzia³a to to te¿
{
	Elemheap* temp = root;
	while (temp != NULL) {
		if (temp->lewy != NULL) {
			rotacjaPrawo(temp);
			temp = temp->rodzic;
		}
		else temp = temp->prawy;
	}
	//cout << "\n\nPo wyprostowaniu\n";
	//wyswietl();
}

void Bst::balansowanie()			//OK
{
	
	prostowanie();
	int x = log2(wezly+1);
	int m = pow(2, x) - 1;
	Elemheap* buf,*bufi;

	buf = root;
	bufi = buf;
	for (int i = 0; i < wezly - m; i++) {
		buf = bufi;
		bufi = buf->prawy->prawy;
		rotacjaLewo(buf);
		
	}

	while (m > 1) {
		m = m / 2;
		buf = root;
		bufi = buf;
		for (int i = 0; i < m; i++) {
			buf = bufi;
			bufi = buf->prawy->prawy;
			rotacjaLewo(buf);
		}
	}
	
		
	
}

void Bst::dodaj(int wartosc)			//BEZ RÓWNOWAZENIA
{
	wezly++;
	Elemheap* nowy= new Elemheap();
	nowy->dane = wartosc;
	Elemheap* y = NULL;
	Elemheap* x = root;

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
	if (y == NULL)
		root = nowy;
	else {
		if (nowy->dane < y->dane) {
			y->lewy = nowy;
		}
		else {
			y->prawy = nowy;
		}
		
	}
	balansowanie();
}

void Bst::usun(int wartosc)
{
	Elemheap* y = NULL;
	Elemheap* x = root;
	Elemheap* id = czyZawiera(wartosc);
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
	wezly--;
	balansowanie();
}

Bst::Elemheap* Bst::minimum(Elemheap* buf)			//OK
{
	while (buf->lewy != NULL)
		buf = buf->lewy;
	return buf;
}

Bst::Elemheap* Bst::maksimum(Elemheap* buf)			//OK
{
	while (buf->prawy != NULL)
		buf = buf->prawy;
	return buf;
}

Bst::Elemheap* Bst::nastepnik(Elemheap* buf)
{
	Elemheap* buft = new Elemheap();
	if (buf->prawy != NULL) return minimum(buf->prawy);
	buft = buf->rodzic;
	while (buft != NULL && buft->lewy != buf) {
		buf = buft;
		buft = buf->rodzic;
	}
	return buft;
}

Bst::Elemheap* Bst::poprzednik(Elemheap* buf)
{
	Elemheap* buft = new Elemheap();
	if (buf->lewy != NULL) return maksimum(buf->lewy);
	buft = buf->rodzic;
	while (buft != NULL && buft->prawy != buf) {
		buf = buft;
		buft = buf->rodzic;
	}
	return buft;
}

void Bst::wyswietl()			//OK
{
	cout << "\n\n";
	cR = cL = cP = "  ";
	cR[0] = 218; cR[1] = 196;
	cL[0] = 192; cL[1] = 196;
	cP[0] = 179;

	printBT("", "", root);



	if (root != NULL) {
		cout << "\nPreorder\n";
		preorder(root);
		cout << "\nInorder\n";
		inorder(root);
		cout << "\npostorder\n";
		postorder(root);
		cout << "\n\nMinimum = " << minimum(root)->dane;
		cout << "\n\Maksimum = " << maksimum(root)->dane;
	}
	
}

void Bst::P(Elemheap* p)			//OK
{	
	cout << p->dane << " ";
}

void Bst::preorder(Elemheap* p)			//OK
{
	if (p == NULL) return;
	P(p);
	preorder(p->lewy);
	preorder(p->prawy);

}

void Bst::inorder(Elemheap* p)			//OK
{
	if (p == NULL) return;
	inorder(p->lewy);
	P(p);
	inorder(p->prawy);
}

void Bst::postorder(Elemheap* p)			//OK
{
	if (p == NULL) return;
	postorder(p->lewy);
	postorder(p->prawy);
	P(p);
}

void Bst::stworz(int size)
{
	wezly = 0;
	root = NULL;
	int liczba;
	for (int i = 0; i < size; i++) {
		liczba = rand() % 100;
		dodaj(liczba);
	}
	
}

void Bst::czas(int ilosc_wyk, int wielkosc, int ilosc_op) {									//OK
	ofstream plik1("czasy_bst1.txt");
	ofstream plik2("czasy_bst2.txt");
	ofstream plik3("czasy_bst3.txt");
	ofstream plik4("czasy_bst4.txt");
	using namespace std::chrono;
	srand(time(NULL));
	int a;
	int wielkoscb, ilosc_opb;
	auto old = steady_clock::now();
	auto t1 = steady_clock::now() - old;
	auto t2 = steady_clock::now() - old;
	auto t3 = steady_clock::now() - old;
	auto t4 = steady_clock::now() - old;

	plik1 << "Dodawanie elementu z rownowazeniem\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 6; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;
		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\nDodawanie elementu z rownowazeniem";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);
			for (int j = 0; j < ilosc_op; j++) {
				a = rand() % 10000;
				old = steady_clock::now();
				dodaj(a);
				t1 += steady_clock::now() - old;
			}
		}
		cout << endl << i << " Uzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik1 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik2 << "Usuwanie korzenia\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 6; i++) {
		old = steady_clock::now();
		t2 = steady_clock::now() - old;
		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\nUsuwanie korzenia";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);
			old = steady_clock::now();
			for (int j = 0; j < ilosc_opb; j++) {
				usun(root->dane);
			}
			t2 += steady_clock::now() - old;
		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t2).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t2).count() / (ilosc_wyk);
		plik2 << wielkoscb << ";" << duration_cast<nanoseconds>(t2).count() / (ilosc_wyk) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik3 << "Rownowazenie drzewa\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 6; i++) {
		old = steady_clock::now();
		t3 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\nRownowazenie drzewa";
		for (int i = 0; i < ilosc_wyk; i++) {
			
				stworz(wielkoscb);
				old = steady_clock::now();
				balansowanie();
				t3 = steady_clock::now() - old;
			
		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t3).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t3).count() / (ilosc_wyk);
		plik3 << wielkoscb << ";" << duration_cast<nanoseconds>(t3).count() / (ilosc_wyk) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik4 << "Wyszukiwanie elementu\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	Elemheap* temp;
	for (int i = 0; i < 6; i++) {
		old = steady_clock::now();
		t4 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\nWyszukiwanie elementu";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);
			
			for (int j = 0; j < ilosc_opb; j++) {
				a = rand() % 1000;
				old = steady_clock::now();
				temp=czyZawiera(a);
				t4 += steady_clock::now() - old;
			}
			
		}
		cout << temp;
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t4).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t4).count() / (ilosc_wyk * ilosc_opb);
		plik4 << wielkoscb << ";" << duration_cast<nanoseconds>(t4).count() / (ilosc_wyk * ilosc_opb) << endl;
	}

	plik1.close();
	plik2.close();
	plik3.close();
	plik4.close();

}