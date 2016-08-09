#pragma once
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MAX 16

struct UCS_WORD {
	UCS_WORD()
	{
		spec_flag = 0;
	}
	char* uChar;  // 匹配到的字符
	int iLen;
	int iWordId; // 匹配到的字符在字符串中的位置
	int spec_flag;

};

struct TrieNode                      //Trie结构树节点
{
	bool isNode =false;
	struct TrieNode* nextptr[MAX];
};

class TrieMatch
{
public:
	TrieMatch() { root = new TrieNode; for (int i = 0; i < MAX; i++) { root->nextptr[i] = NULL; } root->isNode = false; }
	~TrieMatch();
	/*函数功能:trie树初始化建立
	 triemdl_path初始化文件格式:word<\n>*/
	int Init(const string& triemdl_path);   
	int Insert(const char* gbkWord);
	int Init(const string* init_str,int len);
	int delTrie(TrieNode* root);
	/*函数功能：遍历并打印存储在Trie树中的所有字符*/
	int StructTest();
	void Traverse(TrieNode* tn, int hn, const string& path_str, unsigned int strvalue);
	/*函数功能:匹配gbkStr中的字符
	 匹配到的字符放入vtWords*/
	int Match(const  char* gbkStr, int  iLen, vector<UCS_WORD>& vtWords); 
private:
	TrieNode* root;
};