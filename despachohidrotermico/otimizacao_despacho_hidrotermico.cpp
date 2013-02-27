#ifndef otimizacao_despacho_hidrotermico
#define otimizacao_despacho_hidrotermico

#include <iostream>
#include "carregador_dados.cpp"
#include "plano_producao.cpp"
#include "restricoes/restricao.cpp"
#include "otimizacao_despacho_hidrotermico_globals.cpp"

using namespace std;

class OtimizacaoDespachoHidrotermico {
  public:
    string log;
    CarregadorDados carregadorDados;
    Restricao restricoes;
    PlanoProducao plano_producao;
    // array errors;

    //Constructor
    OtimizacaoDespachoHidrotermico();

    void carregarDados(string tipo, int serie);
    void ativarRestricoes(bool balancoHidrico, bool atendimentoDemanda, bool defluenciaMinima, bool limiteVariaveis);
};

OtimizacaoDespachoHidrotermico::OtimizacaoDespachoHidrotermico() {
  cout << "Construtor\n";
}

void OtimizacaoDespachoHidrotermico::carregarDados(string tipo, int serie) {
  cout << "Tipo: " << tipo << " Numero: " << serie << "\n";

  stringstream ss;

  ss << serie;

  string termicas =  "despachohidrotermico/dados/" + tipo + "/Termicas.txt";
  string geracaoTermicas =  "despachohidrotermico/dados/" + tipo + "/planoproducao/termoSaida_" + ss.str() + ".txt";
  string hidreletricas =  "despachohidrotermico/dados/" + tipo + "/Hidreletricas.txt";
  string geracaoHidreletricas =  "despachohidrotermico/dados/" + tipo + "/planoproducao/hidroSaida_" + ss.str() + ".txt";
  string subsistemas =  "despachohidrotermico/dados/" + tipo + "/Subsistemas.txt";
  string deficits =  "despachohidrotermico/dados/" + tipo + "/planoproducao/DeficitsSaida_" + ss.str() + ".txt";
  string demanda =  "despachohidrotermico/dados/" + tipo + "/planoproducao/Demanda.txt";
  string intercambios =  "despachohidrotermico/dados/" + tipo + "/planoproducao/IntercambiosSaida_" + ss.str() + ".txt";

  carregadorDados.carregar_nome_arquivos(termicas, geracaoTermicas, hidreletricas, geracaoHidreletricas, subsistemas, deficits,
                          demanda, intercambios); //Realiza função do construtor do CarregadorDados.php

  plano_producao.termicas = carregadorDados.carregar_usinas_termicas();

  plano_producao.hidreletricas = carregadorDados.carregar_usinas_hidreletricas();

  plano_producao.subsistemas = carregadorDados.carregar_subsistema();

  OtimizacaoDespachoHidrotermicoGlobals::get_instance()->hidreletricas = plano_producao.hidreletricas;

}

void OtimizacaoDespachoHidrotermico::ativarRestricoes(bool balancoHidrico, bool atendimentoDemanda, bool defluenciaMinima, bool limiteVariaveis) {
  if(atendimentoDemanda)
    restricoes.setAtendimentoDemanda(new RestricaoAtendimentoDemanda(plano_producao.subsistemas, plano_producao.hidreletricas, plano_producao.termicas));
  if(balancoHidrico)
    restricoes.setBalancoHidrico(new RestricaoBalancoHidrico(plano_producao.hidreletricas));
  if(defluenciaMinima)
    restricoes.setDefluenciaMinima(new RestricaoDefluenciaMinima(plano_producao.hidreletricas));
  if(limiteVariaveis)
    restricoes.setLimiteVariaveis(new RestricaoLimiteVariaveis(plano_producao.hidreletricas, plano_producao.termicas));
}

#endif
