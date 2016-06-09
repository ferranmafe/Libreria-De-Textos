/** @file Cjt_cites.hh
    @brief Especificació de la classe Cjt_cites
*/


#ifndef _CJT_CITES_HH_
#define _CJT_CITES_HH_

#ifndef NO_DIAGRAM
#include <map>
#include <vector>
#include <set>
using namespace std;
#endif

#include "Cita.hh"
#include "Text.hh"
#include "OP_aux.hh"


/** @class Cjt_cites
    @brief  Representa un conjunt de cites.

    Conté cites associades a diversos textos i/o autors tractats, cada cita té associada una referència (única).
*/

class Cjt_cites {

private:

  /** @brief Map de Cita, ordenat per Referències d'aquestes */
  map<string,Cita> cites;

  /** @brief Set de referenciesja que cada cita té una referencia associada única i no es por repetir.*/
  set<string> referencies;

  /**@brief Transforma un nombre (int) en el mateix nombre com a string
   *
   * \pre Hi ha un integer i >= 0
   * \post Retorna un string assoaciat al integer
  */
  static string int_to_string(int i);


  /**@brief Calcula la ID de la cita.
   *
   * \pre Passem un autor per la entrada
   * \post Retorna un string amb una referència unica en el map.
  */
  string calcular_referencia(const list<string>& autor) const;

public:

  //Constructora
  /** @brief Creadora per defecte

      S'executa automàticament al declarar un conjunt de cites.
      \pre <em>cert</em>
      \post Un Cjt_cites buit.
  */
  Cjt_cites();


  //Destructora
  /** @brief Destructora per defecte

      S'executa automàticament al sortir del bloc on s'ha declarat
      \pre Tenim un Cjt_cites
      \post S'ha eliminat l'objecte del tipus Cjt_cites
  */
  ~Cjt_cites();


  //Modificadors
  /** @brief Afegir un element <em> Cita </em> de Cjt_c

      \pre  Hi ha un text triat vàlid, i dos enters inici i final
      \post Mostra "afegir cita 'inici' 'final'"pel canal de sortida, a més a més:
            -Si 1 <= inci <= final <= nombre de frases text i la Cita triada no hi era en el map,
             s'ha afegit una cita, amb la seva referència(ID), al Cjt_cites.
            -Altrament mostra "error" pel canal de sortida
  */
  void afegir_cita (const Text& text, int inici, int final);


  /** @brief Elimina un element <em> Cita </em> de Cjt_cites

      \pre <em>cert</em>
      \post Mostra 'eliminar cita "ref"' pel canal de sortida els parametres d'entrada no es modifiquen, a més a més:
            -Si ref es una referencia vàlida (cites.find()!= cites.end())
             s'elimina la cita associada del parametre implicit cites.
            -Altrament mostra "error" pel canal de sortida
  */
  void eliminar_cita (const string& ref);


  /** @brief Permet modificar una Cita del parametre implícit

      \pre Hi ha una Cita i la referència associada és vàlida.
      \post El parametre implicit amb la referencia associada ha estat modificat amb cita,
            els parametres d'entrada no es modifiquen.
  */
  void modificar_cita(const Cita& cita, const string &referencia);


  //Consultors
  /** @brief Mostra la informació associada a una cita

      \pre  Cert
      \post Es mostra pel canal de sortida 'info cita "ref" ?' i a més a mes:
            -Si la ref és vàlida mostra pel canal de sortida la informació associada a una cita (autor, titol,
             numero de la frase inicial i numero de la frase final, contingut de la frase o frases que la componen).
            -Altrament escriu pel canal de sortida "error"
            Els parametres d'entrada i implícits no es modifiquen.
  */
  void informacio_cita (const string& ref) const;


  /** @brief Mostra les cites associades a un autor

      \pre Cert
      \post Es mostra pel canal de sortida 'cites autor "autor" ?' i a més a més
            les cites de Cjt_cites associades a l'autor, ordenades per referència.
            Per a cada Cita s'en mostra la seva referencia i el seu contingut
            (numero de frase + frase) i titol del text associat pel canal de sortida.
            Els parametres d'entrada i implícits no es modifiquen.
  */
  void cites_autor (const list<string>& autor) const;


  /** @brief Mostra totes les cites qe pertanyen al text triat

      \pre  Hi ha un Text com a paramete d'entrada
      \post Mostra pel canal de sortida 'cites ?' i totes les Cites del Cjt_cites que
            pertanyen al text triat (per a cada cita se’n mostra la seva referencia,
            el contingut de les frases, autor i titol del text d’on provenen) ordenades per referencia.
            Els parametres d'entrada i implícits no es modifiquen.
  */
  void cites_text(const Text& text) const;


  /** @brief Mostra totes les cites de Cjt_cites

      \pre <em>Cert</em>
      \post Mostra pel canal de sortida 'totes cites ?' i totes les cites del conjunt
            (per a cada cita se'n mostra la seva referencia, el contingut de les frases,
            autor i titol del text d'on provenen), ordenades per referència.
            Els parametres implícits no es modifiquen.
  */
  void totes_cites() const;


  /** @brief Mostra si hi ha una cita amb la referencia en el conjunt

      \pre <em>Cert</em>
      \post un booleà que indica si la referència és vàlida o no.
            Els parametres d'entrada i implícits no es modifiquen.
  */
  bool referencia_valida(const string& ref) const;


  /** @brief Retorna una cita associada a una referència

      \pre La referència és vàlida.
      \post Retorna la Cita que pertany al paràmetre implícit amb la referència associada
            Els parametres d'entrada i implícits no es modifiquen.
  */
  Cita consultar_cita(const string& referencia) const;


  /** @brief Mostra les cites associades a un Text (per cada Cita se'n mostra la )

      \pre El parametre d'entrada es un text
      \post Mostra pel canal de sortida 'Cites associades:' i les cites associades al Text,
            per cada Cita se'n mostra la referencia i el contingut, ordenades per referencia.
            Els parametres d'entrada i implícits no es modifiquen.
  */
  void cites_associdades(const Text& text) const;
};
#endif
