# Nom de l'exécutable
EXEC = testcase.out

# Fichiers source
SRC = TestCase.cc

# Fichiers objets (générés automatiquement à partir des fichiers source)
OBJ = $(SRC:.cc=.o)

# Options de compilation
CXX = g++
CXXFLAGS = -Wall
LDFLAGS = -lncurses -lsfml-graphics -lsfml-window -lsfml-system

# Cible par défaut
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers objets
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets pour éviter des conflits avec des fichiers existants
.PHONY: all clean



