/** @file Cjt_Textos.cc
    @brief Còdig de la classe Cjt_Textos
*/

#include "Cjt_Textos.hh"

    bool Cjt_Textos::cerca_sequencia_text_a_triar(const Text& text, const list<string>& llista){
        bool trobat = false; //Indica si hem trobat la sequencia o no
        list<string>::const_iterator it = llista.begin();
        //Bucle que itera per a totes les paraules de la llista de paraules consecutives que volem trobar en el text.
        //En el cas de que anem trobant les paraules de la llista anirem iterant sobre aquesta. En cas contrari simplement saltarem
        //al final de la mateixa.
        while (it != llista.end()) {
            bool aux = false; //Indica si hem trobat la paraula concreta a la que apunta l'iterador de la llista dintre del text.
            if (*it == "...") ++it; //Condicional que ens fa saltar a la seguent paraula de la llista (per tal de tractar el cas de punts suspensius en cadenes de paraules no consecutives)
            if (cerca_paraula(*it, text.mostrar_autor())) aux = true; //Busca la paraula a trobar a l'autor
            else if (cerca_paraula(*it, text.mostrar_titol())) aux = true; //Busca la paraula a trobar al títol
            else {
                int i = 0;
                vector<Frase> vectaux = text.mostrar_contingut();
                //Es busca la paraula a trobar al contingut (frase per frase). Si la troba a una frase sortim del bucle
                while (i < vectaux.size() and (not aux)) {
                    if (cerca_paraula(*it, vectaux[i].consultar_frase())) aux = true;
                    ++i;
                }
            }
            if (aux) ++it; //Si hem trobat la paraula de la llista saltem a la seguent
            else if (not aux) it = llista.end(); //Si no hem trobat la paraula saltem al final
             //Si estem al final i hem trobat la ultima paraula, voldrà dir que hem trobat tota la seqüencia. En aquest cas trobat passa a true.
             //Altrament, trobat es mantindrà a false
            if (it == llista.end() and aux) trobat = true;
        }
        return trobat; //Retornem trobat. Si true, hem trobat la llista de strings al text. Si false, no.
    }

    list<Text>::iterator Cjt_Textos::calcular_posicio_text(const Text& text) {
      //Volen un iterador que apunti a quina posicio volen el nou element Text per a que
      // quedi endrecat alfabeticament al inserir-lo en el parametre implicit textos
      list<Text>::iterator it = textos.begin();
      while(it != textos.end()){
        //Anem recorrent el parametre implicit i comparant els autors i titols dels seus Text
        //amb els del parametre d'entrada mentre els d'entrada siguin mes grans avancem
        //Quan siguin mes petits retornem l'iterador
        //Primer s'endreça per autor i si l'autor es igual per titol (els titols i autors alhora no poden ser iguals  per la pre)
        int a = ordenar_llistes_string(it->mostrar_autor(), text.mostrar_autor());
        if (a == 0){
          ++it;
        }
        else if (a == 2){
          return it;
        }
        else{
          int b = ordenar_llistes_string(it->mostrar_titol(), text.mostrar_titol());
          if (b == 2) return it;
          else ++it;
        }
      }
      return it;
    }

    Cjt_Textos::Cjt_Textos(){
      //Constructora de la classe. Per defecte fa que text seleccionat apunti al end, per indicar que no hi ha text seleccionat
      text_seleccionat = textos.end();
    }


    Cjt_Textos::~Cjt_Textos(){}


    void Cjt_Textos::modificar_text( const Text& text ){
        //Canvia el text seleccionat pel text passat per paràmetre.
        *text_seleccionat = text;
    }


    void Cjt_Textos::triar_text( const list<string>& sequencia_text_a_triar ){
      //Retorna per pantalla la mateixa comanda que hem inserit
      cout << "triar text {";
      list<string>::const_iterator it = sequencia_text_a_triar.begin();
      while (sequencia_text_a_triar.end() != it) {
          cout << *it;
          ++it;
          if (sequencia_text_a_triar.end() != it) cout << " ";
      }
      cout << "}" << endl;
      //Inicialitzem l'iterador encarregat de recorrer el conjunt de textos a on farem la cerca
      list<Text>::iterator it2 = textos.begin();
      //Iterador que apunta a l'últim text a on haguem trobat un text amb les paraules a cercar
      list<Text>::iterator it3;
      //Contador que indica el nombre de vegades que trobem els strings a cercar
      int contador = 0;
      bool trobat;//Boleà que indica si hem trobat o no uns strings a un text determinat
      //Bucle que recorre tots els textos del sistema. Itera fins a recorrer tots els textos o fins que trobem
      //2 textos amb les paraules a cercar (moment en que donarem error, no cal buscar més)
      while (it2 != textos.end() and contador < 2) {
          trobat = cerca_sequencia_text_a_triar(*it2, sequencia_text_a_triar); //Busca la sequencia de paraules a un text concret
          if (trobat) {//Condicio que s'activa quan trobem les paraules a cercar al text actual
              ++contador;//Si hem trobat les paraules al text, augmentem el contador i guardem la posició del text actual
              it3 = it2;//A un segon iterador
          }
          ++it2;
      }
      if (contador == 1) {//Si el contador val 1 vol dir que només hi ha un text al sistema que conté la sequencia de paraules
      //que hem cercat. En aquest cas, el text seleccionat pasarà a ser l'emmagatzemat a it3 (l'ultim text trobat).
          text_seleccionat = it3;
	if (text_seleccionat->modificar_taula_frequencies()) { //Condició que indica que comprova si hem de calcular o no la taula
	//de frequencies del text seleccioant
	   text_seleccionat->calcular_taula_frequencies();
	}
      }
      else {//Si no hi ha un unic text al sistema que inclogui les paraules cercades, fem que l'iterador que indica el text
      //seleccionat apunti al end. També imprimirem error per pantalla.
        text_seleccionat = textos.end();
        cout << "error" << endl;
      }
    }


    void Cjt_Textos::afegir_text(){
      //Crea un nou objecte del tipus Text amb les dades que hi ha pel canal d'entrada
      Text text;
      text.modificar_titol(llegir_titol());
      string z;
      cin >> z;
      text.modificar_autor(llegir_autor());
      text.modificar_text(llegir_text());
      //Escriu la comanda de sortida
      cout << "afegir text ";
      escriure_titol(text.mostrar_titol());
      cout << endl;

      //Comprova que no hi hagi cap Text al parametre implicit textos amb
      //el mateix titol i mateix autor alhora
      list<Text>::const_iterator it = textos.begin();
      bool found = false;
      while(it != textos.end()and not found){
        //Comprovem que el text no sigui identic (titol,autor)
        if ((it->mostrar_autor() == text.mostrar_autor()) and (it->mostrar_titol() == text.mostrar_titol())){
          found = true;
        }
        ++it;
      }
      //Si no son identics afegim el text
      if (not found){
        //Calculem la posicio on s'ha d'inserir el text a la llista
        list<Text>::iterator it = calcular_posicio_text(text);
        textos.insert(it, text);

        //Hem de modificar tmb el parametre implicit dades_autors
        //en dades_autors l'autor es la ID i es un string per tant transformem
        //la list<string> autor  en un string
        string autor;
        list<string> a = text.mostrar_autor();
        list<string>::const_iterator it2 = a.begin();
        //Si l'autor es buit el string sera buit
        //Si no es buit anem afegint els strings
        if (it2 != a.end()){
      	  autor = *it2;
      	  ++it2;
      	}
        //Si no es buit anem afegi
        while(it2 != a.end()){
          autor = autor + " " + *it2;
          ++it2;
        }
        //Si l'autor ja tenia textos simplement actualitzem les dades de l'element existent
        if (dades_autors.find(autor) != dades_autors.end()){
          ++dades_autors[autor].ntextos;
          dades_autors[autor].nfrases += text.mostrar_contingut().size();
          int npar = 0;
          for (int i = 0; i < text.mostrar_contingut().size(); ++i){
            npar += text.mostrar_contingut()[i].consultar_nparaules();
          }
          dades_autors[autor].nparaules += npar;
        }
        //Sino creem un nou element en el map que quedara ordenat alfabeticament
        else{
          //Actualitzem les dades
          dades_autors[autor].ntextos = 1;
          dades_autors[autor].nfrases = text.mostrar_contingut().size();
          int npar = 0;
          for (int i = 0; i < text.mostrar_contingut().size(); ++i){
            npar += text.mostrar_contingut()[i].consultar_nparaules();
          }
          dades_autors[autor].nparaules = npar;
        }
      }
      //Si titol i autor eren identics no s'afegeix el text i es mostra error
      else cout << "error" << endl;
    }


    void Cjt_Textos::eliminar_text(){
      cout << "eliminar text" << endl;
      //Si no hi ha cap text triat es mostra error
      if (hiha_text_triat()){
        //Si hi ha text seleccionat hem d'eliminar el autor del parametre implicit dades_autors també
        string autor;
        list<string> a = text_seleccionat->mostrar_autor();
        list<string>::const_iterator it2 = a.begin();
        //Com l'autor en dades_autors es un string hem de transformar la list<string> en string
        //per tant recorrem tots els elements d'autor
        autor = *it2;
        ++it2;
        while(it2 != a.end()){
          //anem concatenant strings
          autor = autor + " " + *it2;
          ++it2;
        }
        //Un cop tenim l'autor podem  accedir a través d'ell al map(es el ID)
        //Si nomes te un text eliminem l'autor del map
        if (dades_autors[autor].ntextos == 1){
          dades_autors.erase(autor);
        }
        //Sino disminuim el ntextos, nfrases i el nparaules
        else{
          --dades_autors[autor].ntextos;
          dades_autors[autor].nfrases -= text_seleccionat->mostrar_contingut().size();
          int npar = 0;
          //Hem de calcular les paraules del text que eliminarem
          for (int i = 0; i < text_seleccionat->mostrar_contingut().size(); ++i){
            npar += text_seleccionat->mostrar_contingut()[i].consultar_nparaules();
          }
          dades_autors[autor].nparaules -= npar;
        }
        //Quan dades_autor ha estat actualitzat podem eliminar el text_seleccionat del
        //parametre implicit amb l'iterador i text_seleccionat ja no ha d'apuntar a res.
        textos.erase(text_seleccionat);
        text_seleccionat = textos.end();
      }
      else cout << "error" << endl;
    }


    void Cjt_Textos::info() const{
    	//Imprimeix per pantalla la informacio del text seleccionat
        cout << "info ?" << endl; //Imprimeix la comanda info
        if (hiha_text_triat()){ //Si hi ha text seleccionat imprimeix autor, titol, nº de frases i nº de paraules
          escriure_autor( text_seleccionat->mostrar_autor() );
          cout << " ";
          escriure_titol( text_seleccionat->mostrar_titol() );
          cout << " ";
          cout << text_seleccionat->nombre_frases();
          cout << " ";
          cout << text_seleccionat->nombre_paraules() << endl;
        }
        else cout << "error" << endl; //Si no n'hi ha imprimeix error
    }


    bool Cjt_Textos::hiha_text_triat() const{
    //Retorna un boleà que val true si hi ha text seleccionat. Si no retorna false (text seleccionat apuntant al end)
      return (text_seleccionat != textos.end());
    }


    Text Cjt_Textos::text_triat() const{
    //Retorna el text que està actualment seleccionat. Hi ha d'haver un text seleccionat per a usar aquesta funció
      return *text_seleccionat;
    }


    void Cjt_Textos::textos_autor( const list<string>& autor ) const{
    	//Imprimeix la comanda per pantalla
        cout << "textos autor " << '"';
        escriure_autor(autor);
        cout << '"' << " ?" <<endl;
        //Bucle que es dedica a fer comparacions entre l'autor a cercar i els dels textos. Si coincideixen, mostra el títol
        //Del text per pantalla
        list<Text>::const_iterator it = textos.begin();
        while(it != textos.end()) {
            if (comparar_llistes_string(autor, it->mostrar_autor())) {
                escriure_titol(it->mostrar_titol());
                cout << endl;
            }
            ++it;
        }
    }


    void Cjt_Textos::tots_textos() const{
        cout << "tots textos ?" << endl; //Imprimeix la comanda
        //Recorre tots els textos i va imprimint titol i autor de cada un d'ells
        list<Text>::const_iterator it = textos.begin();
        while(it != textos.end()) {
            escriure_autor(it->mostrar_autor());
            cout << " ";
            escriure_titol(it->mostrar_titol());
            cout << endl;
            ++it;
        }
    }


    void Cjt_Textos::tots_autors() const{
      cout << "tots autors ?" << endl; //Imprimeix la comanda
      //Recorre tot el map d'autors imprimint els valors associats a cadascún dels autors
        map<string, Autor>::const_iterator it = dades_autors.begin();
        while(it != dades_autors.end()) {
            cout << it->first << " " << it->second.ntextos << " " << it->second.nfrases << " " << it->second.nparaules << endl;
            ++it;
        }
    }


    void Cjt_Textos::contingut() const{
        cout << "contingut ?" << endl;//Imprimeix la comanda
        if(hiha_text_triat()){ //Comprova que hi ha text triat. En cas contrari, mostra error
          vector<Frase> aux = text_seleccionat->mostrar_contingut();
          for (int i = 0; i < aux.size(); ++i) {//Recorre totes les frases del text seleccionat i les imprimeix per pantalla
              cout << i + 1 << " ";
              escriure_frase(aux[i].consultar_frase());
          }
        }
        else cout << "error" << endl;
    }

    void Cjt_Textos::escriure_sequencia_frases(int x, int y) const{
        cout << "frases " << x << " " << y << " ?" << endl;//Imprimeix la comanda
        //Condicional que comprova que hi ha text seleccionat, que x es menor que y i que tant x com y estan dintre del rang de frases del text
        if (hiha_text_triat() and (x <= y) and (x > 0) and (y <= text_seleccionat->mostrar_contingut().size())){
       	  //Crida a la funció frases de text, que ens retorna el rang del text que volem. Posteriorment, anem imprimint per
       	  //Pantalla el número de cada frase del rang a imprimir amb el contingut de la mateixa
          vector<Frase> sequencia = text_seleccionat->frases(x, y);
          for (int i = 0; i < sequencia.size(); ++i) {
              cout << i + x << " ";
              escriure_frase(sequencia[i].consultar_frase());

          }
        }
        else cout << "error" << endl; //Si no es compleix el if imprimim error per pantalla.
    }
