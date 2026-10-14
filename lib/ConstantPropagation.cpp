#include "ConstantPropagation.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/Casting.h"

using namespace llvm;

PreservedAnalyses ConstantPropagation::run(Function &F,
                                           FunctionAnalysisManager &FAM)
{
  bool changed = false;

  // Iterate through all basic blocks in the function
  for (auto &BB : F)
  {
    std::vector<Instruction *> worklist;

    for (auto &I : BB)
    {
      if (auto *BO = dyn_cast<BinaryOperator>(&I))
      {
        worklist.push_back(BO);
      }
    }

    // Process the worklist
    for (auto *I : worklist)
    {
      if (auto *BO = cast<BinaryOperator>(I))
      {

        // Check if both operands are constants
        auto *LHS = dyn_cast<ConstantInt>(BO->getOperand(0));
        auto *RHS = dyn_cast<ConstantInt>(BO->getOperand(1));

        if (!LHS || !RHS)
          continue;

        Constant *Result = nullptr;

        switch (BO->getOpcode())
        {
        case Instruction::Add:
          Result = ConstantInt::get(LHS->getType(),
                                    LHS->getValue() + RHS->getValue());
          break;
        case Instruction::Sub:
          Result = ConstantInt::get(LHS->getType(),
                                    LHS->getValue() - RHS->getValue());
          outs() << "Constant folding sub\n";
          break;
        case Instruction::Mul:
          Result = ConstantInt::get(LHS->getType(),
                                    LHS->getValue() * RHS->getValue());
          outs() << "Constant folding mul\n";

          break;
        case Instruction::UDiv:
          if (!RHS->isZero())
            Result = ConstantInt::get(LHS->getType(),
                                      LHS->getValue().udiv(RHS->getValue()));
          outs() << "Constant folding udiv\n";

          break;
        case Instruction::SDiv:
          if (!RHS->isZero())
            Result = ConstantInt::get(LHS->getType(),
                                      LHS->getValue().sdiv(RHS->getValue()));
          outs() << "Constant folding sdiv\n";

          break;
        case Instruction::URem:
          if (!RHS->isZero())
            Result = ConstantInt::get(LHS->getType(),
                                      LHS->getValue().urem(RHS->getValue()));
          outs() << "Constant folding urem\n";

          break;
        case Instruction::SRem:
          if (!RHS->isZero())
            Result = ConstantInt::get(LHS->getType(),
                                      LHS->getValue().srem(RHS->getValue()));
          outs() << "Constant folding srem\n";

          break;
        case Instruction::Shl:
          Result = ConstantInt::get(LHS->getType(),
                                    LHS->getValue().shl(RHS->getValue()));
          outs() << "Constant folding shl\n";

          break;
        case Instruction::LShr:
          Result = ConstantInt::get(LHS->getType(),
                                    LHS->getValue().lshr(RHS->getValue()));
          outs() << "Constant folding lshr\n";

          break;
        case Instruction::AShr:
          Result = ConstantInt::get(LHS->getType(),
                                    LHS->getValue().ashr(RHS->getValue()));
          outs() << "Constant folding ashr\n";

          break;
        case Instruction::And:
          Result = ConstantInt::get(LHS->getType(),
                                    LHS->getValue() & RHS->getValue());
          outs() << "Constant folding and\n";

          break;
        case Instruction::Or:
          Result = ConstantInt::get(LHS->getType(),
                                    LHS->getValue() | RHS->getValue());
          outs() << "Constant folding or\n";

          break;
        case Instruction::Xor:
          Result = ConstantInt::get(LHS->getType(),
                                    LHS->getValue() ^ RHS->getValue());
          outs() << "Constant folding xor\n";

          break;
        default:
          continue;
        }

        if (Result)
        {
          BO->replaceAllUsesWith(Result);
          BO->eraseFromParent();
          changed = true;
        }
      }
      else if (auto *CI = dyn_cast<ICmpInst>(I))
      {
        auto *LHS = dyn_cast<ConstantInt>(CI->getOperand(0));
        auto *RHS = dyn_cast<ConstantInt>(CI->getOperand(1));

        if (!LHS || !RHS)
          continue;

        bool ResultVal = false;

        switch (CI->getPredicate())
        {
        case CmpInst::ICMP_EQ:
          ResultVal = LHS->getValue() == RHS->getValue();
          outs() << "Constant folding icmp eq\n";
          break;
        case CmpInst::ICMP_NE:
          ResultVal = LHS->getValue() != RHS->getValue();
          outs() << "Constant folding icmp ne\n";
          break;
        case CmpInst::ICMP_UGT:
          ResultVal = LHS->getValue().ugt(RHS->getValue());
          outs() << "Constant folding icmp ugt\n";
          break;
        case CmpInst::ICMP_UGE:
          ResultVal = LHS->getValue().uge(RHS->getValue());
          outs() << "Constant folding icmp uge\n";
          break;
        case CmpInst::ICMP_ULT:
          ResultVal = LHS->getValue().ult(RHS->getValue());
          outs() << "Constant folding icmp ult\n";
          break;
        case CmpInst::ICMP_ULE:
          ResultVal = LHS->getValue().ule(RHS->getValue());
          outs() << "Constant folding icmp ule\n";
          break;
        case CmpInst::ICMP_SGT:
          ResultVal = LHS->getValue().sgt(RHS->getValue());
          outs() << "Constant folding icmp sgt\n";
          break;
        case CmpInst::ICMP_SGE:
          ResultVal = LHS->getValue().sge(RHS->getValue());
          outs() << "Constant folding icmp sge\n";
          break;
        case CmpInst::ICMP_SLT:
          ResultVal = LHS->getValue().slt(RHS->getValue());
          outs() << "Constant folding icmp slt\n";
          break;
        case CmpInst::ICMP_SLE:
          ResultVal = LHS->getValue().sle(RHS->getValue());
          outs() << "Constant folding icmp sle\n";
          break;
        default:
          continue;
        }

        Constant *Result = ConstantInt::get(CI->getType(), ResultVal);

        CI->replaceAllUsesWith(Result);
        CI->eraseFromParent();
        changed = true;
      }
    }
  }

  return changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
}

llvm::PassPluginLibraryInfo getConstantPropagationPluginInfo()
{
  return {
      LLVM_PLUGIN_API_VERSION, "ConstantPropagation", LLVM_VERSION_STRING,
      [](PassBuilder &PB)
      {
        PB.registerPipelineParsingCallback(
            [&](StringRef Name, FunctionPassManager &FPM,
                ArrayRef<PassBuilder::PipelineElement>)
            {
              if (Name == "constant-propagation")
              {
                FPM.addPass(ConstantPropagation());
                return true;
              }
              return false;
            });
        PB.registerVectorizerStartEPCallback(
            [](llvm::FunctionPassManager &PM, llvm::OptimizationLevel Level)
            {
              PM.addPass(ConstantPropagation());
            });
      }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
  return getConstantPropagationPluginInfo();
}