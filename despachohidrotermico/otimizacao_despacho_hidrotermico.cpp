#include <iostream>
#include "carregador_dados.cpp"
using namespace std;

class OtimizacaoDespachoHidrotermico {
  public:
    // PlanoProducao planoProducao;
    string log;
    CarregadorDados carregadorDados;
    // array errors;

    //Constructor
    OtimizacaoDespachoHidrotermico();

    void carregarDados(string tipo, int serie);
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

  carregadorDados.carregar_usinas_termicas();
}


