#ifndef restricao_limite_variaveis_h
#define restricao_limite_variaveis_h

#include <iostream>
//#include "../../usina/usina_termica.cpp"
//#include "../../usina/usina_hidreletrica.cpp"
using namespace std;

class RestricaoLimiteVariaveis {
  public:
      RestricaoLimiteVariaveis(vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas);
      RestricaoLimiteVariaveis();
};

RestricaoLimiteVariaveis::RestricaoLimiteVariaveis(vector<UsinaHidreletrica> hidreletricas, vector<UsinaTermica> termicas) {

}

RestricaoLimiteVariaveis::RestricaoLimiteVariaveis() {

}
#endif
