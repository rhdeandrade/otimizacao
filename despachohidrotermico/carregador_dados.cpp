#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include "../util/file_handler.cpp"
#include "../usina/usina_termica.cpp"

using namespace std;
using namespace boost;

class CarregadorDados {
  public:
    string arquivoDadosTermicas;
    string arquivoGeracoesTermicas;
    string arquivoDadosHidreletricas;
    string arquivoGeracoesHidreletricas;
    string arquivoDadosSubsistemas;
    string arquivoDeficitsSubsistemas;
    string arquivoDemandasSubsistemas;
    string arquivoIntercambiosSubsistemas;

    CarregadorDados();

    void carregarNomeArquivos(string arquivoDadosTermicas, string arquivoGeracoesTermicas, 
                    string arquivoDadosHidreletricas, string arquivoGeracoesHidreletricas,
                    string arquivoDadosSubsistemas, string arquivoDeficitsSubsistemas,
                    string arquivoDemandasSubsistemas, string arquivoIntercambiosSubsistemas); //Realiza função do construtor do CarregadorDados.php

    vector<UsinaTermica> carregar_usinas_termicas();

};
CarregadorDados::CarregadorDados() {

}

void CarregadorDados::carregarNomeArquivos(string arquivoDadosTermicas, string arquivoGeracoesTermicas, 
                    string arquivoDadosHidreletricas, string arquivoGeracoesHidreletricas,
                    string arquivoDadosSubsistemas, string arquivoDeficitsSubsistemas,
                    string arquivoDemandasSubsistemas, string arquivoIntercambiosSubsistemas) {

  this->arquivoDadosTermicas = arquivoDadosTermicas;
  this->arquivoGeracoesTermicas = arquivoGeracoesTermicas;
  this->arquivoDadosHidreletricas = arquivoDadosHidreletricas;
  this->arquivoGeracoesHidreletricas = arquivoGeracoesHidreletricas;
  this->arquivoDadosSubsistemas = arquivoDadosSubsistemas;
  this->arquivoDeficitsSubsistemas = arquivoDeficitsSubsistemas;
  this->arquivoDemandasSubsistemas = arquivoDemandasSubsistemas;
  this->arquivoIntercambiosSubsistemas = arquivoIntercambiosSubsistemas;

}

vector<UsinaTermica> CarregadorDados::carregar_usinas_termicas() {
  FileHandler file_handler;
  string delimitador(" ");
  vector<UsinaTermica> termicas;

  vector<string> usinas_termicas = file_handler.open_file(this->arquivoDadosTermicas);

  for(int i = 0; i < usinas_termicas.size(); i++) {
    vector<string> tokens;
    UsinaTermica usina_termica;

    string value(usinas_termicas.at(i).data());
        
    split(tokens, value, is_any_of(delimitador));

    usina_termica.id_usina = (int) lexical_cast<double>(tokens.at(0).data());
    cout << usina_termica.id_usina << '\n';
    
    usina_termica.quantidade_geracao_max = lexical_cast<double>(tokens.at(1).data());
    cout << usina_termica.quantidade_geracao_max << '\n';
    
    usina_termica.quantidade_geracao_min = lexical_cast<double>(tokens.at(2).data());
    cout << usina_termica.quantidade_geracao_min << '\n';
    
    usina_termica.coeficiente_custo_termica_a0 = lexical_cast<double>(tokens.at(3).data());
    cout << usina_termica.coeficiente_custo_termica_a0 << '\n';
    
    usina_termica.coeficiente_custo_termica_a1 = lexical_cast<double>(tokens.at(4).data());
    cout << usina_termica.coeficiente_custo_termica_a1 << '\n';
    
    usina_termica.coeficiente_custo_termica_a2 = lexical_cast<double>(tokens.at(5).data());
    cout << usina_termica.coeficiente_custo_termica_a2 << '\n';
    
    usina_termica.id_subsistema = (int) lexical_cast<double>(tokens.at(6).data());
    cout << usina_termica.id_subsistema << '\n';

    //usina_termica.gerações

    termicas.push_back(usina_termica);
    
  }

  cout << termicas.size() << "\n";

  return termicas;
}