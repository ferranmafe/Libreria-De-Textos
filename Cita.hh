/** @file Cita.hh
    @brief Especificació de la classe Cita
*/
#ifndef _CITA_HH_
#define _CITA_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
using namespace std;
#endif

#include "Frase.hh"

/** @class Cita
    @brief  Representa una cita

    Conté la referència de la cita, el títol del text d'on s'ha extret, el seu autor el contingut (cjt. de frases) que la formen
    i nombre d'inici i final de les frases de la cita en el textd'on sha extret.
*/

class Cita {
private:
  /** @brief Vector de <em>Frase</em> amb el contingut de la cita*/
  vector<Frase> cita;

  /** @brief String que conté la referència que identifica la cita.*/
  string referencia;

  /** @brief conté el títol del text d'on prové la cita*/
  list<string> titol;

  /** @brief conté l'autor del text on prové la cita*/
  list<string> autor;

  /** @brief conté el valor d'inici i final de les frases de cita en el text*/
  pair<int,int> inici_final;

public:

  //Constructora
  /** @brief Creadora per defecte

      S'executa automàticament al declarar una cita.
      \pre <em>cert</em>
      \post Element cita amb tots els seus camps buits.
  */
  Cita();


  //Destructora
  /** @brief Destructora per defecte

      S'executa automàticament al sortir del bloc on s'ha declarat
      \pre Tenim una Cita
      \post S'ha eliminat l'objecte del tipus Cita
  */
  ~Cita();


  //Modificadors

  /** @brief Modificar el parametre implícit referencia

      \pre El parametre d'entrada conté la informació que volem modificar
      \post S'ha modificat el parametre implícit amb el parametre d'entrada, parametre d'entrada no s'ha modificat.
  */
  void modificar_referencia(const string& referencia);


  /** @brief Modificar el parametre implícit cita

      \pre El parametre d'entrada conté la informació que volem modificar
      \post S'ha modificat el parametre implícit amb el parametre d'entrada, parametre d'entrada no s'ha modificat.
  */
  void modificar_cita(const vector<Frase>& cita);


  /** @brief Modificar el parametre implícit títol

      \pre El parametre d'entrada conté la informació que volem modificar
      \post S'ha modificat el parametre implícit amb el parametre d'entrada, parametre d'entrada no s'ha modificat.
  */
  void modificar_titol(const list<string>& titol);


  /** @brief Modificar el parametre implícit autor

      \pre El parametre d'entrada conté la informació que volem modificar
      \post S'ha modificat el parametre implícit amb el parametre d'entrada, parametre d'entrada no s'ha modificat.
  */
  void modificar_autor(const list<string>& autor);


  /** @brief Modificar el parametre implícit inici_final

      \pre El parametre d'entrada conté la informació que volem modificar
      \post S'ha modificat el parametre implícit amb el parametre d'entrada, parametre d'entrada no s'ha modificat.
  */
  void modificar_inici_final(int inici, int final);


  //Consultors

  /** @brief Retorna el parametre implícit referencia

      \pre Cert
      \post Retorna el parametre implícit referencia, no modifica els parametres implicits
  */
  string consultar_referencia() const;


  /** @brief Retorna el parametre implícit cita

      \pre Cert
      \post Retorna el parametre implícit cita, no modifica els parametres implicits
  */
  vector<Frase> consultar_cita() const;


  /** @brief Retorna el parametre implícit titol

      \pre Cert
      \post Retorna el parametre implícit titol, no modifica els parametres implicits
  */
  list<string> consultar_titol() const;


  /** @brief Retorna el parametre implícit autor

      \pre Cert
      \post Retorna el parametre implícit autor, no modifica els parametres implicits
  */
  list<string> consultar_autor() const;


  /** @brief Retorna el parametre implícit inici_final

      \pre Cert
      \post Retorna el parametre implícit inici_final, no modifica els parametres implicits
  */
  pair<int,int> consultar_inici_final() const;
};
#endif
