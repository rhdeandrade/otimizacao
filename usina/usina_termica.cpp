#ifndef usina_termica_h
#define usina_termica_h

#include <iostream>
#include "usina.cpp"

#include <math.h>

using namespace std;

class UsinaTermica : public Usina {
  public:
    double quantidade_geracao_max;
    double quantidade_geracao_min;
    double coeficiente_custo_termica_a2;
    double coeficiente_custo_termica_a1;
    double coeficiente_custo_termica_a0;
    double tempo_minimo_ativada;
    double tempo_minimo_desativada;
    UsinaTermica();
    double custo_termica_mega_watt_medio(int periodo);
};

UsinaTermica::UsinaTermica() {
  this->coeficiente_custo_termica_a2 = 0;
  this->coeficiente_custo_termica_a0 = 0;
  this->coeficiente_custo_termica_a1 = 0;
  this->tempo_minimo_ativada = 3;
  this->tempo_minimo_desativada = 3;
}

double UsinaTermica::custo_termica_mega_watt_medio(int periodo) {
  GeracaoEnergia* g = this->obter_geracao_energia(periodo);

  double resultado = pow(g->quantidade, 2);

  resultado *= this->coeficiente_custo_termica_a2;
  resultado += this->coeficiente_custo_termica_a1 * g->quantidade;
  resultado += this->coeficiente_custo_termica_a0;
  return resultado;
}

#endif