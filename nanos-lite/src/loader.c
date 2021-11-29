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
  Elf_Ehdr Ehdr;
  ramdisk_read(&Ehdr, 0, get_ramdisk_size());
  for(int i = 0; i < Ehdr.e_phnum;i++){
      Elf_Phdr Phdr;
      ramdisk_read(&Phdr, Ehdr.e_phoff + i*Ehdr.e_phentsize, sizeof(Phdr));
      if(!(Phdr.p_type & PT_LOAD)){
          continue;
      }
      for(unsigned int i = Phdr.p_filesz; i < Phdr.p_memsz;i++){
          ((char*)Phdr.p_vaddr)[i] = 0;
      }
      ramdisk_read((void*)Phdr.p_vaddr, Phdr.p_offset, Phdr.p_filesz);
  }
  return Ehdr.e_entry;
  //return 0;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}
/*
001011011010 00011 111 00001 0100000
*/
