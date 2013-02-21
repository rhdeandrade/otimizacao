#include <iostream>
#include <algorithm>
#include "despachohidrotermico/otimizacao_despacho_hidrotermico.cpp"

using namespace std;

int main() {
  cout << "Comecou\n";
  OtimizacaoDespachoHidrotermico odh;
  odh.carregarDados("lote5", 10);
  odh.ativarRestricoes(true, true, true, true);

  OtimizacaoDespachoHidrotermicoGlobals::atualizar_plano_producao(odh.plano_producao);

  return 0;
}
