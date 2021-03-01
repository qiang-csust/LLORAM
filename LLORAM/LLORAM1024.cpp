#include "LLORAM1024.h"



LLORAM1024::LLORAM1024(int L)
{
	m_L = L;
	p.SetL(L);
}

void LLORAM1024::write(long long addr, long long value)
{
	long long a = addr / 1024;
	long long b = addr - a * 1024;
	S1024 data1;
	p.single_round_access("read", a, data1);
	data1.blocks[b] = value;
	p.single_round_access("write",a, data1);
}

long long LLORAM1024::Read(long long addr)
{
	long long a = addr / 1024;
	long long b = addr - a * 1024;
	S1024 data1;
	
	p.single_round_access("read", a, data1);
	long long ret = data1.blocks[b];
	return ret;
}


LLORAM1024::~LLORAM1024()
{
}
