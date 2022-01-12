#include <NDL.h>
#include <SDL.h>
//#include <string.h>

#define keyname(k) #k,

static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};
uint8_t keystate[256] = {};

int SDL_PushEvent(SDL_Event *ev) {
  return 0;
}

int SDL_PollEvent(SDL_Event *ev) {
char key[64]={0};
  key[0] = '\0';
  int keycode = 0;
  int ret = NDL_PollEvent(key,sizeof(key));
  if(key[0] == '\0') {
    ev->key.keysym.sym = SDLK_NONE;
    ev->type = SDL_USEREVENT;
    return 0;
  }
  else {
    char* str = key+3;
    for(int i = 0,cnt = 0;i < sizeof(keyname);i+=strlen(keyname[cnt]),cnt++)
    {
      if(!strncmp(keyname[cnt],str,strlen(str))&&!strncmp(keyname[cnt],str,strlen(keyname[cnt]))) {
        keycode = cnt;
        break;
      }
    }
    //printf("in waitevent %d\n",keycode);
    if(key[1] == 'u')
    {
      ev->key.keysym.sym = keycode;
      ev->type = SDL_KEYUP;
      keystate[keycode] = 0;
    }
    else if(key[1] == 'd'){
      ev->key.keysym.sym = keycode;
      ev->type = SDL_KEYDOWN;
      keystate[keycode] = 1;
    }
    return 1;
  }
}

int SDL_WaitEvent(SDL_Event *event) {
  char key[64]={0};
  char state[2],name[15];
  memset(key,0,sizeof(key));
  key[0] = '0';
  int keycode = 0;
  while(!NDL_PollEvent(key,sizeof(key)));//获取event中的文本
  //printf("%s\n",key);
  sscanf(key,"%s %s\n",state,name);
  event->key.type = event->type =(state[1] == 'd') ? SDL_KEYDOWN : SDL_KEYUP;
  for (int i = 0; i < 83; i++) {
    if (!strcmp(keyname[i], name)) {
      event->key.keysym.sym = i;
      keystate[i] = (state[1] == 'd') ? 1 : 0;
      break;
    }
  }
  return 0;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}
