#pragma once
#include "PathORAM.h"
class OldPathORAM
{
public:
	OldPathORAM();
	~OldPathORAM();
};

class PathORAM2
{
private:
	int leafs;
	int L;
	int Z = 4;
public:
	PathORAM2(int m_L);
	PathORAM2* pos_map;
	DataBlock ReadDataFromStash(int a, bool bFirst);
	void WriteStash(int a, bool bFirst, DataBlock& data, int pos);
	//读取一个节点
	int read(int a, bool bFirst);
	void write(int a, bool bFirst, int v);
	string P(int x, int l);
	Bucket ReadBucket(int x, int l);
	void WriteBucket(int x, int l, Bucket bkt);
	void access(string op, int a, bool bFirst, DataBlock& data);
	unordered_map<string, Bucket> oram;
	unordered_map<int, ORAMBlock> stash;
};
