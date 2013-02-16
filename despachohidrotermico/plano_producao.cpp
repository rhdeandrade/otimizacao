#ifndef plano_producao_h
#define plano_producao_h

#include <iostream>
#include "../usina/usina_termica.cpp"
using namespace std;

class PlanoProducao {
  public:
    vector<UsinaTermica> termicas;
};

#endif