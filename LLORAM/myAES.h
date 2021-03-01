#pragma once
#include "stdio.h"

class myAES
{
public:
	myAES();
	static void SetPrivateKey(char* key, int kenLen);
	static void SetPrivateKey(char* key);
	static void Encrypt(char* input, int inputlen, char* output, int& outputlen);
	static void Decrypt(char* input, int inputlen, char* output, int& outputlen);
	~myAES();
};

