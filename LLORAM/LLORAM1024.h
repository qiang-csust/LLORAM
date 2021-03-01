#pragma once
#include "LLORAM.h"

struct S1024
{
	long long blocks[1024];
};

class LLORAM1024
{
public:
	LLORAM<S1024> p;
	int m_L;
	LLORAM1024(int L);
	void write(long long addr, long long data);
	long long Read(long long addr);
	~LLORAM1024();
};

