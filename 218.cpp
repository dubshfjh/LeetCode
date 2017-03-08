General idea:

Step 1:

Use a multimap (存储每条edge的左右端点的高度，coords的key为x坐标，value为高度) to sort all boundary points(存储 边界点 的高度). 
    对于 interval 的起始点, let the height be positive; 
    对于 interval 的终止点, let the height be negative. 实际上每条edge的终止点 不会影响 水平线左侧节点 的结果，因此将终止点的高度设置为 负数 用作标记，
        当在coords中遇到val为负数的点时(代表该点为边界点)，就可以从multiset变量 height中移除取值为 当前边界点高度 的全部数据
             (ps:当前高度的 俯瞰线 左边界点已经找到，而且这个高度不会再诞生 俯瞰线的左边界点，原因见 step2)
    Time complexity: O(n log n)

Step 2:

Use a multiset (rather than a heap/priority_queue，变量名为height，存储覆盖了 每个边界点的 多个rectangle的高度，为每个边界点取对应多个rectangle的最大高度，存入map变量corner) to maintain the current set of heights to be considered.
     对于新遇到的 起始点, insert the height into the set, 
     otherwise, delete the height.(实际上就是当分析到 某条边的终止点时，说明当前高度的 俯瞰线 左边界点已经找到，今后不需要再分析这个高度了
        原因：与终止点取 相同高度 的 other边界点 会与pre rectangle相连，于是这些边界点不会作为俯瞰线的 左边界点出现，因此这个高度不会再诞生 俯瞰线的左边界点了 )

     The current max height is the back() element of the multiset. (由于之前每分析到edge的右边界点都会移除该高度的所有边，所以在分析了当前边界点后，此时有序集合 height 的整体最大值就是覆盖当前边界点的rectangles的max高度)
     For each point, the time complexity is O(log n). The overall time complexity is O(n log n).

Step 3:

Delete the points with equal heights. Time: O(n)  e.g. 当找到边界点集合为 [2 3], [4 5], [7 5], [11 5],时，应该将每个相同高度的边界点合并为 最左侧的 那个：[2,3], [4,5]
 
class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        //Step 1
        multimap<int,int> coords;
        for(const vector<int> it: buildings){
            coords.emplace(it[0], it[2]);
            coords.emplace(it[1], -it[2]);
        }

        //Step 2
        multiset<int> heights = { 0 };//初始化最大高度0，这是为了最后一条位于X轴上的俯瞰图左节点能够有纵坐标
        map<int,int> corners;//key：俯瞰图水平线左边界点的X坐标；val:y坐标
        for(const pair<int,int>& coordinate:coords){
            if(coordinate.second > 0){
                heights.insert(coordinate.second);
            }
            else{
                heights.erase(heights.find(-coordinate.second));
            }
            int cur_maxy = *(heights.rbegin());
            corners[coordinate.first] = cur_maxy;
        }

        //Step 3
        function<bool(pair<int,int> left, pair<int, int> right)> equals = [](pair<int, int> left, pair<int,int> right){
            return left.second == right.second;
        };

        vector<pair<int,int>> res;
        unique_copy(corners.begin(), corners.end(), back_insert_iterator<vector<pair<int,int>>>(res), equals);
        return res;
        
    }
};