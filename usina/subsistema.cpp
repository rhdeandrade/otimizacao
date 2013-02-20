#ifndef subsistema_h
#define subsistema_h

#include <iostream>
#include "demanda_energia.cpp"
#include "deficit.cpp"
#include "intercambio.cpp"

using namespace std;
using namespace boost;

class Subsistema {
  public:
    int id_subsistema;
    double coeficiente_custo_deficit_a2;
    double coeficiente_custo_deficit_a1;
    double coeficiente_custo_deficit_a0;

    double intercambio_minimo;
    double intercambio_maximo;
    double demanda;

    vector<DemandaEnergia> demandas;
    vector<Deficit> deficits;
    vector<Intercambio> intercambios;
};

#endif