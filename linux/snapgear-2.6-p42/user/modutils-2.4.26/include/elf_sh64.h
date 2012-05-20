/* Machine-specific elf macros for the sh64.  */

#define ELFCLASSM	ELFCLASS32
#define ELFDATAM	ELFDATA2LSB

#define MATCH_MACHINE(x)  (x == EM_SH)

#define SHT_RELM	SHT_RELA
#define Elf32_RelM	Elf32_Rela
