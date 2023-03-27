#include "projekt.h"
#include "Tablica.h"


Tablica *tablica = new Tablica();
void menuTablica() {
	char wybor2;
	string plik;
	int index, wartosc,a;
	int ix = 200;
	wybor2 = getche();
	switch (wybor2) {
	case '1':
		cout << "\nPodaj nazwe pliku: ";
		cin >> plik;
		tablica -> daneZPliku(plik);
		tablica -> wyswietl();
		break;

	case '2':
		cout << "\nPodaj index do usuniecia: ";
		cin >> index;
		tablica->usun(index);
		tablica->wyswietl();
		break;

	case '3':
		cout << "\nPodaj index dodania: ";
		cin >> index;
		cout << "\nPodaj wartosc do dodania: ";
		cin >> wartosc;
		tablica->dodaj(index, wartosc);
		tablica->wyswietl();
		break;

	case '4':
		cout << "\nPodaj wartosc do znalezienia: ";
		cin >> wartosc;
		 a = tablica->czyZawiera(wartosc);
		if (a >= 0) {
			cout << "Element znaleziony na ineksie: " << a << endl;
		}
		else {
			cout << "Brak elementu\n";
		}
		tablica->wyswietl();
		break;


	case '5':
		cout << "\nPodaj ilosc elementow trablicy: ";
		cin >> wartosc;
		tablica->stworz(wartosc);
		tablica->wyswietl();
		break;

	case '6':
		tablica->wyswietl();
		break;
	case '7':
			tablica->czas(20, ix, ix/10);
		break;
	case '0':
		system("cls");
		break;
	default:
		cout << "\nNiepoprawne wybranie";
		menuTablica();
	}
}