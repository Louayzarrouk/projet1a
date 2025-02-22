#include "header.h"
#define MAX_INPUT_LENGTH 100

InputBox inputBox;  // Déclaration de inputBox

int main(int argc, char *argv[]) {
    // Initialisation de SDL et des ressources
    initSDL();

    SDL_Event event;
    char inputText[MAX_INPUT_LENGTH]; // Déclaration correcte
    memset(inputText, 0, sizeof(inputText)); // Initialisation pour éviter les erreurs mémoire

    int textLength = 0;
    int running = 1;  // Ajout de l'initialisation

    // Boucle principale du programme
    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } 
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && textLength > 0) {
                    // Suppression du dernier caractère
                    inputText[--textLength] = '\0';
                } 
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    // Validation de l'entrée
                    running = 0;
                } 
                else if (event.key.keysym.sym >= 32 && event.key.keysym.sym < 127) {
                    // Vérification de la longueur avant d'ajouter un caractère
                    if (textLength < MAX_INPUT_LENGTH - 1) {
                        inputText[textLength++] = (char) event.key.keysym.sym;
                        inputText[textLength] = '\0'; // Assurer la terminaison correcte
                    }
                }
            }
        }

        // Rendu du menu
        renderMenu();
        renderText(inputText); // Affichage du texte saisi
    }

    // Nettoyage des ressources avant de quitter
    cleanUp();
    return 0;
}
