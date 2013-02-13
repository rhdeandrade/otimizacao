#include <iostream>
#include <fstream>
using namespace std;

class FileHandler {

  public:
    string[] open_file(string file_name);

};

string[] FileHandler::open_file(string file_name) {
  
  fstream myfile;
  string line[];
  
  myfile.open(file_name.c_str(), fstream::in); 

  if (myfile.is_open()) {
    while (myfile.good())
      getline(myfile, line);
      cout << "linha: " << line << "\n";
  }
  else {
    cout << "Arquivo não encontrado\n";
  }

}