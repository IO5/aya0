#include "vm.h"

using namespace AYA;

int main()
{
	VM vm;
	
	FunctionBuilder b(vm);
	b.addInst(Inst::LCONST, b.addConst("test"));
	b.addInst(Inst::LCONST, b.addConst(BIND(vm.io.puts)));
	b.addInst(Inst::CALL, 1);
	b.addInst(Inst::RET);

	vm.objectFactory.makeString("leak");
	
	vm.load(b.getResult());
	vm.gc.collect();
	vm.run();
}

