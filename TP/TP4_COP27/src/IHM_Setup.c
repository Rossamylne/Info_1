#include "IHM_Setup.h"

IHM_DataModel_t *dataModelPtr;


void IHM_Setup(IHM_Application_t* application, IHM_DataModel_t* dataModel, IHM_Window_t* mainWindow){
    // Init data Model
    dataModel->clicked = 0;
    dataModel->keyPressed = '\0';

    dataModelPtr = dataModel;

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Inits Application puis éléments graphiques
    ///////////////////////////////////////////////
    IHM_Application_init(application);

    ///////////////////////////////////////////////
    // Inits fenetre Principale
    IHM_Window_init(mainWindow, 771, 900, 1);
    dataModel->windowPtr = mainWindow;
    dataModelPtr->windowWidth = 771;
    dataModelPtr->windowHeight = 900;
    IHM_Window_setTitle(mainWindow, "TP IHM Train");
    IHM_Window_setPosition(mainWindow, 0, 0);
    IHM_Window_setLayout(mainWindow, 55, 20);
    mainWindow->onClick = onMainWindowClick;
    mainWindow->onResize = onMainWindowResize;
    mainWindow->onKeyPressed = onMainWindowKeyPressed;
    mainWindow->onMouseMove = onMainWindowMouseMove;
    IHM_Application_addWindow(application, mainWindow);
    IHM_Application_setWindowAsMain(application, mainWindow);

    ///////////////////////////////////////////////
    // Donne le focus a la fenetre principale
    IHM_Window_setFocus(mainWindow);

    //////////////////////////////////////////////////////////////////////////////////////////////
}

void onMainWindowClick(IHM_Window_t *window, int x, int y, int bouton)
{
    dataModelPtr->clicked = 1;
    dataModelPtr->btnClicked = bouton;
    dataModelPtr->xClicked = x;
    dataModelPtr->yClicked = y;
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

int getMouseClick(int *x, int *y)
{
    if (dataModelPtr->clicked)
    {
        // reagir a un click
        dataModelPtr->clicked = 0;
        *x = dataModelPtr->xClicked;
        *y = dataModelPtr->yClicked;
        return dataModelPtr->btnClicked;
    }
    return 0;
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