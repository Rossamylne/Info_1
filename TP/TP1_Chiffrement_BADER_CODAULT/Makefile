# en premier la tâche par défaut : faire l'executable
all: build/main

PROJECTINCLUDEDIR = include/
INCLUDEFLAGS=-I$(PROJECTINCLUDEDIR)
OBJDIR=obj
LIBS=-lm

# puis les toutes les tâches, intermédiaires et finales
# syntaxe
# cible : liste des dépendances
# \tab la commande

#lister ici tous les modules du programme sans extension (par défaut, un fichier main.c et son main.h associé désignés par "main")
MAINMODULES = main actionsParametrees
OBJ = $(patsubst %,$(OBJDIR)/%.o,$(MAINMODULES)) 

MAINHEADERDEPENDANCIES = $(patsubst %,$(PROJECTINCLUDEDIR)/%.h,$(MAINMODULES))

# compilations
$(OBJDIR)/%.o: src/%.c $(MAINHEADERDEPENDANCIES)
	gcc -g -Wall ${INCLUDEFLAGS} -c $< -o $@


# édition de liens
build/main: $(OBJ)
	gcc -g  $(OBJ) $(LIBS) -o $@

# tests unitaires
tests: build/tests

PROJECTINCLUDEDIR = include/
INCLUDEFLAGS=-I$(PROJECTINCLUDEDIR)
OBJDIR=obj
LIBS=-lm

# puis les toutes les tâches, intermédiaires et finales
# syntaxe
# cible : liste des dépendances
# \tab la commande

#lister ici tous les modules du programme sans extension (par défaut, un fichier main.c et son main.h associé désignés par "main")
TESTMODULES = unitTests actionsParametrees
TESTOBJ = $(patsubst %,$(OBJDIR)/%.o,$(TESTMODULES)) 

TESTHEADERDEPENDANCIES = $(patsubst %,$(PROJECTINCLUDEDIR)/%.h,$(TESTMODULES))

# compilations
$(OBJDIR)/%.o: src/%.c $(TESTHEADERDEPENDANCIES)
	gcc -g -Wall ${INCLUDEFLAGS} -c $< -o $@


# édition de liens
build/tests: $(TESTOBJ)
	gcc -g  $(TESTOBJ) $(LIBS) -o $@


# nettoyage
clean:
	rm -f obj/*.o build/main

run:
	./build/main
