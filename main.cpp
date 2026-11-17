// Autor: Hector Gassan

#include "dlist.h" // Lista doblemente ligada implementada por mi
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <taglib/fileref.h> // Libreria externa
#include <tuple>
#include <vector>

using namespace std;
namespace fs = std::filesystem;
// Recibe string de la ruta de la carpeta de musica
void sortQuality( string rutacarp, DList<string> &SongsInfo) { // Complejidad general: O(N) Mejor, O(N^2) Promedio, O(N^2) Peor
  // Vector de tuplas de 4 columnas (matriz)
  vector<tuple<int, int, string, string>> qmatrix; // O(1) - Constante
  // ciclo que itera por cada archivo de la carpeta
  // funcion de <filesystem>
  for (const auto &song : fs::directory_iterator(rutacarp)) {  // O(N) - Lineal
    // string de la ruta de arhivo
    string filename = song.path().filename().string(); // O(1) - Constante
    // Condicional para ignorar los archivos ocultos que sistemas
    // como macos pueden crear al manejar archivos de audio o que
    // puede haber en la carpeta. Los archivos ocultos empiezan
    // con "."
    if (filename.front() == '.') { // O(1) - Constante
      continue; // O(1) - Constante
    }
    fs::path ext = song.path().extension(); // O(1) - Constante
    if (ext == ".flac" || ext == ".mp3" || ext == ".opus") { // O(1) - Constante
      TagLib::FileRef s(song.path().c_str()); // O(1) - Constante
      // Condicional que ademas de revisar si la referencia esta vacia y si
      // los tag existen, tambien revisa la existencia de las propiedades de
      // audio  (frecuencia de muestreo, tasa de bits)
      if (!s.isNull() && s.audioProperties() && s.tag()) { // O(1) - Constante
          // agrega frecuencia de muestreo, tasa de bits y titulo a una nueva fila
          // (tupla)
        qmatrix.push_back({s.audioProperties()->sampleRate(),
                           s.audioProperties()->bitrate(),
                           s.tag()->title().to8Bit(true),
                           s.tag()->artist().to8Bit(true)}); // O(1) - Constante
      } else { // O(1) - Constante
        cout << "Corrupt or without metadata: "
             << song.path().filename().string() << endl; // O(1) - Constante
      }
    } else { // O(1) - Constante
      cout << "The file " << song.path().filename().string()
           << " is not a compatible audio extension" << endl; // O(1) - Constante
    }
  }
  // Sort comun de C++ (Introsort) para ordenar calidad de mayor a menor usando
  // funcion lambda para cambiar criterio de ordenacion (usando la frecuen
  // cia de muestreo y si llega a haber un igual, usa la tasa de bits)
  sort(qmatrix.begin(), qmatrix.end(), [](const auto &a, const auto &b) { // O(N) mejor, O(N^2) promedio, O(N^2) peor
    if (get<0>(a) != get<0>(b)) { // O(1) - Constante
      return get<0>(a) > get<0>(b); // O(1) - Constante
    }
    return get<1>(a) > get<1>(b); // O(1) - Constante
  });
  for (int i = 0; i < qmatrix.size(); i++) { // O(N) - Lineal
    // Por cada cancion se crea un string con su informacion y se agrega a la lista
    // doblemente encadenada de las canciones.
    string info = get<2>(qmatrix[i]) + ": " + get<3>(qmatrix[i]) + " Hz: "
        + to_string(get<0>(qmatrix[i])) + " kbps: " + to_string(get<1>(qmatrix[i])); // O(1) - Constante
    SongsInfo.insertion(info);// O(1) - Constante
  }
}

// Recibe string de la ruta de la carpeta de musica
void songAlbums(string rutacarp) {  // Complejidad general: O(N) Mejor, O(N^2) Promedio, O(N^2) Peor
  vector<tuple<int, int, string, string>> Amatrix; // O(1) - Constante
  // ciclo que itera por cada archivo de la carpeta
  // funcion de <filesystem>
  for (const auto &song : fs::directory_iterator(rutacarp)) { // O(N) - Lineal
      // string de la ruta de arhivo
    string filename = song.path().filename().string(); // O(1) - Constante
    // Condicional para ignorar los archivos ocultos que sistemas
    // como macos pueden crear al manejar archivos de audio o que
    // puede haber en la carpeta. Los archivos ocultos empiezan
    // con "."
    if (filename.front() == '.') { // O(1) - Constante
      continue; // O(1) - Constante
    }
    // extrae la extension del archivo
    fs::path ext = song.path().extension(); // O(1) - Constante
    // Condicional para aceptar solo extensiones especificas
    if (ext == ".flac" || ext == ".mp3" || ext == ".opus") { // O(1) - Constante
      // Referencia de archivo
      TagLib::FileRef s(song.path().c_str()); // O(1) - Constante
      // Condicional para verificar que la referencia del archivo
      // de audio no este vacio (archivos fantasma, corrputos, etc)
      // y tambien verifica que existan los tag (nombre de cancion, artista,
      // etc).
      if (!s.isNull() && s.tag()) { // O(1) - Constante
        Amatrix.push_back({s.audioProperties()->sampleRate(),
                           s.audioProperties()->bitrate(),
                           s.tag()->title().to8Bit(true),
                           s.tag()->album().to8Bit(true)}); // O(1) - Constante
      } else { // O(1) - Constante
        cout << "Corrupt or without metadata: " // O(1) - Constante
             << song.path().filename().string() << endl; // O(1) - Constante
      }
    } else { // O(1) - Constante
      cout << "The file " << song.path().filename().string()
           << " is not a compatible audio extension" << endl; // O(1) - Constante
    }
  }
  sort(Amatrix.begin(), Amatrix.end(), [](const auto &a, const auto &b) { // O(N) mejor, O(N^2) promedio, O(N^2) peor
    if (get<0>(a) != get<0>(b)) { // O(1) - Constante
      return get<0>(a) > get<0>(b); // O(1) - Constante
    }
    return get<1>(a) > get<1>(b); // O(1) - Constante
  });
  for (int i = 0; i < Amatrix.size(); i++){ // O(N) - Lineal
      cout << i + 1 << ".-" << get<2>(Amatrix[i]) + ": " + get<3>(Amatrix[i]) << endl; // O(1) - Constante
  }
}

