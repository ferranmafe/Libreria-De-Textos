/**
 * @mainpage Gestor de textos i cites

En aquest projecte es construeix un programa modular on, a partir d'un selector de comandes,
es poden tractar fragments de textos associats a diversos autors i extreure'n cites associades.
Algunes de les accions que es poden realitzar són afegir i eliminiar textos, donar informació d'aquests,
crear cites, o cercar un text a partir d'una seqüència de paraules que pertanyen al text.
*/

/** @file program.cc
    @brief Programa principal per al projecte: <em>Gestor de textos i cites</em>.
*/

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
using namespace std;
#endif

#include "Cjt_Textos.hh"
#include "Cjt_cites.hh"
#include "Cita.hh"
#include "Frase.hh"
#include "Text.hh"
#include "OP_aux.hh"

/** @brief Programa principal per al projecte: <em>Gestor de textos i cites</em>.

    El programa principal és un selector de comandes que permet realitzar accions relacionades amb textos i cites.
    La estructura del programa principal és un bucle infinit fins al moment en que pel canal d'entrada entri la paraula
    "sortir", a través de sentencies condicionals succesives es van lleguint paraules i si una seqüència d'aquestes
    coincideix amb una comanda coneguda, es realitza la acció associada a través de la crida a diverses funcions de les
    classes associades Cjt_Textos i Cjt_cites.
*/

void llegir_expressio_frases(list<string>& expressio){
  //Llegeix la expressio de frases (el primer string es llegeix fora)
  string p;
  //entrem l'string a traves d'expressio i primer l'eliminem de la expressio
  //mirem qe no sigui un interrogant nomes com la resta d'elements que llegirem i si no ho es
  //l'inserim
  p = *expressio.begin();
  expressio.erase(expressio.begin());
  //Anem comprovant si es un interrogant a cada lectura
  while(p[p.size() - 1] != '?' ){
    expressio.insert(expressio.end(),p);
    cin >> p;
  }
  //L'ultim element de la expressio podria entrar amb l'interrogant enganxat
  if (p.size() > 1){
    p.erase(p.end()-1,p.end());
    expressio.insert(expressio.end(),p);
  }
}

list<string> llegir_sequencia(){
  //Llegeix la sequencia de triar text per tant en el primer i ultim element eliminem
  //els claudators {} amb erase si els elements son butis despres d'extreure claudators
  //no els afegim a la sequencia
  list<string> sequencia;
  string paraula;
  cin >> paraula;
  paraula.erase(0,1);
  if (paraula.size() <= 0)
    cin >> paraula;
  while(paraula[paraula.size()-1] != '}'){
    sequencia.insert(sequencia.end(),paraula);
    cin >> paraula;
  }
  paraula.erase(paraula.end()-1,paraula.end());
  if (paraula.size() > 0){
    sequencia.insert(sequencia.end(),paraula);
  }
  return sequencia;
}

int string_to_int(string x){
  //Transforma enters positius i negatius que entren en un string 'com a caracters' en int recursivament
  //Simplement anem traient l'element de menys pes (ultim) i sumem el enter que li correspon amb la crida recursiva
  //a la resta de l'string mutliplicat per 10 (mes pes).
  //Si l'enter es negatiu al final canvia el signe de tot i al tornar de la crida recursiva mira el signe d'allo retornat
  int xi = (x[x.size()-1] - '0');
  if (x.size() == 2 and x[0] == '-'){
    return  -1 * xi;
  }
  else if(x.size() > 1){
    x.erase(x.size()-1,x.size());
    int xant =  10 * string_to_int(x);
    if (xant >= 0)
      return  xi + xant;
    else
      return -1 * xi + xant;
  }
  else {
    return xi;
  }
}


