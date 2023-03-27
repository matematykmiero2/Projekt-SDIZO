#include "Kopiec.h"
#include "chrono"

int x = 10, y = 10, z = 5;	// x - ilosc wykonan, y - wielkosc kopca, z - ilosc do dodania/usuniecia


string cr, cl, cp;

Kopiec::Kopiec()
{
	ilosc = 0;
	kopiec = new int[1000000];
}


Kopiec::~Kopiec()
{
	ilosc = NULL;
	delete kopiec;
}

void Kopiec::daneZPliku(string plik)				//OK
{
	ifstream odczyt(plik);
	if (odczyt.is_open()) {
		int il, x;
		odczyt >> il;
		ilosc = il;
		kopiec = new int[1000000];
		for (int i = 0; i < il; i++) {
			odczyt >> x;
			kopiec[i] = x;
		}
		odczyt.close();
		floyd();
	}
	else {
		cout << "\nNie udalo sie otworzyc pliku\n";
	}

}

int Kopiec::czyZawiera(int wartosc)				//OK
{
	for (int i = 0; i < ilosc; i++) {
		if (kopiec[i] == wartosc) {
			return i;
		}
	}
	return -1;
}

void Kopiec::dodaj(int wartosc)				//OK
{
	ilosc++;
	kopiec[ilosc-1] = wartosc;
	naprawianieg(ilosc - 1);
	
}


void Kopiec::wyswietl()				//OK
{
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;


	for (int i = 0; i < ilosc; i++) {
		cout << kopiec[i] << " ";
	}
	cout << endl << endl;
	gotowiec("", "", 0);
}

void Kopiec:: gotowiec(string sp, string sn, int v) {				//GOTOWIEC
	string s;

	if (v < ilosc)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		gotowiec(s + cp, cr, 2 * v + 2);

		s = s.substr(0, sp.length() - 2);

		cout << s << sn << kopiec[v] << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		gotowiec(s + cp, cl, 2 * v + 1);
	}
}

void Kopiec::stworz(int size)				
{
	ilosc = size;
	kopiec = new int[1000000];
	srand(time(NULL));
	int liczba;
	for (int i = 0; i < ilosc; i++) {
		liczba = rand() % 100;
		kopiec[i] = liczba;
	}
	floyd();
}



int rodzic(int i) {
	return (i-1) / 2;
}
int lewy(int i) {
	return 2*i + 1;
}
int prawy(int i) {
	return 2*i + 2;
}

void Kopiec::naprawianieg(int rozmiar)
{
	
	while (rozmiar > 0) {
		if (kopiec[rozmiar] > kopiec[rodzic(rozmiar)]) {
			int x = kopiec[rozmiar];
			kopiec[rozmiar] = kopiec[rodzic(rozmiar)];
			kopiec[rodzic(rozmiar)] = x;
			
		}
		rozmiar = rodzic(rozmiar);
	}
	return;
	
}

void Kopiec::usunW(int i) {

	int poz = czyZawiera(i);
	if (poz < 0) {
		cout << "\nBrak elementu\n";
		return;
	}
	kopiec[poz] = kopiec[ilosc - 1];
	kopiec[ilosc - 1] = NULL;
	ilosc--;
	if (kopiec[poz] < kopiec[lewy(poz)] || kopiec[poz] < kopiec[prawy(poz)]) naprawianied(poz);
	else naprawianieg(poz);
}


void Kopiec::naprawianied(int id)
{

	int bufW, bufId;
	boolean x;
	for (int i = id; i <= rodzic(ilosc); i++) {
		x = false;
		bufW = kopiec[i];
		bufId = i;
		if (kopiec[lewy(i)] >= bufW) {
			bufW = kopiec[lewy(i)];
			bufId = lewy(i);
			id = lewy(i);
			x = true;
		}
		if (kopiec[prawy(i)] > bufW) {
			bufW = kopiec[prawy(i)];
			bufId = prawy(i);
			id = prawy(i);
			x = true;
		}
		if (x) {
			kopiec[bufId] = kopiec[i];
			kopiec[i] = bufW;
		}
	}
}



void Kopiec::naprawienieOdId(int id) {
	
	if (id >= ilosc)return;
	int bufW, bufId;
	boolean x;
		x = false;
		bufW = kopiec[id];
		bufId = id;
		if (lewy(id) < ilosc && kopiec[lewy(id)] > bufW) {
			bufW = kopiec[lewy(id)];
			bufId = lewy(id);
			x = true;
		}
		if (prawy(id) < ilosc && kopiec[prawy(id)] > bufW) {
			bufW = kopiec[prawy(id)];
			bufId = prawy(id);
			x = true;
		}
		if (x) {
			kopiec[bufId] = kopiec[id];
			kopiec[id] = bufW;
			naprawienieOdId(bufId);
		}
}




void Kopiec::floyd() {
	int x = rodzic(ilosc);
	for (int i = x; i >= 0; i--) {
		naprawienieOdId(i);
	}
}


