// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS

#include "LLORAM.h"


struct TestS
{
	int x;
	int y;
	int z;
};

void testDraw()
{
	LLORAM<TestS> oram(4);
	oram.bDebugShuffle = false;
	//for (int i = 0; i < oram.capacity; i++)
	//{
	//	printf("//write i=%d, %d \r\n", i, 100+i);
	//	oram.write(i, 100 + i);
	//	oram.dumpTree();
	//}
	printf("//write i=%d, %d \r\n", 1, 101);
	TestS s;
	s.x = 100;
	oram.write(1, s);
	oram.dumpTree();
	printf("//read i=%d, %d \r\n", 1, 101);
	TestS v=oram.read(1);
	oram.dumpTree();
	printf("v=%d", v.x);
	//oram.read(1);
	//oram.dumpTree();
	//oram.read(1);
	//oram.dumpTree();

}

struct Char20
{
	unsigned char bytes[20];
};
struct B80
{
	Mem20 m1;
	Mem20 m2;
	Char20 c1;
	Char20 c2;
};
struct R
{
	char buf[64];
};
void testSingleRound()
{
	LLORAM<__int64> oram(4);
	__int64 v = 123456789;
	oram.single_round_access("write", 2, v);
	v = 22222;
	oram.single_round_access("write", 3, v);
	v = 11111;
	//oram.single_round_access("write", 0, v);
	__int64 v2;
	oram.single_round_access("read", 2, v2);
	printf("%lld\r\n", v2);
	oram.single_round_access("read", 0, v2);
	printf("%lld", v2);



	LLORAM<R> oram3(16);
	R r1= { "abcdefg" };
	R r2 = { 0 };
	oram3.single_round_access("write", 2, r1);
	oram3.single_round_access("read", 2, r2);

}




void testLLORAMInsertSpeed()
{
	int data1 = 88888;
	for (int i = 4; i < 64; i++)
	{
		LLORAM<int> oram(i);
		for (int j = 0; j < 1024; j++)
		{
			oram.single_round_access("write", j % (oram.capacity), data1);
		}
		double t1 = time_ms();
		oram.single_round_access("write", 12345%(oram.capacity), data1);
		double t2 = time_ms();
		printf("L=%d write time=%f bandwidth=%d bytes \r\n", i, t2 - t1,oram.request_bytes);
		int data2;
		oram.single_round_access("read", 12345 % (oram.capacity), data2);
		if (data2 != data1)
		{
			printf("error!\r\n");
		}
	}
}
void testFixedSizeLLORAMInsertSpeed()
{
	int data1 = 88888;
		LLORAM<int> oram(20);
		printf("testFixedSizeLLORAMInsertSpeed:\r\n");
		for (int i = 0; i < oram.capacity; i++)
		{
			oram.single_round_access("write", i % (oram.capacity), data1);

			if ((i == 1024) || (i == 1024 * 2) || (i == 1024 * 4) || (i == 1024 * 8) || (i == 1024 * 16) || (i == 1024 * 32) || (i == 1024 * 64) || (i == 1024 * 128) || (i == 1024 * 256) || (i == 1024 * 512) || (i == 1024 * 1024) || (i == 1024 * 2048))
			{
				int data2;
				double t1 = time_ms();
				oram.single_round_access("read", i % (oram.capacity), data2);
				double t2 = time_ms();
				printf("L=%d items=%ld read time=%f bandwidth=%d bytes \r\n", 20,i, t2 - t1, oram.request_bytes);
				if (data2 != data1)
				{
					printf("error!\r\n");
				}
			}
		}
}


