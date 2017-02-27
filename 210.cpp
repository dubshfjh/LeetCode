首先应该使用一个vecotr<set<int>>变量graph，graph[i]用set记录所有指向节点i的节点index。再使用vector<int> outdgree记录每个节点的出度
执行n轮移除操作（遍历outdgree寻找取值为0的节点），每次移除一个outdgree为0的node（将outdgree[node]置为-1，避免对当前node的重复分析），并从set中取出所有指向node的from节点，执行 outdgree[from]--
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        list<int> no_outcoming;//存放无出度的node
        vector<int> node_outdgree(numCourses,0);
        vector<vector<int>> node_edgeindex(numCourses,vector<int>());
        //当移除outdgree为0的点node时，需要同时删除指向node的所有边，用vector记录指向node的 所有edge 在prerequisites 中的下标
        for(int i=0;i<prerequisites.size();i++){
            int from = prerequisites[i].first;
            int to = prerequisites[i].second;    
            node_outdgree[from]++;
            node_edgeindex[to].push_back(i);
        }

        for(int i=0;i<node_outdgree.size();i++){
            // cout<<"i的出度："<<node_outdgree[i]<<endl;
            if(node_outdgree[i] == 0){
                no_outcoming.push_back(i);
            }
        }

        vector<int> res;
        for(int i=0;i<numCourses;i++){//挑选n轮，每次都应该找到一个 出度==0的顶点
            if(no_outcoming.size() == 0){
                break;
            }
            int cur_node = no_outcoming.front();//区分front返回value，begin返回iterator
            cout<<"无出度点: "<<cur_node<<endl;

            res.push_back(cur_node);
            // vector<int> node_index = ;
            for(int index:node_edgeindex[cur_node]){
                cout<<"被移除边的下标: "<<index<<"，from点的下标：";
                int from = prerequisites[index].first;
                if(--node_outdgree[from] == 0){
                    cout<<from<<endl;
                    no_outcoming.push_back(from);
                    cout<<"无出度列表的尾部点："<<no_outcoming.back()<<endl;
                }
                // prerequisites.erase(prerequisites.begin()+index);虽然在算法思想中要求执行：移除指向node的边。问题1：edge对应的index是prerequisites未执行erase操作时记录的，
                //随着erase操作的执行，vector<pair>中每个元素的下标是动态变化的，所以这句话不能完成所需功能
                //问题2：由于这个操作真正的要求是对边的fromnode的出度--，如果只将“是否存在拓扑排序”的判断条件修改为(res.size()==n/i==n)，则不一定要死板地移除edge
            }
            no_outcoming.pop_front();

        }

        if(res.size() < numCourses){
            res.clear();
        }
        return res;
    }
};

再次看看205题别人的代码！！！别总是只记住自己的辣鸡算法啊=。=
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>> graph = makeGraph(numCourses,prerequisites);//graph[i]为set<int>，存放每个指向i的节点j(即j->i)
        vector<int> out_degree = compute_degree(graph);
        int i,j;
        for(i=0;i<numCourses;i++){//每次取出一个当前outdegree为0的节点j,并，如果graph为DAG，则所有节点
            for(j=0;j<numCourses;j++){
                if(!out_degree[j]){
                    break;
                }
            }

            if(j == numCourses){//n次循环中有找不到outdegree==0的node，剩下的node集合都位于cycle上(也可以认为n轮每次都能找到一个indgree==0的node)
                return false;
            }
            out_degree[j] = -1;//避免之后的循环再认为j的out_degree为0
            for(int neighbor:graph[j]){//edge为：neighbor->j
                out_degree[neighbor]--;
            }
        }
        return true;//n次循环都能找到一个outdegree==0的node
    }

private:
    vector<unordered_set<int>> makeGraph(int n,vector<pair<int,int>>& edges){
        vector<unordered_set<int>> graph(n);
        for(auto it:edges){
            graph[it.second].insert(it.first);//记录每个出节点对应edge的入节点，用于计算每个node的out_degree
        }
        return graph;
    }

    vector<int> compute_degree(vector<unordered_set<int>> graph){
        vector<int> out_degree(graph.size(),0);
        for(int i=0;i<graph.size();i++){
            for(int neighbor:graph[i]){//edge为：neighbor->i
                out_degree[neighbor]++;
            }
        }
        return out_degree;
    }
};