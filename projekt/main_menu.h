#include "projekt.h"
#include "menu.h"
#include "menuTablica.h"
#include "menuLista.h"
#include "menuKopiec.h"
#include "menuBST.h"
#include "menuRbt.h";

void main_menu() {
	char wybor;
	do {
		
		cout << "\n\n \\	MENU	/\n";
		cout << "Prosze wybrac opcje:\n";
		cout << "1. Tablica\n";
		cout << "2. Lista dwukierunkowa\n";
		cout << "3. Kopiec binarny\n";
		cout << "4. Drzewo przeszukiwan binarnych BST\n";
		cout << "5. Drzewo czerwono-czarne\n";
		cout << "0. Zamkniecie programu\n";

		wybor = getche();


		switch (wybor) {
		case '1':
			menu("Tablica");
			menuTablica();
			break;
		case '2':
			menu("Lista dwukierunkowa");
			menuLista();
			break;
		case '3':
			menu("Kopiec binarny");
			menuKopiec();
			break;
		case '4':
			menu("Drzewo przeszukiwan binarnych BST");
			menuBST();
			break;
		case '5':
			menu("Drzewo czerwono-czarne");
			menuRbt();
			break;
		case '0':
			cout << "\nDo zobaczenia ponownie\n";
			break;
		default:
			cout << "Blad!\n\n";
			main_menu();
		}
	} while (wybor != '0');
	
}

