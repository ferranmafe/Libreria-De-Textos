/** @file OP_aux.cc
    @brief Còdig del mòdul funcional OP_aux
*/

#include "OP_aux.hh"

int calcular_n_paraules(const list<string>& frase){
  //Recorrem la llista d'strings i si l'element no es un signe de puntuacio sumem 1 al nombre de paraules
  list<string>::const_iterator it = frase.begin();
  int paraules = 0;
  while(it != frase.end()){
    string aux = *it;
    if ((aux[0] >= 'A' and aux[0] <= 'Z') or (aux[0] >= 'a' and aux[0] <= 'z') or (aux[0] >= '0' and aux[0] <= '9'))
      ++paraules;
    ++it;
  }
  return paraules;
}


list<string> llegir_autor(){
  list<string> autor;
  //El primer element te " al inici per tant les i traiem amb erase
  string paraula;
  cin >> paraula;
  paraula.erase(0,1);
  //No es guarden els elements buits i al treure " podria quedar buit
  if (paraula.size() == 0)
    cin >> paraula;
  //Un bucle mentre no entri l'ultim element (amb " al final) inserim l'element anterior a la llista
  //i llegim un nou element del canal d'entrada
  while(paraula[paraula.size()-1] != '"'){
    autor.insert(autor.end(),paraula);
    cin >> paraula;
  }
  //Extraiem les cometes del final i si no es un element buit l'inserim a la llista
  paraula.erase(paraula.end()-1,paraula.end());
  if (paraula.size() > 0)
    autor.insert(autor.end(),paraula);
  return autor;
}


list<string> llegir_titol(){
  list<string> titol;
  //El primer element te " al inici per tant les i traiem amb erase
  string paraula;
  cin >> paraula;
  paraula.erase(0,1);
  //No es guarden els elements buits i al treure " podria quedar buit
  if (paraula.size() == 0)
    cin >> paraula;
  //Un bucle mentre no entri l'ultim element (amb " al final)
  while(paraula[paraula.size()-1] != '"'){
    //Distingim si entra un signe de puntuacio al final de l'string, en aquell cas el separem i l'inserim com un string apart
    if(not((paraula[paraula.size()-1] >= 'A' and paraula[paraula.size()-1] <= 'Z') or (paraula[paraula.size()-1] >= 'a' and paraula[paraula.size()-1] <= 'z') or (paraula[paraula.size()-1] >= '0' and paraula[paraula.size()-1] <= '9'))){
      //Crea un string de 1 sol caracter
      string caracter(1,paraula[paraula.size()-1]);
      paraula.erase(paraula.end()-1,paraula.end());
      //Mirem si eran nomes un signe de punutacio o hi habia una paraula tambe
      if (paraula.size() > 0){
        titol.insert(titol.end(),paraula);
      }
      //Inserim el signe de punutacio
      titol.insert(titol.end(),caracter);
    }
    //Si no hi havia signe de puntuacio simplement inserim la paraula a la llista
    else
      titol.insert(titol.end(),paraula);
    cin >> paraula;
  }
  //Per a l'ultim element d'entrada eliminem les " i apliquem el mateix tractament que als elements del bucle
  paraula.erase(paraula.end()-1,paraula.end());
  if (paraula.size() > 0){
    if(not((paraula[paraula.size()-1] >= 'A' and paraula[paraula.size()-1] <= 'Z') or (paraula[paraula.size()-1] >= 'a' and paraula[paraula.size()-1] <= 'z') or (paraula[paraula.size()-1] >= '0' and paraula[paraula.size()-1] <= '9'))){
      string caracter(1,paraula[paraula.size()-1]);
      paraula.erase(paraula.end()-1,paraula.end());
      if (paraula.size() > 0){
        titol.insert(titol.end(),paraula);
      }
      titol.insert(titol.end(),caracter);
    }
    else
      titol.insert(titol.end(),paraula);
  }
  return titol;
}


