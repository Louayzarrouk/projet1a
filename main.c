#include "header.h"
#include <stdio.h>
#include <string.h>
#include "score.h" 


int main(int argc, char *argv[]) {
    int count=3;
    initSDL();

    SDL_Event event;
    while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        handleInput( event,topScores,scoreCount);
    }

    if (showScores) {
        renderTopScores(screen,background,font,topScores,count); // Afficher les scores
    } else {
        renderMenu(); // Afficher l'écran de saisie
    }

    SDL_Delay(16);
}

    cleanUp();
    return 0;
}


