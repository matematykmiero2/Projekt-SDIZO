#include "Rbt.h"
#include "chrono"
string crr, clr, cpr;

//Funkcja wyswietlajaca drzewo
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
	while (root!=NULL)usun(root->dane);
}

//funkcja pobiera dane z pliku i tworzy z nich drzewo
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

//funkcje zwracajace adres elementu w tablicy o zadanej wartosci
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

//funkjca dodajaca element o zadanej wartosci i naprawia drzewo
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

//rotacja w prawo wzgledem elementu A
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

//rotacja w lewo wzgledem elementu A
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

//funkcja przywracajaca wlasnosci drzewa po dodadniu elementu
void Rbt::napraw(Elem* wstawiony)
{
	/*
	Mo¿liwe przypadki:
	A. Stryj jest czerwony 
	-> zamieniamy kolor ojca i stryja na czarny, dziadka kolorujemy na czerwono

	B. Stryj jest czarny a wstawiany wêze³ jest lewym potomkiem
	-> zmieniamy kolor ojca i dziadka
	->rotacja w prawo wzgledem dziadka
	
	C. Stryj jest czarny, a wstawiany wêze³ jest prawym potomkiem
	-> rotacja w lewo wzglêdem ojca
	i lustrzane...
	*/


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
			else {
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

//funkcja zwraca wartosc minimalna elementu w drzewie
Rbt::Elem* Rbt::minimum(Elem* buf)
{
	while (buf->lewy != NULL)
		buf = buf->lewy;
	return buf;
}

//funkcja zwraca wartosc maksymalna elementu w drzewie
Rbt::Elem* Rbt::maksimum(Elem* buf)
{
	while (buf->prawy != NULL)
		buf = buf->prawy;
	return buf;
}

//funkcja zwraca wskaznik na nastepnia
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

//funkcja zwraca wskaznik na poprzednika
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

//funkcja usuwa element o zadanej wartosci
void Rbt::usun(int wartosc)	
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

	if (y->kolor != 'R') {	// Jak jest czerwone to nie naprawiamy
		naprawUsuniecie(y);
	}
	if (y->rodzic == NULL) root = x;
	else {
		if (y == y->rodzic->lewy) y->rodzic->lewy = x;
		else y->rodzic->prawy = x;
	}
	if (y != id) {
		id->dane = y->dane;
	}
	delete y;
	
}

//funkcja przywracajaca wlasnosci drzewa po usunieciu elementu
void Rbt::naprawUsuniecie(Elem* naprawiany)
{
	/*
	1. brat jest czerwony
	-> rotacja w lewo wzglêdem ojca.
	-> zamiana kolorów ojca i stryja

	
	2. brat jest czarny i ma czarnych potomków
	->zamieniamy kolor brata na czerwony
	
	3. brat czarny i lewy syn czerwony a prawy czarny
	-> rotacja w prawo wzglêdem brata
	->zamiana kolorów brata i jego prawego potomka
	
	4. Brat wêz³a A jest czarny a prawy syn jest czerwony
	-> rotacja w lewo wzglêdem ojca
	-> zamiana koloru prawego potomka brata na czarny
	-> zmiana koloru brata na kolor rodzica
	-> zamiana koloru ojca na czarny


	
	*/
	Elem* brat = new Elem();
	char lewyBrata, prawyBrata;	//potrzebne, ¿eby nie by³o problemu z "wy³uskaniem z NULLa"
	while (naprawiany != root && naprawiany->kolor == 'B') {
		if (naprawiany->rodzic->lewy == naprawiany) {
			Elem* brat = naprawiany->rodzic->prawy;

			if (brat == NULL) break;
			else{
				if (brat->kolor == 'R') {				//Przypadek 1. brat jest czerwony
					rotacjaLewo(naprawiany->rodzic);
					naprawiany->rodzic->kolor = 'R';
					brat->kolor = 'B';
					brat = naprawiany->rodzic->prawy;
				}

				if (brat == NULL) break;// Przypisanie do lewyBrata i prawyBrata kolory potomków brata
				else{
					lewyBrata = 'B';
					prawyBrata = 'B';

					if (brat->lewy != NULL) {
						lewyBrata = brat->lewy->kolor;
					}

					if (brat->prawy != NULL) {
						prawyBrata = brat->prawy->kolor;
					}

					if (lewyBrata == 'B' && prawyBrata == 'B') {	//Przypadek 2. CZarny brat i czarne dzieci
						brat->kolor = 'R';
						naprawiany = naprawiany->rodzic;
					}
					else {
						if (lewyBrata == 'R' && prawyBrata == 'B') {	//Przykadek 3.
							rotacjaLewo(naprawiany->rodzic);
							brat->rodzic->kolor = 'B';
							brat->kolor = 'R';
						}// po tej operacji przypadek 4
						rotacjaLewo(naprawiany->rodzic);				//Przykadek 4.
						if(brat->prawy)brat->prawy->kolor = 'B';
						brat->kolor = naprawiany->rodzic->kolor;
						naprawiany->rodzic->kolor = 'B';
					}
				}
			}
		}
		else//LUSTRZANE
		{
			Elem* brat = naprawiany->rodzic->lewy;
			if (brat == NULL)break;
			else{
				if (brat->kolor == 'R') {				//Przypadek 1. brat jest czerwony
					rotacjaPrawo(naprawiany->rodzic);
					naprawiany->rodzic->kolor = 'R';
					brat->kolor = 'B';
					brat = naprawiany->rodzic->lewy;
				}
				if (brat == NULL)break;
				else{
					lewyBrata = 'B';
					prawyBrata = 'B';

					if (brat->lewy != NULL) {
						lewyBrata = brat->lewy->kolor;
					}

					if (brat->prawy != NULL) {
						prawyBrata = brat->prawy->kolor;
					}
					if (prawyBrata == 'B' && lewyBrata == 'B') {	//Przypadek 2. CZarny brat i czarne dzieci
						brat->kolor = 'R';
						naprawiany = naprawiany->rodzic;
					}
					else {
						if (prawyBrata == 'R' && lewyBrata == 'B') {	//Przykadek 3.
							rotacjaPrawo(naprawiany->rodzic);
							brat->rodzic->kolor = 'B';
							brat->kolor = 'R';
						}// po tej operacji przypadek 4
						rotacjaPrawo(naprawiany->rodzic);			//Przykadek 4.
						if(brat->lewy)brat->lewy->kolor = 'B';
						brat->kolor = naprawiany->rodzic->kolor;
						naprawiany->rodzic->kolor = 'B';
					}
				}
				
			}
		}
	}
	naprawiany->kolor = 'B';
}


//funkcja wyswietla drzewo
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
	cout << p->kolor << ": " << p->dane << " ";
	preorder(p->lewy);
	preorder(p->prawy);
}

