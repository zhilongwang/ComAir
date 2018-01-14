#ifndef COMAIR_APROFHOOKPASS_H
#define COMAIR_APROFHOOKPASS_H

#include "llvm/Pass.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/GlobalVariable.h"


using namespace llvm;
using namespace std;


struct AprofHook : public ModulePass
{
    static char ID;
    AprofHook();

    virtual void getAnalysisUsage(AnalysisUsage &AU) const;
    virtual bool runOnModule(Module& M);

    void SetupInit();
    void SetupTypes();
    void SetupConstants();
    void SetupGlobals();
    void SetupFunctions();
    void SetupHooks();

    void InsertAprofInit(Instruction *);
    void InsertAprofIncrementCost(Instruction *);
    void InsertAprofWrite(Value *, Instruction *);
    void InsertAprofCallBefore(std::string FuncName, Instruction *BeforeCallInst);
    void InsertAprofCallAfter(Instruction *AfterCallInst);

    /* Module */
    Module *pModule;
    /* ********** */

    /* Type */
    IntegerType * IntType;
    IntegerType * LongType;
    Type * VoidType;
    PointerType* VoidPointerType;
    /* ********** */

    /* Function */
    // int aprof_init()
    Function * aprof_init;
    // void aprof_increment_cost()
    Function * aprof_increment_cost;
    // void aprof_write(void *memory_addr, unsigned int length)
    Function *aprof_write;
    // void aprof_call_before(char *funcName)
    Function *aprof_call_before;
    // void aprof_call_after()
    Function *aprof_call_after;
    /* ********** */

    /* Global Variable */
    GlobalVariable * aprof_count;
    GlobalVariable * aprof_bb_count;
    /* ********** */

    /* Constant */
    ConstantInt * ConstantLong0;
    ConstantInt * ConstantLong1;
    /* ********** */

};

#endif //COMAIR_APROFHOOKPASS_H