#ifndef usina_hidreletrica_h
#define usina_hidreletrica_h

#include <iostream>
#include "reservatorio.cpp"
#include "montante.cpp"
#include "../util/conversor.cpp"

using namespace std;
using namespace boost;

class UsinaHidreletrica : public Usina {
  public:
    static const char TIPO_MAXIMIZACAO_RESERVATORIO = 'r';
    static const char TIPO_MAXIMIZACAO_AFLUENCIA_NATURAL = 'a';
    Reservatorio reservatorio;
    int jusante; 
    vector<int> montantes; //Classe montante Apenas pra poder fazer atributo de UsinaHidreletrica dentro da class UsinaHidreletrica
    
    double coeficiente_cota_montante_a0;
    double coeficiente_cota_montante_a1;
    double coeficiente_cota_montante_a2;
    double coeficiente_cota_montante_a3;
    double coeficiente_cota_montante_a4;

    double coeficiente_cota_jusante_a0;
    double coeficiente_cota_jusante_a1;
    double coeficiente_cota_jusante_a2;
    double coeficiente_cota_jusante_a3;
    double coeficiente_cota_jusante_a4;

    double tipo_perda_hidraulica;
    double valor_perda_hidraulica;

    double potencia_efetiva;
    double produtividade_media;

    void atualizar_balanco_hidrico(vector<int> excecoes, int periodo);

};

void UsinaHidreletrica::atualizar_balanco_hidrico(vector<int> excecoes, int periodo) {

    if (find(excecoes.begin(), excecoes.end(), this->id_usina) != excecoes.end()) {
        return;
    }

    HistoricoOperacaoReservatorio historico = this->reservatorio.obter_historico_reservatorio(periodo, 0);

    HistoricoOperacaoReservatorio historico_anterior = this->reservatorio.obter_historico_reservatorio(periodo - 1, this->reservatorio.volume_maximo);

    Conversor c;
    double volume = c.hectometro_metro_cubico(historico.volume, periodo);
    double volume_anterior = c.hectometro_metro_cubico(historico_anterior.volume, periodo);

}

#endif