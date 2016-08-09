//#include "stdafx.h"
#include "TrieMatch.h"

TrieMatch::~TrieMatch()
{
	delTrie(root);
}
int TrieMatch::Init(const string& triemdl_path)          //triemdl_path初始化文件格式:word<\n>
{
	FILE* fp;
	errno_t err;
	if (err= fopen_s(&fp , triemdl_path.c_str(),"r")!=0)
	{
		fprintf(stderr, "the file %s is not exist\n", triemdl_path.c_str());
		return -1;
	}
	char szBuff[1024];
	while (fgets(szBuff, 1024, fp))
	{
		if (!strlen(szBuff)) continue;
		char* nextptr = NULL;
		char* word = strtok_s(szBuff, "\n", &nextptr);
		if (word == NULL) continue;
		Insert(word);
		
	}
	fclose(fp);
	return 0;
}
int TrieMatch::Init(const string* init_str,int len)
{
	//fprintf(stderr, "begin to init the triemdl\n");
	if (!len) return -1;
	for(int i=0;i<len;i++)
	{
		if (!init_str[i].size())
			continue;

		Insert(init_str[i].c_str());

	}
	return 0;
}
int TrieMatch::delTrie(TrieNode* root)   //Trie树空间释放
{
	if (root)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (root->nextptr[i] != NULL)
				delTrie(root->nextptr[i]);
		}
		delete root;
	}
	return 0;
}
/*函数功能：遍历并打印存储在Trie树中的所有字符*/
int TrieMatch::StructTest()
{
	if (root == NULL)
		return -1;
	int tree_hn = 0;
	string path_str = "";
	Traverse(root,tree_hn,path_str,0);
	return 0;
}
void TrieMatch::Traverse(TrieNode* tn,int hn,const string& path_str,unsigned int strvalue)
{
	
	hn++;
	if(tn->isNode && hn%2 ==1)
	{
		fprintf(stderr, "the uChar:%s\n", path_str.c_str());
	}
	for (unsigned int i = 0; i < MAX; i++)
	{
		if (tn->nextptr[i] == NULL)
		{
			continue;
		}
		unsigned int str_value = i;
		string path_tmp;
		if (hn %2 == 0 && hn !=0)
		{
			char tmp_str = (strvalue<< 4) + i;
			path_tmp = path_str + tmp_str;
		}
		else
		{
			path_tmp = path_str;
		}
		Traverse(tn->nextptr[i],hn,path_tmp,str_value);
	}
	return;
}
int TrieMatch::Insert(const char* gbkWord)   //插入词汇gbkWord
{
	if (root == NULL || gbkWord == NULL ||strlen(gbkWord) ==0)
		return -1;
	TrieNode* trie_nd = root;
	int charact_h, charact_l;
	for (int i = 0; i < strlen(gbkWord); i++)
	{
		charact_h = (gbkWord[i] & 0xF0) >> 4;    //获取字节高4位
		charact_l = gbkWord[i] & 0x0F;             //获取字节低4位
		if ((trie_nd->nextptr[charact_h] == NULL))
		{
			TrieNode* new_node = new TrieNode;
			for (int item = 0; item < MAX; item++)
			{
				new_node->isNode = false;
				new_node->nextptr[item] = NULL;
			}
			trie_nd->nextptr[charact_h] = new_node;
		}
		trie_nd = trie_nd->nextptr[charact_h];
		if (trie_nd->nextptr[charact_l] == NULL)
		{
			TrieNode* new_node = new TrieNode;
			for (int item = 0; item < MAX; item++)
			{
				new_node->isNode = false;
				new_node->nextptr[item] = NULL;
			}
			trie_nd->nextptr[charact_l] = new_node;
		}
		trie_nd = trie_nd->nextptr[charact_l];
	}
	trie_nd->isNode = true;

	return 0;
}
/*函数功能:匹配gbkStr中的字符
匹配到的字符放入vtWords*/
int TrieMatch::Match(const  char* gbkStr, int  iLen, vector<UCS_WORD>& vtWords)
{
	int charact_h, charact_l;
	if (root == NULL || gbkStr == '\0')
		return -1;
	TrieNode* trie_nd = root;

	int i = 0;
	int begin = 0;
	int end = 0;
	int hanzi_pos;
	if (gbkStr[begin] > 0x81 && gbkStr[begin] < 0xFE)
		hanzi_pos = 2;
	else
		hanzi_pos = 1;
	while (i <= iLen)
	{
		charact_h = (gbkStr[i] & 0xF0) >> 4;         //获取字节高4位
		charact_l = gbkStr[i] & 0x0F;                 //获取字节低4位
		if (trie_nd->isNode)
		{
			end = i;
		}
		if (trie_nd->nextptr[charact_h] == NULL)
		{
			if (begin < end)
			{
				UCS_WORD new_word;
				new_word.iLen = end - begin;
				new_word.iWordId = begin;
				new_word.uChar = new char[end - begin+1];
				strncpy(new_word.uChar, gbkStr + begin, end - begin);
				new_word.uChar[end - begin] = '\0';
				//fprintf(stderr, "the uChar:%s\n", new_word.uChar);
				vtWords.push_back(new_word);
				begin = end; i = begin;
			}
			else
			{
				begin += hanzi_pos;
				i = begin; end = begin;
			}
			if (gbkStr[begin] > 0x81 && gbkStr[begin] < 0xFE)
				hanzi_pos = 2;
			else
				hanzi_pos = 1;
			trie_nd = root; continue;
		}
		trie_nd = trie_nd->nextptr[charact_h];
		if (trie_nd->nextptr[charact_l] == NULL)
		{
			if (begin < end )
			{
				UCS_WORD new_word;
				new_word.iLen = end - begin;
				new_word.iWordId = begin;
				new_word.uChar = new char[end - begin+1];
				strncpy(new_word.uChar,gbkStr + begin, end - begin);
				new_word.uChar[end - begin] = '\0';
				//fprintf(stderr, "the uChar:%s\n", new_word.uChar);
				vtWords.push_back(new_word);
				begin = end; i = begin;
			}
			else
			{
				begin += hanzi_pos;
				i = begin; end = begin;
			}
			if (gbkStr[begin] > 0x81 && gbkStr[begin] < 0xFE)
				hanzi_pos = 2;
			else
				hanzi_pos = 1;
			trie_nd = root; continue;
		}
		trie_nd = trie_nd->nextptr[charact_l];
		i++;
	}
	return 0;
}