list<string> llegir_frase(string& paraula){
  //Llegir frase conté un string a la entrada ja que llegir frase es cridada per llegir text i el primer element es llegeix a text.
  list<string> frase;
  //Una frase acaba en . ! o ? per aixo el bucle mira que l'ultim caracter de l'string llegit no contingui aquests elements
  while((paraula[paraula.size()-1] != '.') and (paraula[paraula.size()-1] != '?') and (paraula[paraula.size()-1] != '!')){
    //Distingim si entra un signe de puntuacio al final de l'string, en aquell cas el separem i l'inserim com un string apart
    if(not((paraula[paraula.size()-1] >= 'A' and paraula[paraula.size()-1] <= 'Z') or (paraula[paraula.size()-1] >= 'a' and paraula[paraula.size()-1] <= 'z') or (paraula[paraula.size()-1] >= '0' and paraula[paraula.size()-1] <= '9'))){
      //Crea un string de 1 sol caracter
      string caracter(1,paraula[paraula.size()-1]);
      paraula.erase(paraula.end()-1,paraula.end());
      //Mirem si eran nomes un signe de punutacio o hi habia una paraula tambe
      if (paraula.size() > 0){
        frase.insert(frase.end(),paraula);
      }
      //Inserim el signe de punutacio
      frase.insert(frase.end(),caracter);
    }
    //Si no hi havia signe de puntuacio simplement inserim la paraula a la llista
    else
      frase.insert(frase.end(),paraula);
    cin >> paraula;
  }
  //Per a l'ultim element d'entrada tractem el . ! o ? com un signe de puntuacio i l'inserim apart
  string caracter(1,paraula[paraula.size()-1]);
  paraula.erase(paraula.end()-1,paraula.end());
  if (paraula.size() > 0){
    frase.insert(frase.end(),paraula);
  }
  frase.insert(frase.end(),caracter);
  return frase;
}


vector<Frase> llegir_text(){
  //Un text es un vector de Frase on frase es (list<string>frase i n_paraules)
  vector<Frase> text;
  string paraula;
  cin >> paraula;
  //La lectura de text acaba amb ****
  while(paraula != "****"){
    Frase f;
    //El bucle llegeix frases (que acaben en . ! o ? i les insereis en un objecte Frase)
    list<string> frase = llegir_frase(paraula);
    //Al element Frase en calcula en n_paraules de la frase llegida
    f.modificar_n_paraules(calcular_n_paraules(frase));
    //Modifica el contingut de la frase del objecte Frase
    f.modificar_frase(frase);
    //Insereix l'objecte Frase al vector de Frase
    text.push_back(f);
    cin >> paraula;
  }
  return text;
}


