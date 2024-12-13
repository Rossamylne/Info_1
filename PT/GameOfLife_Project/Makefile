
all: build/main

PROJECTINCLUDEDIR = include/
IHMINCLUDEDIR = GEII_IHM/include/
INCLUDEFLAGS=-I$(PROJECTINCLUDEDIR) -I$(IHMINCLUDEDIR) -I/usr/include/freetype2/
OBJDIR=obj
LIBS=-lSDL2 -lfreetype -lm


MAINMODULES = main IHM_Helper jeu fonctionsGraphiques
IHMMODULES = IHM_Application IHM_Window IHM_GridPanel IHM_DrawPanel IHM_Button IHM_TextLabel  IHM_Component  SDL_ttf
OBJ = $(patsubst %,$(OBJDIR)/%.o,$(MAINMODULES)) $(patsubst %,$(OBJDIR)/%.o,$(IHMMODULES))
MAINHEADERDEPENDANCIES = $(patsubst %,$(PROJECTINCLUDEDIR)/%.h,$(MAINMODULES))
IHMHEADERDEPENDANCIES = $(patsubst %,$(IHMINCLUDEDIR)/%.h,$(IHMMODULES))

$(OBJDIR)/%.o: src/%.c $(MAINHEADERDEPENDANCIES)
	gcc -g -Wall ${INCLUDEFLAGS} -c $< -o $@
	
$(OBJDIR)/%.o: GEII_IHM/src/%.c $(IHMHEADERDEPENDANCIES)
	gcc -g -Wall ${INCLUDEFLAGS} -c $< -o $@


build/main: $(OBJ)
	gcc -g  $(OBJ) $(LIBS) -o $@

tests: build/tests


TESTMODULES = tests jeu
TESTOBJ = $(patsubst %,$(OBJDIR)/%.o,$(TESTMODULES)) 

TESTHEADERDEPENDANCIES = $(patsubst %,$(PROJECTINCLUDEDIR)/%.h,$(TESTMODULES))


$(OBJDIR)/%.o: src/%.c $(TESTHEADERDEPENDANCIES)
	gcc -g -Wall ${INCLUDEFLAGS} -c $< -o $@


build/tests: $(TESTOBJ)
	gcc -g  $(TESTOBJ) $(LIBS) -o $@


clean:
	rm -f obj/*.o build/main

run:
	./build/main
