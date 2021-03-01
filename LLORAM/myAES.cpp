#include "myAES.h"

#include <aes.h>
#include <math.h>


using namespace std;
using namespace CryptoPP;

AESEncryption aesEncryptor; //加密器 
AESDecryption aesDecryptor;


unsigned char inBlock[AES::BLOCKSIZE] = "123456789"; //要加密的数据块
unsigned char outBlock[AES::BLOCKSIZE]; //加密后的密文块
unsigned char xorBlock[AES::BLOCKSIZE]; //必须设定为全零

myAES::myAES()
{

}

void myAES::SetPrivateKey(char* key)
{
	SetPrivateKey(key, strlen(key));
}
void myAES::SetPrivateKey(char * key, int len)
{
	unsigned char aesKey[AES::DEFAULT_KEYLENGTH] = { 0 }; //密钥
	if (len > AES::DEFAULT_KEYLENGTH) len = AES::DEFAULT_KEYLENGTH;//只保留这么多 16
	memcpy(aesKey, key, len);
	aesEncryptor.SetKey(aesKey, AES::DEFAULT_KEYLENGTH);

	aesDecryptor.SetKey(aesKey, AES::DEFAULT_KEYLENGTH);
}

//加密为随机 RCPA-secure
int counter = 0;
void myAES::Encrypt(char * input, int inputlen, char * output, int & outputlen)
{
	//inputlen += 4;//加上一个4字节的计数器，以产生随机数
	int groupsize = AES::BLOCKSIZE - 4;//每一组后面插入4个字节的随机码
	int blocks = ceil((double)inputlen / groupsize);
	for (int i = 0; i < blocks; i++)
	{
		char* pInput = input + i * groupsize;
		if (i < blocks - 1)
		{
			memcpy(inBlock, pInput, groupsize);
			memcpy(inBlock + groupsize, (void*)&counter, 4);
		}
		else
		{
			memset(inBlock, 0, sizeof(inBlock));
			int left = inputlen - i*groupsize;
			memcpy(inBlock, pInput,left);
			memcpy(inBlock+ groupsize, (void*)&counter, 4);//不足的部分被补0，最后4个字节被插入一个计数器，产生随机数
		}
		//memset(xorBlock, 0, AES::BLOCKSIZE);
		//aesEncryptor.ProcessAndXorBlock((CryptoPP::byte*)inBlock, xorBlock, (CryptoPP::byte*)(output+ i * AES::BLOCKSIZE)); //加密
		aesEncryptor.ProcessBlock((CryptoPP::byte*)inBlock, (CryptoPP::byte*)(output + i * AES::BLOCKSIZE)); //加密
		counter++;
	}
	outputlen = blocks * AES::BLOCKSIZE;
}

void myAES::Decrypt(char * input, int inputlen, char * output, int & outputlen)
{
	if (inputlen%AES::BLOCKSIZE != 0)
	{
		printf("error input!");
		return;
	}
	int blocks = inputlen / AES::BLOCKSIZE;
	int groupsize = AES::BLOCKSIZE - 4;
	outputlen = 0;
	char* temp = (char*)malloc(inputlen);
	for (int i = 0; i < blocks; i++)
	{
		char* pInput = input + i * AES::BLOCKSIZE;
		memcpy(inBlock, pInput, sizeof(inBlock));
		//memset(xorBlock, 0, AES::BLOCKSIZE);
		//aesDecryptor.ProcessAndXorBlock((CryptoPP::byte*)inBlock, xorBlock, (CryptoPP::byte*)(temp + i * AES::BLOCKSIZE)); //加密
		aesDecryptor.ProcessBlock((CryptoPP::byte*)inBlock, (CryptoPP::byte*)outBlock); //


		memcpy(output + i * groupsize, outBlock, groupsize);
		outputlen += groupsize;//解密后可能体积增大了（因为被0对齐到BLOCKSIZE-4字节了)		
	}
	free(temp);
}


myAES::~myAES()
{
}