void Rbt::inorder(Elem* p)
{
	if (p == NULL) return;
	inorder(p->lewy);
	cout << p->kolor << ": " << p->dane << " ";
	inorder(p->prawy);
}

void Rbt::postorder(Elem* p)
{
	if (p == NULL) return;
	postorder(p->lewy);
	postorder(p->prawy);
	cout << p->kolor << ": " << p->dane << " ";
}

//funkcja tworzy drzewo o zadanej wielkosci
void Rbt::stworz(int size)
{
	srand(time(NULL));
	root = NULL;
	int liczba;
	for (int i = 0; i < size; i++) {
		liczba = rand() % 1000000;
		dodaj(liczba);
	}

}

//funkcja do pomiaru czasow
void Rbt::czas(int ilosc_wyk, int wielkosc, int ilosc_op) {									//OK
	ofstream plik1("czasy_rbt1.txt");
	ofstream plik2("czasy_rbt2.txt");
	ofstream plik3("czasy_rbt3.txt");
	ofstream plik4("czasy_rbt4.txt");
	using namespace std::chrono;
	srand(time(NULL));
	int a;
	int wielkoscb, ilosc_opb;
	auto old = steady_clock::now();
	auto t1 = steady_clock::now() - old;

	plik1 << "Dodawanie elementu\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 10; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;
		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\nDodawanie elementu";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);
			for (int j = 0; j < ilosc_opb; j++) {
				a = rand() % 1000000;
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
	for (int i = 0; i < 10; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;
		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 10;
		cout << "\n\nUsuwanie korzenia";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);

			for (int j = 0; j < ilosc_opb; j++) {
				old = steady_clock::now();
				usun(root->dane);
				t1 += steady_clock::now() - old;
			}

		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik2 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik3 << "Tworzenie drzewa\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 10; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\Tworzenie drzewa";
		for (int i = 0; i < ilosc_wyk; i++) {
			int liczba;
				old = steady_clock::now();
				stworz(wielkoscb);
				t1 = steady_clock::now() - old;
				old = steady_clock::now();
				for (int i = 0; i < wielkoscb; i++) {
					liczba = rand() % 1000000;
				}
				t1 -= old - steady_clock::now();
		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk );
		plik3 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik4 << "Wyszukiwanie elementu\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	Elem* temp;
	for (int i = 0; i < 10; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\nWyszukiwanie elementu";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);
			
			for (int j = 0; j < ilosc_opb; j++) {
				a = rand() % 1000000;
				old = steady_clock::now();
				temp = czyZawiera(-1);
				t1 += steady_clock::now() - old;
			}

		}
		cout << temp;
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik4 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}

	plik1.close();
	plik2.close();
	plik3.close();
	plik4.close();

}