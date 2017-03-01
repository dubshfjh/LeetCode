//借鉴他人思路，为了统一return false的集中不同情况：1.某个s[i]不存在，即Trie树中node[s[i]-'a']为NULL，
            // 2.s[i]抵达Trie树终点，e.g：Trie树中为"abc"，寻找"abcd"  3.s[i]为'.'，但遍历了当前node的全部存在子树都找不到完整的s。
            // 于是综合一下每层递归的逻辑：迭代分析s剩余的所有字符，1.s[i]不为'.'时直接将node下移到node->next[s[i]-'a'] ，一旦遇到node==NULL时就跳出循环
            // 2. s[i]为'.'时，尝试对node递归分析26种不同子树(即用backup备份node后，将node下移到backup->next[j]，由于s...s+i都已匹配，下层递归只需分析s+i+1之后的字符)，如果当前node的某个子树返回true，则本层也返回true;如果26个子树都返回false，则本层返回false
            // 当跳出for循环后(1.本层递归的s[i]都匹配 2.中间出现node==NULL的情况)，如果此时代表最后一个字符的node 存在 && node->is_word，则return true;
class TriNode{
public:
    bool is_word;
    TriNode* next[26];
    TriNode(){
        is_word = false;
        memset(next,NULL,26*sizeof(TriNode*));
    }
};

class WordDictionary {
public:
    TriNode *root;
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TriNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TriNode *temp = root;
        for(char c:word){
            int index = c - 'a';
            if(temp->next[index] == NULL){
                TriNode *node = new TriNode();
                temp->next[index] = node;
            }
            temp = temp->next[index];
        }
        temp->is_word = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return help_search(root,word.c_str());
        // return query(word.c_str(),root);
    }
    
    bool help_search(TriNode *node,const char* s){//传递char*类型的参数，比string类型的参数能减少运行时间
        TriNode *temp = node;
        for(int i=0;s[i];i++){//为了减少递归次数，对于能够直接匹配的非'.'字符直接向后匹配，只有在遇到'.'字符时才递归分析本层Trie树的26种不同子树
            if(temp){
                if(s[i] != '.'){
                    temp = temp->next[s[i]-'a'];
                }
                else{
                    TriNode *backup = temp;
                    for(int j=0;j<26;j++){
                        temp = backup->next[j];
                        if(help_search(temp, s+i+1)){
                            return true;
                        }
                    }
                    return false;
                }
            }
            else{
                break;
            }
        }
        return temp && temp->is_word;
    }
};


/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */