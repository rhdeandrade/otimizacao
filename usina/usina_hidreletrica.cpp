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
    double calcular_geracao_energia_com_produtividade_media(int periodo, double volume, double volume_anterior, double vazao_turbinada, double vazao_vertida);
    double calcular_polinomio_montante(double vazao_total);

  private:
    static const double LIMIAR_ERRO_BALANCO_HIDRICO = 16.0; //OtimizacaoDespachoHidrotermicoGlobals::LIMIAR_ERRO_BALANCO_HIDRICO

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

  if (abs((int)resultado) > LIMIAR_ERRO_BALANCO_HIDRICO)  {
    volume_atualizado = c.metro_cubico_hectometro(volume_atualizado, periodo);
    if (volume_atualizado > this->reservatorio.volume_maximo) {
      historico.volume = this->reservatorio.volume_maximo;
      volume_atualizado = volume_atualizado - this->reservatorio.volume_maximo;
      historico.vazao_vertida = historico.vazao_vertida + c.hectometro_metro_cubico(volume_atualizado, periodo);
    }
    else if (this->reservatorio.volume_minimo > volume_atualizado) {
      historico.volume = volume_atualizado;
      historico.volume += c.metro_cubico_hectometro(historico.vazao_vertida, periodo);
      historico.vazao_vertida = 0;

      if (this->reservatorio.volume_minimo > volume_atualizado) {
        double volume_minimo_faltante = this->reservatorio.volume_minimo + historico.volume;
        historico.vazao_turbinada += c.hectometro_metro_cubico(volume_minimo_faltante, periodo);
        historico.volume += volume_minimo_faltante;
        GeracaoEnergia geracao = this->obter_geracao_energia(periodo);
        geracao.quantidade = this->calcular_geracao_energia_com_produtividade_media(periodo, 0.0, 0.0, 0.0, 0.0);
      }
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

double UsinaHidreletrica::calcular_geracao_energia_com_produtividade_media(int periodo, double volume, double volume_anterior, double vazao_turbinada, double vazao_vertida) {
  if (periodo > 0) {
    HistoricoOperacaoReservatorio historico = this->reservatorio.obter_historico_reservatorio(periodo, this->reservatorio.volume_maximo);
    HistoricoOperacaoReservatorio historico_anterior = this->reservatorio.obter_historico_reservatorio(periodo - 1, this->reservatorio.volume_maximo);

    volume = historico.volume;
    volume_anterior = historico_anterior.volume;
    vazao_turbinada = historico.vazao_turbinada;
    vazao_vertida = historico.vazao_vertida;
  }
  double phi = this->calcular_polinomio_montante((volume + volume_anterior) / 2);
  //double theta = this->calcular_polinomio_jusante(vazao_turbinada + vazao_vertida); 

  return 0.0;
}

double UsinaHidreletrica::calcular_polinomio_montante(double vazao_total) {
  double A4 = this->coeficiente_cota_montante_a4 * pow(vazao_total, 4);
  double A3 = this->coeficiente_cota_montante_a4 * pow(vazao_total, 3);
  double A2 = this->coeficiente_cota_montante_a4 * pow(vazao_total, 2);
  double A1 = this->coeficiente_cota_montante_a1 * vazao_total;

  double resultado = this->coeficiente_cota_montante_a0 + A1 + A2 + A3 + A4;

  return resultado;
}
#endif