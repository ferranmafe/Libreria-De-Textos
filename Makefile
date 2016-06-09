OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: program.o Cjt_Textos.o Cjt_cites.o Text.o Frase.o Cita.o OP_aux.o
	g++ -o program.exe program.o Cjt_Textos.o Cjt_cites.o Text.o Frase.o Cita.o OP_aux.o $(OPCIONS)

OP_aux.o: OP_aux.cc OP_aux.hh
	g++ -c OP_aux.cc $(OPCIONS)

Frase.o:  Frase.cc Frase.hh
	g++ -c Frase.cc $(OPCIONS)

Cita.o:  Cita.cc Cita.hh
	g++ -c Cita.cc $(OPCIONS)

Text.o:  Text.cc Text.hh
	g++ -c Text.cc $(OPCIONS)

Cjt_cites.o:  Cjt_cites.cc Cjt_cites.hh
	g++ -c Cjt_cites.cc $(OPCIONS)

Cjt_Textos.o:  Cjt_Textos.cc Cjt_Textos.hh
	g++ -c Cjt_Textos.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe

practica.tar: Makefile program.cc Cjt_Textos.cc Cjt_Textos.hh Cjt_cites.cc Cjt_cites.hh Text.cc Text.hh Cita.cc Cita.hh Frase.cc Frase.hh OP_aux.cc OP_aux.hh Arbre.hh PRO2Excepcio.hh equip.pdf jp_daniel.martinez.bordes_entrada.txt jp_daniel.martinez.bordes_sortida.txt jp_ferran.martinez.felipe_entrada.txt jp_ferran.martinez.felipe_sortida.txt html.zip
	tar -cvf practica.tar Makefile program.cc Cjt_Textos.cc Cjt_Textos.hh Cjt_cites.cc Cjt_cites.hh Text.cc Text.hh Cita.cc Cita.hh Frase.cc Frase.hh OP_aux.cc OP_aux.hh Arbre.hh PRO2Excepcio.hh equip.pdf jp_daniel.martinez.bordes_entrada.txt jp_daniel.martinez.bordes_sortida.txt jp_ferran.martinez.felipe_entrada.txt jp_ferran.martinez.felipe_sortida.txt html.zip 
