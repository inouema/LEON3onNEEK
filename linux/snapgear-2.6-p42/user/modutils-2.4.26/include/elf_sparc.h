/* Machine-specific elf macros for the Sparc.  */

#define ELFCLASSM	ELFCLASS32
#define ELFDATAM	ELFDATA2MSB

#define MATCH_MACHINE(x)  (x == EM_SPARC)

#define SHT_RELM	SHT_RELA
#define Elf32_RelM	Elf32_Rela
