#include "Lista.h"
#include "chrono"


 int e = 20, b = 20000, c = 5000;	// e - ilosc wykonan, b - wielkosc listy, c - ilosc do dodania/usuniecia

Lista::Lista() {
	head = nullptr;
	tail = nullptr;
}


Lista :: ~Lista() {
	while (head) usunp();
}

//funkcja pobiera dane z pliku tekstoweg i generuje z nich liste
void Lista::daneZPliku(string plik) {									//OK
	ifstream odczyt(plik);
	if (odczyt.is_open()) {
		head = nullptr;
		tail = nullptr;
		int il, x;
		odczyt >> il;
		for (int i = 0; i < il; i++) {
			odczyt >> x;
			dodajk(x);
		}
	}
	else {
		cout << "\nNie udalo sie otworzyc pliku\n";
	}
}

//funkcja zwraca wskaznik na miejsce w liscie gdzie znajduje sie szukany element
Lista :: Elemlist* Lista::czyZawiera(int wartosc)									//OK
{
	Elemlist* temp=head;
	while (temp != nullptr) {
		if (temp->dane == wartosc) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

//funkcja dodaje element na zadany index
void Lista::dodaj(int index, int wartosc)
{
	if (index > rozmiar())return;
	if (index == 0) {
		dodajp(wartosc);
		return;
	}
	if (index == rozmiar()) {
		dodajk(wartosc);
		return;
	}
		Elemlist* p = head;
		for (int i = 0; i < index; i++) {
			p = p->next;
		}
		Elemlist* pprev, *pnowy;
		pnowy = new Elemlist();
		pprev = p->prev;
		pnowy->dane = wartosc;
		pnowy->next = p;
		pnowy->prev = pprev;
		pprev->next = pnowy;
		p->prev = pnowy;
}


// dodanie na poczatek listy
void Lista::dodajp(int wartosc) {									//OK
	
	Elemlist* p = new Elemlist();
	p->dane = wartosc;
	p->prev = nullptr;
	p->next = head;
	if (head != nullptr) {
		head->prev = p;
	}
	head = p;
	if (tail== nullptr) {
		tail = p;
	}

}

//dodanie na koniec listy
void Lista::dodajk(int wartosc) {									//OK
	if (head == nullptr) {
		dodajp(wartosc);
		return;
	}

	Elemlist* p = new Elemlist();
	p->dane = wartosc;
	tail->next = p;
	p->prev = tail;
	tail = p;

}


//usuwanie z poczatku
void Lista::usunp()								//OK
{

	if (head == nullptr) {
		return;
	}
	Elemlist* p = head;
	head = head->next;
	delete p;
	if (head != nullptr) {
		head->prev = nullptr;
	}
}

//usuwanie z konca
void Lista::usunk()								//OK
{
	if (head == nullptr) {
		return;
	}
	if (tail == head) {
		usunp();
		return;
	}
	Elemlist* p = tail;
	tail = tail->prev;
	tail->next = nullptr;
	delete p;

}

//usuwanie elementu o zadanej wartosci z listy
void Lista::usun(int wartosc) {								//OK
	Elemlist* p = czyZawiera(wartosc);
	if (p == NULL)return;
	if (rozmiar() == 1) {
		head = NULL;
		tail = NULL;
		return;
	}
	if (p == head) {
		usunp();
		return;
	}
	if (p == tail) {
		usunk();
		return;
	}
	Elemlist* pprev, * pnext;
	pprev = p->prev;
	pnext = p->next;

	pprev->next = pnext;
	pnext->prev = pprev;

	delete p;

}


//usuwanie elementu o zadanym indeksie z listy
void Lista::usuns(int index) {								//OK
	Elemlist* usuwany = head;
	for (int i = 0; i < index; i++) {
		usuwany = usuwany->next;
	}

	Elemlist* pprev, * pnext;
	pprev = usuwany->prev;
	pnext = usuwany->next;

	pprev->next = pnext;
	pnext->prev = pprev;

	delete usuwany;

}

//funkjca wyswietlajaca liste
void Lista::wyswietl() {								//OK
	Elemlist* temp = head;
	cout << endl;
	while (temp) {
		cout << temp->dane << " ";
		temp = temp->next;
	}
	
	wyswietlOdTylu();
}

//funkjca wyswietlajaca liste od tylu
void Lista::wyswietlOdTylu()								//OK
{
	Elemlist* temp = tail;
	cout << endl;
	while (temp) {
		cout << temp->dane << " ";
		temp = temp->prev;
	}
	
}
//funkcja tworzy liste o zadanej wielkosci i wypelnia losowymi wartosciami
void  Lista::stworz(int size) {								//OK
	head = nullptr;
	tail = nullptr;
	srand(time(NULL));
	int x;
	for (int i = 0; i < size; i++) {
		x = rand() % 1000000;
		dodajk(x);
	}
	
}

//zwraca informacje o ilosci elementow
int Lista::rozmiar()
{
	Elemlist* temp = head;
	int licznik=0;
	while (temp) {
		licznik++;
		temp = temp->next;
	}
	return licznik;
}

//funkcja wykonujue pomiary czasow
void Lista::czas(int ilosc_wyk, int wielkosc, int ilosc_op) {									//OK
	ofstream plik1("czasy_lista1.txt");
	ofstream plik2("czasy_lista2.txt");
	ofstream plik3("czasy_lista3.txt");
	ofstream plik4("czasy_lista4.txt");
	ofstream plik5("czasy_lista5.txt");
	ofstream plik6("czasy_lista6.txt");
	ofstream plik7("czasy_lista7.txt");
	using namespace std::chrono;
	srand(time(NULL));
	int a;
	int wielkoscb, ilosc_opb;
	auto old = steady_clock::now();
	auto t1 = steady_clock::now() - old;

	
	plik1 << "Dodawanie na pocz¹tek\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	int liczba;
	for (int i = 0; i < 10; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\nDodawanie na poczatek";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);
			
			for (int j = 0; j < ilosc_opb; j++) {
				liczba = rand() % 1000000;
				old = steady_clock::now();
				dodajp(liczba);
				t1 += steady_clock::now() - old;
			}
			
		}
		cout << endl << i << " Uzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik1 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik2 << "Dodawanie na koniec\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;

	for (int i = 0; i < 10; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\nDodawanie na koniec";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);
	
			for (int j = 0; j < ilosc_opb; j++) {
				liczba = rand() % 1000000;
				old = steady_clock::now();
				dodajk(55);
				t1 += steady_clock::now() - old;
			}
	
		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik2 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik3 << "Dodawanie nie na poczatek nie na koniec\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;

	for (int i = 0; i < 10; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\nDodawanie nie na poczatek i nie na koniec";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);

			for (int j = 0; j < ilosc_opb; j++) {
				a = 1 + rand() % (wielkoscb + j);
				liczba = rand() % 1000000;
				old = steady_clock::now();
				dodaj(a, liczba);
				t1 += steady_clock::now() - old;
			}

		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik3 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik4 << "Uzuwanie z pocz¹tku\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 10; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\nUsowanie z poczatku";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);
			old = steady_clock::now();
			for (int j = 0; j < ilosc_opb; j++) {
				usunp();
			}
			t1 += steady_clock::now() - old;
		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik4 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
/////////////////////////////////////////////////////////////////////////////////////////////
	plik5 << "Usowanie ze srodka\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 10; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = ilosc_opb * 2;
		cout << "\n\nUsowanie ze srodka";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);

			for (int j = 0; j < ilosc_opb; j++) {
				a = 1 + rand() % (wielkoscb - j - 2);
				old = steady_clock::now();
				usuns(a);
				t1 += steady_clock::now() - old;
			}

		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik5 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	plik6 << "Usowanie z konca\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 10; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = ilosc_opb * 2;
		cout << "\n\nUsowanie z konca";
		for (int i = 0; i < ilosc_wyk; i++) {
			stworz(wielkoscb);

			for (int j = 0; j < ilosc_opb; j++) {
				old = steady_clock::now();
				usunk();
				t1 += steady_clock::now() - old;
			}

		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik6 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik7 << "Wyszukiwanie elementu\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	Elemlist* temp;
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
				temp=czyZawiera(a);
				t1 += steady_clock::now() - old;
			}

		}
		cout << temp;
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik7 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	

	plik1.close();
	plik2.close();
	plik3.close();
	plik4.close();
	plik5.close();
	plik6.close();
	plik7.close();
}

