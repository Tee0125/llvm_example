#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

#include <vector>

void gen_constant_array(llvm::Module* module, const char* name)
{
    const int src[] = { 1, 2, 3, 4, 5 };
    std::vector<uint32_t> _src(std::begin(src), std::end(src));

    auto t = llvm::ArrayType::get(llvm::Type::getInt32Ty(module->getContext()), _src.size());

    // Creates a global without assigning parentModule
    auto global = new llvm::GlobalVariable(
      /*Type=*/t,
      /*isConstant=*/false,
      /*Linkage=*/llvm::GlobalValue::PrivateLinkage,
      /*Initializer=*/llvm::ConstantDataArray::get(module->getContext(), _src),
      /*Name=*/name);
 
    global->setAlignment(32);

    // add to module && set attributes...
    module->getGlobalList().push_back(global);
}

int main(int argc, char** argv)
{
    llvm::LLVMContext context;
    auto module = llvm::make_unique<llvm::Module>("My First JIT", context);
 
    gen_constant_array(module.get(), "my_array");

    module->dump();
 
    return 0;
}
