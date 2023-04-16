#include "projekt.h"
#include "Lista.h"

Lista* lista = new Lista();
void menuLista() {

	char wybor2;
	string plik;
	int index, wartosc;
	int ix = 200;
	wybor2 = getche();
	switch (wybor2) {
	case '1':
		cout << "\nPodaj nazwe pliku: ";
		cin >> plik;
		lista -> daneZPliku(plik);
		lista-> wyswietl();
		break;

	case '2':
		cout << "\nPodaj wartosc do usuniecia: ";
		cin >> index;
		lista->usun(index);
	
		lista->wyswietl();
		break;

	case '3':
	
		
		cout << "Podaj miejsce do dodania: ";
		cin >> index;
		cout << "\nPodaj wartosc do dodania: ";
		cin >> wartosc;
		lista->dodaj(index, wartosc);
		lista->wyswietl();
		break;

	case '4':
		cout << "\nPodaj wartosc do znalezienia: ";
		cin >> wartosc;
		cout<<lista->czyZawiera(wartosc);
		lista->wyswietl();
		break;


	case '5':
		cout << "\nPodaj ilosc elementow listy: ";
		cin >> wartosc;
		lista->stworz(wartosc);
		lista->wyswietl();
		break;

	case '6':
		lista->wyswietl();
		
		break;


	case '7':
		lista->czas(100, ix, ix / 10);
		break;

	case '0':
		system("cls");
		break;
	default:
		cout << "\nNiepoprawne wybranie";
		menuLista();
	}
}