#include "FunctionCallCounter.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include <vector>
#include <algorithm>

using namespace llvm;

static void printFunctionCallCounterResult(llvm::raw_ostream &,
                                           const ResultFunctionCallCounter &FC);

llvm::AnalysisKey FunctionCallCounter::Key;

// Helper function
FunctionCallCounter::Result FunctionCallCounter::generateFunctionCallMap(Module &M)
{
    FunctionCallCounter::Result FunctionCallMap;

    for (Function &F : M)
    {
        if (!F.isDeclaration())
        {
            FunctionCallMap[F.getName().str()] = 0;
        }
    }

    for (Function &F : M)
    {
        for (auto &BB : F)
        {
            for (auto &I : BB)
            {
                if (CallInst *CI = dyn_cast<CallInst>(&I))
                {
                    Function *Callee = CI->getCalledFunction();
                    if (Callee && !Callee->isIntrinsic())
                    {
                        FunctionCallMap[Callee->getName().str()]++;
                    }
                }
                else if (InvokeInst *II = dyn_cast<InvokeInst>(&I))
                {
                    Function *Callee = II->getCalledFunction();
                    if (Callee && !Callee->isIntrinsic())
                    {
                        FunctionCallMap[Callee->getName().str()]++;
                    }
                }
            }
        }
    }

    return FunctionCallMap;
}

// Function to run the FunctionCallCounter pass
FunctionCallCounter::Result FunctionCallCounter::run(Module &M,
                                                      ModuleAnalysisManager &)
{
    return generateFunctionCallMap(M);
}

PreservedAnalyses FunctionCallCounterPrinter::run(Module &M, ModuleAnalysisManager &MAM)
{
    auto &FunctionCallMap = MAM.getResult<FunctionCallCounter>(M);

    OS << "Printing analysis 'FunctionCallCounter Pass' for module '"
       << M.getName() << "':\n";

    printFunctionCallCounterResult(OS, FunctionCallMap);
    return PreservedAnalyses::all();
}

static void printFunctionCallCounterResult(raw_ostream &OS, const ResultFunctionCallCounter &FC) {
    // FC is a llvm::StringMap<unsigned>
    std::vector<std::pair<std::string, unsigned>> SortedCounts;
    for (auto &Entry : FC) {
        SortedCounts.push_back({Entry.getKey().str(), Entry.getValue()});
    }

    std::sort(SortedCounts.begin(), SortedCounts.end(),
              [](const std::pair<std::string, unsigned> &A,
                 const std::pair<std::string, unsigned> &B) {
                  return A.second > B.second;
              });

    OS << "=================================================\n";
    const char *str1 = "FUNCTION";
    const char *str2 = "#TIMES CALLED";
    OS << format("%-30s %-10s\n", str1, str2);
    OS << "-------------------------------------------------\n";

    for (auto &Pair : SortedCounts) {
        std::string F = Pair.first;
        unsigned Count = Pair.second;

        if (F != "main")
            OS << format("%-30s %-10u\n", F.c_str(), Count);
    }

    OS << "-------------------------------------------------\n\n";
}

llvm::PassPluginLibraryInfo getFunctionCallCounterPluginInfo()
{
    return {
        LLVM_PLUGIN_API_VERSION, "FunctionCallCounter", LLVM_VERSION_STRING,
        [](PassBuilder &PB)
        {
            // Register for "opt -passes=count-calls"
            PB.registerPipelineParsingCallback(
            [&](StringRef Name, ModulePassManager &MPM,
                ArrayRef<PassBuilder::PipelineElement>) {
              if (Name == "print<call-counter>") {
                MPM.addPass(FunctionCallCounterPrinter(llvm::errs()));
                return true;
              }
              return false;
            });

            // Register for optimization pipelines
            PB.registerOptimizerLastEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel Level)
                {
                    MPM.addPass(FunctionCallCounterPrinter(llvm::errs()));
                });

            PB.registerAnalysisRegistrationCallback(
            [](ModuleAnalysisManager &MAM) {
              MAM.registerPass([&] { return FunctionCallCounter(); });
            });
        }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
    return getFunctionCallCounterPluginInfo();
}
