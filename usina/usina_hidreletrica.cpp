#ifndef usina_hidreletrica_h
#define usina_hidreletrica_h

#include <iostream>
#include <stdlib.h>
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

    void atualizar_balanco_hidrico(vector<int> excecoes, vector<UsinaHidreletrica> hidreletricas, int periodo);

    double carregar_vazao_montante(vector<UsinaHidreletrica> hidreletricas, int periodo);
    double carregar_afluencia_montante(vector<UsinaHidreletrica> hidreletricas, int periodo);

    UsinaHidreletrica obter_usina(vector<UsinaHidreletrica> hidreletricas, int id_usina);

  private:
    static const double LIMIAR_ERRO_BALANCO_HIDRICO = 16.0 //OtimizacaoDespachoHidrotermicoGlobals::LIMIAR_ERRO_BALANCO_HIDRICO

};

void UsinaHidreletrica::atualizar_balanco_hidrico(vector<int> excecoes, vector<UsinaHidreletrica> hidreletricas, int periodo) {

    if (find(excecoes.begin(), excecoes.end(), this->id_usina) != excecoes.end()) {
        return;
    }

    HistoricoOperacaoReservatorio historico = this->reservatorio.obter_historico_reservatorio(periodo, 0);

    HistoricoOperacaoReservatorio historico_anterior = this->reservatorio.obter_historico_reservatorio(periodo - 1, this->reservatorio.volume_maximo);

    Conversor c;
    double volume = c.hectometro_metro_cubico(historico.volume, periodo);
    double volume_anterior = c.hectometro_metro_cubico(historico_anterior.volume, periodo);

    double vazao_total = carregar_vazao_montante(hidreletricas, periodo); // Equivalente a calcularVazaoMontante
    double afluencia_natural = carregar_afluencia_montante(hidreletricas, periodo); // Equivalente a calcularVazaoMontante

    double volume_atualizado = volume_atualizado + vazao_total;
    volume_atualizado = volume_atualizado + historico.vazao_turbinada;
    volume_atualizado = volume_atualizado + historico.vazao_vertida;
    volume_atualizado = volume_atualizado + historico.afluencia_natural;
    volume_atualizado = volume_atualizado + afluencia_natural;

    double resultado = volume - volume_atualizado;

    if (abs(resultado) > LIMIAR_ERRO_BALANCO_HIDRICO)  {
      volume_atualizado = c.metro_cubico_hectometro(volume_atualizado, periodo);
      if (volume_atualizado > this->reservatorio.volume_maximo) {
        historico.volume = this->reservatorio.volume_maximo;
      }
    }



}

double UsinaHidreletrica::carregar_vazao_montante(vector<UsinaHidreletrica> hidreletricas, int periodo) {
    double total = 0.0;
    for (int i = 0; i < this->montantes.size(); ++i) {
        UsinaHidreletrica montante = obter_usina(hidreletricas, this->montantes.at(i));

        if (montante.id_usina != -200) { //-200 não encontrou
            HistoricoOperacaoReservatorio historico = montante.reservatorio.obter_historico_reservatorio(periodo, 0);
            total += historico.vazao_turbinada + historico.vazao_vertida;
        }
    }
    return total;
}

double UsinaHidreletrica::carregar_afluencia_montante(vector<UsinaHidreletrica> hidreletricas, int periodo) {
    double total = 0.0;
    cout << this->id_usina << "\n";
    for (int i = 0; i < this->montantes.size(); ++i) {
        UsinaHidreletrica montante = obter_usina(hidreletricas, montantes.at(i));

        if (montante.id_usina != -200) {//-200 não encontrou
            HistoricoOperacaoReservatorio historico = montante.reservatorio.obter_historico_reservatorio(periodo, 0);
            total += historico.afluencia_natural;
        }
    }
    return total;
}

UsinaHidreletrica UsinaHidreletrica::obter_usina(vector<UsinaHidreletrica> hidreletricas, int id_usina) {
    for (int i = 0; i < hidreletricas.size(); ++i) {
        if (hidreletricas.at(i).id_usina == id_usina) {
            return hidreletricas.at(i);
        }
    }

    UsinaHidreletrica usina;
    usina.id_usina = -200;
    return usina;

}

#endif