#include "projekt.h"

//MENU WYBORU DZIALANIA
void menu(string tekst) {
	system("cls");
	cout << "\n\n \\	" << tekst << "		/";
	cout << "\nProsze wybrac opcje:\n";
	cout << "1. Wczytaj z pliku\n";
	cout << "2. Usun\n";						 
	cout << "3. Dodaj\n";						 
	cout << "4. Znajdz\n";						 
	cout << "5. Utworz losowo\n";				 
	cout << "6. Wyswietl\n";					 
	cout << "7. Pomiary czasu\n";
	cout << "0. Powrot do MENU glownego\n";
}

