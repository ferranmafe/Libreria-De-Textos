/** @file OP_aux.hh
    @brief Especificació del mòdul funcional OP_aux
*/

#ifndef _OP_AUX_HH_
#define _OP_AUX_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;
#endif

#include "Frase.hh"
#include "Arbre.hh"

  /** @brief Calcula el nombre de paraules d'una frase
    \pre  Cert
    \post Retorna un enter amb el nombre de paraules (obviant signes de puntuació)
          d'una frase, el paràmetre d'entrada no es modifica
  */
  int calcular_n_paraules(const list<string>& frase);


  /** @brief Llegeix un autor pel canal d'entrada
    \pre Hi ha un autor = "autor" pel canal d'entrada
    \post Retorna una llista d'string amb els strings que formen l'autor sense '"'
  */
  list<string> llegir_autor();


  /** @brief Llegeix un titol pel canal d'entrada
    \pre Hi ha un titol = "titol" pel canal d'entrada
    \post Retorna una llista d'string amb els strings que formen el titol sense '"'
  */
  list<string> llegir_titol();


  /** @brief Llegeix una frase pel canal d'entrada
    \pre Hi ha una sequencia d'strings cacbada en '.' pel canal d'entrada i "paraula"
         és la primera lectura d'aquesta sequencia la qual permet cridar a la funció
    \post Retorna una llista d'string amb els strings que formen la frase amb els signes de
          puntuació separats en una posicio de la llista seguent a la paraula que les precedeix
  */
  list<string> llegir_frase(string& paraula);


  /** @brief Llegeix el contingut d'un Text pel canal d'entrada
    \pre  Hi ha una sequencia de frases acabada en '****' pel canal d'entrada
    \post Retorna un vector de Frase on Frase conté el contingut de cada frase i el nombre de
          paraules d'aquesta, i el vector conte les frases llegides ordenades.
  */
  vector<Frase> llegir_text();


  /** @brief Crea un arbre de llistres d'string a partir d'una expressio booleana
    \pre  Hi ha un arbre buit a la entrada i una expressio booleana.
    \post Retorna un arbre (que representa la expressio bool d'entrada) amb operacions
          de comparacio als nodes i llistes d'string a trobar en una frase a les fulles
          La expressio a la sortida haurà estat modificada i pot ser buida.
  */
  void llegir_arbre(Arbre<list<string> >& a, list<string>& expressio);


  /** @brief Mostra el contingut d'un titol (list<string>) pel canal de sortida
    \pre  Hi ha un list<string> titol com a paramete d'entrada
    \post Mostra pel canal de sortida el titol entre cometes '"' i amb espais entre strings
          si no son signes de puntuació
  */
  void escriure_titol(const list<string>& titol);


  /** @brief Mostra el contingut d'un autor (list<string>) pel canal de sortida
    \pre  Hi ha un list<string> autor com a paramete d'entrada
    \post Mostra pel canal de sortida l'autor amb espais entre els strings que el formen
  */
  void escriure_autor(const list<string>& autor);


  /** @brief Mostra el contingut d'una frase (list<string>) pel canal de sortida
    \pre  Hi ha un list<string> frase com a paramete d'entrada
    \post Mostra pel canal de sortida la frase amb espais entre stringssi no son
          signes de puntuació i despres de mostrar *frases.end() hi ha un salt de linia.
  */
  void escriure_frase(const list<string>& frase);


  /** @brief Mostra el contingut d'una expressio booleana o sequencia de paraules pel canal de sortida
    \pre  Hi ha un list<string> expressio com a paramete d'entrada
    \post Mostra pel canal de sortida el contingut de la expressio normalitzant aquesta sortida
          (espais entre paraules i signes de puntuació) depenent de si és una exp bool o una sequencia.

  */
  void escriure_expressio(const list<string>& expressio);


  /** @brief Retorna un enter associat a la ordenacio alfbetica d'una list<string>
    \pre  Hi ha 2 list<string> a i b com a paramete d'entrada
    \post Retorna 0 si a < b , retorna 1 si a = b, retorna 2 si a > b alfabeticament,
          es a dir compara els strings un a un i mira la ordenacio d'aquests alfabeticament
  */
  int ordenar_llistes_string(const list<string>& a, const list<string>& b);


  /** @brief Compara dues list<string> alfabeticament
    \pre  Hi ha 2 list<string> a i b com a paramete d'entrada
    \post Retorna 0 si a != b per a algun string que els compont i
          retorna 1 si a == b per a tots els strings que els componen (i per tant tenen el
          mateix tamany ambdues llistes).
  */
  bool comparar_llistes_string(const list<string>& a, const list<string>& b);


  /** @brief Busca un string dins una list<string>
    \pre  Hi ha un string i una list<string>com a parametes d'entrada
    \post Retorna 0 si la paraula no està a la llista,
          retorna 1 si la paraula està a la llista.
  */
bool cerca_paraula (const string& paraula, const list<string>& llista);

#endif
