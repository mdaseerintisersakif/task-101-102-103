#include <SDL3/SDL.h>
#include <stdbool.h>
#include <math.h>

// Function to draw a circle
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x;  // Decision parameter

    while (y <= x) {
        // Draw 8 symmetric points
        SDL_RenderPoint(renderer, centerX + x, centerY + y);
        SDL_RenderPoint(renderer, centerX + y, centerY + x);
        SDL_RenderPoint(renderer, centerX - x, centerY + y);
        SDL_RenderPoint(renderer, centerX - y, centerY + x);
        SDL_RenderPoint(renderer, centerX - x, centerY - y);
        SDL_RenderPoint(renderer, centerX - y, centerY - x);
        SDL_RenderPoint(renderer, centerX + x, centerY - y);
        SDL_RenderPoint(renderer, centerX + y, centerY - x);

        y++;

        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;
        }
        else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "SDL3 Circle",
        800,
        600,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // Clear screen (black)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set draw color (white)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Draw circle at center (400,300) with radius 100
        drawCircle(renderer, 400, 300, 100);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}