void llegir_arbre(Arbre<list<string> >& a,list<string>& expressio){
  //El nostre arbre tindra els caracters de comparacio (& , |) en els nodes i
  //les llistes d'string que s'han de cercar a les fulles. Els caracters de comparacio
  //s'introduiran com a llistes<string> ja que es el tipus de dades necessari en els nodes
  Arbre<list<string> > a1, a2;
  //A cada crida recursiva hi poden haver 2 casos o entra un "(" o un "{"
  //ja que la resta de caracters qe poen entrar es trecten dintre la recursivitat
  //es a dir la expressio s'anira modificant(desfent) fins que quedi l'arbre muntat
  string paraula = *(expressio.begin());
  if ( paraula[0] == '('){
    //Traiem el parentesi
    paraula.erase(0,1);
    //Si l'string llegit es nomes un parentesi elimina l'string de la expressio
    if (paraula.size() == 0){
      expressio.erase(expressio.begin());
    }
    //Sino el modifica
    else {
      *(expressio.begin()) = paraula;
    }
    //Per a cada parentesi hi haura crida recursiva als fills a1 a2 ja que dintre un parentesi
    //hi ha una llista d'strings un caracter de comparacio i una altra llista d'string
    llegir_arbre(a1,expressio);
    //Quan omplim el fill esquerre la seguent informacio en la expressio és la comparacio
    //Pero el fill esquerre podia ser una expressio complexa amb parentesis i aleshores primer
    //amb el while eliminem els ")" que hi pugui haver en l'expressio abans dels caracters de comp.
    while(*(expressio.begin()) != "&" and *(expressio.begin()) != "|"){
      expressio.erase(expressio.begin());
    }
    //Un cop arribats al caracter de comparacio l'inserim en una llista d'string que sera la arrel
    list<string> arrel;
    arrel.insert(arrel.end(),*(expressio.begin()));
    //L'eliminem de la expressio
    expressio.erase(expressio.begin());
    //Fem la crida recursiva per al fill dret.
    llegir_arbre(a2,expressio);
    //Generem el arbre (o subarbre) amb les subexpressions booleanes a les fulles
    //i la operacio de comparacio a la arrel
    a.plantar(arrel,a1,a2);
  }

  //Si llegeix un "{" ens trobem en el cas que es una fulla per tant hem de generar
  //la list<string> de paraules a trobar en el text fins que trobem un '}' o un '}...)'
  else if(paraula[0] == '{'){
    list<string> sequencia;
    //Eliminem el '{'
    paraula.erase(0,1);
    //Si nomes era un '{' l'eliminem de expressio i agafem la primera paraula
    if (paraula.size() == 0){
      expressio.erase(expressio.begin());
      paraula = *expressio.begin();
    }
    //Inserim els strings a la llista mentre no detecti un '}' o ')'
    while(paraula[paraula.size()-1] != '}' and paraula[paraula.size()-1] != ')'){
      sequencia.insert(sequencia.end(),paraula);
      expressio.erase(expressio.begin());
      paraula = *(expressio.begin());
    }
    //Quan el detecti ha d'anar eliminant els parentesis o claudators per a tenir
    //la possible ultima paraula de la sequencia sense caracters que no hi pertanyen
    while ((paraula.size()> 0 ) and (paraula[paraula.size()-1] == '}' or paraula[paraula.size()-1] == ')')){
      paraula.erase(paraula.end()-1,paraula.end());
    }
    //Si la paraula no es buida la insereix a la sequencia que inserirem a la fulla.
    if (paraula.size() > 0 ){
      sequencia.insert(sequencia.end(),paraula);
    }
    //La elimina de la expressio d'entrada
    expressio.erase(expressio.begin());
    //Planta un arbre on el node(fulla) es la sequencia i tes 2 fills buits
    a.plantar(sequencia,a1,a2);
  }
}


void escriure_titol(const list<string>& titol){
  list<string>::const_iterator it = titol.begin();
  bool first = true;
  //El titol s'escriu entre cometes
  cout << '"';
  //Mostra pel canal de sortida els strings de la llista separats per espai entre ells
  //si no son signes de puntuacio
  while (it != titol.end()){
    string paraula = *it;
    if (first){
      cout << *it;
      first = false;
    }
    //Si son signes de puntuacio
    else if (not((paraula[paraula.size()-1] >= 'A' and paraula[paraula.size()-1] <= 'Z') or (paraula[paraula.size()-1] >= 'a' and paraula[paraula.size()-1] <= 'z') or (paraula[paraula.size()-1] >= '0' and paraula[paraula.size()-1] <= '9')))
      cout << *it;
    else
      cout << " " << *it;
    ++it;
  }
  //Cometes del final
  cout << '"';
}


void escriure_autor(const list<string>& autor){
  list<string>::const_iterator it = autor.begin();
  bool first = true;
  //Mostra pel canal de sortida els strings de la llista separats per espais
  while (it != autor.end()){
    if (first){
      cout << *it;
      first = false;
    }
    else
      cout << " " << *it;
    ++it;
  }
}


void escriure_frase(const list<string>& frase){
  list<string>::const_iterator it = frase.begin();
  bool first = true;
  //Mostra els strings de la frase separats per espai si no son signes de puntuacio
  while (it != frase.end()){
    string paraula = *it;
    if (first){
      cout << *it;
      first = false;
    }
    else if (not((paraula[paraula.size()-1] >= 'A' and paraula[paraula.size()-1] <= 'Z') or (paraula[paraula.size()-1] >= 'a' and paraula[paraula.size()-1] <= 'z') or (paraula[paraula.size()-1] >= '0' and paraula[paraula.size()-1] <= '9')))
      cout << *it;
    else
      cout << " " << *it;
    ++it;
  }
  cout << endl;
}


