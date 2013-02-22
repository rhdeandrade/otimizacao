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

    HistoricoOperacaoReservatorio obter_historico_reservatorio(int periodo, int volume_inicial);

};

HistoricoOperacaoReservatorio Reservatorio::obter_historico_reservatorio(int periodo, int volume_inicial) {

  for (int i = 0; i < this->historico.size(); ++i) {
    if(this->historico.at(i).periodo == periodo) {
      return this->historico.at(i);
    }
  }

  HistoricoOperacaoReservatorio historico;
  historico.periodo = periodo;
  historico.volume = volume_inicial;

  return historico;
}
#endif