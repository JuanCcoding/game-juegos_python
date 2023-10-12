#include <SDL.h>
#include <string>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error al inicializar SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Juego Saludo y Vuelo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window || !renderer) {
        SDL_Log("Error al crear la ventana o el renderizador: %s", SDL_GetError());
        return 1;
    }

    std::string playerName;
    bool quit = false;
    SDL_Event event;
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    quit = true;
                } else if (event.key.keysym.sym == SDLK_BACKSPACE && playerName.length() > 0) {
                    playerName.pop_back();
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                } else if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) {
                    playerName += static_cast<char>(event.key.keysym.sym);
                } // Agrega más teclas según sea necesario
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (!playerName.empty()) {
            if (textTexture) {
                SDL_DestroyTexture(textTexture);
                textTexture = nullptr;
            }

            if (textSurface) {
                SDL_FreeSurface(textSurface);
                textSurface = nullptr;
            }

            textSurface = SDL_CreateRGBSurface(0, 800, 100, 32, 0, 0, 0, 0);
            SDL_FillRect(textSurface, NULL, SDL_MapRGB(textSurface->format, 0, 0, 0));

            textTexture = nullptr;
            textSurface = TTF_RenderText_Solid(font, ("¡Hola, " + playerName + "!"), textColor);

            SDL_Rect textRect = { 100, 200, textSurface->w, textSurface->h };
            SDL_BlitSurface(textSurface, NULL, SDL_GetWindowSurface(window), &textRect);

            // Animación de vuelo (desplaza el texto hacia la derecha)
            static int x = 0;
            x += 2;
            if (x > 800) {
                x = 0;
            }
            textRect.x = x;
        }

        SDL_UpdateWindowSurface(window);
    }

    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }

    if (textSurface) {
        SDL_FreeSurface(textSurface);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
