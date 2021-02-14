//Author: Tyler Johnston
#ifndef BUFFER
#define BUFFER

typedef struct {
        int count;
        int size;
        char* buff;
}Buffer;

Buffer* initBuffer(int size);

void addToBuffer(Buffer* b, char c);

void freeBuffer(Buffer* b);

#endif
