#include "SDL_render.h"

int FrameUpdate(SDL_Event, SDL_Renderer*, int, SDL_Rect[], SDL_Surface*, SDL_Surface*, SDL_Surface*);
int windowCreation();
void QuitEvent(SDL_Renderer*, SDL_Window*);
int InitUpdate(SDL_Renderer*, int, SDL_Rect[]);
int OnButtonClick(SDL_Rect[], int, SDL_Surface*, SDL_Surface*, SDL_Surface*, SDL_Renderer*);
void HoverEffect(SDL_Renderer*, SDL_Point, SDL_Rect[], int );
void PlacePieces(SDL_Renderer*, int, SDL_Rect, SDL_Surface*, SDL_Surface*, SDL_Surface*);