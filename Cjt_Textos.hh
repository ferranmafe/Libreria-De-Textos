/** @file Cjt_Textos.hh
    @brief Especificació de la classe Cjt_Textos
*/

#ifndef _CJT_TEXTOS_HH_
#define _CJT_TEXTOS_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
using namespace std;
#endif

#include "Text.hh"

/** @class Cjt_Textos
    @brief  Representa un conjunt de textos.

    Conté el conjunt de textos introduits al sistema. Cada text te associat un títol i un autor.
*/

class Cjt_Textos {

private:

    /** @brief Struct de Autor, amb diversos paràmetres associats als autors.

      El struct conté el nº de textos, el nº de frases i el nº de paraules escrits per l'autor.

  */
    struct Autor{
        int ntextos; int nparaules; int nfrases;
    };

    /** @brief Llista de <em>Text</em>, ordenats alfabeticament primer per autor i despres per titol

      Cada posició de la llista de <em>Text</em> conté tres paràmetres: el títol del text, el nom de l'autor i el conjunt
      de frases que formen el text.
  */
    list<Text> textos;

    /** @brief Iterador que apunta a la posició del text que hem seleccionat.

      En cas de tenir un text seleccionat, l'iterador estarà en una posició entre el principi i el final de la llista. En cas
      contrari, text_seleccionat apuntarà a textos.end().
  */
    list<Text>::iterator text_seleccionat;

    /** @brief Map de <em>Autor</em>, ordenat pel nom de cada un dels autors.*/
    map <string, Autor> dades_autors;

    /** @brief Indica si una sequencia de strings consecutiva es troba a un text o no.
      \pre El text i la llista han de ser vàlides.
      \post Retorna true si la seqüencia es troba al text. En cas contrari, retorna false.
    */
    bool cerca_sequencia_text_a_triar(const Text& text, const list<string>& llista);


    /** @brief Calcula la posicio per ordre alfabetic d'un Text en el parametre implicit textos
      \pre El Text no te titol i autor identics a cap element de textos
      \post Retorna un iterador que apunta a la posicio on s'ha d'inserir el text per a que estigui ordenat alfabeticament (invariant textos)
    */
    list<Text>::iterator calcular_posicio_text(const Text& text);



public:
    //Constructores

     /** @brief Creadora per defecte.
      S'executa automàticament al declarar un conjunt de textos.
      \pre <em>cert.</em>
      \post Un Cjt_Textos buit, l'iterador text_seleccionat apunta a textos.end()
    */
    Cjt_Textos();


    //Destructores
    /** @brief Destructora per defecte

        S'executa automàticament al sortir del bloc on s'ha declarat
        \pre Tenim una Cjt_Textos
        \post S'ha eliminat l'objecte del tipus Cjt_Textos
    */
    ~Cjt_Textos();


    //Modificadores

    /** @brief Canvia el text seleccionat pel passat per paràmetre.
      \pre text = Text.
      \post El text seleccionat passa a ser el passat per paràmetre.
  */
    void modificar_text( const Text& text );


    /** @brief Selecciona un text entre els emmagatzemats al sistema.
      \pre sequencia_text_a_triar ha de ser una list<string> vàlida.
      \post En cas de que la sequencia que introduïm al la funció sigui única, el text que la contingui passarà a ser el text
      seleccionat, a més d'imprimirse per pantalla la instrucció: text triat {sequencia_text_a_triar}.
      En cas contrari, s'imprimeix "error" per pantalla.
    */
    void triar_text( const list<string>& sequencia_text_a_triar );


    /** @brief Afegeix un text a un conjunt de textos.

      \pre <em>cert.</em>
      \post El text introduit queda afegit al conjunt de textos que ja tenia el sistema.
    */
    void afegir_text();


    /** @brief Elimina el text seleccionat.
      \pre Cert
      \post Escriu "eliminar text" pel canal de sortida i:
      -Si text seleccionat apunta a textos.end mostra error pel canal de sortida
      -Altrament actualitza els parametres implicits textos i dades_autors per a eliminar el text
      i tota la informacio relacionada amb el Text i al final text_seleccionat passa a apuntar a textos.end()

    */
    void eliminar_text();


    //Consultores

    /** @brief Imprimeix per pantalla els paràmetres associats al text.
      \pre cert
      \post S'imprimeix per pantalla la comanda "info ?" i: Si hiha_text_triat es mostra l'autor del text, el títol, el nombre de frases, el nombre de paraules
      i les cites associades. Altrament es mostra error. Els parametres implicits de Cjt_Textos no es modifiquen.
  */
    void info() const;


    /** @brief Indica si hi ha un text seleccionat vàlid o no.
      \pre <em>cert.</em>
      \post Retorna true si hi ha text seleccionat. En cas contrari retorna false. Els parametres implicits de Cjt_Textos no es modifiquen.
    */
    bool hiha_text_triat() const;


    /** @brief Retorna el <em>Text</em> seleccionat.
      \pre Hi ha seleccionat un text vàlid.
      \post Retorna el text seleccionat. Els parametres implicits de Cjt_Textos no es modifiquen.
    */
    Text text_triat() const;


    /** @brief Imprimeix per pantalla els títols dels textos associats a un autor determinat.
      \pre autor = Nom de l'autor a cercar.
      \post S'imprimeix per pantalla la comanda "textos autor", seguida pels títols dels textos associats a l'autor indicat, ordenats de forma alfabètica.
            Els parametres implicits de Cjt_Textos no es modifiquen.
    */
    void textos_autor(const list<string>& autor) const;


    /** @brief Imprimeix per pantalla el títol i l'autor de tots els textos contiguts al sistema.
      \pre <em>cert.</em>
      \post S'imprimeix per pantalla la comanda "textos autor", seguida pel conjunt de títols i autors associats a cada text emmagatzemat al sistema, ordenats
      primer per autor i despres per títol. Els parametres implicits de Cjt_Textos no es modifiquen.
    */
    void tots_textos() const;


    /** @brief Imprimeix per pantalla el conjunt d'autors amb textos vàlids del sistema, amb tot un seguit de paràmetres
        associats a cada autor.
      \pre <em>cert.</em>
      \post S'imprimeix per pantalla la comanda "tots autors", seguida de  tots els autors amb textos en el sistema indicant per a cadascun el
      nombre de textos que hi consten, el nombre total de frases i de paraules del contingut dels seus textos. Els parametres implicits de Cjt_Textos no es modifiquen.
    */
    void tots_autors() const;


    /** @brief Imprimeix per pantalla la sequencia de text entre x i y que s'introdueixi.
      \pre Cert
      \post Si el rang introduit es vàlid( 0 < x <= y <= text_seleccionat->size()), i hiha_text_triat() s'imprimeix per pantalla la comanda "frases x y ?"
      seguida de les frases incloses a la seqüencia. En cas contrari, s'imprimeix la comanda "frases x y ?" seguida de "error". Els parametres implicits de Cjt_Textos no es modifiquen.
    */
    void escriure_sequencia_frases(int x, int y) const;


    /** @brief Imprimeix per pantalla la sequencia de frases que inclou el text seleccionat.
      \pre <em>cert.</em>
      \post S'imprimeix per pantalla la comanda "contingut ?" i: Si hi ha un text seleccionat vàlid les frases del text, numerades.
      En cas contrari, s'imprimeix "error". Els parametres implicits de Cjt_Textos no es modifiquen.
    */
    void contingut() const;
};
#endif
