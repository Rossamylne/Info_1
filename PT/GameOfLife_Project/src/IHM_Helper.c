#include "IHM_Helper.h"
#include <time.h>


IHM_DataModel_t *dataModelPtr;


void IHM_Setup(IHM_Application_t* application, IHM_DataModel_t* dataModel, IHM_Window_t* mainWindow){
    static IHM_Component_t boutonPlay;
    static IHM_Component_t boutonReset;
    static IHM_Component_t boutonClear;
    static IHM_Component_t textLabelGenerations;

    // Init data Model
    dataModel->clicked = 0;
    dataModel->mouseState = 0;
    dataModel->keyPressed = '\0';
    dataModel->btnResetClicked=0;
    dataModel->btnClearClicked=0;
    dataModel->btnPlayState=0;

    dataModelPtr = dataModel;

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Inits Application puis éléments graphiques
    ///////////////////////////////////////////////
    printf("Init Application\n");
    IHM_Application_init(application);

    ///////////////////////////////////////////////
    // Inits fenetre Principale
    printf("Init fenetre Principale\n");
    IHM_Window_init(mainWindow, 600, 700, 1);
    dataModel->windowPtr = mainWindow;
    dataModelPtr->windowWidth = 600;
    dataModelPtr->windowHeight = 700;
    IHM_Window_setTitle(mainWindow, "Jeu de la vie");
    IHM_Window_setPosition(mainWindow, 0, 10);
    IHM_Window_setLayout(mainWindow, 55, 20);
    mainWindow->onMouseButtonDown = onMainWindowMouseDown;
    mainWindow->onMouseButtonUp = onMainWindowMouseUp;
    mainWindow->onResize = onMainWindowResize;
    mainWindow->onKeyPressed = onMainWindowKeyPressed;
    mainWindow->onMouseMove = onMainWindowMouseMove;
    IHM_Application_addWindow(application, mainWindow);
    IHM_Application_setWindowAsMain(application, mainWindow);

    ///////////////////////////////////////////////
    // Donne le focus a la fenetre principale
    IHM_Window_setFocus(mainWindow);

    //Init boutonPlay
    printf("Init bouton play\n");
    IHM_Component_init(&boutonPlay, mainWindow, BUTTON_T);
    IHM_Component_setBoundaries(&boutonPlay, mainWindow->borderWidth, mainWindow->borderWidth, 50, 50);
    IHM_Button_setImages(boutonPlay.bouton, "images/BtnPlayReleased.bmp", "images/BtnPlayPressed.bmp");
    boutonPlay.onMouseButtonDown = onBoutonPlayMouseDown;
    IHM_Window_addComponent(mainWindow,&boutonPlay, WINDOW_TOP, ZONEALIGN_LEFT);

    //Init bouton reset
    printf("Init bouton reset\n");
    IHM_Component_init(&boutonReset, mainWindow, BUTTON_T);
    IHM_Component_setBoundaries(&boutonReset, mainWindow->borderWidth, mainWindow->borderWidth+55, 50, 50);
    IHM_Button_setImages(boutonReset.bouton, "images/BtnResetReleased.bmp", "images/BtnResetReleased.bmp");
    boutonReset.onMouseButtonDown = onBoutonResetMouseDown;
    IHM_Window_addComponent(mainWindow,&boutonReset, WINDOW_TOP, ZONEALIGN_LEFT);

    //Init bouton clear
    printf("Init bouton clear\n");
    IHM_Component_init(&boutonClear, mainWindow, BUTTON_T);
    IHM_Component_setBoundaries(&boutonClear, mainWindow->borderWidth, mainWindow->borderWidth+110, 50, 50);
    IHM_Button_setImages(boutonClear.bouton, "images/BtnClearReleased.bmp", "images/BtnClearReleased.bmp");
    boutonClear.onMouseButtonDown = onBoutonClearMouseDown;
    IHM_Window_addComponent(mainWindow,&boutonClear, WINDOW_TOP, ZONEALIGN_LEFT);

    //Init label Generations
    IHM_Component_init(&textLabelGenerations, mainWindow, TEXTLABEL_T);
    dataModelPtr->textLabelGenerationsPtr = &textLabelGenerations;
    IHM_Component_setBoundaries(&textLabelGenerations, mainWindow->height-mainWindow->bottomLayoutHeight, mainWindow->borderWidth, -1, -1);
    setStatustext(0,0);
    IHM_Window_addComponent(mainWindow, &textLabelGenerations, WINDOW_BOTTOM, ZONEALIGN_LEFT);

    //////////////////////////////////////////////////////////////////////////////////////////////
}

