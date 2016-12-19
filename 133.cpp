/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
首先使用map存储原始节点node和它的复制节点clone_node之间的关系
对node递归DFS：对每个node，如果node为空则递归终止；如果map[node]已经存在(即node的复制节点在之前已经create，PS:复制节点的邻居此时不一定全部创建过了)，则直接返回map[node]，从而避免无穷次地创建同一个节点；
如果map中尚未存储node的复制节点，则首先新建一个clone_node(node->label)，然后在map中记录map[node]=clone_node，接着递归创建每一个node->neighbors，在clone_node的neighbors属性中push_back每一个node->neighbors的创建结果，最后返回clone_node
class Solution {
public:
    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> origin_clone;
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node == NULL){
            return node;
        }
        if(origin_clone.find(node) != origin_clone.end()){
            return origin_clone[node];
        }

        UndirectedGraphNode *clone_node = new UndirectedGraphNode(node->label);
        origin_clone[node] = clone_node;//一旦创建了node的clone节点，必须在访问邻居节点之前存储它与clone节点的关系，否则在遇到{0,0,0}时会创建无穷多个"0"节点(如果像被注释的代码一样先创建全部邻居：首先创建"0"，然后创建它的第1个邻居"0_1"，然后再创建"0_1"的第1个邻居"0_1_1"...)
        for(int i=0;i<node->neighbors.size();i++){
            UndirectedGraphNode *new_neighbor = cloneGraph(node->neighbors[i]);
            if(new_neighbor != NULL){
                clone_node->neighbors.push_back(new_neighbor);
            }
        }
        // origin_clone.insert(pair<UndirectedGraphNode*, UndirectedGraphNode*>(node,clone_node));
        return clone_node;
    }
};

BFS复制节点
首先使用map存储原始节点node和它的复制节点clone_node之间的关系
class Solution {
public:
    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> origin_clone;
    unordered_map<UndirectedGraphNode*, bool> visited;
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node == NULL){
            return node;
        }
        queue<UndirectedGraphNode*> q;//队列中存储原始节点！map中存储原始节点是否已经创建过clone节点
        q.push(node);
        while(!q.empty()){//BFS分析队列头的每个原始节点：如果当前节点已访问过则直接取队列next节点(PS：防止对{0#0,0}这种test case无限创建节点)。否则设置该节点已访问过，首先在map中查找它是否有clone节点，如果已有则直接获取；如果尚不存在clone则创建新节点，并在map中记录队列头与新节点的关系
            UndirectedGraphNode *temp = q.front();//然后分析原始节点的neighbor数组中每个邻居节点。如果邻居节点已存在clone则直接取出其clone节点，并push到原始节点clone的邻居列表；如果邻居节点尚不存在clone则将该节点push进入队列，接着为邻居节点创建clone节点，并记录两个节点间的关系，最后在原始节点clone的邻居列表中插入邻居的clone
            q.pop();

            if(!visited[temp]){
                visited[temp] = true;

                UndirectedGraphNode *clone_node;
                if(origin_clone.find(temp) != origin_clone.end()){    
                    clone_node = origin_clone[temp];
                }
                else{
                    clone_node = new UndirectedGraphNode(temp->label);
                    origin_clone[node] = clone_node;
                }
                for(int i=0;i<temp->neighbors.size();i++){
                    if(origin_clone.find(temp->neighbors[i]) == origin_clone.end()){
                        q.push(temp->neighbors[i]);

                        UndirectedGraphNode *new_neighbor = new UndirectedGraphNode(temp->neighbors[i]->label);
                        origin_clone[temp->neighbors[i]] = new_neighbor;
                        clone_node->neighbors.push_back(new_neighbor);
                    }
                    else{
                        clone_node->neighbors.push_back(origin_clone[temp->neighbors[i]]);
                    }
                }
            }
            
        }
        return origin_clone[node];
    }
};