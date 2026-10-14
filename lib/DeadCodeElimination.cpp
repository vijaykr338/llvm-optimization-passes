#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Analysis.h"
#include "llvm/IR/PatternMatch.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/Casting.h"
#include <llvm/Pass.h>

#include "DeadCodeElimination.h"

using namespace llvm;

PreservedAnalyses DeadCodeElimination::run(Function &F, FunctionAnalysisManager &FAM) {
    bool modified = false;

    bool changed;
    do {
        changed = false;
        
        for (auto &BB : F) {
            for (auto I = BB.begin(); I != BB.end();) {
                Instruction &Inst = *I++;
                
                // Skip instructions that have side effects or are critical
                if (Inst.mayHaveSideEffects() ||
                    Inst.isTerminator() ||
                    isa<PHINode>(Inst) ||
                    isa<LandingPadInst>(Inst) ||
                    isa<AllocaInst>(Inst) ||
                    isa<DbgInfoIntrinsic>(Inst))
                    continue;
                
                // If instruction has no uses, it's dead code
                if (Inst.use_empty()) {
                    // Extra check for void-returning calls that might have side effects
                    if (auto *Call = dyn_cast<CallInst>(&Inst)) {
                        if (Call->getType()->isVoidTy())
                            continue;
                    }
                    
                    Inst.eraseFromParent();
                    changed = true;
                    modified = true;
                }
            }
        }
    } while (changed);

    return modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
}

llvm::PassPluginLibraryInfo getDeadCodeEliminationPluginInfo()
{
    return {LLVM_PLUGIN_API_VERSION, "DeadCodeElimination", LLVM_VERSION_STRING,
            [](PassBuilder &PB)
            {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, FunctionPassManager &FPM,
                       ArrayRef<PassBuilder::PipelineElement>)
                    {
                        if (Name == "dead-code-elimination")
                        {
                            FPM.addPass(DeadCodeElimination());
                            return true;
                        }
                        return false;
                    });
            }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
    return getDeadCodeEliminationPluginInfo();
}