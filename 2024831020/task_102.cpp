#include <SDL3/SDL.h>
#include <stdbool.h>
#include <math.h>

// Function to draw a filled circle
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;

            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    int width = 800;
    int height = 600;

    SDL_Window* window = SDL_CreateWindow("Growing Circle", width, height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    bool running = true;
    SDL_Event event;

    int centerX = width / 2;
    int centerY = height / 2;

    int radius = 10;         // initial radius
    int initialRadius = 10;  // reset value

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // Increase radius over time
        radius += 1;

        // Check collision with window boundaries
        if (centerX + radius >= width ||   // right wall
            centerX - radius <= 0 ||       // left wall
            centerY + radius >= height ||  // bottom wall
            centerY - radius <= 0) {       // top wall

            radius = initialRadius; // reset
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw circle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawCircle(renderer, centerX, centerY, radius);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}