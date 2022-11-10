#include "SDL_render.h"

int FrameUpdate(SDL_Event, SDL_Renderer*, int, SDL_Rect[]);
int windowCreation();
void QuitEvent(SDL_Renderer*, SDL_Window*);
int InitUpdate(SDL_Renderer*, int, SDL_Rect[]);
void OnButtonClick(SDL_Rect[], int);