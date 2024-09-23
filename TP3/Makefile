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
MYMODULES = main
OBJ = $(patsubst %,$(OBJDIR)/%.o,$(MYMODULES))
MYHEADERDEPENDANCIES = $(patsubst %,$(PROJECTINCLUDEDIR)/%.h,$(MYMODULES))

# compilations
$(OBJDIR)/%.o: src/%.c $(MYHEADERDEPENDANCIES)
	gcc -g -Wall ${INCLUDEFLAGS} -c $< -o $@


# édition de liens
build/main: $(OBJ)
	gcc -g  $(OBJ) $(LIBS) -o $@

# nettoyage
clean:
	rm -f obj/*.o build/main

run:
	./build/main
