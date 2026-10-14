#ifndef LLVM_PASSES_FUNCTION_CALL_COUNTER_H
#define LLVM_PASSES_FUNCTION_CALL_COUNTER_H

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/Support/raw_ostream.h"

using ResultFunctionCallCounter = llvm::StringMap<unsigned>;

struct FunctionCallCounter : public llvm::AnalysisInfoMixin<FunctionCallCounter> {
  static llvm::AnalysisKey Key;
  friend struct llvm::AnalysisInfoMixin<FunctionCallCounter>;

public:
  using Result = ResultFunctionCallCounter;
  Result run(llvm::Module &M, llvm::ModuleAnalysisManager &);
  FunctionCallCounter::Result generateFunctionCallMap(llvm::Module &M);

  static bool isRequired() { return true; }
};

class FunctionCallCounterPrinter : public llvm::PassInfoMixin<FunctionCallCounterPrinter> {
public:
  explicit FunctionCallCounterPrinter(llvm::raw_ostream &OutS) : OS(OutS) {}
  llvm::PreservedAnalyses run(llvm::Module &M,
                              llvm::ModuleAnalysisManager &MAM);
  
  static bool isRequired() { return true; }

private:
  llvm::raw_ostream &OS;
};

#endif