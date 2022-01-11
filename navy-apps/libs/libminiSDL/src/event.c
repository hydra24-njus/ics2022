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
char key[64]={0};
  memset(key,0,sizeof(key));
  key[0] = '0';
  int keycode = 0;
  while(!NDL_PollEvent(key,sizeof(key)));
  //printf("%s\n",key);
  char* str = key+3;
  for(int i = 0,cnt = 0;i < sizeof(keyname);i+=sizeof(keyname[cnt]),cnt+=1)
  {
    if(!strncmp(keyname[cnt],str,strlen(str))&&!strncmp(keyname[cnt],str,strlen(keyname[cnt]))) {
        keycode = cnt;
        break;
      }
    assert(i <= sizeof(keyname));
  }
  //printf("in waitevent\n");
  if(key[1] == 'u')
  {
    event->key.keysym.sym = keycode;
    event->type = SDL_KEYUP;
  }
  else if(key[1] == 'd'){
    event->key.keysym.sym = keycode;
    event->type = SDL_KEYDOWN;
  }
  return 0;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}
