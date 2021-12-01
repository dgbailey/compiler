#include "common.h"
#include "vm.h"
#include <stdio.h>
#include "debug.h"
VM vm;
//global vm not best practice
void initVM(){
    
}
 void freeVM(){

 }

static InterpretResult run(){
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    for (;;){
    #ifdef DEBUG_TRACING_EXECUTION
        disassembleInstruction(vm.chunk,(int)(vm.ip - vm.chunk.code));
    #endif
        uint8_t instruction;
        switch(instruction = READ_BYTE()){
            //get opcode and find right c code
            case OP_CONSTANT:{
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_RETURN: {
                return INTERPRET_OK;
            }
        }
    }
    #undef READ_BYTE
    #undef READ_CONSTANT
}

 InterpretResult interpret(Chunk* chunk){
     vm.chunk = chunk;
     vm.ip = vm.chunk->code;
     return run();
 }
 //https://stackoverflow.com/questions/4955198/what-does-dereferencing-a-pointer-mean