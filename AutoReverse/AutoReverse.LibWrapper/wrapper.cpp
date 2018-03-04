// wrapper.cpp

#include "stdafx.h"

#include "X86Disassembler.h"

#define API extern "C" __declspec(dllexport)

struct disassembler
{
	const uint8_t *bytes;

	size_t offset;

	explicit disassembler(const uint8_t *bytes) : bytes(bytes)
	{
		offset = 0;
	}
};

API disassembler *create_disassembler(const uint8_t *bytes)
{
	return new disassembler(bytes);
}

API void seek(disassembler *disassembler, const size_t offset)
{
	disassembler->offset += offset;
}

size_t foo(uint8_t *bytes)
{
	size_t i = 1;

	do
	{
		if (bytes[i] == 0xCD)
			break;

		i++;
	}
	while (i < 16);

	return i;
}

API int disassemble(disassembler *disassembler, cs_insn instruction)
{
	csh handle;
	cs_insn *insn;

	if (cs_open(CS_ARCH_X86, CS_MODE_32, &handle) != CS_ERR_OK)
		return -1;

	const auto bytes = disassembler->bytes + disassembler->offset;
	const auto count = cs_disasm(handle, bytes, sizeof(bytes) - 1, disassembler->offset, 1, &insn);
	
	if (count > 0)
	{
		instruction = insn[0];
	}
	else return -1;

	cs_close(&handle);

	seek(disassembler, foo(instruction.bytes));

	return 0;
}
