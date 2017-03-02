直接使用79题的逻辑，思想应该正确，但遇到大用例会超时
struct Node{
    char c;
    int x;
    int y;
    int next_dir;//0,1,2,3分别表示当前node下一次的前进方向为东西南北
    Node(char n_c,int n_x,int n_y): c(n_c),x(n_x),y(n_y),next_dir(0)  {}
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        map<string,bool> visit;//记录已访问的单词
        for(string s:words){
            // cout<<"string is: "<<s<<endl;
            if(!visit[s] && word_exist(board,s)){
                res.push_back(s);
            }
            visit[s] = true;
        }
        return res;
    }
    
    void resetboard(vector<vector<char>>& board, stack<Node>& stk,string s){
        int index = s.length()-1;
        while(!stk.empty()){
            // cout<<"reset: "<<stk.top().x<<",,,"<<stk.top().y<<",,,"<<s[index]<<endl;
            board[stk.top().x][stk.top().y] = s[index--];
            stk.pop();
        }
    }
    
    bool word_exist(vector<vector<char>>& board,string s){
        int row,col,index;
        row = board.size();
        col = board[0].size();
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(board[i][j] == s[0]){
                    if(s.length() == 1){//Attention!!!当s只有1个字符时，必须单独分析！！因为后面的逻辑为：当第{2...size-2}个字符匹配时continue分析next字符，当第{size-1}个字符匹配完毕时return true(假如不单独分析，当只有1个字符时，由于栈顶元素不能再走任何一步，会return false)
                        return true;
                    }
                    stack<Node> stk;
                    index = 0;
                    board[i][j] = '*';
                    stk.push(Node(s[0],i,j));//避免board[i][j]被多次使用
                    
                    while(!stk.empty()){
                        // cout<<stk.top().x<<"..."<<stk.top().y<<"..."<<board[stk.top().x][stk.top().y]<<endl;

                        if(stk.top().next_dir == 0){//本次向上走一步
                            stk.top().next_dir = 1;
                            if(stk.top().x > 0 && s[index+1] == board[stk.top().x - 1][stk.top().y]){
                                stk.push(Node(s[++index], stk.top().x-1, stk.top().y));
                                if(index == s.length()-1){
                                    resetboard(board,stk,s);
                                    return true;
                                }
                                board[stk.top().x][stk.top().y] = '*';
                                continue;
                            }
                        }

                        if(stk.top().next_dir == 1){//本次向下
                            stk.top().next_dir = 2;//下次向左
                            if(stk.top().x < row-1 && s[index+1] == board[stk.top().x+1][stk.top().y]){
                                stk.push(Node(s[++index], stk.top().x+1, stk.top().y));
                                if(index == s.length()-1){
                                    resetboard(board,stk,s);
                                    return true;
                                }
                                board[stk.top().x][stk.top().y] = '*';

                                continue;
                            }
                        }

                        if(stk.top().next_dir == 2){//本次向左
                            stk.top().next_dir = 3;
                            if(stk.top().y > 0 && s[index+1] == board[stk.top().x][stk.top().y-1]){
                                stk.push(Node(s[++index],stk.top().x,stk.top().y-1));
                                if(index == s.length()-1){
                                    resetboard(board,stk,s);
                                    return true;
                                }
                                board[stk.top().x][stk.top().y] = '*';
                                continue;
                            }
                        }

                        if(stk.top().next_dir == 3){//本次向右
                            stk.top().next_dir = 4;
                            if(stk.top().y < col-1 && s[index+1] == board[stk.top().x][stk.top().y+1]){
                                stk.push(Node(s[++index],stk.top().x,stk.top().y+1));
                                if(index == s.length()-1){                                                                        resetboard(board,stk,s);
                                    return true;
                                }
                                board[stk.top().x][stk.top().y] = '*';
                                continue;
                            }
                        }
                        // cout<<"original: "<<s[index]<<endl;
                        board[stk.top().x][stk.top().y] = stk.top().c;
                        stk.pop();
                    }
                }
            }
        }
        return false;
    }
};


使用Trie树！！
//将words存入Trie树后，对于board从每个[i][j]出发，如果[i][j]为特意设置的'*'，则说明当前[i][j]为本次路径延伸已访问的节点，需要回退一步；如果board[i][j]字符对应本层递归node的NULL子节点，则也需要回退一步
    //遵循上下左右四个方向在Trie树中延伸到[i-1][j],[i+1][j],[i][j-1],[i][j+1]对应的节点，如果路径延伸时遇到了is_word=true的叶子节点，则当前路径对应words中的1个单词
    //(因此为Trie树的叶节点设计属性index，保存该叶节点对应words中第index个单词)，在遍历完4个方向搜索Trie树后将board[i][j]从'*' reset为初始字符，然后回退到上一步
class Solution {
    class Trie{
    public:
        Trie* children[26];//指向以'a'-'z'开始的substring
        bool is_leaf;//判断以字符是否为某个word的停止字符
        int index;//如果叶节点，则存储其对应单词在words数组的下标
        Trie(){
            is_leaf = false;
            index = 0;
            memset(children,NULL,26*sizeof(Trie*));
        }
    };
public:
    int row;
    int col;
    void insertWords(Trie *node,vector<string>& words, int index){//将word[index]插入Trie树中
        int pos,len;
        len = words[index].size();
        for(pos = 0;pos < len;pos++){
            if(!node->children[words[index][pos] - 'a']){
                node->children[words[index][pos]-'a'] = new Trie();
            }
            node = node->children[words[index][pos] - 'a'];
        }
        node->is_leaf = true;
        node->index = index;
    }

    Trie* buildTrie(vector<string>& words){
        Trie *root = new Trie();
        for(int i=0;i<words.size();i++){
            insertWords(root,words,i);
        }
        return root;
    }
    
    void checkwords(vector<vector<char>>& board,int i,int j,Trie *node,vector<string>& res,vector<string>& words){
        char temp;
        if(board[i][j] == '.'){//本条路径延伸至已访问节点，需要回退一步
            return;
        }
        if(!node->children[board[i][j] - 'a']){//路径走到board[i][j]时遇到NULL节点，说明words中没有包含这条路径作为prefix的单词
            return;
        }
        else{
            temp = board[i][j];
            if(node->children[ temp-'a' ]->is_leaf){//如果temp节点为Trie树叶节点，则说明当前路径对应words中的一个单词
                res.push_back(words[node->children[temp-'a']->index]);
                node->children[temp-'a']->is_leaf = false;//避免此次的word今后再次被当作新的word
            }
            board[i][j] = '.';//避免分析本条路径时再次回到本节点

            if(i > 0){
                checkwords(board,i-1,j,node->children[temp-'a'],res,words);
            }
            if(i < row-1){
                checkwords(board,i+1,j,node->children[temp-'a'],res,words);
            }
            if(j > 0){
                checkwords(board,i,j-1,node->children[temp-'a'],res,words);
            }
            if(j < col-1){
                checkwords(board,i,j+1,node->children[temp-'a'],res,words);
            }

            board[i][j] = temp;//reset当前位置的字符
        }
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        row = board.size();
        if(row == 0){
            return res;
        }
        col = board[0].size();
        int wordnum = words.size();
        if(col == 0 || wordnum == 0){
            return res;
        }

        Trie *root = buildTrie(words);
        for(int i=0;i<row;i++){
            for(int j=0;j<col && res.size()<wordnum;j++){//当从棋盘的每个[i][j]出发的路径都延伸完毕/words中的每个元素都已经出现在路径里，则返回res
                checkwords(board,i,j,root,res,words);
            }
        }
        return res;
    }
};