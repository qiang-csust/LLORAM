
#include "myhash.h"
#include "windows.h"
#include "blake2.h"
#include "common.h"

//using namespace CryptoPP;

myhash my;
typedef void (__stdcall *Blake2b_Func)(char* output, long outlen, char* input, long inputlen);
Blake2b_Func func;

CryptoPP::BLAKE2b b(false, 20);

CryptoPP::BLAKE2b b28(false, 28);
CryptoPP::BLAKE2b b40(false, 40);
CryptoPP::BLAKE2b b44(false, 44);
CryptoPP::BLAKE2b b24(false, 24);

int counter1 = 0;


unsigned long timeforhashfunction = 0;

myhash::myhash()
{
	//HANDLE h = LoadLibraryA("ConsoleApplication1.dll");
	//func=(Blake2b_Func)GetProcAddress((HMODULE)h, "Blake2b");
	b2= new
	CryptoPP::BLAKE2b (false, 20);
	counter1 = 0;
}

void myhash::Blake2bP(void * input, int len, unsigned char * output)
{
	b2->CalculateDigest((CryptoPP::byte*)output, (CryptoPP::byte*)input, len);
}

void myhash::Blake2b(void * input, int len, unsigned char * output)
{
#ifdef BREAKDOWN_ANALYSIS
	unsigned long t1 = time_us();
#endif
	//BLAKE2b b(false, 20);
	//CryptoPP::byte buf[256] = { 0 };
	//CryptoPP::byte input[256] = { 1,2,3,4,5,6,7,8 };
	b.CalculateDigest((CryptoPP::byte*)output, (CryptoPP::byte*)input, len);
#ifdef BREAKDOWN_ANALYSIS
	unsigned long t2 = time_us();
	timeforhashfunction += (t2 - t1);
#endif
	counter1++;
	//b.CalculateTruncatedDigest(output, 20, (CryptoPP::byte*)input, len);	
	//func((char*)output, 20, (char*)input, len);
}
void myhash::Blake2b_28(void * input, int len, unsigned char * output)
{
#ifdef BREAKDOWN_ANALYSIS
	unsigned long t1 = time_us();
#endif
	//BLAKE2b b(false, 20);
	//CryptoPP::byte buf[256] = { 0 };
	//CryptoPP::byte input[256] = { 1,2,3,4,5,6,7,8 };
	b28.CalculateDigest((CryptoPP::byte*)output, (CryptoPP::byte*)input, len);
#ifdef BREAKDOWN_ANALYSIS
	unsigned long t2 = time_us();
	timeforhashfunction += (t2 - t1);
#endif
	counter1++;
	//b.CalculateTruncatedDigest(output, 20, (CryptoPP::byte*)input, len);	
	//func((char*)output, 20, (char*)input, len);
}
void myhash::Blake2b_40(void* input, int len, unsigned char* output)
{
	b40.CalculateDigest((CryptoPP::byte*)output, (CryptoPP::byte*)input, len);
	counter1++;
}
void myhash::Blake2b_44(void * input, int len, unsigned char * output)
{
	b44.CalculateDigest((CryptoPP::byte*)output, (CryptoPP::byte*)input, len);
	counter1++;
}
void myhash::Blake2b_24(void * input, int len, unsigned char * output)
{
	b24.CalculateDigest((CryptoPP::byte*)output, (CryptoPP::byte*)input, len);
	counter1++;
}

void myhash::SimpleHash_28(void * input, int len, unsigned char * output)
{
	//BLAKE2b b(false, 20);
	//CryptoPP::byte buf[256] = { 0 };
	//CryptoPP::byte input[256] = { 1,2,3,4,5,6,7,8 };
	
	for (int i = 0; i < len; i++)
	{
		output[i%20] = output[i % 20]+((unsigned char*)input)[i];
	};
	//b.CalculateTruncatedDigest(output, 20, (CryptoPP::byte*)input, len);	
	//func((char*)output, 20, (char*)input, len);
}

void hashbytes(void* input, int input_len, int output_len, void* output)
{
	CryptoPP::BLAKE2b b(false, output_len);
	b.CalculateDigest((CryptoPP::byte*)output, (CryptoPP::byte*)input, input_len);
	counter1++;
}
int myhash::counter()
{
	return counter1;
}

unsigned long myhash::getTimeElapsed()
{
	return timeforhashfunction;
}

myhash::~myhash()
{
	//
	delete b2;
}


