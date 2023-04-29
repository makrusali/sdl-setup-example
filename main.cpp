#include <SDL2/SDL.h>
#include <stdio.h>
#include "typedef.h"

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

typedef struct
{
    i32 Width;
    i32 Height;
    i32 X;
    i32 Y;

    SDL_Texture *Texture;
} Player_t;

static Player_t *Player_Create(const i32 Width, const i32 Height)
{
    Player_t *Player = (Player_t *)malloc(sizeof(Player_t));

    Player->X = 0;
    Player->Y = 0;
    Player->Height = Height;
    Player->Width = Width;

    return Player;
}

static void Player_Free(Player_t *Player)
{
    free(Player);
}

static void DrawPlayer(SDL_Renderer *Renderer, const Player_t *Player)
{
    SDL_Rect Rect = {Player->X, Player->Y, Player->Width, Player->Height};
    i32 ColorRed = 255;
    i32 ColorGreen = 0;
    i32 ColorBlue = 0;
    i32 Alpha = 255;
    // set render color to white
    SDL_SetRenderDrawColor(Renderer, ColorRed, ColorGreen, ColorBlue, Alpha);
    SDL_RenderFillRect(Renderer, &Rect);
}

static bool IsTileMapPoint(const u8 *TileMap, i32 TestX, i32 TestY)
{
    const i32 MAX_TILE_COUNT_ROW = 24;
    const i32 MAX_TILE_COUNT_COL = 24;

    bool Result = false;

    i32 TestTileX = TestX / 24;
    i32 TestTileY = TestY / 24;

    // Check bound
    if ((TestTileX >= 0 && TestTileX < MAX_TILE_COUNT_COL) && (TestTileY >= 0 && TestTileY < MAX_TILE_COUNT_ROW))
    {
        // check
        if (TileMap[TestTileX + (TestTileY * 24)] != 0)
        {
            SDL_Log("printf tile x : %d - tile y : %d\n", TestTileX, TestTileY);
            Result = true;
        }
    }

    return Result;
}

// Basic checking Collision between Player and tile map
static bool Player_CheckCollision(const u8 *TileMap, const Player_t *Player, i32 dX, i32 dY)
{
    i32 NewX = Player->X + dX;
    i32 NewY = Player->Y + dY;

    i32 PlayerTileX = NewX + (Player->Width / 2);
    i32 PlayerTileY = NewY + Player->Height;

    // three checking point
    /**
     * a, b, c
     * +----------------+
     * |                |
     * |                |
     * |                |
     * a-------b--------c
     */
    
    // TODO (makrusali) : Debug This Function
    if (IsTileMapPoint(TileMap, PlayerTileX - (Player->Width / 2), PlayerTileY) ||
        IsTileMapPoint(TileMap, PlayerTileX, PlayerTileY) ||
        // TODO (makrusali) : Minus 1 Bug
        IsTileMapPoint(TileMap, PlayerTileX + (Player->Width / 2) - 1, PlayerTileY))
    {
        SDL_Log("collision\n");
        return true;
    }

    return false;
}

static void Player_Move(Player_t *Player, i32 dX, i32 dY)
{
    if (!Player_CheckCollision(TileMap, Player, dX, dY))
    {
        Player->X += dX;
        Player->Y += dY;
    }
}

static void DrawTileMap(SDL_Renderer *Renderer, const u8 *TileMap)
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

    // Load Tile Map Texture
    TileMapTexture = SDL_CreateTextureFromSurface(Renderer, TileMapTextureSurface);
    if (TileMapTexture == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Create Texture Failed : %s\n", SDL_GetError());
        exit(-1);
    }
    SDL_FreeSurface(TileMapTextureSurface);

    // Load Player Texture
    Player_t *Player = Player_Create(24, 24);
    Player->X = 25;
    Player->Y = 25;
    if (Player == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Create Player Failed : %s\n");
        exit(-1);
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
        const u8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_RIGHT])
        {
            Player_Move(Player, 1, 0);
        }
        else if (state[SDL_SCANCODE_LEFT])
        {
            Player_Move(Player, -1, 0);
        }
        else if (state[SDL_SCANCODE_UP])
        {
            Player_Move(Player, 0, -1);
        }
        else if (state[SDL_SCANCODE_DOWN])
        {
            Player_Move(Player, 0, 1);
        }

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
        DrawPlayer(Renderer, Player);

        SDL_RenderPresent(Renderer);

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