["Trie","insert","insert","search","startsWith"]
[[],["ab"],["abc"],["ab"],["ab"]]
Trie树详解：http://blog.csdn.net/hackbuteer1/article/details/7964147(建议及时看TriNode的格式)

Trie的核心思想是空间换时间。利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的。

Trie树的基本性质可以归纳为： 
（1）根节点不包含字符，除根节点意外每个节点只包含一个字符。
（2）从根节点到某一个节点，路径上经过的字符连接起来，为该节点对应的字符串。 
（3）每个节点的所有子节点包含的字符串不相同。

Trie树有一些特性：
1）根节点不包含字符，除根节点外每一个节点都只包含一个字符。
2）从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串。
3）每个节点的所有子节点包含的字符都不相同。
4）如果字符的种数为n，则每个结点的出度为n，这也是空间换时间的体现，浪费了很多的空间。
5）插入查找的复杂度为O(n)，n为字符串长度。

基本思想（以字母树为例）：
1、插入过程
对于一个单词，从根开始，沿着单词的各个字母所对应的树中的节点分支向下走，直到单词遍历完，将最后的节点标记is_word属性为true，表示该单词已插入Trie树。
2、查询过程
查询单词：从根开始按照单词的字母顺序向下遍历trie树，一旦发现某个节点标记不存在 or 单词遍历完成但末尾节点的is_word属性为false，则表示该单词不存在
查询前缀：从上倒下遍历Trie树，一旦发现某个节点标记不存在 or 单词遍历完成但末尾节点的next数组为NULL(即末尾节点不存咋子节点)，则该前缀不存在

踩到的坑：1.刚开始使用的是struct构建TriNode，但是构造函数不知道该如何初始化next[26]中的每个元素指向NULL，
    如果不对next[i]初始化则会导致出现错误  member access within misaligned address 0x7f1e0a2fc335 for type 'TriNode *[26]', which requires 8 byte alignment
class TriNode{
public:
    //int count;//统计单词前缀出现的次数,但本题没有删除操作，所以不需要判断count
    TriNode* next[26];//指向各个子树的指针
    bool is_word;//标记该节点处是否构成单词
    TriNode(){
        is_word = false;
        memeset(next,0,sizeof(next));
    }
    //TriNode(): count(1), exist(true) {}
};

class Trie {
public:
    TriNode *root;
    /** Initialize your data structure here. */
    Trie() {
        root = new TriNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TriNode *temp = root;
        for(int i=0;i<word.length();i++){
            int index = word[i]-97;
            if(temp->next[index] == NULL){
                TriNode *node = new TriNode();
                temp->next[index] = node;
            }
            temp = temp->next[index];
        }
        // cout<<word<<",,,"<<temp->is_word<<endl;
        temp->is_word = true;//标记word的最后一个字符在Trie树中构成单词
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {//当插入单词"ab","abc"时，ab同时为word和prefix，前缀可以通过(最后一个字符->next!=NULL)来判断，但单词只能通过在插入"ab"时标记(最后一个字符->is_word为true来判断)
        TriNode *temp = findnode(word);
        if(!temp || !temp->is_word){//word的最后字符不存在 or word的最后字符只是个前缀(e.g 插入"abc"，seach word "ab"时last字符b处并未构成单词)
            return false;
        }
        return true;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TriNode *temp = findnode(prefix);
        if(!temp || !temp->next){//prefix的最后字符不存在 or prefix的last char没有指向其它字符
            return false;
        }
        return true;
    }
    
private:
    TriNode* findnode(string s){//寻找字符串s最后一个字符在Trie中的节点
        TriNode *temp = root;
        for(int i=0;i<s.length();i++){
            int index = s[i]-97;
            if(temp->next[index] == NULL){//没有删除操作，所以不需要额外判断count==0的情况
            //if(temp->next[index] == NULL || temp->next[index]->count == 0){
                return NULL;
            }
            temp = temp->next[index];
        }
        return temp;
    }
};


/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */