#ifndef usina_h
#define usina_h

#include <iostream>
#include "geracao_energia.cpp"

using namespace std;

class Usina {
  public:
    int id_usina;
    int id_subsistema;
    vector<GeracaoEnergia> geracoes;

};

#endif