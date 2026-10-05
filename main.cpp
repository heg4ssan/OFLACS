// Autor: Hector Gassan
// 23/09/2026
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <taglib/fileref.h> // Libreria externa
#include <tuple>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

void songNames(
    string rutacarp) { // Recibe string de la ruta de la carpeta de musica
  for (const auto &song : fs::directory_iterator(rutacarp)) {
    // ciclo que itera por cada archivo de la carpeta
    // funcion de <filesystem>
    string filename =
        song.path().filename().string(); // string de la ruta de arhivo
    if (filename.front() == '.') {
      // Condicional para ignorar los archivos ocultos que sistemas
      // como macos pueden crear al manejar archivos de audio o que
      // puede haber en la carpeta. Los archivos ocultos empiezan
      // con "."
      continue;
    }
    fs::path ext = song.path().extension(); // extrae la extension del archivo
    if (ext == ".flac" || ext == ".mp3" || ext == ".opus") {
      // Condicional para aceptar solo extensiones especificas
      TagLib::FileRef s(song.path().c_str()); // Referencia de archivo
      if (!s.isNull() && s.tag()) {
        // Condicional para verificar que la referencia del archivo
        // de audio no este vacio (archivos fantasma, corrputos, etc)
        // y tambien verifica que existan los tag (nombre de cancion, artista,
        // etc).
        cout << s.tag()->title().to8Bit(true) << endl; // Imprime titulo
      } else {
        cout << "Corrupt or without metadata: "
             << song.path().filename().string() << endl;
      }
    } else {
      cout << "The file " << song.path().filename().string()
           << " is not a compatible audio extension" << endl;
    }
  }
}

void sortQuality(
    string rutacarp) { // Recibe string de la ruta de la carpeta de musica
  vector<tuple<int, int, string>>
      qmatrix; // Vector de tuplas de 3 columnas (matriz)
  // Para esta funcion uso los mismos metodos de seguridad y ciclos
  // (condicionales, for) que la anterior funcion, como ya estan documentados
  // solo se comentara lo nuevo
  for (const auto &song : fs::directory_iterator(rutacarp)) {
    string filename = song.path().filename().string();
    if (filename.front() == '.') {
      continue;
    }
    fs::path ext = song.path().extension();
    if (ext == ".flac" || ext == ".mp3" || ext == ".opus") {
      TagLib::FileRef s(song.path().c_str());
      if (!s.isNull() && s.audioProperties() && s.tag()) {
        // Condicional que ademas de revisar si la referencia esta vacia y si
        // los tag existen, tambien revisa la existencia de las propiedades de
        // audio  (frecuencia de muestreo, tasa de bits)
        qmatrix.push_back({s.audioProperties()->sampleRate(),
                           s.audioProperties()->bitrate(),
                           s.tag()->title().to8Bit(true)});
        // agrega frecuencia de muestreo, tasa de bits y titulo a una nueva fila
        // (tupla)
      } else {
        cout << "Corrupt or without metadata: "
             << song.path().filename().string() << endl;
      }
    } else {
      cout << "The file " << song.path().filename().string()
           << " is not a compatible audio extension" << endl;
    }
  }
  // Sort comun de C++ (Introsort) para ordenar calidad de mayor a menor usando
  // funcion lambda para cambiar criterio de ordenacion (usando la frecuen
  // cia de muestreo y si llega a haber un igual, usa la tasa de bits)
  // Tiempo de coplejidad O(N log N) -> README
  sort(qmatrix.begin(), qmatrix.end(), [](const auto &a, const auto &b) {
    if (get<0>(a) != get<0>(b)) {
      return get<0>(a) > get<0>(b);
    }
    return get<1>(a) > get<1>(b);
  });
  for (int i = 0; i < qmatrix.size();
       i++) { // Impresion de la lista de canciones ordenadas
    // por calidad con sus datos tecnicos (frecuencia de muestreo y tasa de
    // bits)
    cout << i + 1 << ".-" << get<2>(qmatrix[i]) << " Hz: " << get<0>(qmatrix[i])
         << " kbps: " << get<1>(qmatrix[i]) << endl;
  }
}

void songArtistsAlbums(
    string rutacarp) { // Recibe string de la ruta de la carpeta de musica
  for (const auto &song : fs::directory_iterator(rutacarp)) {
    // ciclo que itera por cada archivo de la carpeta
    // funcion de <filesystem>
    string filename =
        song.path().filename().string(); // string de la ruta de arhivo
    if (filename.front() == '.') {
      // Condicional para ignorar los archivos ocultos que sistemas
      // como macos pueden crear al manejar archivos de audio o que
      // puede haber en la carpeta. Los archivos ocultos empiezan
      // con "."
      continue;
    }
    fs::path ext = song.path().extension(); // extrae la extension del archivo
    if (ext == ".flac" || ext == ".mp3" || ext == ".opus") {
      // Condicional para aceptar solo extensiones especificas
      TagLib::FileRef s(song.path().c_str()); // Referencia de archivo
      if (!s.isNull() && s.tag()) {
        // Condicional para verificar que la referencia del archivo
        // de audio no este vacio (archivos fantasma, corrputos, etc)
        // y tambien verifica que existan los tag (nombre de cancion, artista,
        // etc).
        cout << s.tag()->title().to8Bit(true) << ": "
             << s.tag()->artist().to8Bit(true) << " -- "
             << s.tag()->album().to8Bit(true) << endl; // Imprime titulo
      } else {
        cout << "Corrupt or without metadata: "
             << song.path().filename().string() << endl;
      }
    } else {
      cout << "The file " << song.path().filename().string()
           << " is not a compatible audio extension" << endl;
    }
  }
}

// Funcion de:
// https://stackoverflow.com/questions/6486289/how-to-clear-the-console-in-c
void clearScreen() {
  // \033[2J clears the screen, \033[H moves the cursor to the top-left corner
  std::cout << "\033[2J\033[H" << std::flush;
}

// Funcion que imprime OFLACS en grande
void printOFLACS() {
  cout << "  ___   _____  _         _      ____   ____  \n";
  cout << " / _ \\ |  ___|| |       / \\    / ___| / ___| \n";
  cout << "| | | || |_   | |      / _ \\  | |     \\___ \\ \n";
  cout << "| |_| ||  _|  | |___  / ___ \\ | |___   ___) |\n";
  cout << " \\___/ |_|    |_____|/_/   \\_\\ \\____||____/ \n";
  cout << "--------------------------------------------------- \n";
}

int main() {
  // Main basico para comprobar funcionalidad de las dos funciones anteriores.
  clearScreen();
  cout << "Welcome to:" << endl;
  printOFLACS();
  bool flag = true;
  string rutacarp;
  cout << "Enter the directory extension of your FLAC library:" << endl;
  getline(cin, rutacarp);
  while (flag == true) {
    int option;
    cout << "What would you like to do?\n"
         << "Option 1: Song Names\n"
         << "Option 2: Sort songs quality\n"
         << "Option 3: See artists and albums\n"
         << "Option 4: Exit\n"
         << endl;
    cin >> option;
    clearScreen();
    if (option == 1) {
      songNames(rutacarp);
    } else if (option == 2) {
      sortQuality(rutacarp);
    } else if (option == 3) {
      songArtistsAlbums(rutacarp);
    } else if (option == 4) {
      flag = false;
    } else {
      cout << "That option does not exist, chose a real one." << endl;
    }
  }
  return 0;
}
