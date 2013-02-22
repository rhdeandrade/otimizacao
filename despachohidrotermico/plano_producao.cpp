#ifndef plano_producao_h
#define plano_producao_h

#include <iostream>
#include "../usina/usina_termica.cpp"
#include "../usina/usina_hidreletrica.cpp"
#include "../usina/subsistema.cpp"
//#include "otimizacao_despacho_hidrotermico_globals.cpp"
using namespace std;

class PlanoProducao {
  public:
    vector<UsinaTermica> termicas;
    vector<UsinaHidreletrica> hidreletricas;
    vector<Subsistema> subsistemas;
};

#endif