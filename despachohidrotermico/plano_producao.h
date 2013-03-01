#ifndef plano_producao_h
#define plano_producao_h

using namespace std;
using namespace boost;


class PlanoProducao {
  public:
    vector<UsinaTermica> termicas;
    vector<UsinaHidreletrica> hidreletricas;
    vector<Subsistema> subsistemas;
    //OtimizacaoDespachoHidrotermicoGlobals* globals;
    
    PlanoProducao(PlanoProducao *p);
    PlanoProducao();
    
    void perturbation(int operacao_atomica, int counter);
    void executar(PlanoProducao p, int counter);
    double planejar_maximizacao_energia_hidraulica(vector<UsinaHidreletrica> h, int periodo);
    double minimizar_energia_termica(vector<UsinaTermica> t, int periodo, double* energia_termica_sobrando);
};



#endif