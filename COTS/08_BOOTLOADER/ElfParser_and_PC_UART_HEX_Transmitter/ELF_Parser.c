#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ElF_Parser.h"

typedef struct
{
    uint8_t identity[16];
    uint16_t type;
    uint16_t machine;
    uint32_t version;
    uint32_t entry;
    uint32_t ph_offset;
    uint32_t sh_offset;
    uint32_t flags;
    uint16_t header_size;
    uint16_t ph_size;
    uint16_t ph_num;
    uint16_t sh_size;
    uint16_t sh_num;
    uint16_t strtab_index;
}elf_header;

typedef struct
{
    uint32_t type;
    uint32_t offset;
    uint32_t virtual_address;
    uint32_t physical_address;
    uint32_t file_size;
    uint32_t mem_size;
    uint32_t flags;
    uint32_t align;
}elf_phead;

static uint32_t is_elf(elf_header *elf);

uint8_t * ELF_ParsingFile(uint8_t *FileName, uint32_t ProgramShift, uint32_t *SizeReturn, uint32_t * EntryPoint, uint32_t * StartAddress)
{
	void* fd = fopen(FileName, "rb");
	uint32_t entryPoint = 0;
	uint32_t index = 0;
	uint32_t index1 = 0;
	uint32_t index2 = 0;
	uint32_t size;
	uint8_t buffer[1024*1024] = {0};
	uint8_t * Program;
	
	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	
	fseek(fd, 0, SEEK_SET);
	fread(buffer, sizeof(uint8_t), size, fd);

	elf_header *elfHeader;
	elfHeader = (elf_header *)&buffer;
	
	elf_phead * phOffset  = (elf_phead *)&buffer[elfHeader->ph_offset];
	elf_phead * phOffset1 = (elf_phead *)phOffset;
	elf_phead * phOffset2 = (elf_phead *)(phOffset+1);

	if(fd)
	{
		if(is_elf(elfHeader))
		{
			printf("ELF\n");

			/* Entry Point */
			entryPoint     = elfHeader->entry;
			*EntryPoint    = entryPoint;
			*StartAddress  = phOffset1->physical_address;
			
			Program = (uint8_t *) malloc((phOffset1->mem_size)+(phOffset2->mem_size) - ProgramShift + (((phOffset1->mem_size) - ProgramShift) % 4) * sizeof(uint8_t));
			
			
			printf("OFFSET1(Hex): %X \n", phOffset1->offset);
			printf("OFFSET2(Hex): %X \n", phOffset2->offset);
			
			printf("MEMSIZE1(Hex): %X \n", (phOffset1->mem_size)- ProgramShift);
			printf("MEMSIZE2(Hex): %X \n", phOffset2->mem_size);
			
			
			for(index = 0; index < ((phOffset1->mem_size) - ProgramShift); index++)
			{
				if(index < phOffset1->file_size - ProgramShift)
				{
					Program[index] = buffer[phOffset1->offset + index + ProgramShift];
					//printf("Program[%d]: %02X\n", index, Program[index]);
				}
				else
				{
					Program[index] = 0;
				}
			}
			
			for (index2 = 0; index2< 4 - (((phOffset1->mem_size) - ProgramShift) % 4); index2++)
			{
				Program[index] = 0xFF;
				index++;
			}
			
			*SizeReturn = ((phOffset1->mem_size)+(phOffset2->mem_size) - ProgramShift + (4 -((phOffset1->mem_size) - ProgramShift) % 4));
			
			for(index1 = 0; index1< phOffset2->mem_size; index1++ , index++)
			{
				if(index1 < phOffset2->file_size)
				{
					Program[index] = buffer[phOffset2->offset + index1];
					//printf("Program[%d]: %02X\n", index, Program[index]);
				}
				else
				{
					Program[index] = 0;
				}
			}
		}
		else
		{
			printf("NOT ELF\n");
		}
		/*
		for (index = 0; index < ((phOffset1->mem_size)+(phOffset2->mem_size)); index++)
		{
			printf("Program[%d]: %02X \n", index , Program[index]);
		}
		*/
		fclose(fd);
	}
	return Program;
}


static uint32_t is_elf(elf_header *elf)
{
    uint32_t iself = -1;

    if((elf->identity[0] == 0x7f) && \
        !strncmp((uint8_t *)&elf->identity[1], "ELF", 3))
    {
        iself = 0;
    }

    if(iself != -1)
        iself = elf->type;

    return iself;
}