void testORAMResize()
{
	LLORAM<long long> p(4);
	for (int i = 0; i < p.capacity; i++)
	{
		p.write(i, i * 2);
	}
	p.SetL(63);
	long long d=99;
	p.write(3, d);
	long long e=p.read(3);
	printf("d=%ld e=%ld\r\n", d, e);

}
void testORAMResizeSpeed()
{
	int l = 4;
	LLORAM<long long> oram(l);
	int L = 64;
	for (int i = 0; i < oram.capacity; i++)
	{
		oram.write(i, i * 2);
	}
	//for (int i = 10; i < L; i++)
	//{
	//	oram.SetL(i);
	//	long long data, data2;
	//	oram.write(6, 11);
	//	data2 = oram.read(5);
	//	printf("data2=%ld\r\n", data2);
	//}
	for (int i = l+1; i < L; i++)
	{
		long long data = rand64() ;
		long long addr = rand64()%oram.capacity;
		oram.SetL(i);
		double t1 = time_ms();		
	//	oram.single_round_access("write",addr, data);
		oram.write(addr, data);
		double t2 = time_ms();
		long long data2=0;
		data2=oram.read(addr);
	//	oram.single_round_access("read", addr, data2);
		if (data != data2)
		{
			printf("error ! L=%d\r\n",i);
		}
		else
		{
			printf("OK ! L=%d\r\n", i);
		}
		printf(" L=%d read time=%lf\r\n", i,t2-t1);
	//	oram.single_round_access_complete();//需要调用这个才能洗牌
	
	}
}
void testORAMShuffer()
{
	LLORAM<long long> p(3);
	long long  v = 100;
	long long vv = 0;
//	p.single_round_access("write", 1, v);
//	p.single_round_access("read", 1, vv);
//	printf("vv=%ld", vv);
//	p.dump();
//	getchar();
	for (int i = 0; i < p.capacity; i++)
	{
		long long v2 =  2*i+100;
		//p.single_round_access("write", i, v2);
		p.write(i, v2);
	}
	
	//for (int i = 0; i < p.capacity; i++)
	//{
	//	int v2 = 0;
	//	p.access("read", i, v2);
	//	printf("read i=%d v2=%d\r\n", i, v2);
	//}
	//for (int i = 0; i < 100; i++)
	//{
	//	v = 100 + i;
	//	printf("\r\n times=%d write (2,%d)\r\n", i,v);
	//	p.access("write", 2, v);
	//	p.dump();
	//	getchar();
	//}

	//int v2;
	//p.access("read", 2, v2);
	//for (int i = 0; i < p.capacity; i++)
	//{
	//	int v2;
	//	p.single_round_access("read", i, v2);
	//	printf("%d %d\r\n", i, v2);
	//}
	//int v2;
	//p.single_round_access("read", 3, v2);
	p.dump();
	//printf("\r\n read =%d", v2);


}

void testORAMStashOverflow()
{
	int L = 20; //10 15 20 25
	LLORAM<long long> p(L);

	char mem[64] = { 0 };
	printf("%s testORAMStashOverflow start Z_block =%d: \r\n",  currentTime(mem), Z_block);
	int k = 0;
	long long accessCount = 0;
	long long e3 = 0,e4=0,e5=0,e6=0;
	for (int addr = 0; addr < p.capacity*10000; addr++)
	{
		addr = addr % p.capacity;
		long long data1 = addr;
		p.single_round_access("write", addr, data1);
		//p.single_round_access("read", j, data1);
		for(int i=1;i<=L;i++)
		{ 
			auto v = p.oram[i-1][""];
		//	int d = v.head.maps.size();
		//	printf("size=%d \r\n", d);

			int c = v.head.maps.size();//每一个map包含2个small block
			if (c >= 3)//4)//6)//Z_block
			{
				e3++;
				//printf("%s L=%d addr=%d size=%d\r\n", currentTime(mem),i, addr,c );
			}
			if (c >= 4)
			{
				e4++;
			}
			if (c >= 5)
			{
				e5++;
			}
			if (c >= 6)
			{
				e6++;
			}
			if (c >= 7)
			{
				printf("c=%d! \r\n", c);
			}
			accessCount++;
		}

		int size = p.stash_L.size();
		if(size>0)
		{ 
			printf("%s stash_L size=%d\r\n", currentTime(mem),size);
		}

		if (k++ % 10000 == 0)
		{
			printf("%s current progress: accessCount=%ld e3=%d e4=%d e5=%d e6=%d L=%d Z_block=%d k=%d\r\n", currentTime(mem), accessCount,e3,e4,e5,e6,L, Z_block,k);
		}
	}
	printf("%s Test complete \r\n", currentTime(mem));
}

