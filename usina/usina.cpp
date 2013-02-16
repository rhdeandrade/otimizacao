#include <iostream>
#include "geracao_energia.cpp"

using namespace std;

class Usina {
  public:
    int id_usina;
    int id_subsistema;
    vector<GeracaoEnergia> geracoes;

};