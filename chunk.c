#include <stdlib.h>
#include "memory.h"
#include "chunk.h"

void initChunk(Chunk* chunk){
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
}

void writeChunk(Chunk* chunk,uint8_t byte){
	if(chunk ->capacity < chunk->count + 1){
		/*https://stackoverflow.com/questions/2660633/declaring-pointers-asterisk-on-the-left-or-right-of-the-space-between-the-type*/
		int oldCapacity = chunk->capacity;
		chunk->capacity= GROW_CAPACITY (oldCapacity);
		chunk->code = GROW_ARRAY (uint8_t,chunk->code,oldCapacity,chunk->capacity);
	}
	chunk->code[chunk->count] = byte;
	chunk->count++;
};

void freeChunk(Chunk* chunk){
	FREE_ARRAY(uint8_t,chunk->code,chunk->capacity);
	initChunk(chunk);
};