/** @file Cjt_cites.cc
    @brief Còdig de la classe Cjt_cites
*/

#include "Cjt_cites.hh"

  string Cjt_cites::int_to_string(int i){
    //Si l'enter i < 10 retorna directament el caracter associat
    if(i/10 == 0){
      //Crea un string d'un sol caracter.
      string x(1,char('0' + i));
      return x;
    }
    //Si l'enter i>10 aleshores recursivament i aprofitant que la suma d'strings es la concatenacio
    //d'aquests cridem la funcio al quocient i al residu (estem fraccionat l'int en ints < 10)
    else
      return int_to_string(i/10) + int_to_string(i%10);
  }


  string Cjt_cites::calcular_referencia(const list<string>& autor) const{
    string referencia, aux;
    list<string>::const_iterator it1 = autor.begin();

    //De cada string qe forma l'autor agafem el 1er caracter (la inicial)
    while(it1 != autor.end()){
      aux = *it1;
      //Concatenem strings
      referencia = referencia + aux[0];
      ++it1;
    }
    //Calculem el digit de la Ref com ha de ser unic haurem d'anar buscant en el
    // set referencies i anar actualitzant la primera ref tindira i=1 cm a digit associat
    set<string>::const_iterator it2 = referencies.begin();
    int i = 1;
    //Convertim l'int a string per a poder crear la referencia
    aux = referencia + int_to_string(i);
    //Mentre trobem la referencia al set hem d'anar actualitzant la que hem calculat
    while(referencies.find(aux) != referencies.end()){
      ++i;
      aux = referencia + int_to_string(i);
    }
    referencia = aux;
    return referencia;
  }

  Cjt_cites::Cjt_cites(){}


  Cjt_cites::~Cjt_cites(){}


  void Cjt_cites::afegir_cita (const Text& text, int inici, int final){
    //Retorna la comanda d'entrada.
    cout << "afegir cita " << inici << " " << final << endl;

    /*Amb el boolea i l'iterador comprova que:
    1- 1 <= inci <= final <= nombre de frases text
    2- No hi hagi cap cita amb el mateix autor, titol i inici_final de la cita en el map
    El boolea decidira si mostrar error o afegir la cita */

    map<string,Cita>::const_iterator it = cites.begin();
    bool found = false;
    //Si es compleix 1 <= inci <= final <= nombre de frases text mirem si hi ha algun element en el map
    if ((inici > 0) and (inici <= final) and (final <= text.mostrar_contingut().size())){
      //El bucle es per a fer la comprovació en tots els elements del map
      while(it != cites.end()and not found){
        if ((it->second.consultar_autor() == text.mostrar_autor()) and (it->second.consultar_titol() == text.mostrar_titol()) and (it->second.consultar_inici_final().first == inici and it->second.consultar_inici_final().second == final)){
          found = true;
        }
        ++it;
      }
    }
    //Si no es compleix 1 <= inci <= final <= nombre de frases text canviem el bolea a true ja que no compleix les cond per afegir
    //l'element al bucle
    else found = true;

    if (not found){
      //Creem un nou objecte cita i modifiquem tots els camps a partir de la informacio d'entrada
      Cita cita;
      cita.modificar_cita(text.frases(inici, final));
      cita.modificar_titol(text.mostrar_titol());
      cita.modificar_autor(text.mostrar_autor());
      //Calculem la referencia unica
      string referencia = calcular_referencia(text.mostrar_autor());
      cita.modificar_referencia(referencia);
      cita.modificar_inici_final(inici, final);
      //Afegim al parametre implicit un nou element en el map (el map ordena per ref)
      cites.insert(pair<string,Cita>(referencia,cita));
      //Guardem la nova referencia en el set per a assegurar-nos de que sigui unica quan afegim una nova cita
      referencies.insert(referencia);
    }
    else cout << "error" << endl;
  }


  void Cjt_cites::eliminar_cita (const string& ref){
    cout << "eliminar cita " << '"' << ref << '"' << endl;
    if (referencia_valida(ref))
       cites.erase(ref);
    else
    cout << "error" << endl;
  }


  void Cjt_cites::modificar_cita(const Cita& cita, const string& referencia){
    cites[referencia] = cita;
  }


  void Cjt_cites::informacio_cita (const string& ref) const {
    cout << "info cita " << '"' << ref <<'"' << " ?" << endl;
    if(referencia_valida(ref)){
      //Accedim al 2 element del pair del map, que es una Cita, i en consulta l'autor, el titol...
      //i els escriu pel canal de sortida.
      escriure_autor(cites.find(ref)->second.consultar_autor());
      cout << " ";
      escriure_titol(cites.find(ref)->second.consultar_titol());
      cout << endl;
      pair<int,int> inici_final = cites.find(ref)->second.consultar_inici_final();
      cout << inici_final.first << "-" << inici_final.second << endl;
      //El bucle escriu pel canal de sortida les frases de la cita i el seu numero de frase
      for (int i = 0; i < cites.find(ref)->second.consultar_cita().size(); ++i){
        cout << i + inici_final.first << " ";
        escriure_frase(cites.find(ref)->second.consultar_cita()[i].consultar_frase());
      }
    }
    else cout << "error" << endl;
  }


  void Cjt_cites::cites_autor (const list<string>& autor) const {
    cout << "cites autor " << '"';
    escriure_autor(autor);
    cout <<'"' << " ?" << endl;
    //Un bucle que recorre els elements de cites i si l'autor associat coincideix
    //escriu la referencia, les frases i el titol del text associat.
    map<string,Cita>::const_iterator it = cites.begin();
    while(it != cites.end()){
      //Crida la funcio comparar llistes string que compara el autor associat al param implicit
      //i el parametre d'entrada
      if (comparar_llistes_string(it->second.consultar_autor(),autor)){
        //Escriu la referencia (primer element del pair en el map de cites)
        cout << it->first << endl;
        int inici = it->second.consultar_inici_final().first;
        for (int i = 0; i < it->second.consultar_cita().size(); ++i){
          cout << i + inici << " ";
          escriure_frase(it->second.consultar_cita()[i].consultar_frase());
        }
        escriure_titol(it->second.consultar_titol());
        cout << endl;
      }
      ++it;
    }
  }


  void Cjt_cites::cites_text (const Text& text) const {
    cout << "cites ?" << endl;
    map<string,Cita>::const_iterator it = cites.begin();
    //Un bucle que recorre el param. implicit cites i per a cada element mira si
    //la Cita te el mateix autor i titol associats que el Text del param. d'entrada
    //Com el param implicit esta ordenat per referencies (map.first) al reccorrer amb
    //el iterador sortiran ordenats per ref.
    while(it != cites.end()){
      //Comparem amb llistes string els autors i titol de Cita i Text.
      if (comparar_llistes_string(it->second.consultar_autor(),text.mostrar_autor()) and (comparar_llistes_string(it->second.consultar_titol(),text.mostrar_titol()))){
        //Escribim pel canal de sortida la ref
        cout << it->first << endl;
        int inici = it->second.consultar_inici_final().first;
        for (int i = 0; i < it->second.consultar_cita().size(); ++i){
          cout << i + inici << " ";
          escriure_frase(it->second.consultar_cita()[i].consultar_frase());
        }
        escriure_autor(it->second.consultar_autor());
        cout << " ";
        escriure_titol(it->second.consultar_titol());
        cout << endl;
      }
      ++it;
    }
  }


  void Cjt_cites::totes_cites () const {
    cout << "totes cites ?" << endl;
    //Un bulce que recorre el parametre implicit cites (map ordenat per ref)
    map<string,Cita>::const_iterator it = cites.begin();
    while(it != cites.end()){
      //Per a cada element escriu ref, frases, autor i titol
      cout << it->first << endl;
      int inici = it->second.consultar_inici_final().first;
      for (int i = 0; i < it->second.consultar_cita().size(); ++i){
        cout << i + inici << " ";
        escriure_frase(it->second.consultar_cita()[i].consultar_frase());
      }
      escriure_autor(it->second.consultar_autor());
      cout << " ";
      escriure_titol(it->second.consultar_titol());
      cout << endl;
      ++it;
    }
  }


  bool Cjt_cites::referencia_valida(const string& ref) const {
    //La funcio find retorna cites.end() si no troba la ref
    return (cites.find(ref) != cites.end());
  }


  Cita Cjt_cites::consultar_cita(const string& referencia) const {
    return cites.find(referencia)->second;
  }


  void Cjt_cites::cites_associdades(const Text& text) const {
    cout << "Cites Associades:" << endl;
    //Bucle que recorre el parametre implicit cites
    map<string,Cita>::const_iterator it = cites.begin();
    while(it != cites.end()){
      //Si la Cita esta associada el text (autor i titol iguals)
      if (comparar_llistes_string(it->second.consultar_autor(),text.mostrar_autor()) and (comparar_llistes_string(it->second.consultar_titol(),text.mostrar_titol()))){
        //Escriu referencia i frases de la Cita
        cout << it->first << endl;
        int inici = it->second.consultar_inici_final().first;
        for (int i = 0; i < it->second.consultar_cita().size(); ++i){
          cout << i + inici << " ";
          escriure_frase(it->second.consultar_cita()[i].consultar_frase());
        }
      }
      ++it;
    }
  }
