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

  Elf_Ehdr eh;
  Elf_Phdr ph;
  ramdisk_read(&eh, 0, sizeof(Elf_Ehdr));
  for (int i = 0; i < eh.e_phnum; i++) {
    ramdisk_read(&ph, eh.e_phoff + i * sizeof(Elf_Phdr), sizeof(Elf_Phdr));
    if (ph.p_type == 1) {
      ramdisk_read((void *)ph.p_vaddr, ph.p_offset, ph.p_filesz);
    }
  }
  return eh.e_entry;
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
