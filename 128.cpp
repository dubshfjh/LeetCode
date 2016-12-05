并查集介绍： http://blog.csdn.net/dm_vincent/article/details/7655764，
并查集模型：首先给定一个节点set,然后输入了一组整数对{(4,3),(3,8)}等等，每对整数(a,b)代表这a,b节点是连通的。同时，对于已经处于连通状态的两个节点c、d，直接忽略整数对(c,d)
建模思路：
    简单而直观的假设是，对于连通的所有节点，我们可以认为它们属于一个组，因此不连通的节点必然就属于不同的组。随着Pair的输入，我们需要首先判断输入的两个节点是否连通。如何判断呢？
    按照上面的假设，我们可以通过判断它们属于的组，然后看看这两个组是否相同，如果相同，那么这两个节点连通，反之不连通。
    为简单起见，我们将所有的节点以整数表示，即对N个节点使用0到N-1的整数表示。
    而在处理输入的Pair之前，每个节点必然都是孤立的，即他们分属于不同的组，可以使用数组来表示这一层关系，数组的index是节点的整数表示，而相应的值就是该节点的组号了。
    该数组可以初始化为：for(int i=0;i<size;i++){ group[i]=i; }，即对于节点i初始化它的组号为自己的value。
    初始化完毕之后，对该动态连通图有几种可能的操作：
    1.查询节点属于的组
        数组对应位置的值即为组号
    2.判断两个节点是否属于同一个组
        分别得到两个节点的组号，然后判断组号是否相等
    3.连接两个节点，使之属于同一个组
        分别得到两个节点的组号，组号相同时操作结束，不同时，将其中的一个节点的组号换成另一个节点的组号
    4.获取group的数目
        初始化为节点的数目，然后每次成功连接两个节点之后，递减1
    /*
    public class UF
    {
        private int[] id; // access to component id (site indexed)
        private int count; // number of components
        public UF(int N)
        {
            // Initialize component id array.
            count = N;
            id = new int[N];
            for (int i = 0; i < N; i++)
                id[i] = i;
        }
        public int count()
        { return count; }
        public boolean connected(int p, int q)
        { return find(p) == find(q); }
        public int find(int p)
        { return id[p]; }
        public void union(int p, int q)
        { 
            // 获得p和q的组号
            int pID = find(p);
            int qID = find(q);
            // 如果两个组号相等，直接返回
            if (pID == qID) return;
            // 遍历一次，改变组号使他们属于一个组
            for (int i = 0; i < id.length; i++)
                if (id[i] == pID) id[i] = qID;
            count--;
        }
    }
     */
Quick Union优化：
    如何将节点以更好的方式组织起来，组织的方式有很多种，但是最直观的还是将组号相同的节点组织在一起，想想所学的数据结构，什么样子的数据结构能够将一些节点给组织起来？常见的就是链表，图，树，什么的了。但是哪种结构对于查找和修改的效率最高？
    毫无疑问是树，因此考虑如何将节点和组的关系以树的形式表现出来。
 
    如果不改变底层数据结构，即不改变使用数组的表示方法的话。可以采用parent-link的方式将节点组织起来，
    举例而言，group[p]的值就是p节点的父节点的序号，如果p是树根的话，group[p]的值就是p，因此最后经过若干次查找，
    一个节点总是能够找到它的根节点，即满足group[root] = root的节点也就是组的根节点了，然后就可以使用根节点的序号来表示组号。
    所以在处理一个pair的时候，将首先找到pair中每一个节点的组号(即它们所在树的根节点的序号)，
    如果属于不同的组的话，就将其中一个根节点的父节点设置为另外一个根节点，相当于将一颗独立的树==>另一颗独立的树的子树。

    在实现上，和之前的Quick-Find只有find和union两个方法有所不同：
    /*
    private int find(int p)
    { 
        // 寻找p节点所在组的根节点，根节点具有性质id[root] = root
        while (p != id[p]) p = id[p];
        return p;
    }
    public void union(int p, int q)
    { 
        // Give p and q the same root.
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot) 
            return;
        id[pRoot] = qRoot;    // 将一颗树(即一个组)变成另外一课树(即一个组)的子树
        count--;
    }
     */

本题的算法思想：采用QuickUnion的概念，设置节点的group数组，以及记录分组tree中节点数目的数组size(PS：只需要记录size[root]即可)。
对每个节点node(取值为nums[i])，初始化其分组group[node] = node，size[node] = 1。然后遍历数组中的每个nums[i]，因为题目要得到Consecutive Sequence，
对应到并查集模型中就是：存在连线{(nums[i],nums[i]-1) , (nums[i],nums[i]+1)}，即每个nums[i]与自己的左右邻居都是相邻的。
因此，对于每个nums[i]，如果nums数组中包含nums[i]-1，则Union(nums[i],nums[i-1])；如果nums数组中包含nums[i]+1，则Union(nums[i],nums[i+1])

