/** @file Frase.hh
    @brief Especificació de la classe Frase
*/

#ifndef _FRASE_HH_
#define _FRASE_HH_

#ifndef NO_DIAGRAM
#include <string>
#include <list>
using namespace std;
#endif


/** @class Frase
    @brief  Representa una frase.
    Conté el contingut d'una de les frases d'un text.
*/
class Frase {

private:

    /** @brief Llista de strings amb el contingut d'una frase*/
    list<string> frase;

    /** @brief Enter que indica el número de paraules d'una frase.*/
    int n_paraules;

public:
    //Constructores

    /** @brief Creadora per defecte
      S'executa automàticament al declarar una frase.
      \pre <em>cert</em>
      \post Una frase buida.
  */
    Frase();

    //Destructores

    /** @brief Destructora per defecte
      S'executa automàticament al sortir del bloc on s'ha declarat
      \pre Tenim una frase.
      \post S'ha eliminat l'objecte del tipus Frase
  */
    ~Frase();

    //Modificadores

    /** @brief Actualitza el contingut del parametre implicit frase
      \pre <em>cert.</em>
      \post El parametre implicit frase pren el valor del parametre d'entrada.
  */
    void modificar_frase( const list<string>& frase );


    /** @brief Actualitza el contingut del parametre implicit n_paraules
      \pre <em>cert.</em>
      \post  El parametre implicit n_paraules pren el valor del parametre d'entrada.
  */
    void modificar_n_paraules(int n_paraules);


    //Consultores

    /** @brief Retorna si el string passat per paràmetre està a la frase o no.
      \pre <em>cert</em>
      \post Es retorna true si el string passat per paràmetre es troba a la frase. En cas contrari
      retorna false.
  */
    bool cerca_string(string paraula) const;


  /** @brief Retorna la frase continguda a la classe <em>Frase</em>.
      \pre <em>cert.</em>
      \post Es retorna el parametre implicit frase de <em>Frase</em>.
  */
    list<string> consultar_frase() const;


  /** @brief Retorna el número de paraules de la frase.
      \pre <em>cert.</em>
      \post Es retorna el parametre implicit n_paraules de <em>Frase</em>.
  */
    int consultar_nparaules() const;


};
#endif
