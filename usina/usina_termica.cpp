#include <iostream>
#include "usina.cpp"

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

};