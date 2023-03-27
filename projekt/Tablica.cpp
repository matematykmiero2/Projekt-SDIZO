#include "tablica.h"
#include "chrono"

Tablica::Tablica(){
	ilosc = 0;
	tablica = new int[0];
}

Tablica::Tablica(int l) {
	ilosc = l;
	tablica = new int[l];
}

Tablica :: ~Tablica() {
	ilosc = NULL;
	delete tablica;
}

void Tablica :: daneZPliku(string plik){									//OK
	ifstream odczyt(plik);
	if (odczyt.is_open()) {
		int il, x;
		odczyt >> il;
		ilosc = il;
		tablica = new int[il];
		for (int i = 0; i < il; i++) {
			odczyt >> x;
			tablica[i] = x;
		}
	}
	else {
		cout << "\nNie udalo sie otworzyc pliku\n";
	}

}



int Tablica :: czyZawiera(int wartosc) {									//OK
	
	for (int i = 0; i < ilosc; i++) {
		if (tablica[i] == wartosc) {
			return i;
		}
	}
	return -1;
}

void Tablica :: dodaj(int index, int wartosc) {									//OK
	if (ilosc == 0 && index==0) {
		ilosc = 1;
		tablica = new int[1];
		tablica[0] = wartosc;
		return;
	}
	if (index > ilosc)return;
	ilosc++;
	int* buf = tablica;
	tablica = new int[ilosc];
	tablica[index] = wartosc;
	for (int i = 0; i < index; i++) {
		tablica[i] = buf[i];
	}
	for (int i = index + 1; i < ilosc; i++) {
		tablica[i] = buf[i - 1];
	}
	delete[] buf;
}


void Tablica::usun(int index) {									//OK
	if (index < ilosc) {
		ilosc--;
		int* buf = tablica;
		tablica = new int[ilosc];

		for (int i = 0; i < index; i++) {
			tablica[i] = buf[i];
		}
		for (int i = index + 1; i <= ilosc; i++) {
			tablica[i - 1] = buf[i];
		}
		delete[] buf;
	}


}

void Tablica :: wyswietl() {									//OK

	for (int i = 0; i < ilosc; i++) {
		cout << tablica[i]<<" ";
	}
	
}
void  Tablica :: stworz(int size) {									//OK
	ilosc = size;
	tablica = new int[ilosc];
	srand(time(NULL));
	int liczba;
	for (int i = 0; i < ilosc; i++) {
		liczba = rand() % 100;
		tablica[i] = liczba;
	}
}

