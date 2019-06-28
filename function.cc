#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

#include <iostream>
#include <string>

void declare_func(llvm::Module* module, llvm::IRBuilder<>& builder)
{
    auto ret_type = llvm::Type::getFloatTy(module->getContext());
    std::vector<llvm::Type*> arg_types;

    arg_types.push_back(builder.getDoubleTy());
    arg_types.push_back(builder.getInt32Ty());

    llvm::FunctionType *fun_type = llvm::FunctionType::get(ret_type, arg_types, false);
    llvm::Function::Create(fun_type, llvm::Function::ExternalLinkage, "my_function", module);
}

void define_func(llvm::Module* module, llvm::IRBuilder<>& builder)
{
    std::vector<llvm::Type*> arg_types;

    llvm::Function *fun = module->getFunction("my_function");
    
    auto arg = fun->arg_begin();
    arg->setName(std::string("my_first_argument")); arg++;
    arg->setName(std::string("my_second_argument"));

    auto block = llvm::BasicBlock::Create(module->getContext(), "", fun);
    builder.SetInsertPoint(block);

    builder.CreateRet(llvm::ConstantFP::get(builder.getFloatTy(), 1.1));
}

void define_func_body(llvm::Module* module, llvm::IRBuilder<>& builder)
{
    llvm::Function *fun = module->getFunction("my_function");
    
    auto block = llvm::BasicBlock::Create(module->getContext(), "another_block", fun);
    builder.SetInsertPoint(block);

    std::vector<llvm::Value*> variables;
    variables.push_back(llvm::ConstantFP::get(builder.getInt32Ty(), 0));
    variables.push_back(llvm::ConstantFP::get(builder.getInt32Ty(), 1));

    // make recursive call
    builder.CreateCall(fun, variables, "my_destination");
}

int main(int argc, char** argv)
{
    llvm::LLVMContext context;
    auto module = llvm::make_unique<llvm::Module>("My First JIT", context);

    llvm::IRBuilder<> builder(module->getContext());

    std::cout << "declare function: " << std::endl;
    declare_func(module.get(), builder);
    module->dump();
    std::cout << std::endl << std::endl;

    std::cout << "define function: " << std::endl;
    define_func(module.get(), builder);
    module->dump();
    std::cout << std::endl << std::endl;

    std::cout << "define function body: " << std::endl;
    define_func_body(module.get(), builder);
    module->dump();
    std::cout << std::endl << std::endl;

    return 0;
}
