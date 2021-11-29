#include <proc.h>
#include <elf.h>
#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif
extern uint8_t ramdisk_start;
extern uint8_t ramdisk_end;
extern size_t ramdisk_read(void *, size_t, size_t);
extern size_t ramdisk_write(const void*, size_t, size_t);
extern size_t get_ramdisk_size();
static uintptr_t loader(PCB *pcb, const char *filename) {
  //TODO();
  //ramdisk_read(elf,0,sizeof(Elf_Ehdr));
  volatile int32_t entry=-1;
  printf("%d\n",entry);
  return entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}
/*
0 0001001
*/
