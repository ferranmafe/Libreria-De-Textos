/** @file Cita.cc
    @brief Còdig de la classe Cita
*/

#include "Cita.hh"

  Cita::Cita(){}


  Cita::~Cita(){}


  void Cita::modificar_referencia(const string& referencia){
    this->referencia = referencia;
  }


  void Cita::modificar_cita(const vector<Frase>& cita){
    this->cita = cita;
  }


  void Cita::modificar_titol(const list<string>& titol){
    this->titol = titol;
  }


  void Cita::modificar_autor(const list<string>& autor){
    this->autor = autor;
  }

  void Cita::modificar_inici_final(int inici, int final){
    pair<int, int> in_fi;
    in_fi.first = inici;
    in_fi.second = final;
    this->inici_final = in_fi;
  }

  string Cita::consultar_referencia() const {
    return referencia;
  }


  vector<Frase> Cita::consultar_cita() const {
    return cita;
  }


  list<string> Cita::consultar_titol() const {
    return titol;
  }


  list<string> Cita::consultar_autor() const {
    return autor;
  }

  pair<int,int> Cita::consultar_inici_final() const{
    return inici_final;
  }
