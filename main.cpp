#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <taglib/fileref.h>
#include <tuple>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

void songNames(string rutacarp) {
  for (const auto &song : fs::directory_iterator(rutacarp)) {
    string filename = song.path().filename().string();
    if (filename.front() == '.') { // Hiden files
      continue;
    }
    fs::path ext = song.path().extension();
    if (ext == ".flac" || ext == ".mp3" || ext == ".opus") {
      TagLib::FileRef s(song.path().c_str());
      if (!s.isNull() && s.tag()) {
        cout << s.tag()->title().to8Bit(true) << endl;
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

void sortQuality(string rutacarp) {
  vector<tuple<int, int, string>> qmatrix;
  for (const auto &song : fs::directory_iterator(rutacarp)) {
    string filename = song.path().filename().string();
    if (filename.front() == '.') { // Hiden files
      continue;
    }
    fs::path ext = song.path().extension();
    if (ext == ".flac" || ext == ".mp3" || ext == ".opus") {
      TagLib::FileRef s(song.path().c_str());
      if (!s.isNull() && s.audioProperties() && s.tag()) {
        qmatrix.push_back({s.audioProperties()->sampleRate(),
                           s.audioProperties()->bitrate(),
                           s.tag()->title().to8Bit(true)});
      } else {
        cout << "Corrupt or without metadata: "
             << song.path().filename().string() << endl;
      }
    } else {
      cout << "The file " << song.path().filename().string()
           << " is not a compatible audio extension" << endl;
    }
  }
  sort(qmatrix.begin(), qmatrix.end(), [](const auto &a, const auto &b) {
    if (get<0>(a) != get<0>(b)) {
      return get<0>(a) > get<0>(b);
    }
    return get<1>(a) > get<1>(b);
  });
  for (int i = 0; i < qmatrix.size(); i++) {
    cout << i + 1 << ".-" << get<2>(qmatrix[i]) << " Hz: " << get<0>(qmatrix[i])
         << " kbps: " << get<1>(qmatrix[i]) << endl;
  }
}

int main() {
  string rutacarp;
  int option;
  cout << "Enter the directory extension of your FLAC library:" << endl;
  getline(cin, rutacarp);
  cout << "What would you like to do?\n"
       << "Option 1: Song Names\n"
       << "Option 2: Sort songs quality" << endl;
  cin >> option;
  if (option == 1) {
    songNames(rutacarp);
  } else if (option == 2) {
    sortQuality(rutacarp);
  } else {
    cout << "That option does not exist, chose a real one." << endl;
  }
  return 0;
}