void testORAMCorrectness()
{
	LLORAM<long long> p(20);
	int L = 20;

	for (int j = 0; j < p.capacity; j++)
	{
		long long data1 = j+100;
		p.single_round_access("write", j, data1);
	}
	for (int j = 0; j < p.capacity; j++)
	{
		long long data2 = j + 100;
		long long data1;
		p.single_round_access("read", j, data1);
		if (data1 != data2)
		{
			printf("error! data1=%ld data2=%ld j=%d\r\n", data1, data2, j);
		}
	}
	printf("Test complete!\r\n");
}
void ORAMDemo()
{
	LLORAM<long long> p(4);
	p.write(5, 99);
	p.dump();
	//Tree 1: "" (a = 0 d0 = 1 d1 = -1 node = 0)();
	//Tree 2: "1" ()(); "" (a = 0 d0 = -1 d1 = 5 node = 1)(); "0" ()();
	//Tree 3: "0" ()(); "11" ()(); "10" ()(); "1" (a = 1 d0 = 14 d1 = -1 node = 5)(); "" ()();
	//Tree 4: "" ()(); "110" ()(); "0" ()(); "11" (a = 2 d0 = 0 d1 = 99 node = 14)(); "10" ()(); "1" ()(); "111" ()();
}

#define Block_size_bytes 1 //1024
struct data1024
{
	long long abc[Block_size_bytes];
};

void ORAMBigBlock()
{
	//LLORAM1024 oram(10);
	//int c = pow(2, 10) *1024;
	//for (int i = 0; i < c; i++)
	//{
	//	printf("write =%ld\r\n", i);
	//	oram.write(i, i * 2);
	//}
	//long long v=oram.Read(100);
	//printf("value =%ld", v);
	LLORAM< data1024> p(15);
	data1024 data1;
	double t1 = time_ms();

	p.single_round_access("write", 1, data1);
	double t2 = time_ms();
	printf("time=%lf (ms)\r\n", (t2 - t1) );

	for (long long i = 0; i < p.capacity; i++)
	{
		data1.abc[i % Block_size_bytes] = i;
		double t3 = time_ms();
		p.single_round_access("write", i%p.capacity, data1);
		double t4 = time_ms();
		printf("height=%d i=%d time=%lf (ms) per keyword time=%lf Block_size_bytes=%d speed=%lf\r\n",p.L, i,(t4 - t3), (t4 - t3)/ (double)(Block_size_bytes), (Block_size_bytes), (double)(Block_size_bytes)/(t4-t3)*1000);
	}

	//printf("time=%lf (ms)", (t2 - t1)/10);
}
void testORAMBandwidth()
{
	LLORAM< data1024> p(12);
	data1024 data1;
	double t1 = time_ms();

	p.single_round_access("write", 1, data1);
	double t2 = time_ms();
	printf("Z_block=%d time=%lf (ms)\r\n", Z_block,(t2 - t1));

	for (long long i = 0; i < p.capacity; i++)
	{
		data1.abc[i % Block_size_bytes] = i;
		double t3 = time_ms();
		p.single_round_access("write", i%p.capacity, data1);
		double t4 = time_ms();
	//	printf("height=%d i=%d time=%lf (ms) per keyword time=%lf Block_size_bytes=%d speed=%lf\r\n", p.L, i, (t4 - t3), (t4 - t3) / (double)(Block_size_bytes), (Block_size_bytes), (double)(Block_size_bytes) / (t4 - t3) * 1000);
		printf("bandwidth=%d, height=%d i=%d time=%lf (ms) per keyword time=%lf Block_size_bytes=%d speed=%lf\r\n",p.request_bytes, p.L, i, (t4 - t3), (t4 - t3) / (double)(Block_size_bytes), (Block_size_bytes), (double)(Block_size_bytes) / (t4 - t3) * 1000);	
	}
}