int seleccionar_comanda_frases(const string& paraula){
  //La funcio selecciona quina comanda de frases s'executa segons el primer caracter de la expressio lleguida
  if (paraula[0] == '(' or paraula[0] == '{') return 0; //Frases expressio bool
  else if (paraula[0] == '"') return 1; //Frases sequencia
  else if (paraula[0] <= '9' and paraula[0] >= '0') return 2; //Frases x y
  else if (paraula[0] == '-' and (paraula[1] <= '9' and paraula[1] >= '0')) return 2; //Frases x y
  else return 3; //En qualsevol altre cas torna 3 i no selecciona cap comanda en els condicionals
}

int main(){
  string p;
  Cjt_Textos textos;
  Cjt_cites cites;
  cin >> p;
  //Si entrem la comanda sortir finalitza la execucio del programa
  while (p != "sortir"){
    if (p == "afegir"){
      cin >> p;
      if (p == "text"){
        //Afegir text
        textos.afegir_text();
        cout << endl;
        cin >> p;
      }
      if(p == "cita"){
        int x, y;
        cin >> x >> y;
        if (textos.hiha_text_triat())
          //Afegir cita
          cites.afegir_cita(textos.text_triat(),x ,y);
        else cout << "error" << endl;
        cout << endl;
        cin >> p;
      }
    }
    else if (p == "triar"){
      cin >> p;
      if (p == "text"){
        //Triar text
        textos.triar_text(llegir_sequencia());
        cout << endl;
        cin >> p;
      }
    }
    else if (p == "eliminar"){
      cin >> p;
      if (p == "text"){
        //Eliminar text
        textos.eliminar_text();
        cout << endl;
        cin >> p;
      }
      if (p == "cita"){
        string referencia;
        cin >> referencia;
        referencia.erase(0,1);
        referencia.erase(referencia.size()-1,referencia.size());
        //Eliminar cita "ref"
        cites.eliminar_cita(referencia);
        cout << endl;
        cin >> p;
      }
    }
    else if (p == "substitueix"){
      string paraula1, paraula2, intermig;
      cin >> paraula1 >> intermig >> paraula2;
      //Traiem les cometes dels strings
      paraula1.erase(0,1);
      paraula1.erase(paraula1.size()-1,paraula1.size());
      paraula2.erase(0,1);
      paraula2.erase(paraula2.size()-1,paraula2.size());
      cout << "substitueix " << '"' << paraula1 << '"' << " per " << '"' << paraula2 << '"' << endl;
      if (textos.hiha_text_triat()){
        //Substitueix paraules
        Text text = textos.text_triat();
        text.substitueix_paraules(paraula1,paraula2);
        textos.modificar_text(text);
      }
      else cout << "error" << endl;
      cout << endl;
      cin >> p;
    }
    else if (p == "textos"){
      cin >> p;
      if (p == "autor"){
	      list<string> autor;
	      autor = llegir_autor();
	      cin >> p;
	      if (p == "?"){
          //Textos autor
	        textos.textos_autor(autor);
          cout << endl;
          cin >> p;
	      }
      }
    }
    else if (p == "tots"){
      cin >> p;
      if (p == "textos"){
	      cin >> p;
	      if (p == "?"){
          //Tots textos
	        textos.tots_textos();
          cout << endl;
          cin >> p;
	      }
      }
      else if (p == "autors"){
	      cin >> p;
        if (p == "?"){
          //Tots autors
          textos.tots_autors();
          cout << endl;
          cin >> p;
        }
      }
    }
    else if (p == "info"){
      cin >> p;
      if (p == "cita"){
        string referencia;
        cin >> referencia;
        referencia.erase(0,1);
        referencia.erase(referencia.size()-1,referencia.size());
        cin >> p;
        if(p == "?"){
          //Info cita "Ref"
          cites.informacio_cita(referencia);
          cout << endl;
          cin >> p;
        }
      }
      else if (p == "?"){
        //Info text seleccionat
        textos.info();
        if(textos.hiha_text_triat())
          cites.cites_associdades(textos.text_triat());
        cout << endl;
        cin >> p;
      }
    }
    else if (p == "autor"){
      cin >> p;
      if (p == "?"){
        //Autor text seleccionat
        cout << "autor ?" <<endl;
        if(textos.hiha_text_triat()){
          escriure_autor(textos.text_triat().mostrar_autor());
          cout << endl;
        }
        else cout << "error" << endl;
        cout << endl;
        cin >> p;
      }
    }
    else if (p == "contingut"){
      cin >> p;
      if (p == "?"){
        //Contingut ?
        textos.contingut();
        cout << endl;
        cin >> p;
      }
    }
    else if (p == "frases"){
      list<string> expressio;
      cin >> p;
      if (p [0] == '(' or p[0] == '{' or p[0] == '"' or p[0] == '-' or (p[0] >= '0' and p[0] <= '9')){
        expressio.insert(expressio.end(), p);
        llegir_expressio_frases(expressio);
        int comanda;
        if (not expressio.empty())
          comanda = seleccionar_comanda_frases(*expressio.begin());
        else
          comanda = 3;

        if (comanda == 0){
          cout << "frases ";
          escriure_expressio(expressio);
          cout << " ?" << endl;
          //Frases expressio bool
          if (textos.hiha_text_triat())
            textos.text_triat().frases_expressio(expressio);
          else
            cout << "error" << endl;
          cout << endl;
        }
        else if (comanda == 1){
          cout << "frases ";
          escriure_expressio(expressio);
          cout << " ?" << endl;
          //Frases sequencia
          if (textos.hiha_text_triat())
            textos.text_triat().frases_sequencia(expressio);
          else
            cout << "error" << endl;
          cout << endl;
        }
        else if ((comanda == 2) and (expressio.size() >= 2)){
          int x, y;
          x = string_to_int(*(expressio.begin()));
          y = string_to_int(*(++expressio.begin()));
          //Frases x y
          textos.escriure_sequencia_frases(x, y);
          cout << endl;
        }
        cin >> p;
      }
    }
    else if (p == "nombre"){
      cin >> p;
      if (p == "de"){
        cin >> p;
        if (p == "frases"){
          cin >> p;
          if (p == "?"){
            //Nombre de frases
            cout << "nombre de frases ?" << endl;
            if (textos.hiha_text_triat())
              cout << textos.text_triat().nombre_frases() << endl;
            else cout << "error" << endl;
            cout << endl;
            cin >> p;
          }
        }
        else if (p == "paraules"){
          cin >> p;
          if (p == "?"){
            //Nombre de paraules
            cout << "nombre de paraules ?" << endl;
            if (textos.hiha_text_triat())
              cout << textos.text_triat().nombre_paraules() << endl;
            else cout << "error" << endl;
            cout << endl;
            cin >> p;
          }
        }
      }
    }
    else if (p == "taula"){
      cin >> p;
      if (p == "de"){
        cin >> p;
        if (p == "frequencies"){
          cin >> p;
          if (p == "?"){
            //Taula de frequencies
            cout << "taula de frequencies ?" << endl;
            if (textos.hiha_text_triat())
               textos.text_triat().taula_frequencies();
            else
              cout << "error" << endl;
            cout << endl;
            cin >> p;
          }
        }
      }
    }
    else if (p == "cites"){
      cin >> p;
      if(p == "autor"){
        list<string> autor = llegir_autor();
        cin >> p;
        if (p == "?")
        //Cites autor
          cites.cites_autor(autor);
          cout << endl;
          cin >> p;
      }
      else if(p == "?"){
        //Cites text seleccionat ?
        if (textos.hiha_text_triat())
          cites.cites_text(textos.text_triat());
        else {
          cout << "cites ?" << endl;
          cout << "error" << endl;
        }
        cout << endl;
        cin >> p;
      }
    }
    else if (p == "totes"){
      cin >> p;
      if (p == "cites"){
        cin >> p;
        if (p == "?"){
          //Totes cites ?
          cites.totes_cites();
          cout << endl;
          cin >> p;
        }
      }
    }
    else {
      //Si no entra a cap condicional la paraula p no es una comanda valida llegim la seguent
      //Si entra en algun condicional ja llegeix quan es necessari i sino podriem perdre comandes
      cin >> p;
    }
  }
}
