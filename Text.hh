/** @file Text.hh
    @brief Especificació de la classe Text
*/

#ifndef _TEXT_HH_
#define _TEXT_HH_

#ifndef NO_DIAGRAM
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "Arbre.hh"
using namespace std;
#endif

#include "Frase.hh"
#include "OP_aux.hh"

/** @class Text
    @brief  Representa un Text

    Conté un text (conjunt de frases) i el títol i l'autor del text.
*/
class Text {

private:
    /** @brief Llista de strings que conté el títol del text*/
    list<string> titol;

    /** @brief Llista de strings que conté el nom de l'autor del text*/
    list<string> autor;

    /** @brief Vector de <em>Frase</em> amb el contingut del text*/
    vector<Frase> text;

    /** @brief Llista de pairs que conté totes les paraules diferents aparegudes al text i el nº d'aparicions
    de cada una d'elles*/
    list<pair<int, string> > tipus_paraules;

    /** @brief Bolea que indica si el parametre implicit text ha estat modificat*/
    bool text_modificat;


    /** @brief Funcio recursiva auxiliar a frases_expressio() que indica si la frase d'entrada compleix la expressio bool (arbre).
      \pre La entrada es un Arbre que conte una expressio bool tal com s'especifica a (OP_aux::llegir_arbre())
           i la  frase a estudiar
      \post Retorna 0 si la frase no compleix la expressio boleana i 1 altrament.
            Ells parametres implicits no es modifiquen, i el parametre d'entrada frase tampoc.
  */
    bool frases_expressio_i(Arbre<list<string> >& a, const list<string>& frase) const;

public:
    //Constructores

    /** @brief Creadora per defecte
      S'executa automàticament al declarar un text.
      \pre <em>cert</em>
      \post Un Text buit i el parametre implicit text_modifcat = true.
  */
    Text();


    //Destructores

    /** @brief Destructora per defecte
      S'executa automàticament al sortir del bloc on s'ha declarat
      \pre Tenim un Text.
      \post S'ha eliminat l'objecte del tipus Text.
  */
    ~Text();


    //Modificadores

    /** @brief Substitueix la frase continguda a la posició indicada per la passada per paràmetre.
      \pre  0 <= i < frase.size()
      \post La frase del parametre implicit text[i] ha estat modificada per frase.
            Els paramtres d'entrada no es modifiquen.
    */
    void modificar_frase(const Frase& frase, int i);


    /** @brief Modifica el parametre implicit títol de Text
      \pre <em>cert</em>
      \post El parametre implicit titol de Text pren el valor del parametre d'entrada
            Els paramtres d'entrada no es modifiquen.
    */
    void modificar_titol(const list<string>& titol);


     /** @brief Modifica el parametre implicit autor de Text
      \pre <em>cert</em>
      \post El parametre implicit autor de Text pren el valor del parametre d'entrada
            Els paramtres d'entrada no es modifiquen.
    */
    void modificar_autor(const list<string>& autor);


    /** @brief Modifica el parametre implicit text de Text
     \pre <em>cert</em>
     \post El parametre implicit text de Text pren el valor del parametre d'entrada
           Els paramtres d'entrada no es modifiquen.
   */
    void modificar_text(const vector<Frase>& text);


    /** @brief Substitueix totes les aparicions de p1 en el parametre implícit text per p2
      \pre El text no es buit.
      \post A tots els llocs on aparegués la paraula p1 en text aquesta quedarà sustituida per p2.
            Si s'ha modificat alguna posicio delparametre implicit  aleshores text_modificat = true
            Els paramtres d'entrada no es modifiquen.
    */
    void substitueix_paraules(const string& p1, const string& p2);


    /** @brief Calcula la taula de frequencies del text.
      \pre <em>cert</em>.
      \post el paràmetre tipus_paraules passa a contenir la taula de freqüencies associada al text,
      ordenada desde el end al begin de la llista per numero de aparicions (de major a menor), per longitud
      de paraula (de petita a gran) i per ordre alfabètic.
    */
    void calcular_taula_frequencies();



    //Consultores

    /** @brief Retorna el parametre implícit autor de Text
      \pre <em>cert</em>.
      \post Retorna el parametre implícit autor de Text
            Els paramtres implícits no es modifiquen.
    */
    list<string> mostrar_autor() const;


    /** @brief Retorna el parametre implícit text de Text
      \pre <em>cert</em>.
      \post Retorna el parametre implícit text de Text
            Els paramtres implícits no es modifiquen.
    */
    vector<Frase> mostrar_contingut() const;


    /** @brief Retorna el parametre implícit titol de Text
      \pre <em>cert</em>.
      \post Retorna el parametre implícit titol de Text
            Els paramtres implícits no es modifiquen.
    */
    list<string> mostrar_titol() const;


    /** @brief Retorna el nombre de frases del parametre implicit text.
      \pre <em>cert</em>.
      \post Retorna el nombre de frases del text.  nombre_frases() = text.size().
            Els paramtres implícits no es modifiquen.
    */
    int nombre_frases() const;


    /** @brief Retorna el nombre de paraules del parametre implicit text.
      \pre <em>cert</em>.
      \post Retorna el nombre de paraules del text (obviant signes de puntuació)
            text està compost de Frase i per a cadascuna se'n consulta Frase.consultar_nparaules().
            Els paramtres implícits no es modifiquen.
    */
    int nombre_paraules() const;


    /** @brief Indica si la taula de frequencies està actualitzada amb el contingut de text
      \pre <em>cert</em>.
      \post Retorna 1 si text ha estat modificat i 0 si no s'ha modificat. (consulta text_modificat)
            Ja que si s'ha modificat text la taula de frequencies esta desactualitzada
            Els paramtres implícits no es modifiquen.
    */
    bool modificar_taula_frequencies() const;


    /** @brief Imprimeix per pantalla les freqüencies de les paraules del text
      \pre <em>cert</em>
      \post Imprimeix per pantalla les freqüencies de cadascuna de les paraules del text.
    */
    void taula_frequencies();


    /** @brief Retorna el contingut del vector text comprès entre les posicions x - 1 i y - 1.
      \pre Les variables d'entrada compleixen 1 <= x <= y <= text.size().
      \post Retorna un vector amb el contingut de text[i] on i pertany [x - 1, y - 1].
            Els parametres implicits no es modifiquen.
    */
    vector<Frase> frases( int x, int y ) const;


    /** @brief Mostra pel canal de sortida frases de text que compleixen la expressió bool indicada.
      \pre expressio és una expressio booleana valida
      \post Mostra pel canal de sortida les frases que compleixen la expr. bool amb el seu nª de frase al inici.
            Els parametres implicits no es modifiquen, el parametre d'entrada si es modifica.
    */
    void frases_expressio(list<string>& expressio) const;


    /** @brief Mostra pel canal de sortida frases de text que contenen la sequencia de paraules d'entrada (obviant signes de puntuació)
      \pre sequencia_paraules no es buida
      \post Mostra pel canal de sortida frases de text que contenen la sequencia de paraules d'entrada (obviant signes de puntuació) amb el seu nª de frase al inici.
            Els parametres implicits no es modifiquen, el parametre d'entrada si es modifica.
    */
    void frases_sequencia(list<string>& sequencia_paraules) const;
};

#endif