void Tablica::czas(int ilosc_wyk, int wielkosc, int ilosc_op) {									//OK
	ofstream plik1("czasy_tablica1.txt");
	ofstream plik2("czasy_tablica2.txt");
	ofstream plik3("czasy_tablica3.txt");
	ofstream plik4("czasy_tablica4.txt");
	ofstream plik5("czasy_tablica5.txt");
	ofstream plik6("czasy_tablica6.txt");
	ofstream plik7("czasy_tablica7.txt");
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
		auto t7 = steady_clock::now() - old;

		plik1 << "Dodawanie na pocz¹tek\n";
		wielkoscb = wielkosc;
		ilosc_opb = ilosc_op;
		for (int i = 0; i < 10; i++) {
			old = steady_clock::now();
			t1 = steady_clock::now() - old;

			wielkoscb = wielkoscb * 2;
			ilosc_opb = wielkoscb / 20;
			cout << "\nDodawanie na poczatek";
			for (int i = 0; i < ilosc_wyk; i++) {
				stworz(wielkoscb);
				old = steady_clock::now();
				for (int j = 0; j < ilosc_opb; j++) {
					dodaj(0,55);
				}
				t1 += steady_clock::now() - old;
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
			t2 = steady_clock::now() - old;

			wielkoscb = wielkoscb * 2;
			ilosc_opb = wielkoscb / 20;
			cout << "\n\nDodawanie na koniec";
			for (int i = 0; i < ilosc_wyk; i++) {
				stworz(wielkoscb);
				old = steady_clock::now();
				for (int j = 0; j < ilosc_opb; j++) {
					dodaj(wielkoscb-1-j,55);
				}
				t2 += steady_clock::now() - old;
			}
			cout << endl << i << " Uzyskany czas [ns]:		";
			cout << duration_cast<nanoseconds>(t2).count();
			cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t2).count() / (ilosc_wyk * ilosc_opb);
			plik2 << wielkoscb << ";" << duration_cast<nanoseconds>(t2).count() / (ilosc_wyk * ilosc_opb) << endl;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////
		plik3 << "Dodawanie nie na poczatek nie na koniec\n";
		wielkoscb = wielkosc;
		ilosc_opb = ilosc_op;
		for (int i = 0; i < 10; i++) {
			old = steady_clock::now();
			t3 = steady_clock::now() - old;

			wielkoscb = wielkoscb * 2;
			ilosc_opb = wielkoscb / 20;
			cout << "\n\nDodawanie nie na poczatek i nie na koniec";
			for (int i = 0; i < ilosc_wyk; i++) {
				stworz(wielkoscb);

				for (int j = 0; j < ilosc_opb; j++) {
					a = 1 + rand() % (wielkoscb + j);
					old = steady_clock::now();
					dodaj(a, 55);
					t3 += steady_clock::now() - old;
				}

			}
			cout << endl << i << " Uzyskany czas [ns]:		";
			cout << duration_cast<nanoseconds>(t3).count();
			cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t3).count() / (ilosc_wyk * ilosc_opb);
			plik3 << wielkoscb << ";" << duration_cast<nanoseconds>(t3).count() / (ilosc_wyk * ilosc_opb) << endl;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////
		plik4 << "Uzuwanie z pocz¹tku\n";
		wielkoscb = wielkosc;
		ilosc_opb = ilosc_op;
		for (int i = 0; i < 10; i++) {
			old = steady_clock::now();
			t4 = steady_clock::now() - old;

			wielkoscb = wielkoscb * 2;
			ilosc_opb = wielkoscb / 20;
			cout << "\n\nUsowanie z poczatku";
			for (int i = 0; i < ilosc_wyk; i++) {
				stworz(wielkoscb);
				old = steady_clock::now();
				for (int j = 0; j < ilosc_opb; j++) {
					usun(0);
				}
				t4 += steady_clock::now() - old;
			}
			cout << endl << i << " Uzyskany czas [ns]:		";
			cout << duration_cast<nanoseconds>(t4).count();
			cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t4).count() / (ilosc_wyk * ilosc_opb);
			plik4 << wielkoscb << ";" << duration_cast<nanoseconds>(t4).count() / (ilosc_wyk * ilosc_opb) << endl;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////
		plik5 << "Usowanie ze srodka\n";
		wielkoscb = wielkosc;
		ilosc_opb = ilosc_op;
		for (int i = 0; i < 10; i++) {
			old = steady_clock::now();
			t5 = steady_clock::now() - old;

			wielkoscb = wielkoscb * 2;
			ilosc_opb = ilosc_opb *2;
			cout << "\n\nUsowanie ze srodka";
			for (int i = 0; i < ilosc_wyk; i++) {
				stworz(wielkoscb);

				for (int j = 0; j < ilosc_opb; j++) {
					a = 1 + rand() % (wielkoscb - j - 1);
					old = steady_clock::now();
					usun(a);
					t5 += steady_clock::now() - old;
				}
			}
			cout << endl << i << " Uzyskany czas [ns]:		";
			cout << duration_cast<nanoseconds>(t5).count();
			cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t5).count() / (ilosc_wyk * ilosc_opb);
			plik5 << wielkoscb << ";" << duration_cast<nanoseconds>(t5).count() / (ilosc_wyk * ilosc_opb) << endl;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
		plik6 << "Usowanie z konca\n";
		wielkoscb = wielkosc;
		ilosc_opb = ilosc_op;
		for (int i = 0; i < 10; i++) {
			old = steady_clock::now();
			t6 = steady_clock::now() - old;

			wielkoscb = wielkoscb * 2;
			ilosc_opb = ilosc_opb * 2;
			cout << "\n\nUsowanie z konca";
			for (int i = 0; i < ilosc_wyk; i++) {
				stworz(wielkoscb);
				for (int j = 0; j < ilosc_opb; j++) {
					old = steady_clock::now();
					usun(wielkoscb-1-j);
					t6 += steady_clock::now() - old;
				}
			}
			cout << endl << i << " Uzyskany czas [ns]:		";
			cout << duration_cast<nanoseconds>(t6).count();
			cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t6).count() / (ilosc_wyk * ilosc_opb);
			plik6 << wielkoscb << ";" << duration_cast<nanoseconds>(t6).count() / (ilosc_wyk * ilosc_opb) << endl;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////
		plik7 << "Wyszukiwanie elementu\n";
		wielkoscb = wielkosc;
		ilosc_opb = ilosc_op;
		int temp;
		for (int i = 0; i < 10; i++) {
			old = steady_clock::now();
			t7 = steady_clock::now() - old;

			wielkoscb = wielkoscb * 2;
			ilosc_opb = wielkoscb / 20;
			cout << "\n\nWyszukiwanie elementu";

			for (int i = 0; i < ilosc_wyk; i++) {
				stworz(wielkoscb);

				for (int j = 0; j < ilosc_opb; j++) {
					a = rand() % 1000;
					old = steady_clock::now();
					temp=czyZawiera(a);
					t7 += steady_clock::now() - old;
				}

			}
			cout << temp;
			cout << endl << i << " Uzyskany czas [ns]:		";
			cout << duration_cast<nanoseconds>(t7).count();
			cout << "\nSredni czas [ns]:		" << duration_cast<nanoseconds>(t7).count() / (ilosc_wyk * ilosc_opb);
			plik7 << wielkoscb << ";" << duration_cast<nanoseconds>(t7).count() / (ilosc_wyk * ilosc_opb) << endl;
		}

	plik1.close();
	plik2.close();
	plik3.close();
	plik4.close();
	plik5.close();
	plik6.close();
	plik7.close();
}