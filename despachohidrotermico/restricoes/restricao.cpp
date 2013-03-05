#ifndef restricao_cpp
#define restricao_cpp

#include "restricao.h"
#include "restricao_atendimento_demanda.cpp"

Restricao::Restricao() {
}


void Restricao::setBalancoHidrico(RestricaoBalancoHidrico *restricao) {
  balanco_hidrico = restricao;
}

void Restricao::setAtendimentoDemanda(RestricaoAtendimentoDemanda *restricao) {
  atendimento_demanda = restricao;
}

void Restricao::setDefluenciaMinima(RestricaoDefluenciaMinima *restricao) {
  defluencia_minima = restricao;
}

void Restricao::setLimiteVariaveis(RestricaoLimiteVariaveis *restricao) {
  limite_variaveis = restricao;
}


#endif
