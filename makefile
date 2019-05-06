#Project: plagrismCatcher
# Project: plagrismCatcher
# # Makefile created by Dev-C++ 4.9.9.2
# # Modified by Jeffrey Liew and Adin Lee

CPP  = g++
RES  = 
OBJ  = hashTab.o main.o $(RES)
LINKOBJ  = hashTab.o main.o $(RES)
BIN  = plagrismCatcher
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS)  
RM = rm -f


all: plagrismCatcher 

clean: 
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o plagrismCatcher $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

hashTab.o: hashTab.cpp
	$(CPP) -c hashTab.cpp -o hashTab.o $(CXXFLAGS)


