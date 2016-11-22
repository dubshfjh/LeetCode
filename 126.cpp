#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <unordered_set>
using namespace std;

算法正确性未去验证，因为思想跑偏了（未利用 unordered_set类似于map的find等特性 ）
以下的思想：每次递归延长一次梯子直到本层的 beginWord与endWord 的距离为1时停止，对于每一层都遍历当前剩余的字典，尝试将每个距离为1的单词作为下一层梯子，并从字典中移除被选单词后进入下一层
明显缺陷：题目中的输入字典为 unordered_set，说明字典的size肯定大的逆天，对字典的每个单词backtrace后的时间复杂度明显是作大死。
思路转换：应该在第i层递归，对本层梯子word的第i个字母用'a' to 'z'进行替换，如果新产生的单词能在字典中find到，则进入下一层；如果新产生的单词就是 endWord，则递归就停止。
class Solution {
public:
    int ladder_length=INT_MAX;
    vector<vector<string>> res;
    int count_dif(string a,string b){
        int count=0;
        for(int i=0;i<a.length();i++){
            if(a[i]!=b[i]){
                count++;
            }
            return count;
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        int size = wordList.size(); 
        if(size==0){
            return res;
        }
        vector<string> temp;
        temp.push_back(beginWord);
        find_ladder(beginWord,endWord,temp,wordList);
        return res;
    }

    void find_ladder(string beginWord,string endWord,vector<string> temp,unordered_set<string> &wordList){
        if(count_dif(beginWord,endWord) == 1){
            temp.push_back(endWord);
            if(ladder_length > temp.size()){
                res.clear();
                ladder_length = temp.size();
                res.push_back(temp);
            }
            else if(ladder_length == temp.size()){
                res.push_back(temp);
            }
            return;
        }

        if(wordList.size()==0){
            return;
        }
        unordered_set<string>::iterator it;
        for(it=wordList.begin();it!=wordList.end();it++){
            if(count_dif(beginWord,*it)==1){
                temp.push_back(*it);
                wordList.erase(it);
                find_ladder(*it,endWord,temp,wordList);
                wordList.insert(*it);
                temp.pop_back();
            }
        }
    }
};

PS:Judge Small没有问题。Judge Large不幸超时。代码参见：http://www.tuicool.com/articles/BRJZBv

最直接的DFS想法是从start开始，对每个字母位置从'a'到'z'尝试替换。如果替换字母后的单词在字典中，将其加入路径，然后以新单词为起点进行递归调用，否则继续循环。每层递归函数终止的条件是end出现或者单词长度*26次循环完毕。end出现时表示找到一个序列，对比当前最短序列做相应更新即可。

处理过程中需要注意的主要有几点：

不能相同字母替换，如hot第一个位置遍历到h时不应该处理。否则就会不断的在hot上死循环。因此在替换后前要做一次检查。

我们要找的是最短的转换方案，所以转换序列不应该出现重复的单词。否则组合将会有无数多种，如例子中的["hit","hot","dot","dog","dot","dog","dog",....."cog"]。这里我们可以使用一个unordered_set容器来保存某次一次替换序列中已出现过的单词，也可以每次使用std:find去搜索当前替换序列。如果使用unordered_set，在递归处理时，和单词序列一样，要在递归后做相应的出栈操作。

处理过程中如果发现当前处理序列长度已经超过当前最短序列长度，可以中止对该序列的处理，因为我们要找的是最短的序列。


第一次优化
观察我们的处理方法，找到可变换后的单词后，我们会马上基于它继续查找。这是一种深度优先的查找方法，即英文的DFS（Depth-first search）。这对找出答案很可能是不利的，如果一开始进入了一条很长的序列，就会浪费了时间。而广度优先BFS（Breadth-first search）的方法似乎更合适，当找到一个序列时，这个序列肯定是最短的之一。

要进行广度优先遍历，我们可以在发现替换字母后的单词在字典中时，不马上继续处理它，而是将其放入一个队列中。通过队列先进先出的性质，就可以实现广度优先的处理了。由于最后要输出的是整个转换序列，为了简单起见，我们可以将当前已转换出的序列放入队列中，即队列形式为std::vector<std::vector<std::string>>，序列的最后一个元素就是下次处理时要继续转换的单词。

使用广度优先遍历后，还有一个特性使得我们可以更方便的处理深度优先中重复单词的问题。当一个单词在某一层（一层即从第一个单词到当前单词的长度一样的序列）出现后，后面再出现的情况肯定不会是最短序列（相当于走了回头路），因此我们可以在处理完一层后直接将已用过的单词从字典中去除。需要注意的是，同一层是不能去除的，如例子中的hot在两个序列的第二层中都出现了。这样我们就需要一个容器把当前层用过的单词保存起来，等处理的层数发生变化时再将它们从字典里移除。

最后要注意的是查找结束的条件。由于找到了一个序列后该序列只是最短的之一，我们还要继续进行处理，直到队列中当前层都处理完毕。所以我们要在找到一个序列后将它的长度记录下来，当要处理的序列长度已经大于该值时，就可以结束查找了。

PS: typedef unsigned int size_t

class Solution {
public:
    vector<vector<string>> res;
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        queue<vector<string>> candidate;//candidate[i]存储了当前层次的第i条路径，在下一层时取出queue.front()，对其每个字母进行(26-1)次替换后将{queue.front(),新单词}作为新的vector加入queue之后，pop掉queue.front()
        unordered_set<string> usedWord;

