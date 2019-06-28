#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

void init_global_variable(llvm::Module* module, const char* name)
{
    llvm::GlobalVariable* g = module->getNamedGlobal(name);
    llvm::Constant* c = llvm::ConstantInt::get(llvm::Type::getInt32Ty(module->getContext()), 111);
 
    g->setInitializer(c);
    g->setLinkage(llvm::GlobalValue::ExternalLinkage);
    g->setAlignment(8);
}

llvm::GlobalVariable* gen_global_0(llvm::Module* module, const char* name)
{
    // Creates a global without assigning parentModule
    auto global = new llvm::GlobalVariable(
      /*Type=*/llvm::Type::getInt32Ty(module->getContext()),
      /*isConstant=*/true,
      /*Linkage=*/llvm::GlobalValue::PrivateLinkage,
      /*Initializer=*/nullptr,
      /*Name=*/name);
 
    // add to module && set attributes...
    module->getGlobalList().push_back(global);
 
    init_global_variable(module, name);
 
    return global;
}

llvm::GlobalVariable* gen_global_1(llvm::Module* module, const char* name)
{
    llvm::LLVMContext& context = module->getContext();
    llvm::Constant* const_variable = llvm::ConstantFP::get(llvm::Type::getFloatTy(context), 222.22);
 
    // Creates a global:
    //   If a parent module is specified, the global is automatically
    //   inserted into the end of the specified modules global list.
    auto global = new llvm::GlobalVariable(
      /*Module=*/*module,
      /*Type=*/llvm::Type::getFloatTy(context),
      /*isConstant=*/true,
      /*Linkage=*/llvm::GlobalValue::PrivateLinkage,
      /*Initializer=*/const_variable,
      /*Name=*/name);

    return global;
}

llvm::GlobalVariable* gen_global_2(llvm::Module* module, const char* name, llvm::GlobalVariable* insertBefore=nullptr)
{
    llvm::LLVMContext& context = module->getContext();
    llvm::Constant* const_variable = llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(context));
 
    // Creates a global and inserts it before the specified other global variables
    auto global = new llvm::GlobalVariable(
      /*Module=*/*module,
      /*Type=*/llvm::Type::getInt8PtrTy(context),
      /*isConstant=*/true,
      /*Linkage=*/llvm::GlobalValue::PrivateLinkage,
      /*Initializer=*/const_variable,
      /*Name=*/name,
      /*InsertBefore=*/insertBefore);
 
    return global;
}

int main(int argc, char** argv)
{
    llvm::LLVMContext context;
    auto module = llvm::make_unique<llvm::Module>("My First JIT", context);
 
    auto g0 = gen_global_0(module.get(), "my_global_0");
    auto g1 = gen_global_1(module.get(), "my_global_1");
    auto g2 = gen_global_2(module.get(), "my_global_2", g1);

    module->dump();
 
    return 0;
}
