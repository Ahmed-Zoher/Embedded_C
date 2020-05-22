#ifndef ELF_PARSER_H
#define ELF_PARSER_H

uint8_t *ELF_ParsingFile(uint8_t *FileName, uint32_t ProgramShift, uint32_t *SizeReturn, uint32_t * EntryPoint, uint32_t * StartAddress);


#endif /* ELF_PARSER_H */