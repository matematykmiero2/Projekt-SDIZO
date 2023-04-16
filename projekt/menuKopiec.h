#include "projekt.h"
#include "Kopiec.h"

Kopiec* kopiec = new Kopiec();
void menuKopiec() {

	char wybor2;
	string plik;
	int index, wartosc;
	int ix = 200;
	wybor2 = getche();
	switch (wybor2) {
	case '1':
		cout << "\nPodaj nazwe pliku: ";
		cin >> plik;
		kopiec -> daneZPliku(plik);
		kopiec -> wyswietl();
		break;

	case '2':
		cout << "\nPodaj wartosc do usuniecia \n";
		cin >> wartosc;
		kopiec->usunW(wartosc);
		cout << "\n\nPo usunieciu:\n\n";
		kopiec->wyswietl();
		break;

	case '3':
		cout << "\nPodaj wartosc do dodania: ";
		cin >> wartosc;
		kopiec->dodaj(wartosc);
		kopiec->wyswietl();
		break;

	case '4':
		cout << "\nPodaj wartosc do znalezienia: ";
		cin >> wartosc;
		if (kopiec->czyZawiera(wartosc) >= 0) {
			cout << "\nElement znajduje sie na ideksie " << kopiec->czyZawiera(wartosc) << endl;
		}
		else {
			cout << "\nBrak elementu w kopcu\n";
		}
		kopiec->wyswietl();
		break;


	case '5':
		cout << "\nPodaj ilosc elementow kopca: ";
		cin >> wartosc;
		kopiec->stworz(wartosc);
		kopiec->wyswietl();
		break;

	case '6':
		kopiec->wyswietl();
		break;

	case '7':
		kopiec->czas(100, ix, ix / 10);
		break;

	case '0':
		system("cls");
		break;
	default:
		cout << "\nNiepoprawne wybranie";
		menuKopiec();
	}
}