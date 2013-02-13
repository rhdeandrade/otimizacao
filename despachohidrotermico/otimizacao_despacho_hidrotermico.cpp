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

  string termicas =  "despachohidrotermico/dados/" + tipo + "/Termicas.txt";
  string geracaoTermicas =  "dados/$lote/planoproducao/termoSaida_$serie.txt";
  string hidreletricas =  "dados/$lote/Hidreletricas.txt";
  string geracaoHidreletricas =  "dados/$lote/planoproducao/hidroSaida_$serie.txt";
  string subsistemas =  "dados/$lote/Subsistemas.txt";
  string deficits =  "dados/$lote/planoproducao/DeficitsSaida_$serie.txt";
  string demanda =  "dados/$lote/planoproducao/Demanda.txt";
  string intercambios =  "dados/$lote/planoproducao/IntercambiosSaida_$serie.txt";

  carregadorDados.carregarNomeArquivos(termicas, geracaoTermicas, hidreletricas, geracaoHidreletricas, subsistemas, deficits,
                          demanda, intercambios); //Realiza função do construtor do CarregadorDados.php

  carregadorDados.carregar_usinas_termicas();
}


