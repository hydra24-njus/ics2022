#include <NDL.h>
#include <SDL.h>

#define keyname(k) #k,

static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};

int SDL_PushEvent(SDL_Event *ev) {
  return 0;
}

int SDL_PollEvent(SDL_Event *ev) {
  return 0;
}

int SDL_WaitEvent(SDL_Event *event) {
while(1){
  char buf[64];
  NDL_PollEvent(buf, 64);
  char keydown[3],keycode[15];
  if(buf[0]=='0')continue;//no event.
  sscanf(buf,"%s %s\n",keydown,keycode);
  //printf("%s %s\n",keydown,keycode);
  event->key.type=event->type=(keydown[1] == 'd')?SDL_KEYDOWN:SDL_KEYUP;
  for (int i = 0; i < 83; i++) {
    if (!strcmp(keyname[i], keycode)) {
      event->key.keysym.sym = i;
    }
  }
  return 1;
  }
  return 0;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}
