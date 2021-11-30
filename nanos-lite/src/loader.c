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
  Elf_Ehdr elf;
  Elf_Phdr Phdr;
  ramdisk_read((void*)&elf,0,sizeof(Elf_Ehdr));
  assert(*(uint32_t*)elf.e_ident==0x464c457f);
  for (int i = 0; i < elf.e_phnum; i++) {
    ramdisk_read(&Phdr, elf.e_phoff + i * sizeof(Elf_Phdr), sizeof(Elf_Phdr));
    if (Phdr.p_type == 1) {
      ramdisk_read((void *)Phdr.p_vaddr, Phdr.p_offset, Phdr.p_filesz);
    }
  }
  return elf.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}
