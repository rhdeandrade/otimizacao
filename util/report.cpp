#ifndef resport_h
#define resport_h

class Report {
public:
  static void imprimir_resultados(PlanoProducao plano_producao);
};

void Report::imprimir_resultados(PlanoProducao plano_producao) {
  cout << "Funcao Objetivo\n";
  //print_funcao_objetivo

  double total_energia_hidraulica = 0;

  for (int i = 0; i < plano_producao.hidreletricas.size(); i++) {
    total_energia_hidraulica += plano_producao.hidreletricas.at(i).total_energia_gerada();
  }

  cout << "Total Energia Hidraulica: " << total_energia_gerada << "\n";

  double total_energia_termica = 0;
  for (int i = 0; i < plano_producao.termicas.size(); i++) {
    total_energia_termica += plano.termicas.at(i).total_energia_gerada();
  }

  
}


#endif