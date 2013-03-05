#include <iostream>
#include <algorithm>

#include "despachohidrotermico/otimizacao_despacho_hidrotermico.cpp"
#include "despachohidrotermico/plano_producao.h"
#include "despachohidrotermico/otimizacao_despacho_hidrotermico_globals.h"
#include "util/report.cpp"
#include <ctime>

using namespace std;

int main() {
  cout << "Comecou\n";

  OtimizacaoDespachoHidrotermico odh;
  odh.carregarDados("lote5", 10);
  odh.ativarRestricoes(true, true, true, true);

  OtimizacaoDespachoHidrotermicoGlobals::atualizar_plano_producao(odh.plano_producao);

  //odh.validar_plano_producao();

  int operacao_atomica = 4;
  cout << "Executando Hill Climbing\n";
  odh.executar_hill_climbing(operacao_atomica, 60, 3);

  Report::imprimir_resultados(odh.plano_producao);

  return 0;
}
