#ifndef otimizacao_global_h
#define otimizacao_global_h

#include <iostream>

using namespace std;

class OtimizacaoDespachoHidrotermicoGlobals {

public:
  static int NUM_PERIODOS = 60
  static double TAXA_DESCONTO = 0.00948879
  static int LIMIAR_ERRO_BALANCO_HIDRICO = 16;
  static OtimizacaoDespachoHidrotermicoGlobals* get_instance();

  vector<int> cascata74;
  vector<UsinaHidreletrica> hidreletricas;

private:
  OtimizacaoDespachoHidrotermicoGlobals();
  static OtimizacaoDespachoHidrotermicoGlobals* instance;

};

OtimizacaoDespachoHidrotermicoGlobals::OtimizacaoDespachoHidrotermicoGlobals() {
  cascata74.push_back(74);
  cascata74.push_back(76);
  cascata74.push_back(77);
  cascata74.push_back(71);
  cascata74.push_back(72);
  cascata74.push_back(73);
  cascata74.push_back(77);
  cascata74.push_back(78);
  cascata74.push_back(82);
}

OtimizacaoDespachoHidrotermicoGlobals* OtimizacaoDespachoHidrotermicoGlobals::get_instance() {
  if (instance == NULL) {
    instance = new OtimizacaoDespachoHidrotermicoGlobals();
  }
  return instance;
}


#endif