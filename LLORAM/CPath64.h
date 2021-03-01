#pragma once
#include <string>
using namespace std;
class CPath64
{
public:
	CPath64();
	CPath64(long long node_value);
	CPath64 LeftChild();
	CPath64 RightChild();
	CPath64 Sibiling();
	CPath64 Father();
	string ToString();
	string P(long long x, int l, int height);
	string AtLevelPath(int l);
	void LoadPath(string path);
	void LoadLeaf(int level,long long leaf);
	unsigned long long MapToRandomLeaf(int height);
	//映射到一个随机的叶子
	unsigned long long GetLeaf();//读取从左边开始到当前位置的位置，最左边的节点leaf=0
	unsigned long long value; //根节点value=0 ，左边 2i+1，右边2i+2
	~CPath64();
};

//Number从0开始编号 左边孩子为2*i+1，右边孩子为2*i+2
unsigned long long GetFatherNumber(unsigned long long node);
unsigned long long GetLeftChildNumber(unsigned long long node);//2*I+1
unsigned long long GetRightChildNumber(unsigned long long node);//2*I+2
string NumberToPath(unsigned long long node);
unsigned long long PathToNumber(string path);

