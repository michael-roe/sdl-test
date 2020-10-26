/*-
 * Copyright (c) 2020 Michael Roe
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <unistd.h>
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
double zoom;
SDL_Window *win;
SDL_Surface *screen;
SDL_Rect rect;
SDL_Event event;
int box_x = 100;
int box_y = 100;
int new_x = 100;
int new_y = 100;
int done = 0;
char *clipboard;

  zoom = 1.0;

  rect.x = box_x;
  rect.y = box_y;
  rect.w = 100;
  rect.h = 100;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
  {
    printf("Couldn't initialize\n");
    return -1;
  }

  win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

  screen = SDL_GetWindowSurface(win);

  SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_UpdateWindowSurface(win);

  while (done == 0)
  {
  while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_KEYDOWN:
          printf("Key down 0x%x (%s) 0x%x (%s)\n",
                     event.key.keysym.sym,
              SDL_GetKeyName(event.key.keysym.sym),
              event.key.keysym.scancode,
              SDL_GetScancodeName(event.key.keysym.scancode));
          new_x = box_x;
          new_y = box_y;
          switch (event.key.keysym.scancode)
          {
            case SDL_SCANCODE_UP:
              printf("UP\n");
              new_y = box_y - 10;
              break;
            case SDL_SCANCODE_DOWN:
              printf("DOWN\n");
              new_y = box_y + 10;
              break;
            case SDL_SCANCODE_RIGHT:
              printf("RIGHT\n");
              new_x = box_x + 10;
              break;
            case SDL_SCANCODE_LEFT:
              printf("LEFT\n");
              new_x = box_x - 10;
              break;
            case SDL_SCANCODE_AUDIOPREV:
              printf("AUDIOPREV\n");
              break;
            case SDL_SCANCODE_PASTE:
              printf("PASTE\n");
              clipboard = SDL_GetClipboardText();
              if (clipboard)
                printf("%s\n", clipboard);
              break;
            case SDL_SCANCODE_MENU:
              printf("MENU\n");
              break;
            case SDL_SCANCODE_APPLICATION:
              printf("APPLICATION\n");
              break;
          }
          printf("Modifiers:");
          if (event.key.keysym.mod & KMOD_LSHIFT)
            printf(" LSHIFT");
          if (event.key.keysym.mod & KMOD_RSHIFT)
            printf(" RSHIFT");
          if (event.key.keysym.mod & KMOD_LCTRL)
            printf(" LCTRL");
          if (event.key.keysym.mod & KMOD_RCTRL)
            printf(" RCTRL");
          if (event.key.keysym.mod & KMOD_LALT)
            printf(" LALT");
          if (event.key.keysym.mod & KMOD_RALT)
            printf(" RALT");
          if (event.key.keysym.mod & KMOD_MODE)
            printf(" MODE");
          printf("\n");
          break;
        case SDL_KEYUP:
          printf("key up 0x%x (%s) 0x%x (%s)\n",
                     event.key.keysym.sym,
              SDL_GetKeyName(event.key.keysym.sym),
              event.key.keysym.scancode,
              SDL_GetScancodeName(event.key.keysym.scancode));
          break;
        case SDL_TEXTINPUT:
          printf("text input event: %s\n", event.text.text);
          break;
        case SDL_MOUSEWHEEL:
          printf("mouse wheel event: %d %d\n", event.wheel.x,
              event.wheel.y);
          break;
        case SDL_QUIT:
          printf("quitting...\n");
          done = 1;
          break;
        default:
          printf("event type %d\n", event.type);
          break;
      }
    }
    if ((new_x != box_x) || (new_y != box_y))
    {
      rect.w = 100;
      rect.h = 100;
      SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));
      box_x = new_x;
      box_y = new_y;
      rect.x = box_x; 
      rect.y = box_y;
      SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 255));
      SDL_UpdateWindowSurface(win);
    }
  }

  SDL_Quit();

  return 0;
}
