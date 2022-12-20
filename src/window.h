#include "SDL_render.h"
#include <stdbool.h>

int windowCreation(int, bool, bool);
void QuitEvent(int, SDL_Renderer*, SDL_Window*, int* , int* , int[], int[], bool, int, int);
int Update(SDL_Renderer*, int, SDL_Rect[], int);
void OnButtonClick(SDL_Rect[], int);
//void HoverEffect(SDL_Renderer*, SDL_Point, SDL_Rect[], int);
void PlacePieces(SDL_Renderer *, SDL_Rect[], int[], int[], int[], int[], int, int);
int DragPiece(int , int , int , int* , int* , int* , int* , int*);
int GetQuadrant(SDL_Rect[], int);
void DrawPiece(SDL_Renderer*, SDL_Rect, SDL_Color, int);
void MouseInteraction(int, SDL_Window *window, SDL_Rect[], int, SDL_Renderer*, int , int* , int* , int* , int*, bool, int*, int*);
void isWin(SDL_Renderer *renderer, SDL_Window *window, int* TableauNoir, int* TableauBlanc, int TableauForteresses[], int TableauPieges[], bool difficile, int Roi, int taille);