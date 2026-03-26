#include <SDL3/SDL.h>
#include <math.h>
#include <stdbool.h>

// Draw filled circle
void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int w = -radius; w <= radius; w++) {
        for (int h = -radius; h <= radius; h++) {
            if (w * w + h * h <= radius * radius) {
                SDL_RenderPoint(renderer, cx + w, cy + h);
            }
        }
    }
}

// Collision check
bool isColliding(int x1, int y1, int r1, int x2, int y2, int r2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    return (dx * dx + dy * dy) <= (r1 + r2) * (r1 + r2);
}

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Collision Demo", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    // Circle 1 (auto moving)
    int x1 = 100, y1 = 300;
    int r1 = 30;
    int dx = 3;

    // Circle 2 (controlled)
    int x2 = 400, y2 = 300;
    int r2 = 30;

    SDL_Event event;
    bool running = true;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }

        // Keyboard input (SDL3 FIX)
        const bool* keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_UP])    y2 -= 5;
        if (keys[SDL_SCANCODE_DOWN])  y2 += 5;
        if (keys[SDL_SCANCODE_LEFT])  x2 -= 5;
        if (keys[SDL_SCANCODE_RIGHT]) x2 += 5;

        // Move circle 1 (bounce left-right)
        x1 += dx;
        if (x1 <= r1 || x1 >= 800 - r1) {
            dx = -dx; // bounce
        }

        // Check collision
        bool collision = isColliding(x1, y1, r1, x2, y2, r2);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (collision) {
            // 🔥 COLLISION EFFECT
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // RED
            drawCircle(renderer, x1, y1, r1 + 10); // bigger
            drawCircle(renderer, x2, y2, r2 + 10);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // GREEN
            drawCircle(renderer, x1, y1, r1);
            drawCircle(renderer, x2, y2, r2);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}