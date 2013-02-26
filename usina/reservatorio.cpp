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

    HistoricoOperacaoReservatorio* obter_historico_reservatorio(int periodo, int volume_inicial);

};

HistoricoOperacaoReservatorio* Reservatorio::obter_historico_reservatorio(int periodo, int volume_inicial) {

  for (int i = 0; i < this->historico.size(); i++) {
    //cout << i << " " << this->historico.at(i).periodo <<" Aquiiiiiiiiiiii\n";
    if(this->historico.at(i).periodo == periodo) {
      return &this->historico.at(i);
    }
  }

  HistoricoOperacaoReservatorio* historico2 = new HistoricoOperacaoReservatorio();

  historico2->periodo = periodo;
  historico2->volume = volume_inicial;

  return historico2;
}
#endif