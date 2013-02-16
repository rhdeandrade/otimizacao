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

    vector<GeracaoEnergia> carregar_geracoes_usinas_termicas(int id_usina, string arquivo);

    void carregar_nome_arquivos(string arquivoDadosTermicas, string arquivoGeracoesTermicas, 
                    string arquivoDadosHidreletricas, string arquivoGeracoesHidreletricas,
                    string arquivoDadosSubsistemas, string arquivoDeficitsSubsistemas,
                    string arquivoDemandasSubsistemas, string arquivoIntercambiosSubsistemas); //Realiza função do construtor do CarregadorDados.php

    vector<UsinaTermica> carregar_usinas_termicas();

};

CarregadorDados::CarregadorDados() {
}


void CarregadorDados::carregar_nome_arquivos(string arquivoDadosTermicas, string arquivoGeracoesTermicas, 
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
    
    usina_termica.quantidade_geracao_max = lexical_cast<double>(tokens.at(1).data());
    
    usina_termica.quantidade_geracao_min = lexical_cast<double>(tokens.at(2).data());
    
    usina_termica.coeficiente_custo_termica_a0 = lexical_cast<double>(tokens.at(3).data());
    
    usina_termica.coeficiente_custo_termica_a1 = lexical_cast<double>(tokens.at(4).data());
    
    usina_termica.coeficiente_custo_termica_a2 = lexical_cast<double>(tokens.at(5).data());
    
    usina_termica.id_subsistema = (int) lexical_cast<double>(tokens.at(6).data());

    //usina_termica.gerações
    this->carregar_geracoes_usinas_termicas(usina_termica.id_usina, this->arquivoGeracoesTermicas);

    termicas.push_back(usina_termica);
    
  }

  cout << termicas.size() << "\n";

  return termicas;
}

vector<GeracaoEnergia> CarregadorDados::carregar_geracoes_usinas_termicas(int id_usina, string arquivo) {
  FileHandler file_handler;
  vector<GeracaoEnergia> geracoes;
  vector<string> dados_arquivo = file_handler.open_file(arquivo);
  string delimitador(" ");
  
  int i = 0;
  while(i <= dados_arquivo.size()) {
    vector<string> tokens;
    string value(dados_arquivo.at(i).data());
    split(tokens, value, is_any_of(delimitador));

    if(((int) lexical_cast<double>(tokens.at(0).data())) == id_usina) {
      int periodo = 1;
      while (periodo <= 60) { //Esse é o número de períodos definidos na classe OtimizacaoDespachoHidrotermicoGlobals do pj PHP
        i++;
        string value(dados_arquivo.at(i).data());
        split(tokens, value, is_any_of(delimitador));
        GeracaoEnergia geracao;
        geracao.periodo = periodo;
        periodo++;
        geracao.quantidade = lexical_cast<double>(tokens.at(0).data());

        geracoes.push_back(geracao);
      }

      return geracoes;
    }
    else {
      i += 60;
    }

    i++; //Pra mim essa linha não faz sentido, pq não fazer i += 61 na linha de cima então? Apenas copiei do cogido php

  }
  return geracoes;
}