思想太过僵化：并查集基本应用，结果正确，但是时间复杂度为O(a*n)，导致了超时
class Solution {
public:
    map<int,int> group;
    map<int,int> size;
    int res = 0;
    int find_group(int node){
        //寻找node节点所在group的根节点，只有根节点具有性质 node == group[node]
        while(node != group[node]){
            node = group[node];
        }
        return node;
    }

    void union(int p,int q){
        //将表示p和q所属树的root node设置为一致
        int p_root = find_group(p);
        int q_root = find_group(q);
        if(p_root == q_root){
            return;
        }
        group[p_root] = q_root;
        size[q_root] += size[p_root];
        res = max(res,size[q_root]);
    }

    int longestConsecutive(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            group.insert(pair<int,int>(nums[i],nums[i]));
            size.insert(pair<int,int>(nums[i],1));
        }

        for(int i=0;i<nums.size();i++){
            int node = nums[i];
            if(group.count(node-1) > 0){
                union(node,node-1);
            }
            if(group.count(node+1) > 0){
                union(node,node+1);
            }
        }
        return res;
    }
};

想法一：wrong
用01数组代表该数字是否存在序列中，化归为：一个01序列中，最长连续1的问题。
小数据上可以，但是大数据测试上遇到了问题，当数据跨度很大，比如INT_MIN~INT_MAX时，空间复杂度太高。

想法二：wrong
用map代替数组实现上面的想法，可以解决空间复杂度问题。
但是在计算最长连续1的过程中发现新的问题，遍历INT_MIN~INT_MAX的时间复杂度太高。

Solution:
对num数组中的元素分别向左/向右延伸 连续子序列 (左邻居={nums[i]-1,nums[i]-2,...}；右邻居={nums[i]+1,nums[i]+2,...})，如果(左右邻居都包含在nums中 && 左右邻居未访问过 && INT_MIN<=左右邻居<=INT_MAX)，则{标记左右邻居已访问过；继续向左/向右延伸一次}，并将consequent序列长度++。
PS：visit记录元素是否已访问的意义：当元素[j]在其之前的某个元素[j-a]向右延伸子序列时访问过，即 visit[[j]]=true时，不应该再对[j]尝试向左/向右延伸了
e.g. nums为{1,3,4}，在对元素"3"向左延伸时，nums中不包含左邻居"3-1= 2"，停止向左延伸；向右延伸时，nums包含右邻居"2+1= 3"，标记"3"为已访问，再延伸一次发现nums中不包含"3+1= 4"，停止向右延伸
然后分析元素"4"，元素"4"向左延伸得到的连续序列[3,4] 包含在 (元素"3"左连续子序列 并 右连续子序列)中，向左延伸无意义；该元素向右延伸得到的连续序列 包含在 (元素"3"右连续子序列)中。
因此元素"4"的左/右延伸没有意义，应该跳过它分析nums中的下一个元素

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int res = 0;
        unordered_map<int,bool> visit;//因为元素取值可能接近 INT_MAX，所以使用map数组记录元素，visit[nums[i]]记录元素是否已被访问过，一旦元素[j]在其之前的元素[j-a]的延伸连续序列中访问过，则[j]的左右延伸序列都包含在了[j-a]的延伸序列中
        for(int i=0;i<nums.size();i++){
            visit[nums[i]] = false;
        }

        for(int i=0;i<nums.size();i++){
            if(visit[nums[i]] == false){
                visit[nums[i]] = true;
                int size = 1;//size记录连续子序列的长度

                int left_neighbor = nums[i]-1;
                while(visit.find(left_neighbor)!=visit.end() && visit[left_neighbor] == false && left_neighbor>=INT_MIN){
                    visit[left_neighbor] = true;//左邻居的左/右延伸连续序列 必然为 [i]延伸连续序列的子集，所以不需要再分析左邻居的延伸情况了 
                    size++;
                    left_neighbor--;   
                }

                int right_neighbor = nums[i]+1;
                while(visit.find(right_neighbor)!=visit.end() && visit[right_neighbor] == false && right_neighbor<=INT_MAX){
                    visit[right_neighbor] = true;//右邻居的左/右延伸连续序列 必然为 [i]延伸连续序列的子集，所以不需要再分析右邻居的延伸情况了 
                    size++;
                    right_neighbor++;
                }

                res = max(res,size);
            }
        }
        return res;
    }
};