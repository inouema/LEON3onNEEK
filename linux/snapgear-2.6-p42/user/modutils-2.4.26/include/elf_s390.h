/* Machine-specific elf macros for i386 et al.  */

#define ELFCLASSM	ELFCLASS32
#define ELFDATAM	ELFDATA2MSB

#define EM_S390_OLD	0xa390

#define MATCH_MACHINE(x)  (x == EM_S390 || x == EM_S390_OLD)

#define SHT_RELM	SHT_RELA
#define Elf32_RelM	Elf32_Rela
