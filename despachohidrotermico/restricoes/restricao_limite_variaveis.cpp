#ifndef restricao_limite_variaveis
#define restricao_limite_variaveis

#include <iostream>
#include "../../usina/usina_termica.cpp"
#include "../../usina/usina_hidreletrica.cpp"
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
