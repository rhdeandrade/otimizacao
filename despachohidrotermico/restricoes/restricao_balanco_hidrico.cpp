#ifndef restricao_balanco_hidrico
#define restricao_balanco_hidrico

#include <iostream>
using namespace std;
#include "../../usina/usina_hidreletrica.cpp"

class RestricaoBalancoHidrico {
  public:
      RestricaoBalancoHidrico(vector<UsinaHidreletrica> hidreletricas);
      RestricaoBalancoHidrico();
};

RestricaoBalancoHidrico::RestricaoBalancoHidrico(vector<UsinaHidreletrica> hidreletricas) {

}

RestricaoBalancoHidrico::RestricaoBalancoHidrico() {

}
#endif
