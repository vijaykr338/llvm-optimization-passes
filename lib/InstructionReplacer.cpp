#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Analysis.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/PatternMatch.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include <llvm/Pass.h>
#include <vector>

#include "InstructionReplacer.h"

using namespace llvm;

PreservedAnalyses InstructionReplacer::run(Function &F, FunctionAnalysisManager &FAM)
{
    bool modified = false;

    if (F.isDeclaration())
        return PreservedAnalyses::all();

    std::vector<BinaryOperator *> ToReplace;

    for (BasicBlock &BB : F)
    {
        for (Instruction &I : BB)
        {
            if (auto *BO = dyn_cast<BinaryOperator>(&I))
            {
                if (BO->getOpcode() == Instruction::Add)
                {
                    if (BO->getOperand(0) == BO->getOperand(1))
                    {
                        ToReplace.push_back(BO);
                    }
                }
            }
        }
    }

    for (BinaryOperator *addInst : ToReplace)
    {
        IRBuilder<> builder(addInst);
        Value *operand = addInst->getOperand(0);

        BinaryOperator *subInst = BinaryOperator::Create(
            Instruction::Sub, operand, operand, "", addInst);

        if (addInst->hasNoSignedWrap())
            subInst->setHasNoSignedWrap();
        if (addInst->hasNoUnsignedWrap())
            subInst->setHasNoUnsignedWrap();

        addInst->replaceAllUsesWith(subInst);
        addInst->eraseFromParent();

        modified = true;
    }

    return modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
}

llvm::PassPluginLibraryInfo getInstructionReplacerPluginInfo()
{
    return {LLVM_PLUGIN_API_VERSION, "InstructionReplacer", LLVM_VERSION_STRING,
            [](PassBuilder &PB)
            {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, FunctionPassManager &FPM,
                       ArrayRef<PassBuilder::PipelineElement>)
                    {
                        if (Name == "inst-replace")
                        {
                            FPM.addPass(InstructionReplacer());
                            return true;
                        }
                        return false;
                    });
            }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
    return getInstructionReplacerPluginInfo();
}