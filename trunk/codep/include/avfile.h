#ifndef _FILE_H_
#define _FILE_H_ 


typedef FILE * (*FUN_fopen)(const char*, int, ...);
typedef size_t (*FUN_fread)(int, void*, unsigned int);
typedef size_t (*FUN_fwrite)(int, const void*, unsigned int);
typedef int    (*FUN_fseek)(int, long, int);
typedef  long  (*FUN_ftell)(int);
typedef int    (*FUN_fclose)(int);
typedef int    (*FUN_stat) (const char*, struct stat*);
typedef  int   (*FUN_fstat) (int, struct stat*);

int setFileCallBack(FUN_fopen o,FUN_fwrite w,FUN_fread r, FUN_fseek  s,FUN_ftell t,FUN_fclose c,FUN_stat Fstat,FUN_fstat fst);

#endif