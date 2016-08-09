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
	char* uChar;  // ƥ�䵽���ַ�
	int iLen;
	int iWordId; // ƥ�䵽���ַ����ַ����е�λ��
	int spec_flag;

};

struct TrieNode                      //Trie�ṹ���ڵ�
{
	bool isNode =false;
	struct TrieNode* nextptr[MAX];
};

class TrieMatch
{
public:
	TrieMatch() { root = new TrieNode; for (int i = 0; i < MAX; i++) { root->nextptr[i] = NULL; } root->isNode = false; }
	~TrieMatch();
	/*��������:trie����ʼ������
	 triemdl_path��ʼ���ļ���ʽ:word<\n>*/
	int Init(const string& triemdl_path);   
	int Insert(const char* gbkWord);
	int Init(const string* init_str,int len);
	int delTrie(TrieNode* root);
	/*�������ܣ���������ӡ�洢��Trie���е������ַ�*/
	int StructTest();
	void Traverse(TrieNode* tn, int hn, const string& path_str, unsigned int strvalue);
	/*��������:ƥ��gbkStr�е��ַ�
	 ƥ�䵽���ַ�����vtWords*/
	int Match(const  char* gbkStr, int  iLen, vector<UCS_WORD>& vtWords); 
private:
	TrieNode* root;
};