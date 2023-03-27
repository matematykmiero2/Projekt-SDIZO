# CMakeList.txt: projekt CMake dla elementu projekt, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (projekt "projekt.cpp" "projekt.h"   "menu.h" "main_menu.h"  "Tablica.h" "Tablica.cpp" "Lista.h" "Lista.cpp" "menuLista.h" "Kopiec.h" "Kopiec.cpp"   "menuBST.h" "Bst.h" "Bst.cpp" "Rbt.h" "Rbt.cpp"  )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET projekt PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
