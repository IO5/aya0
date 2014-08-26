#include "inst.h"

static const char* Inst_name_data[] =
{
    OPCODES(STRINGIFY)
};

const char** Inst::name = Inst_name_data;

