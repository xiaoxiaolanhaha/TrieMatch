# TrieMatch
Match words in dict encoding by GBK From a string.
应用范围：GBK编码、ASCII编码字符串
基本功能: 匹配字符串query中属于词典（词表）词汇中的子串。

一．实现原理：词典词汇编码->词典Trie树的建立-> 待匹配字符串编码->查找匹配
编码举例:
如词典中有词汇 string word =”ab”; 按照每4个位编码转换：
Int charact_high = (word[i]&0xF0) >>4;
Int charact_low = (word[i]&0x0F);
每个字符取高4字符位和低字符位，”ab”可表示为整型数组int word_char[4]={6,1,6,2};
词典Trie树的建立：
该方案中，由于按照每4个位编码，因此，每个单位变换出的整型数<16.因此，Trie节点next指针数组大小为16. 以简单的词典”ab”(6,1,6,2),”ed”(6,5,6,4)”xh”(7,8,6,8)为例，建立的trie结构如图所示：
匹配：
如上图所示，按照Trie树中所指示的路径进行字符串匹配的判断，可以大大减少搜索时间。如判断字符串query中是否包含abc，只查看a开头的字符后面是否有路径b->c就可以了,其他的词典子串都可以不管。
二．类TrieMatch的定义和接口实现：
/函数功能：初始化字典，构建Trie树
Init_str: 用于初始化的字符串数组 len:字符串数组长度
成功输出非0/
int Init(const string* init_str,int len);
/函数功能：遍历Trie树中存储的所有字符串，用于检测词典是否正确插入
Trie中只有根节点输出 -1/
int StructTest();
/Trie树中插入一个词gbkWord
int Insert(const char* gbkWord);
/函数功能：字符串匹配，该函数也是主要的函数接口
将字符串gbkStr中属于词典中的词加入vtWords，vtWords中保存该词的位置信息和词汇信息。/
int Match(const  char* gbkStr, int  iLen, vector<UCS_WORD>& vtWords);
三．使用举例：
Const string numbers[]= {"Ⅰ","Ⅱ","Ⅲ","Ⅳ","Ⅴ","Ⅵ","Ⅶ","Ⅷ",\
"Ⅸ","Ⅹ","Ⅺ","Ⅻ","ⅩⅢ","ⅩⅣ","ⅩⅤ","ⅩⅥ"};
TrieMatch trie_mdl;
int trie_len = sizeof(numbers)/ sizeof(string);
if (-1 == trie_mdl.Init(numbers, trie_len))
{
		fprintf(stderr, "the init is error\n");
		return -1;
}
string query_test1 = "罗马数字文档第Ⅴ篇第ⅩⅢ页";
vector<UCS_WORD> vtCup;
trie_mdl.Match(query_test3.c_str(), query_test3.size(), vtCup);
for (int i = 0; i < vtCup.size(); i++)
{
		fprintf(stderr, "the uChar test:%s\n", vtCup[i].uChar);
}
输出：
The uChar test:Ⅴ
The uchar test:ⅩⅢ
