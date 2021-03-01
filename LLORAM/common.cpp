
#include "common.h"
#include "string.h"
using namespace std;
#include "windows.h"
#include "vector"
#include <unordered_map>
#include <unordered_set>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef linux
#include <unistd.h>
#include <dirent.h>
#endif
#ifdef WIN32
#include <direct.h>
#include <io.h>
#endif
using namespace std;
#include <string>  
#include <fstream>  
#include <streambuf>  
common::common()
{
}


common::~common()
{
}
#include <iostream>
#include <io.h>
#include <string>
#include <vector>
#include <bitset>

void getFiles(const std::string & path, std::vector<std::string> & files)
{
	//文件句柄
	__int64 hFile = 0;
	//文件信息，_finddata_t需要io.h头文件
	struct __finddata64_t fileinfo;
	std::string p;
	if ((hFile = _findfirst64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib & 0x10))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext64(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void getDirs(const std::string & path, std::vector<std::string> & files)
{
	//文件句柄
	__int64 hFile = 0;
	//文件信息，_finddata_t需要io.h头文件
	struct __finddata64_t fileinfo;
	std::string p;
	if ((hFile = _findfirst64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				}
				//if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) getDirs(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext64(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void split(const string& src, const string& separator, vector<string>& dest)
{
	string str  = src;
	string substring;
	string::size_type start  = 0, index;

	do
	{
		index  = str.find_first_of(separator, start);
		if (index  != string::npos)
		{
			substring  = str.substr(start, index - start);
			dest.push_back(substring);
			start  = str.find_first_not_of(separator, index);
			if (start  == string::npos) return;
		}
	} while (index  != string::npos);

	//the last token
	substring  = str.substr(start);
	dest.push_back(substring);
}


//#include <iostream>
//#include <vector>
//#include <string>
//#include <sstream>
//using namespace std;

vector<char> is_any_of(string str)
{
	vector<char> res;
	for (auto s : str)
		res.push_back(s);
	return res;
}

void split(vector<string>& result, string str, vector<char> delimiters)
{
	result.clear();
	auto start = 0;
	while (start < str.size())
	{
		//根据多个分割符分割
		auto itRes = str.find(delimiters[0], start);
		for (int i = 1; i < delimiters.size(); ++i)
		{
			auto it = str.find(delimiters[i], start);
			if (it < itRes)
				itRes = it;
		}
		if (itRes == string::npos)
		{
			result.push_back(str.substr(start, str.size() - start));
			break;
		}
		result.push_back(str.substr(start, itRes - start));
		start = itRes;
		++start;
	}
}

string ReadAllFile(char* filename)
{
	FILE* fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	size_t t=ftell(fp);
	if (t == 0)
	{
		fclose(fp);
		return "";
	}
	fseek(fp, 0, SEEK_SET);
	char* buf = (char*)malloc(t+2);
	memset(buf, 0, t+2);
	fread(buf, 1, t, fp);
	string ret = buf;
	free(buf);
	fclose(fp);
	return ret;
}


string& trim(string &s)
{
	if (s.empty())
	{
		return s;
	}
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}
/*
*去掉字符串首尾的 \x20 \r \n 字符
*/
void TrimSpace(char* str)
{
	char *start = str - 1;
	char *end = str;
	char *p = str;
	while (*p)
	{
		switch (*p)
		{
		case ' ':
		case '\r':
		case '\n':
		{
			if (start + 1 == p)
				start = p;
		}
		break;
		default:
			break;
		}
		++p;
	}
	//现在来到了字符串的尾部 反向向前
	--p;
	++start;
	if (*start == 0)
	{
		//已经到字符串的末尾了
		*str = 0;
		return;
	}
	end = p + 1;
	while (p > start)
	{
		switch (*p)
		{
		case ' ':
		case '\r':
		case '\n':
		{
			if (end - 1 == p)
				end = p;
		}
		break;
		default:
			break;
		}
		--p;
	}
	memmove(str, start, end - start);
	*(str + (int)end - (int)start) = 0;
}

string trim(const string& str,char sep)
{
	string::size_type pos = str.find_first_not_of(sep);
	if (pos == string::npos)
	{
		return str;
	}
	string::size_type pos2 = str.find_last_not_of(sep);
	if (pos2 != string::npos)
	{
		return str.substr(pos, pos2 - pos + 1);
	}
	return str.substr(pos);
}
string Trim(const string& str)
{
	string s1 = trim(str,' ');
	s1 = trim(s1, '\r');
	s1 = trim(s1, '\n');
	s1 = trim(s1, '\t');
	return s1;
}
int split(const string& str, vector<string>& ret_, string sep = ",")
{
	if (str.empty())
	{
		return 0;
	}

	string tmp;
	string::size_type pos_begin = str.find_first_not_of(sep);
	string::size_type comma_pos = 0;

	while (pos_begin != string::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return 0;
}
string replace(const string& str, const string& src, const string& dest)
{
	string ret;

	string::size_type pos_begin = 0;
	string::size_type pos= str.find(src);
	while (pos!= string::npos)
	{
	//	cout << "replacexxx:" << pos_begin << " " << pos << "\n";
		ret.append(str.data() + pos_begin, pos - pos_begin);
		ret += dest;
		pos_begin = pos + 1;
		pos= str.find(src, pos_begin);
	}
	if (pos_begin < str.length())
	{
		ret.append(str.begin() + pos_begin, str.end());
	}
	return ret;
}

#include "time.h"
char* currentTime(char* ch)
{
	time_t t = time(0);
	strftime(ch,32, "%Y-%m-%d %H:%M:%S", localtime(&t));
	return ch;
}


//单位微秒
int64_t time64()
{
#ifdef _WIN32
	// 从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
#define EPOCHFILETIME   (116444736000000000UL)
	FILETIME ft;
	LARGE_INTEGER li;
	int64_t tt = 0;
	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	// 从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)
	tt = (li.QuadPart - EPOCHFILETIME) / 10;
	return tt;
#else
	timeval tv;
	gettimeofday(&tv, 0);
	return (int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec;
#endif // _WIN32
	return 0;
}

double time_ms()
{
	LARGE_INTEGER nFreq;
	LARGE_INTEGER t1;
	double dt;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	dt = t1.QuadPart/(double)nFreq.QuadPart*1000.0;
	return dt;
}
double time_us()
{
	LARGE_INTEGER nFreq;
	LARGE_INTEGER t1;
	double dt;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	dt = t1.QuadPart / (double)nFreq.QuadPart*1000.0*1000.0;
	return dt;
}
string IntToStr(int number)
{
	char buf[16] = { 0 };
	_itoa(number, buf, 10);
	return string(buf);
}
int StrToInt(string s)
{
	return atoi((const char*)s.c_str());
}


string GetCurrentDir()
{
	char buf[256] = { 0 };
	char * p=_getcwd(buf, 256);
	return buf;
}

bool FileExists(string file)
{
	FILE *fp = fopen(file.c_str(), "r");
	if (fp)
	{
		fclose(fp);
		return true;
	}
	return false;
}

//#include <string.h>
//#include <stdlib.h>

char * strLeft(const char *src, unsigned int n)
{
	if (!src || n <= 0 || n > strlen(src))
		return NULL;

	char *retBuffer = (char *)malloc(n + 1);
	memset(retBuffer, 0, n + 1);
	strncpy(retBuffer, src, n);

	return retBuffer;
}

char * strMid(const char *src, unsigned int startIdx, unsigned int n)
{
	if (!src || startIdx < 0 || startIdx >= strlen(src) || n <= 0 || n >= strlen(src))
		return NULL;

	char *retBuffer = (char *)malloc(n + 1);
	memset(retBuffer, 0, n + 1);

	strncpy(retBuffer, src + startIdx, n);

	return retBuffer;
}



string strRight(const char *src, unsigned int n)
{
	if (!src || n <= 0 || n >= strlen(src))
		return NULL;

	char *retBuffer = (char *)malloc(n + 1);
	memset(retBuffer, 0, n + 1);

	unsigned int offset = strlen(src) - n;
	strncpy(retBuffer, src + offset, n);
	string ret(retBuffer);
	free(retBuffer);
	return ret;
}


bool getBit( int & input, const unsigned char n)
{
	return (input >> n)&1;
}
void setBit( int & input, const unsigned char n)
{
	input |= ( int)(1 << n);
}

void clearBit(unsigned int & input, const unsigned char n)
{
	input &= ~( int)(1 << n);
}

string IntToPath(int i)
{
	//bitset<32> b(i);
	int len = GetIntPathLength(i);
	int k = 0;
	char buf[32] = { 0 };
	for(int j=1;j<=len;j++)
	{
		buf[k++] = getBit(i,32-j) ? '1' : '0';		
	}
	return buf;
}
int GetIntPathLength(int i)
{
	//bitset<32> b(i);
	bool last = getBit(i,0);
	char buf[32] = { 0 };
	bool bstart = false;
	for (int j = 0; j <=31;j++)
	{
		if (getBit(i,j) != last) return (32 - j);
	}
	return 0;
}
//获取父亲节点的整型路劲
//bitset 排列是从低位到高位排列
//PATH 字符串 是从高位到低位排列
//最低位采用相同的
int GetFatherIntPath(int i)
{
	int c = GetIntPathLength(i);
	//int n = i;
	//int bit = 0;
	//bs由最低到高排列
	bitset<32> bs = i;
	for (int j = c; j <= 31; j++)
	{
		//setBit(n, bit);
		bs[32 - j+1] = bs[32 - j];
	}
	return bs.to_ulong();
}
//"01" => "0100000000000000000000000000000"
int PathToInt(string path)
{
	bitset<32> b;
	int c = path.length();
	if (c == 0) return 0;
	for (int i = 0; i < 32; i++)
	{
		if (i < c)
		{
			b[31-i] = (path[i] == '0') ? 0 : 1;
		}
		if (i >= c)
		{
			b[31-i] = ~(b[32-c]);
		}
	}
	return (int)(b.to_ulong());
}

// 001
// 0011
// 00111 
// 返回最长的 00111, 如果出现不相等的，则返回0; 如果有一个指针的长度是31，那么其他指针的长度也必须是31，否则返回0
int GetOverlapPath(vector<int> paths, vector<int>& lens,int& max,int& max_i)
{
//	if (paths.size() == 1)
//	{
//		return paths[0];
//	}
	
	int max_index = 0;
	//int max = 0;
	max = 0;
	for (int i = 0; i < paths.size(); i++)
	{
		int c = GetIntPathLength(paths[i]);
		lens.push_back(c);
		if (c > max)
		{
			max_index = i;
			max = c;
		}
	}

	//int m = paths[max_i] >> (32-lens[max_i]);

	for(int i=0;(i<paths.size());i++)
	{
		if ((paths[i] ^ paths[max_index]) >> (32 - lens[i]) )
		{
			return 0;//存在不匹配的
		}
	}
//	if (max == 31)
//	{
//		for (int i = 0; (i<paths.size()); i++)
//		{
//			if (lens[i] != 31) return 0;
//		}
//		return paths[max_i];
//	}
	return paths[max_index];
}

//从左边开始取出长度为pathLen的字符串int ，比如 1000,取出3后为 100
int PathSubStringInt(int v,int pathLen)
{
	//bitset<32> b2(v);
	bitset<32> b(v);
	bool last = b[0];
	char buf[32] = { 0 };
	bool bstart = false;
	bstart = ~b[32-pathLen];
	for (int j = 0; j < 32- pathLen; j++)
	{
		b[j] = bstart;
	}
	return (int)b.to_ulong();
}
// 001
// 0011
// 00111 
// 返回最短的 00111, 如果出现不相等的，则返回0
int GetOverlapedLongestPath(vector<int> paths)
{
	if (paths.size() == 1) return paths[0];
	vector<int> lens;
	int min_i = 0;
	int min = 1024;
	for (int i = 0; i < paths.size()  ; i++)
	{
			int c = GetIntPathLength(paths[i]);
			lens.push_back(c);
			if ((c < min)&&(c>0))//0不算
			{
				min_i = i;
				min = c;
			}
	}
	//int m = paths[min_i] >> (32 - lens[min_i]);//不带尾部标记的指针
	bool bZero = true;
	for (int j = min; j >=1; j--)
	{
		bool bAllSame = true;
		for (int i = 0; (i < paths.size()) ; i++)//从全部路径 取出非空的 逐个判断
		{
			if ( (lens[i] > 0))//(i != min_i)
			{
				bZero = false;
				if ((paths[i] ^ paths[min_i]) >> (32 - j)) //判断前面的部分是否相同
				{
					bAllSame = false;
					break;//存在不匹配的 取出子字符串返回
				}
			}
		}
		if (bAllSame&&!bZero)
		{
			//
#ifdef _DEBUG
			string debug = IntToPath(paths[min_i]);
#endif
			return PathSubStringInt(paths[min_i], j);
			//int lowBit = (m>>(min-j)) & 1;
			//if (lowBit)//低第2位为1
			//{
			//	return paths[min_i] & (-1<<(32-j));//低j位置0 取子字符串
			//}
			//else
			//{//低位为0
			//	return paths[min_i] | (~(-1 << (32-j)));//低j位置1
			//}
		}
	}
	return 0;
}


PathWithNumber GetOverlapPath(vector<PathWithNumber> paths, vector<int>& lens, int& max)
{
	//	if (paths.size() == 1)
	//	{
	//		return paths[0];
	//	}

	int max_i = 0;
	//int max = 0;
	max = 0;
	for (int i = 0; i < paths.size(); i++)
	{
		int c = GetIntPathLength(paths[i].path);
		lens.push_back(c);
		if (c > max)
		{
			max_i = i;
			max = c;
		}
	}
	//int m = paths[max_i] >> (32-lens[max_i]);

	for (int i = 0; (i<paths.size()); i++)
	{
		if ((paths[i].path ^ paths[max_i].path) >> (32 - lens[i]))
		{
			PathWithNumber pn = { 0 };
			return pn;//存在不匹配的
		}
	}
	//	if (max == 31)
	//	{
	//		for (int i = 0; (i<paths.size()); i++)
	//		{
	//			if (lens[i] != 31) return 0;
	//		}
	//		return paths[max_i];
	//	}
	PathWithNumber pn;
	pn.path = paths[max_i].path;
	pn.disjunctive_i = paths[max_i].disjunctive_i;
	pn.conjunctive_j = paths[max_i].conjunctive_j;
	return pn;
}
PathWithNumber GetOverlapedLongestPath(vector<PathWithNumber> paths, vector<int>& lens)
{
	if (paths.size() == 1) return paths[0];
//	vector<int> lens;
	int min_i = 0;
	int min = 1024;
	for (int i = 0; i < paths.size(); i++)
	{
		int c = GetIntPathLength(paths[i].path);
		lens.push_back(c);
		if ((c < min) && (c>0))//0不算
		{
			min_i = i;
			min = c;
		}
	}
	//int m = paths[min_i] >> (32 - lens[min_i]);//不带尾部标记的指针
	bool bZero = true;
	for (int j = min; j >= 1; j--)
	{
		bool bAllSame = true;
		for (int i = 0; (i < paths.size()); i++)//从全部路径 取出非空的 逐个判断
		{
			if ((lens[i] > 0))//(i != min_i)
			{
				bZero = false;
				if ((paths[i].path ^ paths[min_i].path) >> (32 - j)) //判断前面的部分是否相同
				{
					bAllSame = false;
					break;//存在不匹配的 取出子字符串返回
				}
			}
		}
		if (bAllSame && !bZero)
		{
			//
#ifdef _DEBUG
//			string debug = IntToPath(paths[min_i]);
#endif
			PathWithNumber pn;
			pn.path = PathSubStringInt(paths[min_i].path, j);
			pn.disjunctive_i = paths[min_i].disjunctive_i;
			pn.conjunctive_j = paths[min_i].conjunctive_j;
			return pn;
			//int lowBit = (m>>(min-j)) & 1;
			//if (lowBit)//低第2位为1
			//{
			//	return paths[min_i] & (-1<<(32-j));//低j位置0 取子字符串
			//}
			//else
			//{//低位为0
			//	return paths[min_i] | (~(-1 << (32-j)));//低j位置1
			//}
		}
	}
	PathWithNumber pn = { 0 };	
	return pn;
}

int GetOverlapedLongestPath(vector<int>& paths, vector<int>& lens)
{
	if (paths.size() == 1) return paths[0];
	//	vector<int> lens;
	int min_i = 0;
	int min = 1024;
	for (int i = 0; i < paths.size(); i++)
	{
		int c = GetIntPathLength(paths[i]);
		lens.push_back(c);
		if ((c < min) && (c>0))//0不算
		{
			min_i = i;
			min = c;
		}
	}
	//int m = paths[min_i] >> (32 - lens[min_i]);//不带尾部标记的指针
	bool bZero = true;
	for (int j = min; j >= 1; j--)
	{
		bool bAllSame = true;
		for (int i = 0; (i < paths.size()); i++)//从全部路径 取出非空的 逐个判断
		{
			if ((lens[i] > 0))//(i != min_i)
			{
				bZero = false;
				if ((paths[i] ^ paths[min_i]) >> (32 - j)) //判断前面的部分是否相同
				{
					bAllSame = false;
					break;//存在不匹配的 取出子字符串返回
				}
			}
		}
		if (bAllSame && !bZero)
		{
			//
#ifdef _DEBUG
			//			string debug = IntToPath(paths[min_i]);
#endif
		//	PathWithNumber pn;
		//	pn.path = PathSubStringInt(paths[min_i], j);
			return PathSubStringInt(paths[min_i], j);
			//int lowBit = (m>>(min-j)) & 1;
			//if (lowBit)//低第2位为1
			//{
			//	return paths[min_i] & (-1<<(32-j));//低j位置0 取子字符串
			//}
			//else
			//{//低位为0
			//	return paths[min_i] | (~(-1 << (32-j)));//低j位置1
			//}
		}
	}
	//PathWithNumber pn = { 0 };
	return 0;
}

int GetOverlapPath_old(vector<int> paths)
{
	vector<string> pathstring;
	for (auto p : paths)
	{
		pathstring.push_back(IntToPath(p));
	}
	string retstring;
	for (int i = 0; i < 32; i++)
	{
		bool bHasValue = false;
		char c;
		for (int j = 0; j<pathstring.size(); j++)
		{
			//
			if (pathstring[j] == "") return 0;
			if (!bHasValue && (i<pathstring[j].length()))
			{
				bHasValue = true;
				c = pathstring[j][i];
				retstring = pathstring[j];
				continue;
			}
			if (bHasValue)
			{
				if (i < pathstring[j].length())
				{
					if (pathstring[j][i] != c)
					{
						//出现不相等字符串
						return 0;
					}
				}
			}
		}
	}

	return PathToInt(retstring);
}
string BufToStr(byte* p, int len)
{
	char m[1024] = { 0 };
	for (int i = 0; i < len; i++)
	{
		sprintf(m + 3 * i, "%.2x", (char)m[i]);
	}
	return m;
}

int rand(int a, int b)
{
	return rand32() % (b - a) + a;
}
//产生count 个不重复的随机数，最大数为 max
void RandomArray(vector<int>& v, int count, int max)
{
	int* nums = new int[count];
	int d = max / count;
	for (int i = 0; i < count; i++)
	{
		int e = i*d + rand32() % d;
		nums[i] = e;
	}
	for (int i = 0; i < count; i++)
	{
		int r = rand(i, count);
		int c = nums[r];
		v.push_back(c);
		nums[r] = nums[i];
		nums[i] = c;
	}
	delete[] nums;
}
void RandomArrayWithExclusion(vector<int>& v, int count, int max,vector<int> &except)
{	
	unordered_set<int> buf;
	int* nums = new int[count];
	int d = max / count;
	for (auto& e : except)
	{
		buf.insert(e);
	}
	for (int i = 0; i < count; i++)
	{
		int e = i*d + rand32() % d;
		nums[i] = e;
	}
	for (int i = 0; i < count; i++)
	{
		int r = rand(i, count);
		int c = nums[r];
		while(1)
		{
			if (buf.find(c) == buf.end())
			{
				v.push_back(c);
				buf.insert(c);
				break;
			}
			else
			{
				c = (c+1) % max;
			}
		}
		
		nums[r] = nums[i];
		nums[i] = c;
	}
	delete[] nums;
}
string rndStr(int len)
{
	char buf[256] = { 0 };
	for (int i = 0; i < len; i++)
	{
		buf[i] = rand() % 254 + 1;
	}
	return buf;
}

int rand32()
{
	int v;
	for (int i = 0; i < 4; i++)
	{
		*((byte*)&v + i) = rand() % 256;
	}
	return v;
}

long long rand64()
{
	long long v;
	for (int i = 0; i < 8; i++)
	{
		*((byte*)&v + i) = rand() % 256;
	}
	return v;
}

void split_nonempty(vector<string>& result, string str, vector<char> delimiters)
{
	result.clear();
	auto start = 0;
	string d = "";
	unordered_map<string, bool> duplicates;//去除重复
	while (start < str.size())
	{
		//根据多个分割符分割
		auto itRes = str.find(delimiters[0], start);
		for (int i = 1; i < delimiters.size(); ++i)
		{
			auto it = str.find(delimiters[i], start);
			if (it < itRes)
				itRes = it;
		}
		if (itRes == string::npos)
		{
			d = str.substr(start, str.size() - start);
			if (!duplicates[d] && d.length() > 0)
			{
				duplicates[d] = true;
				result.push_back(d);
			}
			break;
		}
		d = str.substr(start, itRes - start);
		if (!duplicates[d] && d.length() > 0)
		{
			duplicates[d] = true;
			result.push_back(d);
		}
		start = itRes;
		++start;
	}
}


//读取一个文件的全部关键词，以空格回车换行分割，不算重复的单词
vector<string> ReadAllKeywords(string filename)
{
	vector<string> kwd;
	string txt = ReadAllFile((char*)filename.c_str());
	if (txt.length() == 0) return kwd;
	vector<char> v;
	v.push_back(' ');
	v.push_back('\r');
	v.push_back('\n');
	v.push_back('\t');
	split_nonempty(kwd, txt, v);

	return kwd;
}


void Log(const char* filename,const char* fmt, ...)
{
	FILE* fp = fopen(filename, "ab+");
	va_list args;
	va_start(args, fmt);
	vfprintf(fp,fmt, args); 
	va_end(args);
	fclose(fp);
}