void onMainWindowMouseDown(IHM_Window_t *window, int x, int y, int bouton)
{
    dataModelPtr->clicked = 1;
    dataModelPtr->mouseState = 1;
    dataModelPtr->btnClicked = bouton;
    dataModelPtr->xClicked = x;
    dataModelPtr->yClicked = y;
    printf("Mouse Down btn=%d - x,y = %d,%d\n", bouton, x, y);
}

void onMainWindowMouseUp(IHM_Window_t *window, int x, int y, int bouton)
{
    dataModelPtr->clicked = 1;
    dataModelPtr->mouseState = 0;
    dataModelPtr->btnClicked = bouton;
    dataModelPtr->xClicked = x;
    dataModelPtr->yClicked = y;
    printf("Mouse Up btn=%d - x,y = %d,%d\n", bouton, x, y);
}

void onMainWindowResize(IHM_Window_t *window, int width, int height)
{
    dataModelPtr->windowWidth = width;
    dataModelPtr->windowHeight = height;
}

void onMainWindowKeyPressed(struct IHM_Window *window, char caractere)
{
    dataModelPtr->keyPressed = caractere;
}

void onMainWindowMouseMove(struct IHM_Window *window, int x, int y)
{
    dataModelPtr->xMouse = x;
    dataModelPtr->yMouse = y;
}

void onBoutonPlayMouseDown(IHM_Component_t *self, int localX, int localY){
    printf("Click bouton Play\n");
    self->bouton->state = ~self->bouton->state;
    dataModelPtr->btnPlayState = self->bouton->state;
}

void onBoutonResetMouseDown(IHM_Component_t *self, int localX, int localY){
    printf("Click bouton Reset\n");
    dataModelPtr->btnResetClicked = 1;
}

void onBoutonClearMouseDown(IHM_Component_t *self, int localX, int localY){
    printf("Click bouton Clear\n");
    dataModelPtr->btnClearClicked = 1;
}

void getWindowSize(int* width, int* height){
    *width = dataModelPtr->windowWidth;
    *height = dataModelPtr->windowHeight;
}

char getKeyPressed()
{
    char keyPressed;
    if (dataModelPtr->keyPressed != '\0')
    {
        keyPressed = dataModelPtr->keyPressed;
        dataModelPtr->keyPressed = '\0';
        return keyPressed;
    }
    else
        return '\0';
}

void getMousePosition(int *x, int *y)
{
    *x = dataModelPtr->xMouse;
    *y = dataModelPtr->yMouse;
}

int getMouseClick(int *x, int *y, int *state)
{
    if (dataModelPtr->clicked)
    {
        // reagir a un click
        dataModelPtr->clicked = 0;
        *x = dataModelPtr->xClicked;
        *y = dataModelPtr->yClicked;
        *state = dataModelPtr->mouseState;
        return dataModelPtr->btnClicked;
    }
    return 0;
}

int getBoutonPlayState(){
    return(dataModelPtr->btnPlayState);
}

int getBoutonResetClicked(){
    if(dataModelPtr->btnResetClicked){
        dataModelPtr->btnResetClicked = 0;
        return 1;
    }
    else return 0;
}

int getBoutonClearClicked(){
 if(dataModelPtr->btnClearClicked){
        dataModelPtr->btnClearClicked = 0;
        return 1;
    }
    else return 0;
}

void dessineRectangle(int x, int y, int h, int l, unsigned long couleur){
    IHM_Window_drawRect(dataModelPtr->windowPtr, x, y, h, l, couleur);
}

void dessineRectanglePlein(int x, int y, int h, int l, unsigned long couleur){
    IHM_Window_drawFillRect(dataModelPtr->windowPtr, x, y, h, l, couleur);
}

void dessineLigne(int x1, int y1, int x2, int y2, unsigned long couleur){
    IHM_Window_drawLine(dataModelPtr->windowPtr, x1, y1, x2, y2, couleur);
}

void setStatustext(int generation, int population){
    char tmpString[50];
    sprintf(tmpString, "Generation %d - Population %d", generation, population);
    IHM_TextLabel_setText(dataModelPtr->textLabelGenerationsPtr->textLabel, tmpString);
}

int timeLapse(double timeStep){
    struct timespec laptime1;
    struct timespec laptime2;
    static double fTime1;
    double fTime2;
    double timeLapse;
    static int restart=1;

    if(restart){
        timespec_get(&laptime1, TIME_UTC);
        fTime1 = ((double)(laptime1.tv_nsec)) / 1000000000 + (double)laptime1.tv_sec;
        restart = 0;
    }

    timespec_get(&laptime2, TIME_UTC);
    fTime2 = ((double)(laptime2.tv_nsec)) / 1000000000 + (double)laptime2.tv_sec;
    timeLapse = fTime2 - fTime1;

    if(timeLapse > timeStep){
        restart =1;
        return 1;
    }
    else return 0;
}