// Funcion de:
// https://stackoverflow.com/questions/6486289/how-to-clear-the-console-in-c
void clearScreen() { // Complejidad general de la función: O(1) - Constante
  // \033[2J clears the screen, \033[H moves the cursor to the top-left corner
  cout << "\033[2J\033[H" << flush;  // O(1) - Constante
}

// Funcion que imprime OFLACS en grande
void printOFLACS() { // Complejidad general de la función: O(1) - Constante
  cout << "  ___   _____  _         _      ____   ____  \n"; // O(1) - Constante
  cout << " / _ \\ |  ___|| |       / \\    / ___| / ___| \n"; // O(1) - Constante
  cout << "| | | || |_   | |      / _ \\  | |     \\___ \\ \n"; // O(1) - Constante
  cout << "| |_| ||  _|  | |___  / ___ \\ | |___   ___) |\n"; // O(1) - Constante
  cout << " \\___/ |_|    |_____|/_/   \\_\\ \\____||____/ \n"; // O(1) - Constante
  cout << "--------------------------------------------------- \n"; // O(1) - Constante
}

int main() { // Complejidad general: O(N) Mejor, O(N^2) Promedio, O(N^2) Peor
  // Main para comprobar funcionalidad de las dos funciones anteriores.
  clearScreen(); // O(1) - Constante
  cout << "Welcome to:" << endl; // O(1) - Constante
  printOFLACS(); // O(1) - Constante
  bool flag = true; // O(1) - Constante
  string rutacarp; // O(1) - Constante
  // Creo la estructura de datos a utilizar para la lista de canciones
  // favoritas.
  DList<string> Fsongs; // O(1) - Constante
  DList<string> SongsInfo; // O(1) - Constante
  Fsongs.loadFromFile("favoritos.txt"); //O(N) - Lineal
  cout << "Enter the directory extension of your FLAC library:" << endl; // O(1) - Constante
  getline(cin, rutacarp); // O(1) - Constante
  sortQuality(rutacarp, SongsInfo); // O(N) Mejor, O(N^2) Promedio, O(N^2) Peor
  while (flag == true) { // O(N) - Lineal
    int option; // O(1) - Constante
    cout << "What would you like to do?\n"
         << "Option 1: Songs (Name, Artist, Tecnical info) - Sorted by Quality\n"
         << "Option 2: Songs albums - Sorted by Quality\n"
         << "Option 3: Add favorite song\n"
         << "Option 4: See favorite songs\n"
         << "Option 5: Delete favorite song\n"
         << "Option 6: Serch song\n"
         << "Option 7: Exit\n"
         << endl; // O(1) - Constante
    cin >> option; // O(1) - Constante
    clearScreen(); // O(1) - Constante
    if (option == 1) { // O(1) - Constante
        SongsInfo.printList(); //O(N) - Lineal
    } else if (option == 2) { // O(1) - Constante
      songAlbums(rutacarp); // O(N) Mejor, O(N^2) Promedio, O(N^2) Peor
    } else if (option == 3) { // O(1) - Constante
        int pos; // O(1) - Constante
        SongsInfo.printList(); //O(N) - Lineal
        cout << "Select the number of song that you want to add to your favorite songs:" << endl; // O(1) - Constante
        cin >> pos; // O(1) - Constante
        string s = SongsInfo.searchPos(pos - 1); // O(1) mejor, O(N) promedio, O(N) peor
        if (s == "Invalid"){ // O(1) - Constante
            cout << "That is an invalid position, please enter a valid one" << endl; // O(1) - Constante
        } else {
            Fsongs.insertion(s); // O(1) - Constante
        }
    } else if (option == 4) { // O(1) - Constante
      Fsongs.printList(); //O(N) - Lineal
    } else if (option == 5) { // O(1) - Constante
        cout << "Select the song number of the favorite songs list that you want "
                "to delete:"
             << endl; // O(1) - Constante
        int pos; // O(1) - Constante
        cin >> pos; // O(1) - Constante
        Fsongs.deleteAt(pos - 1);
    } else if (option == 6) { // O(1) - Constante
        cin.ignore(); // O(1) - Constante
        cout << "Enter the song name to serch:" << endl; // O(1) - Constante
        string songname; // O(1) - Constante
        getline(cin, songname); // O(1) - Constante
        cout << "Results are:" << endl; // O(1) - Constante
        int test = SongsInfo.searchString(songname); // O(1) mejor, O(N) promedio, O(N) peor
        if(test < 1){ // O(1) - Constante
            cout << "No Results" << endl; // O(1) - Constante
        }
    } else if (option == 7){ // O(1) - Constante
        Fsongs.saveToFile("favoritos.txt"); //O(N) - Lineal
        flag = false; // O(1) - Constante
    } else {
      cout << "That option does not exist, chose a real one." << endl; // O(1) - Constante
    }
  }
  return 0; // O(1) - Constante
}
