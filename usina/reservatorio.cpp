#ifndef reservatorio_h
#define reservatorio_h

#include <iostream>
#include "historico_operacao_reservatorio.cpp"

using namespace std;
class Reservatorio {
  public:
    double volume_maximo;
    double volume_minimo;
    double minimo_vazao_turbinada;
    double maximo_vazao_turbinada;
    double maximo_vazao_vertida;
    double defluencia_minima;
    vector<HistoricoOperacaoReservatorio> historico;

};
#endif