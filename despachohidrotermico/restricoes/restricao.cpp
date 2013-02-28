#ifndef restricao
#define restricao

#include <iostream>
#include "restricao_atendimento_demanda.cpp"
#include "restricao_balanco_hidrico.cpp"
#include "restricao_defluencia_minima.cpp"
#include "restricao_limite_variaveis.cpp"

using namespace std;

class Restricao {
  public:
    RestricaoAtendimentoDemanda *atendimento_demanda;
    RestricaoBalancoHidrico *balanco_hidrico;
    RestricaoDefluenciaMinima *defluencia_minima;
    RestricaoLimiteVariaveis *limite_variaveis;

    void setAtendimentoDemanda(RestricaoAtendimentoDemanda *restricao);
    void setBalancoHidrico(RestricaoBalancoHidrico *restricao);
    void setDefluenciaMinima(RestricaoDefluenciaMinima *restricao);
    void setLimiteVariaveis(RestricaoLimiteVariaveis *restricao);
    Restricao();
};

Restricao::Restricao() {
}


void Restricao::setBalancoHidrico(RestricaoBalancoHidrico *restricao) {
  balanco_hidrico = new RestricaoBalancoHidrico(restricao);
}

void Restricao::setAtendimentoDemanda(RestricaoAtendimentoDemanda *restricao) {
  atendimento_demanda = new RestricaoAtendimentoDemanda(restricao);
}

void Restricao::setDefluenciaMinima(RestricaoDefluenciaMinima *restricao) {
  defluencia_minima = new RestricaoDefluenciaMinima(restricao);
}

void Restricao::setLimiteVariaveis(RestricaoLimiteVariaveis *restricao) {
  limite_variaveis = new RestricaoLimiteVariaveis(restricao);
}


#endif
