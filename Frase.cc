/** @file Frase.cc
    @brief Còdig de la classe Frase
*/

#include "Frase.hh"


    Frase::Frase(){}


    Frase::~Frase(){}


    void  Frase::modificar_frase( const list<string>& frase ){
        //Canvia el contingut del paràmetre frase al que passem per referència.
        this->frase = frase;
    }
    void Frase::modificar_n_paraules(int n_paraules){
        //Canvia el contingut del paràmetre valor al que passem per referència.
        this->n_paraules = n_paraules;
    }


    bool  Frase::cerca_string(string paraula) const{
        //Recorre la frase buscant la paraula passada per referència. Retornem true si la trobem, false en cas contrari
        list<string>::const_iterator it = frase.begin();
        while (it != frase.end()) {
            if (*it == paraula) return true;
            ++it;
        }
        return false;
    }


    list<string>  Frase::consultar_frase() const{
        //Retorna la llista de strings que formen una frase
        return frase;
    }


    int  Frase::consultar_nparaules() const{
        //Retorna un int que conté el nº de paraules d'una frase
        return n_paraules;
    }
