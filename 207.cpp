Hints:
This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
Topological sort could also be done via BFS.

粗糙的思想(时间复杂度直接上天)：使用vector<map>/list<map>来存放每个node的邻接点，然后使用bfs/dfs检测是否有任何点能回到自身...DFS的递归方法中可以加入参数map<int> path来存放之前的路径


http://blog.csdn.net/dm_vincent/article/details/7714519
拓扑排序思想：对一个有向无环图G进行拓扑排序，是将G中所有顶点排成一个线性序列，使得图中任意一对顶点u和v，若边(u,v)∈E(G)，则u在线性序列中出现在v之前
即由某个集合上的一个偏序（自反、反对称、传递）得到该集合上的一个全序（自反、对称、传递），这个操作称之为拓扑排序。
    E.g. 不是所有的有向图都能够被拓扑排序：选修课程A要求先选B和C，而选修B又要求先选A。在这种情况下，就无法进行拓扑排序，因为它中间存在互相依赖的关系，从而无法确定谁先谁后。
    在有向图中，这种情况被描述为存在环路。因此，一个有向图能被拓扑排序的充要条件就是它是一个DAG(有向无环图)

偏序/全序关系：
偏序和全序实际上是离散数学中的概念。
这里不打算说太多形式化的定义，形式化的定义教科书上或者上面给的链接中就说的很详细。
 
还是以上面选课的例子来描述这两个概念。假设我们在学习完了算法这门课后，可以选修机器学习或者计算机图形学。这个或者表示，学习机器学习
    和计算机图形学这两门课之间没有特定的先后顺序。因此，在我们所有可以选择的课程中，任意两门课程之间的关系要么是确定的(即拥有先后关系)
    要么是不确定的(即没有先后关系)，绝对不存在互相矛盾的关系(即环路)。以上就是偏序的意义，
    抽象而言，有向图中两个顶点之间不存在环路，至于连通与否，是无所谓的。所以，有向无环图必然是满足偏序关系的。
 
理解了偏序的概念，那么全序就好办了。所谓全序，就是在偏序的基础之上，有向无环图中的任意一对顶点还需要有明确的关系
    (反映在图中，就是单向连通的关系，注意不能双向连通，那就成环了)。可见，全序就是偏序的一种特殊情况。
    回到我们的选课例子中，如果机器学习需要在学习了计算机图形学之后才能学习(可能学的是图形学领域相关的机器学习算法……)，
    那么它们之间也就存在了确定的先后顺序，原本的偏序关系就变成了全序关系。

Kahn算法：
摘一段维基百科上关于Kahn算法的伪码描述：

L← Empty list that will contain the sorted elements
S ← Set of all nodes with no incoming edges
while S is non-empty do
    remove a node n from S
    insert n into L
    for each node m with an edge e from n to m do (n->m)
        remove edge e from the graph
        if m has no other incoming edges then
            insert m into S

if graph has edges then（当有cycle导致存在多余边时，cycle上的每个节点永远都不会满足no incoming edge，所以它们不会进入s，而只有s中node的出edge才会被remove）
    return error (graph has at least onecycle)
else 
    return L (a topologically sortedorder)

每次从该集合中取出(没有特殊的取出规则，随机取出也行，使用队列/栈也行，下同)一个顶点，将该顶点放入保存结果的List中。
紧接着循环遍历由该顶点引出的所有边，从图中移除这条边，同时获取该边的另外一个顶点，如果该顶点的入度在减去本条边之后为0，
    那么也将这个顶点放到入度为0的集合中。然后继续从集合中取出一个顶点…………
    当集合为空之后，检查图中是否还存在任何边，如果存在的话，说明图中至少存在一条环路。不存在的话则返回结果List，此List中的顺序就是对图进行拓扑排序的结果。



基于DFS的拓扑排序：
除了使用上面直观的Kahn算法之外，还能够借助深度优先遍历来实现拓扑排序。这个时候需要使用到栈结构来记录拓扑排序的结果。
同样摘录一段维基百科上的伪码：
L ← Empty list that will contain the sorted nodes
S ← Set of all nodes with no outgoing edges(无出edge的node集合)
for each node n in S do
    visit(n) 
function visit(node n)
    if n has not been visited yet then
        mark n as visited
        for each node m with an edge from m to n do (m->n)
            visit(m)
        add n to L

下面简单证明一下它的正确性：(对于每个node而言，只有当每个指向node的节点i都visit完毕并加入L后，node本身才加入L，因此在有向无环如图DAG中L就是拓扑排序序列)
考虑任意的边v->w，当调用dfs(v)的时候，有如下三种情况：
1. dfs(w)还没有被调用，即w还没有被mark，此时会调用dfs(w)，然后当dfs(w)返回之后，dfs(v)才会返回
2. dfs(w)已经被调用并返回了，即w已经被mark
3（DAG中不可能发生）. dfs(w)已经被调用但是在此时调用dfs(v)的时候还未返回

