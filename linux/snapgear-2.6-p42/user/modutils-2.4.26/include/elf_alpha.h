/* Machine-specific elf macros for the Alpha.  */

#define ELFCLASSM	ELFCLASS64
#define ELFDATAM	ELFDATA2LSB

#define MATCH_MACHINE(x)  (x == EM_ALPHA)

#define SHT_RELM	SHT_RELA
#define Elf64_RelM	Elf64_Rela
