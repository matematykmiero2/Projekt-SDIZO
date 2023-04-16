#include "projekt.h"
#include "Rbt.h"

Rbt* rbt = new Rbt();
void menuRbt() {
	char wybor2;
	string plik;
	int index, wartosc;
	int ix = 200;
	wybor2 = getche();
	switch (wybor2) {
	case '1':
		cout << "\nPodaj nazwe pliku: ";
		cin >> plik;
		rbt->daneZPliku(plik);
		rbt->wyswietl();
		break;

	case '2':
		cout << "\nPodaj wartosc do usuniecia \n";
		cin >> wartosc;
		rbt->usun(wartosc);
		cout << "\n\nPo usunieciu:\n\n";
		rbt->wyswietl();
		break;

	case '3':
		cout << "\nPodaj wartosc do dodania: ";
		cin >> wartosc;
		rbt->dodaj(wartosc);
		rbt->wyswietl();
		break;

	case '4':
		cout << "\nPodaj wartosc do znalezienia: ";
		cin >> wartosc;
		if (rbt->czyZawiera(wartosc) != NULL) {
			cout << "\nElement znajduje sie pod adresem " << rbt->czyZawiera(wartosc) << endl;
		}
		else {
			cout << "\nBrak elementu w drzewie\n";
		}
		rbt->wyswietl();
		break;


	case '5':
		cout << "\nPodaj ilosc elementow drzewa CC: ";
		cin >> wartosc;
		rbt->stworz(wartosc);
		rbt->wyswietl();
		break;

	case '6':
		rbt->wyswietl();
		break;

	case '7':
		rbt->czas(100, ix, ix / 10);
		break;

	case '0':
		system("cls");
		break;
	default:
		cout << "\nNiepoprawne wybranie";
		menuRbt();
	}
}