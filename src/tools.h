#ifndef TOOLS_H
#define TOOLS_H

int GLOBAL_MEMORY;  

void tools_memory_init(void);
void *tools_malloc(int alloc); 
void tools_free(void* ptr, int alloc); 
void tools_check_at_end_of_app(void); 



int string_to_int(char* str);
int char_to_int(char c);

int str_len(char* str);
void str_copy(char* str, char* str_copy);

#endif 