//-------------------------------------------------------------------------------
//小数据块的实验，判断 空和满的时候，是否存在读写的效率差别
#define Block_size_bytes2 16 //
struct data16
{
	long long abc[Block_size_bytes2];
};
void testORAMFullWriteTime()
{
	LLORAM< data16> p(16);
	data16 data1;
	double t1 = time_ms();

	p.single_round_access("write", 1, data1);
	double t2 = time_ms();
	printf("Z_block=%d time=%lf (ms)\r\n", Z_block, (t2 - t1));

	for (long long i = 0; i < p.capacity; i++)
	{
		data1.abc[i % Block_size_bytes2] = i;
		double t3 = time_ms();
		p.single_round_access("write", i%p.capacity, data1);
		double t4 = time_ms();
		//	printf("height=%d i=%d time=%lf (ms) per keyword time=%lf Block_size_bytes=%d speed=%lf\r\n", p.L, i, (t4 - t3), (t4 - t3) / (double)(Block_size_bytes), (Block_size_bytes), (double)(Block_size_bytes) / (t4 - t3) * 1000);
		if (i < 10 || (i > p.capacity - 10) ||(i %10000==0))
		{
			printf("bandwidth=%d, height=%d i=%d time=%lf (ms) per keyword time=%lf Block_size_bytes=%d speed=%lf\r\n", p.request_bytes, p.L, i, (t4 - t3), (t4 - t3) / (double)(Block_size_bytes), (Block_size_bytes), (double)(Block_size_bytes) / (t4 - t3) * 1000);
		}
		if (i % 10000 == 0)
		{
			//printf("i=%lld \r\n", i);
		}
	}
}
//-----------------------------------
void testORAMDistribution()
{
	LLORAM<long long> p(5);
	for (int i = 0; i < p.capacity; i++)
	{
		p.write(i, i * 10);
	};
	for (int i = 0; i < 100; i++)
	{
		//int c = rand() % p.capacity;
		//p.write(c, c * 10);
		p.write(0, 99);		
		p.dump();
		getchar();
	}
	p.dump();
	//Tree 1: "" (a = 0 d0 = 1 d1 = -1 node = 0)();
	//Tree 2: "1" ()(); "" (a = 0 d0 = -1 d1 = 5 node = 1)(); "0" ()();
	//Tree 3: "0" ()(); "11" ()(); "10" ()(); "1" (a = 1 d0 = 14 d1 = -1 node = 5)(); "" ()();
	//Tree 4: "" ()(); "110" ()(); "0" ()(); "11" (a = 2 d0 = 0 d1 = 99 node = 14)(); "10" ()(); "1" ()(); "111" ()();
}
void tests()
{
	testLLORAMInsertSpeed(); getchar();
	testORAMDistribution(); getchar();
	testORAMFullWriteTime(); getchar();
	testORAMBandwidth(); getchar();
	ORAMBigBlock(); getchar();
	ORAMDemo(); getchar();
	testORAMResize(); getchar();
	testORAMResizeSpeed(); getchar();
	testORAMCorrectness(); getchar();
	testORAMStashOverflow(); getchar();
	testORAMShuffer(); getchar();
	testORAMResize(); getchar();
	testFixedSizeLLORAMInsertSpeed(); getchar();
	testSingleRound(); getchar();
}

struct TestData
{
	char helloworld[256];
	char author[256];
	char email[256];
	double version;
};
void helloworld()
{
	LLORAM<TestData> oram(10);
	TestData test = { "--------------------\r\n Hello World, LLORAM \r\n 2021/02/18\r\n--------------------\r\n","Dr. Zhiqiang wu","cxiaodiao@hnu.edu.cn", 1.0 };
	oram.write(100, test);
	TestData test2=oram.read(100);
	printf("%s Version: %.1f \r\n %s\r\n Email:%s", test2.helloworld,test2.version,test2.author,test2.email);;
}


int main()
{
	helloworld(); 
	getchar();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
