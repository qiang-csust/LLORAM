#pragma once

#include "windows.h"
#include "stdio.h"
#include "common.h"

struct headerInfo
{
	long bucketCounter;
	long bucketSize;
	long M;
	long C;
};

#define ValueBitSize 64
template<class T>
 class Myhastable
{
private:
	byte* bucket[64];
	long bucketCounter;
	long bucketSize;

	bool isSame(byte* pData,byte* pKey);
	int valueBitSize;
public:
	Myhastable(int bucket_size_bytes, int bucket_count);
	~Myhastable();
	long M;
	bool ContainsKey(byte* myKey);
	bool ReadValue(byte * mykey, byte * valueRet);
	bool ReadValue(byte *myKey, T* obj);
	bool Add(byte * mykey, byte * pvalue);
	bool Add(byte * mykey, T pvalue);

	void SaveToFile(char* file);
	void LoadFromFile(char* file);
	double getLoadfactor();
	double setLoadfactor(double factor);
	static unsigned long readTimeElasped();
};

 template <class T>
 Myhastable<T>::Myhastable(int size, int count)
 {
	 valueBitSize = sizeof(T);
	 bucketCounter = 64;
	 bucketSize = size;// 1024 * 1024 * 1024 - 1;
	 bucketCounter = count;
	 if (count >= 64) count = 64;
	 for (int i = 0; i < 64; i++)
	 {
		 bucket[i] = 0;
	 }
	 for (int i = 0; i < count; i++)
	 {
		 bucket[i] = new byte[bucketSize];//1G
		 memset(bucket[i], 0, bucketSize);
	 }
	 M = 0;
 }

 template <class T>
 Myhastable<T>::~Myhastable()
 {
	 for (int i = 0; i < bucketCounter; i++)
	 {
		 delete[] bucket[i];
	 }
 }

 template <class T>
 double Myhastable<T>::getLoadfactor()
 {
	 double Cap = ((double)bucketSize*(double)bucketCounter) / (20 + ValueBitSize / 8);
	 double c = M / Cap;
	 return c;
 }

 template <class T>
 double Myhastable<T>::setLoadfactor(double factor)
 {
	 //unsigned long newC = M / factor;
	 //unsigned long newBucketCount = newC / bucketSize+1;
	 ////	bucketCounter = 64;
	 ////	bucketSize = 1024 * 1024 * 1024 - 1;
	 ////	bucketCounter = count;
	 ////	if (count >= 64) count = 64;
	 //byte* bucketTemp[64] = { 0 };
	 //for (int i = 0; i < 64; i++)
	 //{
	 //	bucketTemp[i] = bucket[i];//保留原来的
	 //}	
	 //for (int i = 0; i < newBucketCount; i++)
	 //{
	 //	bucket[i] = new byte[bucketSize];//重新分配内存
	 //	memset(bucket[i], 0, bucketSize);
	 //}
	 //long count = 0;
	 //long oldbucketCounter = bucketCounter;
	 //bucketCounter = newBucketCount;
	 //int k = 0;
	 //char zero[20] = { 0 };
	 //M = 0;
	 //for (int i = 0; i < oldbucketCounter; i++)
	 //{
	 //	for (int j = 0; j <= bucketSize-20; j+=20)
	 //	{
	 //	//	bucketCounter = 64;
	 //	//	bucketSize = 1024 * 1024 * 1024 - 1;
	 //	//	bucketCounter = count;
	 //	//	if (count >= 64) count = 64;
	 //		byte* pdata = bucketTemp[i] + j;
	 //		if (memcmp(pdata, zero, 20) != 0)//相等
	 //		{
	 //			Add(pdata);
	 //			count++;
	 //		}
	 //	}
	 //}

	 //for (int i = 0; i < 64; i++)
	 //{
	 //	delete[] bucketTemp[i];
	 //}
	 //return newBucketCount;
	 return 0;
 }

 unsigned long hashtableAcessTime = 0;

 template <class T>
 unsigned long Myhastable<T>::readTimeElasped()
 {
	 return hashtableAcessTime;
 }


 template <class T>
 bool Myhastable<T>::ContainsKey(byte * mykey)
 {
#ifdef BREAKDOWN_ANALYSIS
	 unsigned long t1 = time_us();
#endif
	 unsigned long long addr;
	 unsigned long bucketNumber = *(unsigned long*)(mykey + 16) % 67 % bucketCounter;
	 byte* pBase = bucket[bucketNumber];
	 byte* pData;// = pBase + addr%bucketSize;
	 unsigned int i = 0;
	 unsigned int j = 0;
	 while (1)
	 {
		 addr = *(unsigned long long*)(mykey + 8 * (i % 2));
		 pData = pBase + (20 + ValueBitSize / 8)*((addr + i * i) % (bucketSize / (20 + ValueBitSize / 8)));
		 if (isSame(pData, mykey))
		 {
#ifdef BREAKDOWN_ANALYSIS
			 unsigned long t2 = time_us();
			 hashtableAcessTime += (t2 - t1);
#endif
			 return true;
		 }
		 if ((*(long long*)pData == 0) && (*(long long*)(pData + 8) == 0) && (*(int*)(pData + 16) == 0))
		 {
#ifdef BREAKDOWN_ANALYSIS
			 unsigned long t2 = time_us();
			 hashtableAcessTime += (t2 - t1);
#endif
			 return false;
		 }
		 i++;
		 j++;
		 if (j++ > 100000) return false;
	 };
#ifdef BREAKDOWN_ANALYSIS
	 unsigned long t2 = time_us();
	 hashtableAcessTime += (t2 - t1);
#endif
	 return false;
 }

 template <class T>
 bool Myhastable<T>::ReadValue(byte * mykey, byte* valueRet)
 {
#ifdef BREAKDOWN_ANALYSIS
	 unsigned long t1 = time_us();
#endif
	 unsigned long long addr;
	 unsigned long bucketNumber = *(unsigned long*)(mykey + 16) % 67 % bucketCounter;
	 byte* pBase = bucket[bucketNumber];
	 byte* pData;// = pBase + addr%bucketSize;
	 unsigned int i = 0;
	 unsigned int j = 0;
	 while (1)
	 {
		 addr = *(unsigned long long*)(mykey + 8 * (i % 2));
		 pData = pBase + (20 + ValueBitSize / 8)*((addr + i * i) % (bucketSize / (20 + ValueBitSize / 8)));
		 if (isSame(pData, mykey))
		 {
			 memcpy(valueRet, pData + 20, ValueBitSize / 8);//8 个字节
#ifdef BREAKDOWN_ANALYSIS
			 unsigned long t2 = time_us();
			 hashtableAcessTime += (t2 - t1);
#endif
			 return true;
		 }
		 if ((*(long long*)pData == 0) && (*(long long*)(pData + 8) == 0) && (*(int*)(pData + 16) == 0))
		 {
#ifdef BREAKDOWN_ANALYSIS
			 unsigned long t2 = time_us();
			 hashtableAcessTime += (t2 - t1);
#endif
			 return false;
		 }
		 i++;
		 j++;
		 if (j++ > 100000) return false;
	 };
#ifdef BREAKDOWN_ANALYSIS
	 unsigned long t2 = time_ms();
	 hashtableAcessTime += (t2 - t1);
#endif
	 return false;
 }

 template<class T>
 inline bool Myhastable<T>::ReadValue(byte * myKey, T * obj)
 {
	 return ReadValue(myKey,(byte*)obj);
 }

 template <class T>
 bool Myhastable<T>::Add(byte * mykey, byte* pvalue)
 {
	 unsigned long bucketNumber = *(unsigned long *)(mykey + 16) % 67 % bucketCounter;
	 byte* pBase = bucket[bucketNumber];
	 byte* pData;// = pBase + addr%bucketSize;
	 unsigned int i = 0;
	 unsigned int j = 0;
	 unsigned int k = 0;
	 unsigned long long addr;
	 while (1)
	 {
		 addr = *(unsigned long long*)(mykey + 8 * (i % 2));
		 //k = 20*((addr + i*i)   % (bucketSize/20));
		 pData = pBase + (20 + ValueBitSize / 8) * ((addr + i * i) % (bucketSize / (20 + ValueBitSize / 8)));
		 if (isSame(pData, mykey))
		 {
			 memcpy(pData + 20, pvalue, (ValueBitSize / 8));//用新的覆盖老的
			 return false;//已经 存在
		 }
		 if ((*(long long*)pData == 0) && (*(long long*)(pData + 8) == 0) && (*(int*)(pData + 16) == 0))
		 {
			 memcpy(pData, mykey, 20);
			 memcpy(pData + 20, pvalue, (ValueBitSize / 8));
			 M++;
			 return true;
		 }
		 i++;
		 j++;
		 if (j++ > 100000) return false;
	 };
 }



 template <class T>
 void Myhastable<T>::SaveToFile(char * file)
 {
	 FILE* fp = fopen(file, "wb");
	 headerInfo hd;
	 hd.bucketCounter = bucketCounter;
	 hd.bucketSize = bucketSize;
	 hd.M = M;
	 hd.C = bucketCounter * bucketSize / (20 + ValueBitSize / 8);
	 fwrite(&hd, sizeof(hd), 1, fp);
	 for (int i = 0; i < bucketCounter; i++)
	 {
		 fwrite(bucket[i], 1, bucketSize, fp);
	 }
	 fclose(fp);
 }

 template <class T>
 void Myhastable<T>::LoadFromFile(char * file)
 {
	 FILE* fp = fopen(file, "rb");
	 if (!fp) return;
	 headerInfo hd;
	 fread((void*)&hd, sizeof(hd), 1, fp);
	 bucketCounter = hd.bucketCounter;
	 bucketSize = hd.bucketSize;
	 M = hd.M;
	 for (int i = 0; i < bucketCounter; i++)
	 {
		 if (bucket[i] == NULL) bucket[i] = new byte[bucketSize];
		 fread(bucket[i], 1, bucketSize, fp);
	 }
	 fclose(fp);

 }

 template <class T>
 bool Myhastable<T>::isSame(byte* pData, byte* pkey)
 {
	 return memcmp(pData, pkey, 20) == 0;
 };

 template<class T>
 inline bool Myhastable<T>::Add(byte* mykey1, T pvalue)
 {
	// return 1;
	 byte* p = (byte*)&pvalue;
	 return Add(mykey1, p);
 }