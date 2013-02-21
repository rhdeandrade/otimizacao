#ifndef otimizacao_despacho_hidrotermico
#define otimizacao_despacho_hidrotermico

#include <iostream>
#include "carregador_dados.cpp"
#include "plano_producao.cpp"
#include "restricoes/restricao_balanco_hidrico.cpp"

using namespace std;

class OtimizacaoDespachoHidrotermico {
  public:
    string log;
    CarregadorDados carregadorDados;
    vector<bool> restricoes;
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

}

void OtimizacaoDespachoHidrotermico::ativarRestricoes(bool balancoHidrico, bool atendimentoDemanda, bool defluenciaMinima, bool limiteVariaveis) {
  if(balancoHidrico)
    cout << "BalanciHidrico\n";
//    restricoes.push_back(new RestricaoBalancoHidrico(hidreletricas));
  if(atendimentoDemanda)
    cout << "Atendimento\n";
//    restricoes.push_back(new RestricaoAtendimentoDemanda(subsistemas, hidreletricas, termicas));
  if(defluenciaMinima)
    cout << "Defluencia\n";
//    restricoes.push_back(new RestricaoDefluenciaMinima(hidreletricas));
  if(limiteVariaveis)
    cout << "Limite\n";
//    restricoes.push_back(new RestricaoLimiteVariaveis(hidreletricas, termicas));
}

#endif
