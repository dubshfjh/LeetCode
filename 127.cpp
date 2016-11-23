#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <unordered_set>
#include <unordered_map>

using namespace std;
参照126的解法，但是内存超限了

class Solution {
public:
    int res = 0;
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        vector<unordered_set<string>> candidates(2);
        unordered_map<string,vector<string>> pre_Map;
        for(auto iter=wordList.begin(); iter!=wordList.end(); iter++){
            vector<string> temp;
            pre_Map[*iter] = temp;
        }
        int pre = 1;
        int cur = 0;
        candidates[0].insert(beginWord);
        while(true){
            pre = !pre;
            cur = !cur;
            for(auto iter=candidates[pre].begin(); iter!=candidates[pre].end(); iter++){
                wordList.erase(*iter);
            }

            candidates[cur].clear();
            for(auto iter=candidates[pre].begin(); iter!=candidates[pre].end(); iter++){
                // string word = *iter;
                for(int pos=0;pos<(*iter).size();pos++){
                    // char before_change = word[pos];
                    string word = *iter;
                    for(int i='a';i<='z';i++){
                        if(i == word[pos]){
                            continue;
                        }

                        word[pos] = i;
                        if(wordList.count(word) > 0){
                            candidates[cur].insert(word);
                            pre_Map[word].push_back(*iter);
                        }
                        
                    }
                    // word[pos] = before_change;
                }
            }

            if(candidates[cur].size() == 0){
                return 0;
            }

            if(candidates[cur].count(endWord) > 0){
                break;
            }
        }
        generatePath(pre_Map,endWord);
        return res;
    }

    void generatePath(unordered_map<string,vector<string>> pre_Map, string word){
        if(pre_Map[word].size()==0){
            res++;
            return;
        }

        res++;
        generatePath(pre_Map,pre_Map[word][0]);//因为只需要计算ladder的长度而非存储全部ladder路径，所以直接选择word的1个前驱单词回溯即可，没必要对word的全部前驱序列递归
        return;
    }
};


最短搜索路径，所以是广度优先搜索(BFS)。
算法思想：BFS一层层地执行“对word的某位置字母替换”操作，并设置结构体记录每个节点的路径长度，因此将 beginWord 初始化长度为1的节点，节点i改变字母得到的邻居节点长度=(节点i长度+1)。一旦节点j新生成的邻居单词为 endWord 则return j.length+1，如果BFS结束还未返回则结果为0
PS:由于不需要遍历所有可能的路径(即只需要得到其中1条以上的路径即可)，因此不需要等到BFS整体进入下一层后，再禁止当前层全部节点的单词出现(即同层节点允许出现相同单词)。为了简化代码逻辑，使用bool变量直接将每次构建的新单词标记为不再可用即可

有几个问题需要注意：

1、怎样判断是否为邻居节点？

按照定义，存在一个字母差异的单词为邻居，因此采用逐位替换字母并查找字典的方法寻找邻居。

（逐个比对字典里单词也可以做，但是在这题的情况下，时间复杂度会变高，容易TLE）

2、怎样记录路径长度？

对队列中的每个单词记录路径长度。为 beginWord 初始化长度为1的节点，将其push进入队列

路径长度为i的word通过改变字母生成新的邻居节点，如果邻居单词在上层没有出现过，则邻居单词的路径长度为i+1

#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Node{
    string word;
    int len;
    Node(string a, int l): word(a), len(l) {}
};

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        queue<Node*> q;
        unordered_map<string,bool> m;//m[word]=false:代表该单词尚未在之前节点出现过，这样做会导致同层元素不会出现相同单词，虽然可能会跳过某些可能路径，但不会影响返回的最短路径长度(因为至少会走过1条路径)
        Node *start = new Node(beginWord, 1);
        q.push(start);
        m[beginWord] = true;
        while(!q.empty()){
            Node *head_node = q.front();
            q.pop();

            string head_word = head_node->word;
            //搜索其邻居节点
            for(int pos=0;pos<head_word.size();pos++){
                for(int i='a';i<='z';i++){
                    if(i == head_word[pos]){
                        continue;
                    }

                    string tempword = head_word;
                    tempword[pos] = i;

                    if(tempword == endWord){
                        return head_node->len+1;
                    }
                    if(wordList.find(tempword) != wordList.end() && m[tempword] == false){
                        Node *neighbor = new Node(tempword, head_node->len+1);
                        q.push(neighbor);
                        m[tempword] = true;
                    }
                }
            }
        }
        return 0;
    }
};
