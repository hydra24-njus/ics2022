#include <proc.h>
#include <elf.h>
#include <fs.h>
#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif
extern int fs_open(const char */*, int flags, mode_t mode*/);
extern size_t fs_lseek(int fd, size_t offset, int whence);
extern size_t fs_read(int,void *,size_t);
static uintptr_t loader(PCB *pcb, const char *filename) {
  //TODO();
  Elf_Ehdr elf;
  int fd=fs_open(filename);
  fs_lseek(fd, 0, SEEK_SET);
  fs_read(fd, &elf, sizeof(Elf_Ehdr));
  Elf_Phdr Phdr;
  assert(*(uint32_t*)elf.e_ident==0x464c457f);
  //printf("success!\n");
  for (int i = 0; i < elf.e_phnum; i++) {
    fs_lseek(fd, elf.e_phoff + i*elf.e_phentsize, SEEK_SET);//TODO：改为CUR
    fs_read(fd, &Phdr, sizeof(Phdr));
    if (Phdr.p_type == 1) {
      fs_lseek(fd, Phdr.p_offset, SEEK_SET);
      fs_read(fd, (void*)Phdr.p_vaddr, Phdr.p_filesz);
      for(unsigned int i = Phdr.p_filesz; i < Phdr.p_memsz;i++){
          ((char*)Phdr.p_vaddr)[i] = 0;
      }
    }
  }
  return elf.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}
