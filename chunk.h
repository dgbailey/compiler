#ifndef clox_chunk_h
#define clox_chunk_h
#include "common.h"
#include "memory.h"
#include "value.h"

typedef struct{
	int count;
	int capacity;
	uint8_t* code;
	int* lines;
	ValueArray constants;
}Chunk;

void initChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);


#endif