#include "chunk.h"
#include "common.h"
#include "debug.h"
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

static void repl(){
  char line[1024];
  for(;;){
    printf("> ");

    if(!fgets(line,sizeof(line),stdin)){
      prinf("\n");
      break;
    }
    
    interpret(line);
  }
}

static char* readFile(const char* path){
  FILE* file = fopen(path, "rb");
  if(file == NULL){
    fprintf(stderr, "Could not open file \"%s\".\n",path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);//go to last byte of file
  size_t fileSize = ftell(file);//tell us how many bytes we are from start of file
  rewind(file);//rewind back to first byte

  char* buffer = (char*)malloc(fileSize + 1);//make room for null byte
  if(buffer == NULL){
    fprintf(stderr, "Not enough memory to read \"%s\".\n",path);
    exit(74);
  }
  size_t bytesRead = fread(buffer, sizeof(char),fileSize,file);
  if(bytesRead < fileSize){
    fprintf(stderr,"Could not read file \"%s\".\n",path);
    exit(74);
  }
  buffer[bytesRead] = '/0';
  fclose(file);
  return buffer;
}

static void runFile(const char* path){
  char* source = readFile(path);
  InterpretResult result = interpret(source);
  free(source);

  if(result == INTERPRET_COMPILE_ERROR) exit(65);
  if(result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main (int argc, const char* argv[]){
    signal(SIGSEGV, handler);   // install our handler
    initVM();
    if(argc == 1){
      repl();
    }else if(argc ==2){
      runFile(argv[1]);
    }else{
      fprintf(stderr,"Usage: clox [path]\n");
      exit(64);
    }
    // Chunk chunk;
    // initChunk(&chunk);
    // int constant = addConstant(&chunk, 1.2);
    // writeChunk(&chunk, OP_CONSTANT,123);
    // writeChunk(&chunk, constant,123);
    // writeChunk(&chunk, OP_RETURN,123);
    // disassembleChunk(&chunk, "test chunk");
    // interpret(&chunk);
    freeVM();
    // freeChunk(&chunk);
    return 0;
}