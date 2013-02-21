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

    GeracaoEnergia obter_geracao_energia(int periodo);

};

GeracaoEnergia Usina::obter_geracao_energia(int periodo) {
  for (int i = 0; i < geracoes.size(); i++)
  { 
    if(geracoes.at(i).periodo == periodo) {
      return geracoes.at(i);
    }
  }

  GeracaoEnergia g;

  g.periodo = periodo;
  g.quantidade = 0;
  return g;
}
#endif