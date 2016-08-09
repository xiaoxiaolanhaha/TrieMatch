# TrieMatch
Match words in dict encoding by GBK From a string.
应用范围：GBK编码、ASCII编码字符串
基本功能: 匹配字符串query中属于词典（词表）词汇中的子串。

一．实现原理：词典词汇编码->词典Trie树的建立-> 待匹配字符串编码->查找匹配

二．类TrieMatch的定义和接口实现：

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