        string cur_str;
        bool found_shortest = false;
        int shortest,pre_pathlen;
        shortest_len = pre_pathlen = 0;

        candidate.push({beginWord});

        while(!candidate.empty()){
            cur_str = *(candidate.front().rbegin());
            //当一个单词在某一层（一层即从第一个单词到当前单词的长度一样的序列）出现后，后面再出现的情况肯定不会是最短序列（相当于走了回头路)。需要注意的是，同一层是不能去除的，如例子中的hot在两个序列的第二层中都出现了
            if(candidate.front().size() != pre_pathlen){//使用 usedWord 把当前层用过的单词保存起来(避免自己和兄弟节点延伸路径之后走“回头路”。即再次使用本单词)。等处理的层数发生变化时（此时的队列头，和pre元素相对初始 beginWord 的路径长度不一样，说明队列头已经进入了下一层）再将它们从字典里移除
                for(auto iter=usedWord.begin(); iter!=usedWord.end(); iter++){
                    wordList.erase(*iter);
                }
            }

            //是查找结束的条件。由于找到了一个序列后该序列只是最短的之一，我们还要继续进行处理，直到队列中当前层都处理完毕。。
            if(found_shortest && candidate.front().size() >= shortest_len){//所以我们要在找到一个序列后将它的长度记录下来，当要处理的序列长度已经大于该值时，就可以结束查找了
                break;//不用继续BFS了！
            }

            for(int pos=0;pos<cur_str.size();pos++){
                char before_change = cur_str[pos];
                for(int i='a';i<='z';i++){
                    if(i == before_change){
                        continue;
                    }

                    cur_str[pos] = i;

                    if(wordList.count(cur_str) > 0){
                        usedWord.insert(cur_str);

                        if(cur_str == endWord){//因为是BFS，而且在之前的校验语句  队列头.size() >= shortest_len时并未跳出
                            res.push_back(candidate.front()) //因此要么未出现最短路径，要么最短路径由 cur_str的同层元素构建出来
                            res.rbegin()->push_back(endWord);//需要在路径末尾补充一个 endWord
                            
                            found_shortest = true;
                            shortest_len = res.rbegin()->size();
                        }
                        else{
                            vector<string> newpath(candidate.front());
                            newpath.push_back(cur_str);

                            candidate.push(newpath);
                        }
                    }
                }
                cur_str[pos] = before_change;//对队列头第pos个字母尝试了26-1次字母替换后，将第pos个字母reset，尝试替换队列头的下一个字母
            }
            //将本层队列头可以构成的新path全部push进入了queue
            if(!candidate.empty()){
                pre_pathlen = candidate.front().size();
                candidate.pop();
            }
        }
        return res;
    }
};


再次优化：
使用邻接列表
在继续优化之前，我们先来学习一个图论中的概念 - 邻接列表（Adjacency List）。具体细节可以参见这篇wiki： http://en.wikipedia.org/wiki/Adjacency_list 。
简单来说，这是一个存储图中每个顶点的所有邻接顶点的数据结构。如无向图：

       a

   /       \

b    ---    c

它的邻接列表为：

a => b, c

b => a, c

c => a, b

具体到本问题，我们可以发现，start到end的所有序列，就是一个这些序列中所有单词为点组成的图。如果我们生成了该图的邻接列表，就可以不断的在每个单词的邻接列表里找到转换的下一个单词，从而最终找到end。
那么，我们首先要对字典里的单词生成邻接列表：遍历字典里的单词，针对每个单词用前面逐字母替换的方法找出邻接单词，并保存起来。这里使用一个unordered_map <string ,unordered_set <string>>来保存邻接列表。

有了邻接列表，寻找序列的方法就发生变化了。我们不再逐个替换字母，而是从start出发，遍历start的邻接顶点，将邻接顶点放入队列中。并重复操作直到队列为空。

还有一个发生变化的地方是去重操作。由于不再遍历字典，现在我们发现非同层出现重复的单词就跳过它而不是从字典里删去。



下面再介绍一种更快的解决方案，思路及代码来自 niaokedaoren的博客 。

前一个解决方案虽然能通过大数据集测试，但是为了保存路径信息我们额外引入了一个结构体而且因为需要用到指针使用了大量的new操作。还有什么不用保存所有路径信息的办法？

niaokedaoren的方案中使用了一个前驱单词表，即记录每一个单词的前驱单词是哪些。这样在遍历完毕后，我们从end出发递归就能把所有路径生成出来。

