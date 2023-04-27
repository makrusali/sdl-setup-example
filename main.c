#include <SDL2/SDL.h>
#include <stdio.h>
#include "typedef.h"

i32 main(i32 argc, i8 **argv)
{

    u8 IsRunning = true;

    SDL_Window *Window;
    SDL_Renderer *Renderer;
    SDL_Event Event;

    // init SDL video
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Init SDL Error : %s", SDL_GetError());
        return -1;
    }

    const char *Title = "SDL WINDOW";
    i32 PosX = SDL_WINDOWPOS_CENTERED;
    i32 PosY = SDL_WINDOWPOS_CENTERED;
    i32 WindowWidth = 480;
    i32 WindowHeight = 480;
    i32 WindowFlags = SDL_WINDOW_SHOWN;

    Window = SDL_CreateWindow(Title, PosX, PosY, WindowWidth, WindowHeight, WindowFlags);
    if (Window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Create Window Failed : %s", SDL_GetError());
        return -1;
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Create Renderer Failed : %s", SDL_GetError());
        return -1;
    }

    while (IsRunning)
    {
        while (SDL_PollEvent(&Event))
        {
            switch (Event.type)
            {
            case SDL_QUIT:
                IsRunning = false;
                break;
            case SDL_KEYDOWN:
                // if you want to get key symbol
                // char key = Event.key.keysym.sym;
                break;
            case SDL_KEYUP:
                // if you want to get key symbol
                // char key = Event.key.keysym.sym;
                break;
            default:
                break;
            }
        }

        // if you want to scan key
        // scan event
        // const u8 *state = SDL_GetKeyboardState(NULL);
        // if (state[SDL_SCANCODE_RIGHT])
        // {
        //     GameContext->GameState->Man.X += 10;
        // }
        // else if (state[SDL_SCANCODE_LEFT])
        // {
        //     GameContext->GameState->Man.X -= 10;
        // }
        // else if (state[SDL_SCANCODE_UP])
        // {
        //     GameContext->GameState->Man.Y -= 10;
        // }
        // else if (state[SDL_SCANCODE_DOWN])
        // {
        //     GameContext->GameState->Man.Y += 10;
        // }

        // Render
        // clear render *for clearing screen
        i32 ColorRed = 255;
        i32 ColorGreen = 255;
        i32 ColorBlue = 255;
        i32 Alpha = 255;
        // set render color to white
        SDL_SetRenderDrawColor(Renderer, ColorRed, ColorGreen, ColorBlue, Alpha);
        SDL_RenderClear(Renderer);

        // create a object 
        i32 RectPosX = 0;
        i32 RectPosY = 0;
        i32 RectWidth = 50;
        i32 RectHeight = 50;
        // set render color to red
        SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
        // create rect
        SDL_Rect Rect = {RectPosX, RectPosY, RectWidth, RectHeight};
        // fill rect
        SDL_RenderFillRect(Renderer, &Rect);
        // render present *to render in screen without clearing the screen
        SDL_RenderPresent(Renderer);

        // delay
        SDL_Delay(10);
    }

    // destroy all instance
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}