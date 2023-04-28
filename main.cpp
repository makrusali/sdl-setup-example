#include <SDL2/SDL.h>
#include <stdio.h>
#include "typedef.h"

typedef struct
{
    f16 X;
    f16 Y;
} Vec2_t;

typedef struct
{
    char *Name;
    int Health;
    int Damage;
    Vec2_t Vec;
} Player_t;

#define WINDOW_WIDTH 576
#define WINDOW_HEIGHT 576

const u8 TileMap[24 * 24] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
    1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 3, 2, 4, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

static SDL_Surface *TileMapTextureSurface;
static SDL_Texture *TileMapTexture;

void DrawTileMap(SDL_Renderer *Renderer, const u8 *TileMap)
{
    SDL_Rect SourceRectangle = {0, 0, 24, 24};
    SDL_Rect DestinationRect = {0, 0, 24, 24};

    for (i16 i = 0; i < 24 * 24; i++)
    {
        i16 X = i % 24;
        i16 Y = i / 24;

        // SDL_Log("Draw Tile Map in X : %d, Y : %d\n", X, Y);

        switch (TileMap[X + (Y * 24)])
        {
        case 0:
            continue;
            break;
        case 1:
            SourceRectangle.x = 24;
            SourceRectangle.y = 0;
            break;
        case 2:
            SourceRectangle.x = 48;
            SourceRectangle.y = 0;
            break;
        case 3:
            SourceRectangle.x = 0;
            SourceRectangle.y = 24;
            break;
        case 4:
            SourceRectangle.x = 24;
            SourceRectangle.y = 24;
            break;
         case 5:
            SourceRectangle.x = 48;
            SourceRectangle.y = 24;
            break;
        default:
            break;
        }

        DestinationRect.x = X * 24;
        DestinationRect.y = Y * 24;

        if (SDL_RenderCopy(Renderer, TileMapTexture, &SourceRectangle, &DestinationRect) != 0)
        {
            printf("Render Result : %s\n", SDL_GetError());
        }
    }

    SDL_RenderPresent(Renderer);
}

i32 main(i32 argc, i8 **argv)
{
    bool IsRunning = true;

    SDL_Window *Window;
    SDL_Renderer *Renderer;
    SDL_Event Event;

    // init SDL video
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Init SDL Error : %s\n", SDL_GetError());
        exit(-1);
    }

    const char *Title = "SDL WINDOW";
    i32 PosX = SDL_WINDOWPOS_CENTERED;
    i32 PosY = SDL_WINDOWPOS_CENTERED;
    i32 WindowFlags = SDL_WINDOW_SHOWN;

    Window = SDL_CreateWindow(Title, PosX, PosY, WINDOW_WIDTH, WINDOW_HEIGHT, WindowFlags);
    if (Window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Create Window Failed : %s\n", SDL_GetError());
        exit(-1);
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Create Renderer Failed : %s\n", SDL_GetError());
        exit(-1);
    }

    // init texture
    TileMapTextureSurface = SDL_LoadBMP("./textures/number_tilemap.bmp");
    if (TileMapTextureSurface == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Load Texture in %s Failed : %s\n", "./textures/number_tilemap.bmp", SDL_GetError());
        exit(-1);
    }

    TileMapTexture = SDL_CreateTextureFromSurface(Renderer, TileMapTextureSurface);
    if (TileMapTexture == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Create Texture Failed : %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_FreeSurface(TileMapTextureSurface);

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

        DrawTileMap(Renderer, TileMap);

        // delay
        SDL_Delay(10);
    }

    SDL_Delay(500);

    // destroy all instance
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}