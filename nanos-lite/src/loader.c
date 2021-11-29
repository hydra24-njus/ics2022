#include <proc.h>
#include <elf.h>
#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

extern size_t ramdisk_read(void *, size_t, size_t);
extern size_t ramdisk_write(const void*, size_t, size_t);

static uintptr_t loader(PCB *pcb, const char *filename) {
  //TODO();
   Elf_Ehdr Ehdr;
  ramdisk_read(&Ehdr, 0, sizeof(Ehdr));
  for(int i = 0; i < Ehdr.e_phnum;i++){
      Elf_Phdr Phdr;
      ramdisk_read(&Phdr, Ehdr.e_phoff + i*Ehdr.e_phentsize, sizeof(Phdr));
  }
  return Ehdr.e_entry;
  //return 0;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}

