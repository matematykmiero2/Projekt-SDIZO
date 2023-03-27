#include "projekt.h"
#include "Bst.h"

Bst* bst = new Bst();
void menuBST() {
	char wybor2;
	string plik;
	int index, wartosc;
	int ix = 200;
	wybor2 = getche();
	switch (wybor2) {
	case '1':
		cout << "\nPodaj nazwe pliku: ";
		cin >> plik;
		bst->daneZPliku(plik);
		bst->wyswietl();
		break;

	case '2':
		cout << "\nPodaj wartosc do usuniecia \n";
		cin >> wartosc;
		bst->usun(wartosc);
		cout << "\n\nPo usunieciu:\n\n";
		bst->wyswietl();
		break;

	case '3':
		cout << "\nPodaj wartosc do dodania: ";
		cin >> wartosc;
		bst->dodaj(wartosc);
		bst->wyswietl();
		break;

	case '4':
		cout << "\nPodaj wartosc do znalezienia: ";
		cin >> wartosc;
		if (bst->czyZawiera(wartosc) !=NULL) {
			cout << "\nElement znajduje sie pod adresem " << bst->czyZawiera(wartosc) << endl;
		}
		else {
			cout << "\nBrak elementu w drzewie\n";
		}
		bst->wyswietl();
		break;


	case '5':
		cout << "\nPodaj ilosc elementow drzewa BST: ";
		cin >> wartosc;
		bst->stworz(wartosc);
		bst->wyswietl();
		break;

	case '6':
		bst->wyswietl();
		break;

	case '7':
		bst->czas(20, ix, ix / 10);
		break;

	case '0':
		system("cls");
		break;
	default:
		cout << "\nNiepoprawne wybranie";
		menuKopiec();
	}
}