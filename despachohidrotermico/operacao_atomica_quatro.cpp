#ifndef operacao_atomica_quatro_h
#define operacao_atomica_quatro_h

class OperacaoAtomicaQuatro {
  public:
    void executar(PlanoProducao p, int counter);
};

void OperacaoAtomicaQuatro::executar(PlanoProducao p, int counter) {
  for (int i = 0; i < p.subsistemas.size(); i++) {
    vector<UsinaHidreletrica> hidreletricas = OtimizacaoDespachoHidrotermicoGlobals::obter_usinas_hidreletricas(p.hidreletricas, p.subsistemas.at(i).id_subsistema);
  }
}
#endif