#include "CFGPrinter.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CFG.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Casting.h"
#include <map>
#include <vector>

using namespace llvm;

static void printFunctionCFG(raw_ostream &OS, Function &F)
{
    OS << "digraph \"" << F.getName() << "_cfg\" {\n";
    OS << "  label=\"CFG for " << F.getName() << "\";\n";
    OS << "  node [shape=record, fontname=\"Courier\"];\n\n";

    // Assign stable names to BBs
    std::map<BasicBlock *, std::string> BBNames;
    unsigned idx = 0;
    for (BasicBlock &BB : F)
    {
        std::string name = BB.hasName() ? BB.getName().str()
                                        : ("bb" + std::to_string(idx++));
        BBNames[&BB] = name;
    }

    for (BasicBlock &BB : F)
    {
        std::string &name = BBNames[&BB];
        bool isEntry = (&BB == &F.getEntryBlock());
        std::string label = "{ " + name;
        if (isEntry)
        {
            label += " (" + F.getName().str() + ")";
        }
        label += " | ";
        for (Instruction &I : BB)
        {
            std::string instr;
            raw_string_ostream rso(instr);
            I.print(rso);
            rso.flush();
            for (char &c : instr)
                if (c == '"')
                    c = '\'';
            label += instr + "\\l";
        }
        label += "}";
        OS << "  \"" << name << "\" [label=\"" << label << "\"];\n";
    }

    for (BasicBlock &BB : F)
    {
        auto *TI = BB.getTerminator();
        for (unsigned i = 0, e = TI->getNumSuccessors(); i != e; ++i)
        {
            BasicBlock *Succ = TI->getSuccessor(i);
            OS << "  \"" << BBNames[&BB] << "\" -> \""
               << BBNames[Succ] << "\";\n";
        }
    }

    OS << "}\n\n";
}

PreservedAnalyses CFGPrinter::run(Module &M, ModuleAnalysisManager &)
{
    OS << "Generating call graph for module '" << M.getName() << "':\n";

    for (Function &F : M)
    {
        if (F.isDeclaration())
            continue;
        printFunctionCFG(OS, F);
    }

    return PreservedAnalyses::all();
}

llvm::PassPluginLibraryInfo getCFGPrinterPluginInfo()
{
    return {
        LLVM_PLUGIN_API_VERSION, "CFGPrinter", LLVM_VERSION_STRING,
        [](PassBuilder &PB)
        {
            // Register for "opt -passes=print-callgraph"
            PB.registerPipelineParsingCallback(
                [&](StringRef Name, ModulePassManager &MPM,
                    ArrayRef<PassBuilder::PipelineElement>)
                {
                    if (Name == "cfg-printer")
                    {
                        MPM.addPass(CFGPrinter(llvm::errs()));
                        return true;
                    }
                    return false;
                });

            PB.registerOptimizerLastEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel Level)
                {
                    MPM.addPass(CFGPrinter(llvm::errs()));
                });
        }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
    return getCFGPrinterPluginInfo();
}