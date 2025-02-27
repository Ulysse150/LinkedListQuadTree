
#Partie1
partie1Compile: LeonardiRaphael1.c
	gcc LeonardiRaphael1.c -o p1.o 

partie1Lance : 
	./p1.o

partie1: partie1Compile partie1Lance


#Partie2
partie2Compile: LeonardiRaphael2.c
	gcc LeonardiRaphael2.c -o p2.o 

partie2Lance : 
	./p2.o

partie2: partie2Compile partie2Lance


#Partie2P
partie2PCompile: LeonardiRaphael2P.c
	gcc LeonardiRaphael2P.c -o p2P.o 

partie2PLance : 
	./p2P.o

partie2P: partie2PCompile partie2PLance


#Partie2Z
partie2ZCompile: LeonardiRaphael2Z.c
	gcc LeonardiRaphael2Z.c -o p2Z.o 

partie2ZLance : 
	./p2Z.o

partie2Z: partie2ZCompile partie2ZLance


#Partie3
partie3Compile : Leonardi3.c
	gcc Leonardi3.c -o p3.o

partie3Lance:
	./p3.o

partie3: partie3Compile partie3Lance




#tout compiler et exécuter

allCompile: partie1Compile partie2Compile partie2PCompile partie2ZCompile partie3Compile

allLance: partie1Lance partie2Lance partie2PLance partie2ZLance partie3Lance

all: allCompile allLance

#Les cleans pour enlever les fichiers .o
clean_partie1:
	rm -f p1.o

clean_partie2:
	rm -f p2.o

clean_partie2P:
	rm -f p2P.o

clean_partie2Z:
	rm -f p2Z.o

clean_partie3:
	rm -f p3.o

clean: 
	rm -f *.o
	
	


	