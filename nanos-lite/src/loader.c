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
extern size_t get_ramdisk_size();
static uintptr_t loader(PCB *pcb, const char *filename) {
  //TODO();
  printf("%d\n",get_ramdisk_size());
  Elf_Ehdr elf;
  ramdisk_read((void*)&elf,0,sizeof(Elf_Ehdr));
  printf("%x\n",*elf.e_ident);
  uint32_t a,b;
  a=elf.e_entry>>16;b=(elf.e_entry<<16)>>16;
  printf("%x %x\n",a,b);
  return elf.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}
