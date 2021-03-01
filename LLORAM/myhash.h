#pragma once


//#include "blake2.h"
#include "blake2.h"
//using namespace CryptoPP;
#include "windows.h"

//#include "cryptlib.h"

//using namespace CryptoPP;
//typedef unsigned char byte;
class myhash
{
public:
	CryptoPP::BLAKE2b *b2;
	myhash();
	void Blake2bP(void* input, int len, unsigned char* output);
	static void Blake2b(void* input, int len, unsigned char* output);
	static void Blake2b_28(void * input, int len, unsigned char * output);
	static void Blake2b_40(void* input, int len, unsigned char* output);
	static void Blake2b_44(void* input, int len, unsigned char* output);
	static void Blake2b_24(void * input, int len, unsigned char * output);

	static void SimpleHash_28(void * input, int len, unsigned char * output);
	//28字节输出伪随机
	static int counter();
static	unsigned long getTimeElapsed();
	~myhash();
};

//hash任意长度，得到任意长度的输出
void hashbytes(void* input, int input_len, int output_len, void* output);
