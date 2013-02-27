#ifndef plano_producao_h
#define plano_producao_h

#include <iostream>
#include "../usina/usina_termica.cpp"
#include "../usina/usina_hidreletrica.cpp"
#include "../usina/subsistema.cpp"
//#include "otimizacao_despacho_hidrotermico_globals.cpp"
using namespace std;
using namespace boost;

class PlanoProducao {
  public:
    vector<UsinaTermica> termicas;
    vector<UsinaHidreletrica> hidreletricas;
    vector<Subsistema> subsistemas;
    PlanoProducao(PlanoProducao* p);
    PlanoProducao();
    void perturbation(int operacao_atomica, int counter);

};

PlanoProducao::PlanoProducao(PlanoProducao* p) {
  this->termicas.swap(p->termicas);
  this->hidreletricas.swap(p->hidreletricas);
  this->subsistemas.swap(p->subsistemas);
}

PlanoProducao::PlanoProducao() {

}

void PlanoProducao::perturbation(int operacao_atomica, int counter) {
  
}



#endif