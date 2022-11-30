#include "SDL_render.h"
#include <stdbool.h>

//int FrameUpdate(SDL_Event, SDL_Renderer*, int, SDL_Rect[], SDL_Surface*, SDL_Surface*, SDL_Surface*);
int windowCreation(int, bool,int);
void QuitEvent(SDL_Renderer*, SDL_Window*, int* , int* , int[], int, int);
int Update(SDL_Renderer*, int, SDL_Rect[]);
void OnButtonClick(SDL_Rect[], int, SDL_Renderer*);
//void HoverEffect(SDL_Renderer*, SDL_Point, SDL_Rect[], int);
void PlacePieces(SDL_Renderer *, SDL_Rect[], int[], int[], int[], int, int);
int DragPiece(int, int);
int GetQuadrant(SDL_Rect[], int);
void DrawPiece(SDL_Renderer*, SDL_Rect, SDL_Color, int);
void MouseInteraction(int , SDL_Rect[], int, SDL_Renderer*);