#include "plano_producao.h"
#include "otimizacao_despacho_hidrotermico_globals.cpp"

#include "../usina/usina_termica.cpp"
#include "../usina/usina_hidreletrica.cpp"
#include "../usina/subsistema.cpp"


PlanoProducao::PlanoProducao(PlanoProducao *p) {
  this->termicas.swap(p->termicas);
  this->hidreletricas.swap(p->hidreletricas);
  this->subsistemas.swap(p->subsistemas);
}

PlanoProducao::PlanoProducao() {}


void PlanoProducao::perturbation(int operacao_atomica, int counter) {
  //Implementado apenas operacao atomica 4, que é a usada atualmente
  if (operacao_atomica == 4)  {
    this->executar(this, counter);
  }
}

double PlanoProducao::planejar_maximizacao_energia_hidraulica(vector<UsinaHidreletrica> h, int periodo) {
  double resultado = 0.0;
  vector<int> cascata74 = OtimizacaoDespachoHidrotermicoGlobals::get_instance()->cascata74;

  h = OtimizacaoDespachoHidrotermicoGlobals::ordernar_hidreletricas_tamanho_reservatorio(h, false);

  for (int i = 0; i < h.size(); ++i) {
    if (find(cascata74.begin(), cascata74.end(), h.at(i).id_usina) != cascata74.end()) {
      continue;
    }
    else {
      if (h.at(i).reservatorio.obter_tamanho() > 0) {
        resultado += h.at(i).maximizar_producao_energia(periodo, UsinaHidreletrica::TIPO_MAXIMIZACAO_RESERVATORIO, true);
      }
      else {
        resultado += h.at(i).maximizar_producao_energia(periodo, UsinaHidreletrica::TIPO_MAXIMIZACAO_AFLUENCIA_NATURAL, true);
      }

      GeracaoEnergia* geracao = h.at(i).obter_geracao_energia(periodo);

      resultado -= geracao->quantidade;
    }
  }

  return resultado;
}

double PlanoProducao::minimizar_energia_termica(vector<UsinaTermica> t, int periodo, double* energia_hidraulica_sobrando) {
  double resultado = 0.0;

  t = OtimizacaoDespachoHidrotermicoGlobals::obter_termicas_com_prioridade_desativacao(t, periodo);

  for (int i = 0; i < t.size(); i++) {
    GeracaoEnergia* geracao = t.at(i).obter_geracao_energia(periodo);
    double saldo = *energia_hidraulica_sobrando - geracao->quantidade;

    if (saldo > 0) {
      double quantidade = t.at(i).iniciar_processo_desativacao(periodo);
      *energia_hidraulica_sobrando -= quantidade;

      resultado += quantidade;
    }
  }  

  return resultado;
}

void PlanoProducao::executar(PlanoProducao p, int counter) {
  for (int i = 0; i < p.subsistemas.size(); i++) {
    vector<UsinaHidreletrica> hidreletricas = OtimizacaoDespachoHidrotermicoGlobals::obter_usinas_hidreletricas(p.hidreletricas, p.subsistemas.at(i).id_subsistema);
    vector<UsinaTermica> termicas = OtimizacaoDespachoHidrotermicoGlobals::obter_usinas_termicas(p.termicas, p.subsistemas.at(i).id_subsistema);

    double total_energia_hidraulica_sobrando = planejar_maximizacao_energia_hidraulica(p.hidreletricas, counter);

    double total_energia_termica_desligada = minimizar_energia_termica(p.termicas, counter, &total_energia_hidraulica_sobrando);

  }
}

