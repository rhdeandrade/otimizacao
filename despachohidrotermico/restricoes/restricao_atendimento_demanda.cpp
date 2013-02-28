#ifndef restricao_atendimento_demanda
#define restricao_atendimento_demanda

#include <iostream>
#include "../../usina/usina_termica.cpp"
#include "../../usina/usina_hidreletrica.cpp"
#include "../../usina/subsistema.cpp"
using namespace std;

class RestricaoAtendimentoDemanda {
  public:
      RestricaoAtendimentoDemanda(vector<Subsistema> subsistemas, vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas);
      RestricaoAtendimentoDemanda();

      string checkConstraint();
};

RestricaoAtendimentoDemanda::RestricaoAtendimentoDemanda() {
}

RestricaoAtendimentoDemanda::RestricaoAtendimentoDemanda(vector<Subsistema> subsistemas, vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas) {
}

string RestricaoAtendimentoDemanda::checkConstraint() {
  return "Oi";
}
#endif
