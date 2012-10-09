#ifndef _SYMTABLE_H
#define _SYMTABLE_H
#include <stdlib.h>
#include <map>
#include <stdint.h>
#include <iostream>
#include "data.h"
using namespace std;

#define OPCODE(op,bin)	ret[std::string(op)] = bin


//Constants for operand types.
#define REG8	2
#define REG16	4
#define MEM8	8
#define MEM16	16
#define IMM8	32
#define IMM16	64

//Defines a bitmask for the MOD/RM Extension for one-byte opcodes. See Intel refMan.
#define MOD_RM_EXT 0xFF

//Bitmask for the bit values.
#define MOD_RM_EXTMASK 0x07

#define SINGLE_OP 0x00


typedef std::vector<uint8_t> 	opvariant_t;
typedef std::vector<OpType> 	opvariants_t;

typedef struct OpVar{
	opvariant_t opvar;
	OpVar(uint8_t opt, uint8_t opcode, uint8_t modRM, uint8_t operand1, uint8_t operand2):
};


//single byte opcodes supported only!
//OpType format: [future implementation, 0x00] opcode modRM (optional) operand1 operand2


class SymTable{
		public:
						SymTable();
						uint8_t get(std::string opcode);
						void repr();
		private:
					typedef map<std::string, OpVar<OpType>> SymMap;
						static SymMap m_opmap;
						static SymMap generate();
};

#endif
