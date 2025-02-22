#include "header.h"
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>

SDL_Surface *screen = NULL, *background = NULL;
TTF_Font *font = NULL;
char playerName[20] = "";
int running = 1;

// Bouton Valider uniquement
Button btnValidate = {{100, 150, 75, 25}, NULL, NULL, 0}; // Taille réduite

// Boîte blanche pour la saisie du nom
SDL_Rect inputBox = {100, 50, 200, 40}; // Position et taille de la boîte
SDL_Color boxColor = {255, 255, 255};   // Blanc
SDL_Color textColor = {0, 0, 0};        // Noir (pour le texte)

// Fonction pour charger une image avec vérification
SDL_Surface* loadImage(const char *filename) {
    SDL_Surface *loadedImage = IMG_Load(filename);
    if (!loadedImage) {
        printf("Erreur: Impossible de charger %s : %s\n", filename, IMG_GetError());
        return NULL;
    }
    SDL_Surface *optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
    SDL_FreeSurface(loadedImage);
    return optimizedImage;
}

// Initialisation de SDL
void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur IMG_Init : %s\n", IMG_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        printf("Erreur TTF_Init : %s\n", TTF_GetError());
        exit(1);
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (!screen) {
        printf("Erreur SDL_SetVideoMode : %s\n", SDL_GetError());
        exit(1);
    }

    font = TTF_OpenFont("Sunflare.ttf", 24);
    if (!font) {
        printf("Erreur TTF_OpenFont : %s\n", TTF_GetError());
        exit(1);
    }

    SDL_EnableUNICODE(1);

    background = loadImage("island.jpg");
    btnValidate.image = loadImage("validate.jpg");
    btnValidate.hoverImage = loadImage("12.jpeg");

    if (!background || !btnValidate.image || !btnValidate.hoverImage) {
        printf("Erreur: Une ou plusieurs images n'ont pas été chargées correctement.\n");
        exit(1);
    }

    // Position du bouton en bas à droite
    btnValidate.rect.x = SCREEN_WIDTH - btnValidate.rect.w - 195;
    btnValidate.rect.y = SCREEN_HEIGHT - btnValidate.rect.h - 20;
}

// Affichage du texte
void renderText(const char *text, int x, int y) {
    if (strlen(text) == 0) return;
    SDL_Surface *message = TTF_RenderText_Blended(font, text, textColor);
    if (!message) {
        printf("Erreur lors du rendu du texte : %s\n", TTF_GetError());
        return;
    }
    SDL_Rect dest = {x, y, 0, 0};
    SDL_BlitSurface(message, NULL, screen, &dest);
    SDL_FreeSurface(message);
}

// Affichage du menu
void renderMenu() {
    SDL_BlitSurface(background, NULL, screen, NULL);

    // Dessiner la boîte blanche
    SDL_Surface *whiteBox = SDL_CreateRGBSurface(SDL_SWSURFACE, inputBox.w, inputBox.h, 32, 0, 0, 0, 0);
    SDL_FillRect(whiteBox, NULL, SDL_MapRGB(screen->format, 255, 255, 255)); // Remplir en blanc
    SDL_BlitSurface(whiteBox, NULL, screen, &inputBox);
    SDL_FreeSurface(whiteBox);

    // Afficher le texte du joueur dans la boîte
    if (strlen(playerName) > 0) {
        SDL_Surface *textSurface = TTF_RenderText_Blended(font, playerName, textColor);
        SDL_Rect textPos = {inputBox.x + 5, inputBox.y + 10}; // Décalage pour éviter les bords
        SDL_BlitSurface(textSurface, NULL, screen, &textPos);
        SDL_FreeSurface(textSurface);
    }

    // Dessiner le bouton Valider
    SDL_Rect destValidate = {
        btnValidate.rect.x,
        btnValidate.rect.y,
        btnValidate.rect.w,
        btnValidate.rect.h
    };

    SDL_Surface *btnValidateImg = btnValidate.hovered ? btnValidate.hoverImage : btnValidate.image;
    SDL_BlitSurface(btnValidateImg, NULL, screen, &destValidate);

    SDL_Flip(screen);
}

// Gestion des entrées utilisateur
void handleInput(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RETURN) {
            printf("Nom du joueur : %s\n", playerName);
        } else if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(playerName) > 0) {
            playerName[strlen(playerName) - 1] = '\0'; // Efface un caractère
        } else {
            char key = event.key.keysym.unicode;
            if (strlen(playerName) < 19 && key >= 32 && key <= 126) { // Limite à 19 caractères
                char tmp[2] = {key, '\0'};
                strncat(playerName, tmp, 1);
            }
        }
    } else if (event.type == SDL_MOUSEMOTION) {
        int x = event.motion.x;
        int y = event.motion.y;

        btnValidate.hovered = (x > btnValidate.rect.x &&
                               x < btnValidate.rect.x + btnValidate.rect.w &&
                               y > btnValidate.rect.y &&
                               y < btnValidate.rect.y + btnValidate.rect.h);
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (btnValidate.hovered) {
            printf("Nom du joueur validé : %s\n", playerName);
        }
    }
}

// Nettoyage des ressources
void cleanUp() {
    if (background) SDL_FreeSurface(background);
    if (btnValidate.image) SDL_FreeSurface(btnValidate.image);
    if (btnValidate.hoverImage) SDL_FreeSurface(btnValidate.hoverImage);
    if (font) TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}
