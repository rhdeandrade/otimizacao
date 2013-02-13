#include <iostream>
#include "../util/file_handler.cpp"
using namespace std;

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

    void carregar_usinas_termicas();

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


void CarregadorDados::carregar_usinas_termicas() {
  FileHandler file_handler;

  file_handler.open_file(this->arquivoDadosTermicas);
}