void Kopiec::czas(int ilosc_wyk, int wielkosc, int ilosc_op) {									//OK
	ofstream plik1("czasy_kopiec1.txt");
	ofstream plik2("czasy_kopiec2.txt");
	ofstream plik3("czasy_kopiec3.txt");
	ofstream plik4("czasy_kopiec4.txt");
	ofstream plik5("czasy_kopiec5.txt");
	using namespace std::chrono;
	srand(time(NULL));
	int a;
	int wielkoscb, ilosc_opb;
	auto old = steady_clock::now();
	auto t1 = steady_clock::now() - old;
	auto t2 = steady_clock::now() - old;
	auto t3 = steady_clock::now() - old;
	auto t4 = steady_clock::now() - old;
	auto t5 = steady_clock::now() - old;
	auto t6 = steady_clock::now() - old;

	plik1 << "Dodawanie elementu\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 8; i++) {
		old = steady_clock::now();
		t1 = steady_clock::now() - old;
		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\nDodawanie elementu";
		for (int i = 0; i < ilosc_wyk; i++) {
			delete kopiec;
			stworz(wielkoscb);
			old = steady_clock::now();
			for (int j = 0; j < ilosc_opb; j++) {
				dodaj(55);
			}
			t1 += steady_clock::now() - old;
		}
		cout << endl << i << " Uzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t1).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb);
		plik1 << wielkoscb << ";" << duration_cast<nanoseconds>(t1).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik2 << "Tworzenie kopca (normalna metoda)\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 8; i++) {
		old = steady_clock::now();
		t2 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\nTworzenie kopca (normalna metoda)";
		for (int i = 0; i < ilosc_wyk; i++) {
			int* x = new int[wielkoscb];
			for (int p = 0; p < wielkoscb; p++) {
				x[p] = rand() % 100;
			}
			old = steady_clock::now();
			for (int j = 0; j < ilosc_opb; j++) {
				dodaj(x[j]);
			}
			t2 += steady_clock::now() - old;
		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t2).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t2).count() / (ilosc_wyk );
		plik2 << wielkoscb << ";" << duration_cast<nanoseconds>(t2).count() / (ilosc_wyk) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik3 << "Tworzenie kopca (floyd)\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 8; i++) {
		old = steady_clock::now();
		t3 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\nTworzenie kopca (floyd)";
		for (int i = 0; i < ilosc_wyk; i++) {
			ilosc = wielkoscb;
			kopiec = new int[wielkoscb];
			int* x = new int[wielkoscb];
			for (int p = 0; p < wielkoscb; p++) {
				x[p] = rand() % 100;
			}
			old = steady_clock::now();
			for (int p = 0; p < wielkoscb - 1; p++) {
				kopiec[p] =x[p];
			}
				floyd();
			t3 += steady_clock::now() - old;
		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t3).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t3).count() / (ilosc_wyk);
		plik3 << wielkoscb << ";" << duration_cast<nanoseconds>(t3).count() / (ilosc_wyk) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik4 << "Uzuwanie korzenia\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	for (int i = 0; i < 8; i++) {
		old = steady_clock::now();
		t4 = steady_clock::now() - old;

		wielkoscb = wielkoscb * 2;
		ilosc_opb = wielkoscb / 20;
		cout << "\n\nUsowanie korzenia";
		for (int i = 0; i < ilosc_wyk; i++) {
			delete kopiec;
			stworz(wielkoscb);
			old = steady_clock::now();
			for (int j = 0; j < ilosc_opb; j++) {
				usunW(kopiec[0]);
			}
			t4 += steady_clock::now() - old;
		}
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t4).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t4).count() / (ilosc_wyk * ilosc_opb);
		plik4 << wielkoscb << ";" << duration_cast<nanoseconds>(t4).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	plik5 << "Wyszukiwanie elementu\n";
	wielkoscb = wielkosc;
	ilosc_opb = ilosc_op;
	int temp;
	for (int i = 0; i < 8; i++) {
		old = steady_clock::now();
		t5 = steady_clock::now() - old;
		wielkoscb = wielkoscb * 2;
		ilosc_opb = ilosc_opb * 2;
		cout << "\n\nWyszukiwanie elementu";
		for (int i = 0; i < ilosc_wyk; i++) {
			delete kopiec;
			stworz(wielkoscb);

			for (int j = 0; j < ilosc_opb; j++) {
				a = rand()%1000;
				old = steady_clock::now();
				temp=czyZawiera(a);
				t5 += steady_clock::now() - old;
			}

		}
		cout << temp;
		cout << "\nUzyskany czas [ns]:		";
		cout << duration_cast<nanoseconds>(t5).count();
		cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t5).count() / (ilosc_wyk * ilosc_opb);
		plik5 << wielkoscb << ";" << duration_cast<nanoseconds>(t5).count() / (ilosc_wyk * ilosc_opb) << endl;
	}
	plik1.close();
	plik2.close();
	plik3.close();
	plik4.close();
	plik5.close();
}

