#ifndef MENU_H
#define MENU_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

// Screen dimensions
#define SCREEN_WIDTH 1083
#define SCREEN_HEIGHT 500
#define FONT_PATH "fonts/arial.ttf"

// Button Structure
typedef struct {
    SDL_Rect rect;
    SDL_Surface *image;
    SDL_Surface *hoverImage;
    int hovered;
} Button btnValidate;

// Input Box Structure
typedef struct {
    SDL_Rect rect;
    char text[50]; // Max characters that can be entered
    int active;
} InputBox;

// Global Variables
extern SDL_Surface *screen;
extern SDL_Surface *background;
extern TTF_Font *font;
extern int running;
extern int showScores;
extern char playerName[20];
extern InputBox inputBox;

// Buttons
extern Button btnValidate;
extern Button btnRetour;
extern Button btnQuitter;

// Function Declarations
void initSDL();
void cleanUp();
void handleInput(SDL_Event event);
void renderMenu();
void renderText();
SDL_Surface* loadImage(const char *filename);

#endif
