#include "CPath64.h"
#include <bitset>
#include "common.h"


CPath64::CPath64()
{
	value = 0;
}

CPath64::CPath64(long long v)
{
	value = v;
}

CPath64 CPath64::LeftChild()
{
	return CPath64(2*value+1);
}

CPath64 CPath64::RightChild()
{
	return CPath64(2*value+2);
}

CPath64 CPath64::Sibiling()
{
	long long father;
	long long s=0;
	father = (value - 1) / 2;
	if (value % 2 == 1) //左边的
	{
		s = 2 * father + 2;
	}
	else
	{
		s = 2 * father + 1;
	}
	return CPath64(s);
}

CPath64 CPath64::Father()
{
	return CPath64((value-1)/2);
}

string CPath64::ToString()
{
	return NumberToPath(value);
}

string CPath64::P(long long x, int l, int height)
{
	if ((l > 64) || (l < 1)||(x>pow(2,l-1)-1))
	{
		printf("error input, out of range!\r\n"); return "";
	};
	bitset<64> s = x;
	string v = s.to_string();
	return v.substr((size_t)(64 - height + 1), (size_t)(l - 1));
}
string CPath64::AtLevelPath(int l)
{
	if (l < 1) return "not support";
	string path = ToString();
	if (l > path.length()+1) return "not support";
	string p2 = path.substr(0,l-1);
	return p2;
}
void CPath64::LoadPath(string path)
{
	value = PathToNumber(path);
}

//leaf为叶子编号，最左边的叶子编号为0 level从1开始
void CPath64::LoadLeaf(int level,long long leaf)
{
	string path = P(leaf, level, level);
	value =PathToNumber(path);
}

//映射到一个随机的叶子（沿着路径往下）从1开始
unsigned long long CPath64::MapToRandomLeaf(int height)
{
	unsigned long long startLeafNode = pow(2, height-1) - 1;
//	unsigned long endLeafNode = pow(2, height) - 1;
	unsigned long long newValue = value;
	while (newValue < startLeafNode)
	{
		newValue = 2 * newValue + ((unsigned long long)rand64()) % 2+1;
	}
	return newValue - startLeafNode;//叶子的编号（从0开始）
}

unsigned long long CPath64::GetLeaf()//level从1开始
{
	string path = ToString();//将节点编号转换为字符串路径
	//path = path.substr(0, level - 1);//将路径转换为叶子的路径
	bitset<64> b(path);
	return b.to_ullong();
}


CPath64::~CPath64()
{
}

//node 从零开始编号
unsigned long long GetFatherNumber(unsigned long long node)
{
	return node/2;
}

//左边为2i+1
unsigned long long GetLeftChildNumber(unsigned long long node)
{
	return 2 * node + 1;
}

//右边为2i+2
unsigned long long GetRightChildNumber(unsigned long long node)
{
	return 2 * node + 2;	
}

string NumberToPath(unsigned long long node)
{
	string s = "";
	for (int i = 0; i < 64; i++)
	{
		if (node == 0) break;
		if (node % 2 == 1)
		{
			s =string("0")+s;
		}
		else
		{
			s=string("1")+s;
		};
		node = (node-1) / 2;

	}
	return s;
}

unsigned long long PathToNumber(string path)
{
	unsigned long long i = 0;
	for (auto a : path)
	{
		if (a == '0')
		{
			i = 2 * i + 1;
		}
		else
		{
			i = 2 * i + 2;
		}
	}
	return i;
}