void escriure_expressio(const list<string>& expressio){
  //Funcio d'escriptura de les expressions boleanes i la sequencia de paraules de frases.
  list<string>::const_iterator it = expressio.begin();
  //bolea que decideix si la expressio es una expressio boleana o una sequencia de paraules
  bool expseq = ((*it)[0] == '"');
  if(expseq){
    bool first = true;
    //Normalitza la escriptura per pantalla segons els casos si hi ha cometes, una paraula...
    while(it != expressio.end()){
      string paraula = *it;
      if ( paraula[0] == '"' and paraula.size() == 1){
        cout << *it;
        first = true;
      }
      else if (first or paraula[0] == '"'){
        cout << *it;
        first = false;
      }
      else
        cout << " " << *it;
      ++it;
    }
  }
  //Pel cas d'expresions boleanes, hi ha mes condicionals ja que la expresio pot ser de més maneres
  else{
    //Boolea que mria si l'string anterior cacabab en lletra i per tant ha d'escriure un espai si la
    //seguent tampoc son parentesis o claudators
    bool word = false;
    while(it != expressio.end()){
      string paraula = *it;
      if (paraula[paraula.size() - 1] == '{'){
        cout << paraula;
        word = false;
      }
      else if ((word) and ((paraula[0] >= 'A' and paraula[0] <= 'Z') or (paraula[0] >= 'a' and paraula[0] <= 'z') or (paraula[0] >= '0' and paraula[0] <= '9')))
        cout << " " << paraula;
      else if ((paraula[paraula.size() - 1] >= 'A' and paraula[paraula.size() - 1] <= 'Z') or (paraula[paraula.size() - 1] >= 'a' and paraula[paraula.size() - 1] <= 'z') or (paraula[paraula.size() - 1] >= '0' and paraula[paraula.size() - 1] <= '9')){
        cout << paraula;
        word = true;
      }
      //Entre comandes de pomparacio i expresions hi ha espais al normalitzar la sortida.
      else if (paraula == "&" or paraula == "|")
        cout << " " << paraula << " ";
      else
        cout << paraula;
      ++it;
    }
  }
}


bool comparar_llistes_string(const list<string>& a, const list<string>& b){
  //Mira si els strings qe componen 2 llistes son identics
  list<string>::const_iterator it1 = a.begin();
  list<string>::const_iterator it2 = b.begin();
  //Recorre ambdues llistes
  while (it1 != a.end()) {
    //Si arriba una al end i la altra no, diferent tamany i no son iguals
      if (it2 == b.end()) return false;
      //Si hi ha un string diferent, no son iguals les llistes
      else if (*it1 != *it2) return false;
      //ÇEn l'altre cas (son iguals) mirarem els seguents elements.
      ++it1;
      ++it2;
  }
  //Si surt del bucle vol dir que ha reccoregut tota la llista a
  //si itb no apunta al final les llistes tenen diferen tamany sino son iguals
  if (it2 != b.end()) return false;
  return true;
}


int ordenar_llistes_string(const list<string>& a, const list<string>& b){
  //Ordena les llistes d'string alfabeticament pirmer el 1 element de la llista
  //si es mes petit alfabeticament a que b retorna un 0, si a > b retorna 2 i si
  //tots els elements son iguals retorna 1 (ordena primer pel 1er element si es igual mira el 2n element...)
   list<string>::const_iterator it1 = a.begin();
  list<string>::const_iterator it2 = b.begin();
  while (it1 != a.end() and it2 != b.end()) {
      if (*it2 == *it1){
        ++it1;
        ++it2;
      }
      else if (*it1 < *it2) return 0;
      else return 2;
  }
  return 1;
}


bool cerca_paraula (const string& paraula, const list<string>& llista) {
  //Cerca una paraula (string) en una list<string>
    list<string>::const_iterator it = llista.begin();
    while (it != llista.end()) {
        if (*it == paraula) return true;
        ++it;
    }
    return false;
}
