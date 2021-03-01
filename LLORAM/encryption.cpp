#include "encryption.h"
#include "aes.h"

//pAeskey 指向16字节的秘钥
string EnStr(string w, char* pAeskey)
{
	unsigned char buf2[256] = { 0 };
	unsigned char block[16] = { 0 };
	memcpy(block, w.c_str(), w.length());
	char key[64] = { 0 };
	if (strlen(pAeskey) > 16)
	{
		memcpy(key, pAeskey, 16);
	}
	else
	{
		strcpy(key, pAeskey);
	}
	if (w.length() > 15) memcpy(block, key, 15);
	CryptoPP::AESEncryption aes((CryptoPP::byte*)key, 16);
	aes.ProcessBlock((CryptoPP::byte*)block, (CryptoPP::byte*)buf2);//16字节
	char buf3[256] = { 0 };
	for (int i = 0; i < 16; i++)
	{
		sprintf(buf3 + 2 * i, "%.2x", buf2[i]);
	}
	return buf3;
}
//pAeskey 指向16字节的秘钥
string DeStr(string w, char* pAeskey)
{
	unsigned char buf2[256] = { 0 };
	for (int i = 0; i < 16; i++)
	{
		int b = 0;
		char* c = (char*)w.c_str() + 2 * i;
		sscanf(c, "%2x", &b);
		buf2[i] = b;
	}
	char key[64] = { 0 };
	if (strlen(pAeskey) > 16)
	{
		memcpy(key, pAeskey, 16);
	}
	else
	{
		strcpy(key, pAeskey);
	}
	CryptoPP::AESDecryption aes((CryptoPP::byte*)key, 16);
	char buf3[256] = { 0 };
	aes.ProcessBlock((CryptoPP::byte*)buf2, (CryptoPP::byte*)buf3);//16字节
	return buf3;
}


encryption::encryption()
{
}


encryption::~encryption()
{
}
