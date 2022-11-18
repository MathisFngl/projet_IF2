#include "SDL_render.h"
#include <stdbool.h>

int FrameUpdate(SDL_Event, SDL_Renderer*, int, SDL_Rect[], SDL_Surface*, SDL_Surface*, SDL_Surface*);
int windowCreation();
void QuitEvent(SDL_Renderer*, SDL_Window*);
int Update(SDL_Renderer*, int, SDL_Rect[]);
void OnButtonClick(SDL_Rect[], int, SDL_Surface*, SDL_Surface*, SDL_Surface*, SDL_Renderer*);
void HoverEffect(SDL_Renderer*, SDL_Point, SDL_Rect[], int );
void PlacePieces(SDL_Renderer*, int, SDL_Rect, SDL_Texture*);
void LoadTextures(SDL_Surface*, SDL_Surface*, SDL_Surface*);
int DragPiece(int, int);
int GetQuadrant(SDL_Rect[], int);
void MouseInteraction(int , SDL_Rect[], int , SDL_Surface*, SDL_Surface*, SDL_Surface*, SDL_Renderer*);