/** @file Text.cc
    @brief Còdig de la classe Text
*/

#include "Text.hh"

  bool Text::frases_expressio_i(Arbre<list<string> >& a, const list<string>& frase) const{
    //L'arbre conte la expressio booleana creada amb llegir_arbre() i la frase a estudiar
    //a cada crida recursiva s'estudiara la subexpressio booleana(subarbre) fins al cas base
    Arbre<list<string> >a1, a2;
    //Guardem la arrel (operacio & o |)
    list<string> arrel = a.arrel();
    //Generem els fills
    a.fills(a1,a2);
    //Si ambdos son buits es una fulla i estudiarem si la sequencia de paraules de la fulla esta a la frase
    if(a1.es_buit() and a2.es_buit()){
      list<string>::const_iterator it = arrel.begin();
      bool found = true;
      //Mentre trobi la paraula a la frase i la sequencia no hagi arribat al final
      while(it != arrel.end() and found){
        //Busquem la paraula en la list<string> frase
        found = cerca_paraula(*it, frase);
        ++it;
      }
      //Si la sequencia es buida retornem fals
      if (arrel.size() == 0)
        found = false;
      //Retornem si la sequencia esta a la frase o no
      return found;
    }
    //Si no son ambdos buits arrel es un node amb una operacio boleana
    //distingim si es and o or i fem crida recursiva als fills seguint la expressio booleana
    else if (*(arrel.begin()) == "&"){
      return (frases_expressio_i(a1,frase) and (frases_expressio_i(a2,frase)));
    }
    else{
      return (frases_expressio_i(a1,frase) or (frases_expressio_i(a2,frase)));
    }
  }


  Text::Text(){
      //Constructor de la classe. Posa text seleccionat a true, cosa que indica que hem de calcular la taula de frequencies.
      text_modificat = true;
  }


  Text::~Text(){}


  void Text::modificar_frase( const Frase& frase, int i ){
    //Substitueix el paràmetre frase del text actual (la posició ve donada pel parametre i) de la classe Text per la frase que passem per paràmetre
    text[i] = frase;
  }



  void Text::modificar_titol( const list<string>& titol ){
      //Substitueix el paràmetre títol de la classe Text pel que passem per paràmetre
      this->titol = titol;
  }



  void Text::modificar_autor( const list<string>& autor ){
      //Substitueix el paràmetre autor de la classe Text pel que passem per paràmetre
      this->autor = autor;
  }


  void Text::modificar_text(const vector<Frase>& text){
      //Substitueix el paràmetre text de la classe Text pel que passem per paràmetre
      this->text = text;
  }


  void Text::substitueix_paraules(const string& p1, const string& p2){
      if (p1 != p2) { //Condició que comprova que les paraules a substituir no son la mateixa
          text_modificat = true;//Boleà de la classe Text que indica que s'haurà de recalcular la taula de freqüencies
          //Bucle que recorre tot el contingut del text
          for (int i = 0; i < text.size(); ++i) {
              if (text[i].cerca_string(p1)) { //Condició que ens indica si hem trobat la paraula per la que substituirem al text o no
                  list<string> aux = text[i].consultar_frase(); //Auxiliar que conté la frase actual
                  list<string>::iterator it = aux.begin();
                  while (it != aux.end()) { //Bucle que recorre tota la frase actual
                      bool aux2 = true; //Boleà que indica si hem d'incrementar l'iterador o no. S'incrementa sempre,
                      //A excepció de quan la paraula a substituir valgui 0
                      if (*it == p1) { //Condició que comprova si la paraula actual de la frase es la que volem substituir
                          if (p2.size() == 0) {  //Si la paraula nova es buida borrem la paraula de la llista
                              it = aux.erase(it);
                              aux2 = false; //Indiquem que no hem d'augmentar l'iterador en aquesta iteracio del bucle
                          }
                          else *it = p2; //Si la paraula no es buida substituim la paraula vella per la nova
                      }
                      if (aux2) ++it; //Comprova que no haguem esborrat la paraula actual. En cas contrari passem a comprovar
                      //La seguent paraula de la frase actual
                  }
                  text[i].modificar_frase(aux); //Canviem la frase antiga per la nova, modificada.
              }
          }
      }
  }


  void Text::calcular_taula_frequencies() {
      if (text_modificat) tipus_paraules.clear(); //Si hem modificat el contingut del text, esborrem la taula de frequencies anterior
      list<pair<int, string> >::iterator it = tipus_paraules.begin();
      //Recorrem tot el contingut del text (frase a frase)
      for (int i = 0; i < text.size(); ++i) {

          list<string> frase_a_tractar = text[i].consultar_frase(); //Frase actual a tractar
          list<string>::iterator it2 = frase_a_tractar.begin();
          //Recorrem tota la frase paraula per paraula
          while (it2 != frase_a_tractar.end()) {
              string aux = *it2; //Comprobem mitjançant un string auxiliar que la paraula actual de la frase sigui una paraula de veritat (o número) i
              //No un signe de puntuació com una coma o un punt. Si ho és, passem a la seguent sense fer res
              if (not ((aux[0] >= 'A' and aux[0] <= 'Z') or (aux[0] >= 'a' and aux[0] <= 'z') or (aux[0] >= '0' and aux[0] <= '9'))) ++it2;
              else { //Si la paraula actual no es coma o punt, proseguim
                  bool trobat = false; //Boleà que indica si hem arribat a la posició on hauría d'anar la paraula actual a inserir.
                  if (it == tipus_paraules.end()) { //Si arribem al final i no hem trobat a la taula de frequencies la paraula actual
                  //De la frase actual, l'afegim
                      pair<int, string> aux;
                      aux.first = 1;
                      aux.second = *it2;
                      tipus_paraules.insert(it, aux);
                      trobat = true;
                  }
                  else {
                      if (it2->length() < it->second.length()) ++it; //Si la paraula que estem cercant ara es mes petita que la actual
                      //Que estem consultant a la taula de frequencies, passem a la següent
                      else if (it2->length() == it->second.length()) { //Si la paraula que estem cercant es igual a la actual de taula
                      //De frequencies, sumem 1 al nombre d'aparicions de la paraula de la taula de frequencies
                          if (*it2 == it->second) {
                              ++it->first;
                              trobat = true;
                          }
                          //Si la paraula actual que estem cercant es major (alfabeticament) a la actual de la taula de frequencies, voldrà dir que
                          //hem trobat el lloc a on va la paraula. La inserim a la taula de frequencies. En cas contrari, passem a la seguent paraula d
                          //la taula de frequencies
                          else if (*it2 < it->second) ++it;
                          else if (*it2 > it->second) {
                              pair<int, string> aux;
                              aux.first = 1;
                              aux.second = *it2;
                              tipus_paraules.insert(it, aux);
                              trobat = true;
                          }
                      }
                      //Si la longitud de la paraula a cercar es major a la de taula de frequencies actual, la inserim
                      else if (it2->length() > it->second.length()) {
                          pair<int, string> aux;
                          aux.first = 1;
                          aux.second = *it2;
                          tipus_paraules.insert(it, aux);
                          trobat = true;
                      }
                  }
                  if (trobat) { //Si hem trobat una paraula, passem a la seguent paraula a cercar. Tornem a començar a buscar desde
                  //El primer element de la taula de frequencies
                      ++it2;
                      it = tipus_paraules.begin();
                  }
              }
          }
      }
      if (tipus_paraules.begin() != tipus_paraules.end()){ //Condició que comprova que la taula de frequencies no sigui buida
      //En aquest punt la taula està ordenada alfabeticament i per tamany, pero NO per numero de aparicions. Això ho fem en
      //Aquest moment mitjançant un bubble sort.
          //Per ferho necessitarem 2 iteradors, un que vagi una posició mes avançada que l'altre
          it = tipus_paraules.begin();
          list<pair<int, string>>::iterator it3 = tipus_paraules.begin();
          ++it3;
          while (it3 != tipus_paraules.end()) { //Bucle que itera fins a arribar al final de la taula de frequencies
              if (it->first > it3->first) { //Condició que salta si un element es major al seguent
              //En aquest cas fem un swap entre aquest dos elements i reiniciem els iteradors.
                  pair <int, string> aux;
                  aux.first = it3->first;
                  aux.second = it3->second;
                  *it3 = *it;
                  *it = aux;
                  it = tipus_paraules.begin();
                  it3 = tipus_paraules.begin();
                  ++it3;
              }
              //En cas de no haver de fer swap incrementem els iteradors
              else {
                  ++it;
                  ++it3;
              }
          }
      }
      text_modificat = false; //Un cop calculada la taula de frequencies, posem el boleà de la classe que indica que hem de calcular
      //la taula a false, per indicar que la taula ja està actualitzada
  }



  list<string> Text::mostrar_autor() const{
      //Retorna el paràmetre autor de la classe Text.
      return autor;
  }


  vector<Frase> Text::mostrar_contingut() const{
      //Retorna el contingut del text (vector de frases que emmagatzema la totalitat del text).
      return text;
  }


  list<string> Text::mostrar_titol() const{
      //Retorna el paràmetre títol de la classe Text.
      return titol;
  }


  int Text::nombre_frases() const{
      //Retorna el nombre de frases del text
      return text.size();
  }


  int Text::nombre_paraules() const{
      int sumpar = 0; //Contador que conté el nº de paraules totals del text
      for (int i = 0; i < text.size(); ++i) {
          //Recorrem cada frase, i sumem al contador el numero de paraules que cadascuna conté
          sumpar += text[i].consultar_nparaules();
      }
      return sumpar; //Retornem el nombre de paraules del text
  }


  bool Text::modificar_taula_frequencies() const{
      //Funció que retorna un boleà. Aquest boleà valdrà true quan haguem de tornar a calcular la taula de frequencies.
      //en cas contrari retorna false
    return text_modificat;
  }


  void Text::taula_frequencies(){
      //Si hem modificat el text (amb substitueix paraules) recalculem la taula de frequencies
      if (text_modificat) calcular_taula_frequencies();
          if (tipus_paraules.begin() != tipus_paraules.end()) { //Condició que comprova que la taula no es buida
          //Inicialitzem l'iterador al end, ja que el nostre algorisme calcula la taula de darrere a davant.
          list< pair <int, string> >::const_iterator it = tipus_paraules.end();
          --it;
          //imprimim per pantalla línia per línia desde el final al principi.
          while (it != tipus_paraules.begin()) {
              cout << it->second << " " << it->first << endl;
              --it;
          }
          //Tal com està creat el bucle la primera parella no la imprimirà. Cal fer-ho a part.
          cout << it->second << " " << it->first << endl;
      }
  }


  vector<Frase> Text::frases( int x, int y ) const{
      //Vector auxiliar que emmagatzema les frases de la sequencia compresa entre x i y
      vector<Frase> aux;
      for (int i = x - 1; i <= y -1; ++i) {
          //Emmagatzemem tots els elements entre x i y
          aux.push_back(text[i]);
      }
      return aux; //Retornem les frases de la sequencia
  }


  void Text::frases_expressio(list<string>& expressio) const{
    Arbre<list<string> > arbre;
    //Transforma la list<string> expressio en un arbre per a poder fer la crida a la funcio recursiva
    llegir_arbre(arbre,expressio);
    list<string>::iterator it = expressio.begin();
    //Per a totes les frases crida la funcio recursiva i si les frases compleixen la expressio booleana
    //les mostra pel canal de sortida
    for (int i = 0; i < text.size(); ++i){
      //Com a cada crida recursiva l'arbre resultant es buit hem de copiar el arbre del inici cada vegada
      Arbre<list<string> > arbre_aux(arbre);
      if (frases_expressio_i(arbre_aux,text[i].consultar_frase())){
        cout << i + 1 << " ";
        escriure_frase(text[i].consultar_frase());
      }
    }
  }


  void Text::frases_sequencia(list<string>& sequencia_paraules) const{
    //Com sequencia_paraules entra entre '"' s'han d'eliminar
    list<string>::iterator itseq = sequencia_paraules.begin();
    //Traiem les cometes al 1er element
    itseq->erase(0,1);
    //Si nomes contenia les cometes l'eliminem de la sequencia
    if (itseq->size() == 0){
      sequencia_paraules.erase(itseq);
    }
    //Traiem les cometes del ultim element
    itseq = --sequencia_paraules.end();
    itseq->erase(itseq->end()-1,itseq->end());
    //Si nomes tenia les cometes l'eliminem de la sequencia
    if (itseq->size() == 0){
      sequencia_paraules.erase(itseq);
    }

    //Condicional que comprova que la llista introduida no sigui buida
    if (sequencia_paraules.begin() != sequencia_paraules.end()){
        //Bucle que itera frase a frase, per tal de cercar la llista de paraules en cadascúna d'elles.
      for (int i = 0; i < text.size(); ++i) {
          //Auxiliar que conté la frase actual sobre la que treballem
        list<string> frase = text[i].consultar_frase();
        //Iteradors que treballen sobre la frase a on busquem (it1) i sobre la sequencia que estem cercant (it2)
        list<string>::const_iterator it1 = frase.begin();
        list<string>::const_iterator it2 = sequencia_paraules.begin();
        bool trobat = false; //Boleà que indica si hem trobat la sequencia o no
        while (it1 != frase.end() and trobat == false) { //Bucle que itera mentre no arribem al final de la frase o trobem la sequencia
        //Condició que s'assegura de que si introduïm un signe de puntuació permes continui funcionant la funció (simplement l'ignorem)
          if (*it1 == "," or *it1 == ";" or *it1 == ":") ++it1;
          if (*it1 == *it2) {//Si els dos strings que estem mirant son iguals, saltem als 2 seguents
            ++it2;
            ++it1;
          }
          else if (*it1 != *it2 and (it2 == sequencia_paraules.begin())){
              //Si els dos strings que mirem son diferents, i estem al primer element de la sequencia, passem al seguent element de la frase.
            ++it1;
          }
          else{
              //Si els elements son diferents i no estem al principi de la sequencia a cercar, tornem al principi.
              //Això es fa aixi perque cada cop que no trobem la sequencia de paraules haurem de tornar a començar desde el principi.
              //Si distingim entre aquest cas i l'anterior es per tal d'evitar saltarnos la paraula immediatament posterior a no trobar
              //una igualtat.
            it2 = sequencia_paraules.begin();
          }

          if (it2 == sequencia_paraules.end()) trobat = true;
          //Si la sequencia a cercar arriba al final, voldrà dir que l'hem trobat al text
        }
        if (trobat) {
            //Si hem trobat la sequencia al text, la imprimim per pantalla.
          cout << i + 1 << " ";
          escriure_frase(text[i].consultar_frase());
        }
      }
    }
  }
