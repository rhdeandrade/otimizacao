#include <iostream>
#include <algorithm>
#include "despachohidrotermico/otimizacao_despacho_hidrotermico.cpp"

using namespace std;

int main() {
  cout << "Comecou\n";
  OtimizacaoDespachoHidrotermico odh;
  odh.carregarDados("lote5", 10);
  return 0;
}