需要注意的是，以上第三种情况在拓扑排序的场景下是不可能发生的，因为如果情况3是合法的话，就表示存在一条由w到v的路径。
而现在我们的前提条件是由v到w有一条边，这就导致我们的图中存在环路，从而该图就不是一个有向无环图(DAG)，
而我们已经知道，非有向无环图是不能被拓扑排序的。



Solution 1: Kahn算法
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

        int i;
        for(i=0;i<numCourses;i++){//挑选n轮，每次都应该找到一个 出度==0的顶点
            if(no_outcoming.size() == 0){
                break;
            }
            int cur_node = no_outcoming.front();//区分front返回value，begin返回iterator
            //cout<<"无出度点: "<<cur_node<<endl;

            // vector<int> node_index = ;
            for(int index:node_edgeindex[cur_node]){
                //cout<<"被移除边的下标: "<<index<<"，from点的下标：";
                int from = prerequisites[index].first;
                if(--node_outdgree[from] == 0){
                    cout<<from<<endl;
                    no_outcoming.push_back(from);
                    //cout<<"无出度列表的尾部点："<<no_outcoming.back()<<endl;
                }
                // prerequisites.erase(prerequisites.begin()+index);虽然在算法思想中要求执行：移除指向node的边。问题1：edge对应的index是prerequisites未执行erase操作时记录的，
                //随着erase操作的执行，vector<pair>中每个元素的下标是动态变化的，所以这句话不能完成所需功能
                //问题2：由于这个操作真正的要求是对边的fromnode的出度--，如果只将“是否存在拓扑排序”的判断条件修改为(res.size()==n/i==n)，则不一定要死板地移除edge
            }
            no_outcoming.pop_front();

        }

        return i == numCourses;
    }
};


Since pair<int, int> is inconvenient for the implementation of graph algorithms, we first transform it to a graph.
 If course u is a prerequisite of course v, we will add a directed edge from node u to node v.


Solution 2:BFS(搬运了别人的code,它的原意说的是分析indegree，但实际上为了简化计算，它分析的却都是outdegree(但in/out_degree both work!!!)：
    在n轮循环中，每轮都应该找到一个out_degree==0的node，并且对每个m->node的节点m的outdgree--)
BFS uses the indegrees of each node. We will first try to find a node with 0 indegree. If we fail to do so, there must be a cycle 
    in the graph and we return false. Otherwise we have found one. We set its indegree to be -1 to prevent from visiting it again 
    and reduce the indegrees of all its neighbors by 1. This process will be repeated for n (number of nodes) times. 
    If we have not returned false, we will return true.

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

DFS(在面对1000规模的testcase时 timelimit exceeds!)

For DFS, it will first visit a node, then one neighbor of it, then one neighbor of this neighbor... and so on. If it meets a node which was visited 
    in the current process of DFS visit, a cycle is detected and we will return false. Otherwise it will start from another unvisited node and repeat this process 
    till all the nodes have been visited. Note that you should make two records: 
        one is to record all the visited nodes and the other is to record the visited nodes in the current DFS visit.

The code is as follows. We use a vector<bool> visited to record all the visited nodes and another vector<bool> onpath to record 
    the visited nodes of the current DFS visit. Once the current visit is finished, we reset the onpath value of the starting node to false.
/*
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>> graph = makeGraph(numCourses,prerequisites);
        vector<bool> visited(numCourses,false),onpath(numCourses,false);//visited标记之前所有在dfs中访问过的节点
        //onpath通过bool标记一次dfs路径上的节点是否被访问，递归每回退一步都需要reset当前node的onpath为false
        for(int i=0;i<numCourses;i++){
            if(!visited[i] && dfs_cycle(i,graph,visited,onpath)){//一次dfs遍历一个branch
                return false;
            }
        }
        return true;
    }

private:
    vector<unordered_set<int>> makeGraph(int n, vector<pair<int,int>>& edges){
        vector<unordered_set<int>> graph(n);
        for(int i=0;i<edges.size();i++){//dfs：从一个node出发向下延伸路径，延伸到尽头后退一步再尝试延伸；所以此时需要为每个入节点保存对应的出节点列表
            graph[edges[i].first].insert(edges[i].second);
        }
        return graph;
    }

    bool dfs_cycle(int node,vector<unordered_set<int>> graph,vector<bool> visited,vector<bool> onpath){
        //由于在进入dfs时就检测过visited[i]，所以下面的visited[node]检测是没有意义的。
        // if(visited[node]){//在一个branch中递归分析的每个node，初始visited[node]都为false
        //     return false;
        // }
        visited[node] = onpath[node] = true;
        for(int neighbor:graph[node]){
            // cout<<node<<",,,"<<neighbor<<endl;
            if(onpath[neighbor] || dfs_cycle(neighbor, graph,visited,onpath)){//如果邻居在本次路径中已经出现过/递归分析邻居能发现本次路径上的重复节点
                return true;//此时图中有cycle
            }
        }
        onpath[node] = false;
        return false;
        //可以简写为 return onpath[node] = false;
    }
};
*/