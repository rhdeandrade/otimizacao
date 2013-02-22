#ifndef otimizacao_global_h
#define otimizacao_global_h

#include <iostream>

using namespace std;

class OtimizacaoDespachoHidrotermicoGlobals {

public:
  const static int NUM_PERIODOS = 60;
  const static double TAXA_DESCONTO = 0.00948879;
  const static int LIMIAR_ERRO_BALANCO_HIDRICO = 16;
  static OtimizacaoDespachoHidrotermicoGlobals* get_instance();
  static void atualizar_plano_producao(PlanoProducao plano_producao);

  vector<int> cascata74;
  vector<UsinaHidreletrica> hidreletricas;

  static vector<UsinaTermica> obter_usinas_termicas(vector<UsinaTermica> t, int id_subsistema);
  
  static vector<UsinaHidreletrica> obter_usinas_hidreletricas(vector<UsinaHidreletrica> h, int id_subsistema);

private:
  OtimizacaoDespachoHidrotermicoGlobals();
  static OtimizacaoDespachoHidrotermicoGlobals* instance;

};

OtimizacaoDespachoHidrotermicoGlobals* OtimizacaoDespachoHidrotermicoGlobals::instance;

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

void OtimizacaoDespachoHidrotermicoGlobals::atualizar_plano_producao(PlanoProducao plano_producao) {
  for (int i = 1; i <= 60; i++) {
    for (int j = 0; j < plano_producao.subsistemas.size(); j++) {
      
      double total_geracao_hidreletricas = 0;
      double total_geracao_termicas = 0;
      double total_intercambio = 0;
      
      vector<UsinaTermica> termicas = OtimizacaoDespachoHidrotermicoGlobals::obter_usinas_termicas(plano_producao.termicas, plano_producao.subsistemas.at(j).id_subsistema);

      for (int k = 0; k < termicas.size(); k++) {

        GeracaoEnergia geracao = termicas.at(k).obter_geracao_energia(i);
        total_geracao_termicas += geracao.quantidade;

      }

      vector<UsinaHidreletrica> hidreletricas = OtimizacaoDespachoHidrotermicoGlobals::obter_usinas_hidreletricas(plano_producao.hidreletricas, plano_producao.subsistemas.at(j).id_subsistema);

      for (int k = 0; k < hidreletricas.size(); k++) {
        hidreletricas.at(k).atualizar_balanco_hidrico(OtimizacaoDespachoHidrotermicoGlobals::get_instance()->cascata74, OtimizacaoDespachoHidrotermicoGlobals::get_instance()->hidreletricas, i);
      }      

    }

  }

}

vector<UsinaTermica> OtimizacaoDespachoHidrotermicoGlobals::obter_usinas_termicas(vector<UsinaTermica> t, int id_subsistema) {
  vector<UsinaTermica> termicas;

  for (int i = 0; i < t.size(); i++) {
    if (t.at(i).id_subsistema == id_subsistema) {
      termicas.push_back(t.at(i));
    }
  }

 return termicas;
}

vector<UsinaHidreletrica> OtimizacaoDespachoHidrotermicoGlobals::obter_usinas_hidreletricas(vector<UsinaHidreletrica> h, int id_subsistema) {
  vector<UsinaHidreletrica> hidreletricas;

  for (int i = 0; i < h.size(); i++) {
    if (h.at(i).id_subsistema == id_subsistema) {
      hidreletricas.push_back(h.at(i));
    }
  }

 return hidreletricas;
}

#endif