但是由于前驱单词表不能记录当前的层次信息，似乎我们没法完成去重的工作。这个方案的巧妙之处就在于它没有使用我们通常的队列保存待处理的单词，一个单词一个单词先进先出处理的方法，

而是使用两个vector来模拟队列的操作。我们从vector 1中遍历单词进行转换尝试，发现能转换的单词后将其push_back放入vector 2中。当vector 1中的单词处理完毕后即为一层处理完毕，它里面的单词就可以从字典里删去了。
接着我们对vector 2进行同样处理，如此反复直到当前处理的vector中不再有单词。

我们发现vector 1和vector 2在不断地交换正处理容器和待处理容器的身份，因此可以通过将其放入一个二维数组中，每次循环对数组下标值取反实现vector1 和 vector2的数组切换：

//算法思想总结：
1. 记录单词的前驱序列，使用变量 prev_map记录word-->前驱单词列表(即能够变换到word的单词列表)
2. 使用unordered_set的数组 candidate[0,1][]用来模拟queue实现BFS遍历字典，设置两个下标pre(1->0->1...切换)和cur(0->1->0...切换)
3. 初始化 candidate[0]的值为{beginWord}。每次先切换cur与pre的值，然后将candidate[pre][i]通过变换字母诞生的新单词word_1，存放到candidate[cur]里面，并将word_1 insert到 prev_map[word]这个unordered_set的位置上(位置基于word的hash值)
4. 循环直到本层对[prev]遍历产生的新单词中出现了 endWord，即 candidate[current].count(endWord)>0 或者 本次的遍历无法再生成新单词了，即candidate[current].size() == 0
5. 获得了从 beginWord出发的整体前驱单词列表后，调用递归算法获得每个word的生成路径(将 endWord作为初始输入)。递归思想：将当前word前驱序列中的每个单词作为下层递归中的word，直到某层递归中prev_map[word].size()==0，这说明当前的word不是由任何其它单词变换而来，则说明它就是beginWord，将其push_back到path里面，然后整体reverse后生成真实路径

int current = 0; //vector[current]用来存放[previous]中每个单词变化生成的新单词，它在vector 2和vector 1来回切换
int previous = 1;

循环
current = !current;
previous = !previous;
......
循环结束

#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <unordered_set>
using namespace std;
class Solution {
public:
    vector<vector<string>> res;
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        res.clear();
        unordered_map<string, vector<string>> prev_map;//word-->前驱单词列表(即能够变换到word的单词列表)
        for(auto iter=wordList.begin(); iter!=wordList.end(); iter++){
            vector<string> temp;
            prev_map[*iter] = temp;
        }

        vector<unordered_set<string>> candidate(2);
        int current = 0; //vector<current>表示当前分析的数组，它在vector1和vector2来回切换
        int previous = 1;
        candidate[current].insert(beginWord);

        while(true){
            current = !current;
            previous = !previous;

            for(auto iter=candidate[previous].begin(); iter!=candidate[previous].end(); iter++){
                wordList.erase(*iter);
            }

            candidate[current].clear();

            for(auto iter=candidate[previous].begin(); iter!=candidate[previous].end(); iter++){
                for(int pos=0;pos<iter->size();pos++){
                    string word = *iter;
                    for(int i='a';i<='z';i++){
                        if(word[pos] == i){
                            continue;
                        }

                        word[pos]=i;

                        if(wordList.count(word) > 0){
                            prev_map[word].push_back(*iter);
                            //unordered_set容器是一个存储无重元素的关联容器，容器中的元素无特别的次序关系。该容器允许基于值地快速元素检索。
                            candidate[current].insert(word);//unordered_set 内部，元素不会按任何顺序排序，而是通过元素值的 hash 值将元素分组放置到各个槽（Bucket，也可译成“桶”）中，这样就能通过元素值快速地访问各个对应的元素
                        }
                    }
                }
            }

            if(candidate[current].size() == 0){//说明[previous]里面的每个单词都无法通过变换字母构建出新单词，此时res应该为空
                return res;
            }

            if(candidate[current].count(endWord) > 0){//一旦本层出现了路径，则只有这些路径为最短，直接跳出循环并且输出它们即可
                break;
            }
        }

        vector<string> path;
        generate_path(prev_map, path, endWord);
        return res;
    }


    void generate_path(unordered_map<string, vector<string>>& prev_map, vector<string>& path, const string& word){//构建能够到达word的所有单词路径
        if(prev_map[word].size() == 0){//如果当前的word不是由任何其它单词变换而来，则说明它就是beginWord，将其push_back到path里面，然后整体reverse后生成真实路径
            path.push_back(word);

            vector<string> cur_path = path;
            reverse(cur_path.begin(), cur_path.end());
            res.push_back(cur_path);

            path.pop_back();
            return;
        }

        path.push_back(word);
        for(auto iter=prev_map[word].begin(); iter!=prev_map[word].end(); iter++){
            generate_path(prev_map, path, *iter);
        }
        path.pop_back();
    }
};