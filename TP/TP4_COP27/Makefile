# en premier la tâche par défaut : faire l'executable
all: build/main

PROJECTINCLUDEDIR = include/
IHMINCLUDEDIR = GEII_IHM/include/
INCLUDEFLAGS=-I$(PROJECTINCLUDEDIR) -I$(IHMINCLUDEDIR) -I/usr/include/freetype2/
OBJDIR=obj
LIBS=-lSDL2 -lfreetype -lm

# puis les toutes les tâches, intermédiaires et finales
# syntaxe
# cible : liste des dépendances
# \tab la commande

#lister ici tous les modules du programme sans extension (par défaut, un fichier main.c et son main.h associé désignés par "main")
MAINMODULES = main actionsParametrees IHM_Setup
IHMMODULES = IHM_Application IHM_Window IHM_GridPanel IHM_DrawPanel IHM_Button IHM_TextLabel  IHM_Component  SDL_ttf
OBJ = $(patsubst %,$(OBJDIR)/%.o,$(MAINMODULES)) $(patsubst %,$(OBJDIR)/%.o,$(IHMMODULES))
MAINHEADERDEPENDANCIES = $(patsubst %,$(PROJECTINCLUDEDIR)/%.h,$(MAINMODULES))
IHMHEADERDEPENDANCIES = $(patsubst %,$(IHMINCLUDEDIR)/%.h,$(IHMMODULES))

# compilations
$(OBJDIR)/%.o: src/%.c $(MAINHEADERDEPENDANCIES)
	gcc -g -Wall ${INCLUDEFLAGS} -c $< -o $@
	
$(OBJDIR)/%.o: GEII_IHM/src/%.c $(IHMHEADERDEPENDANCIES)
	gcc -g -Wall ${INCLUDEFLAGS} -c $< -o $@


# édition de liens
build/main: $(OBJ)
	gcc -g  $(OBJ) $(LIBS) -o $@

# tests unitaires
tests: build/tests

# puis les toutes les tâches, intermédiaires et finales
# syntaxe
# cible : liste des dépendances
# \tab la commande

#lister ici tous les modules du programme sans extension (par défaut, un fichier main.c et son main.h associé désignés par "main")
TESTMODULES = unitTests
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
