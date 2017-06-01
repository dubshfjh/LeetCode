[LeetCode] Number of Islands II 岛屿的数量之二
 

A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land.
Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 
You may assume all four edges of the grid are all surrounded by water.

Example:

Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0
Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0
Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0
Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0
Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0
We return the result as an array: [1, 1, 2, 3]

Challenge:

Can you do it in time complexity O(k log mn), where k is the length of the positions?

并查集 解决 动态变化数组中的 连通域数目问题(无向图中的连通域；有向图中的强连通域)
并查集 
    1. 检测元素是否在集合中
    2. 集合求并集
    3. 检测无向图中是否有环

public class Main {
    Map<Integer,Integer> father;
    int[] size;
    public int find(int x){
        //查找x所在 group的老大哥
        int bigFather = father.get(x);
        while(bigFather != father.get(bigFather)){
            bigFather = father.get(bigFather);
        }
        //路径压缩：修改x所在路径上"每个节点"的parent为 所在group的老大哥 (ps:在TKW的递归版find中我误认为只修改x的parent)
        int curNode = x;
        while(curNode != father.get(curNode)){
            int curFather = father.get(curNode);
            father.put(curNode,bigFather);
            curNode = curFather;
        }
        return bigFather;
    }

    public void union(int x,int y){
        int xBigFather = find(x);
        int yBigFather = find(y);
        if(xBigFather != yBigFather){
            if(size[xBigFather] < size[yBigFather]){
                father.put(xBigFather, yBigFather);
                size[yBigFather] += size[xBigFather];
            }
            else{
                father.put(yBigFather, xBigFather);
                size[xBigFather] += size[yBigFather];
            }
        }
    }

    public List<Integer> numIslands2(int m, int n, int[][] positions) {
        father = new HashMap<Integer,Integer>();
        size = new int[m*n];
        List<Integer> res = new LinkedList<Integer>();
        Set<Integer> isLandPos = new HashSet<Integer>();
        for(int i=0;i<m*n;i++){
            father.put(i,i);
            size[i] = 1;
        }
        int tempres = 0;
        int[][] dir = {{1,0},{-1,0},{0,-1},{0,1}};
        for(int i=0;i<positions.length;i++){
            int x = positions[i][0];
            int y = positions[i][1];
            int index = x*n+y;
            isLandPos.add(index);
            tempres++;
            for(int j=0;j<4;j++){
                int neighborX = x + dir[j][0];
                int neighborY = y + dir[j][1];
                int neighborIndex = neighborX*n+neighborY;
                if(neighborX >= m || neighborY >= n || !isLandPos.contains(neighborIndex)){
                    continue;
                }

                if(find(index) != find(neighborIndex)){
                    tempres--;
                    union(index, neighborIndex);
                }
            }
            res.add(tempres);
        }
        return res;
    }

    public static void main(String[] args){
        int[][] pos = {{0,0}, {0,1}, {1,2}, {2,1}, {1,1}};
        int m = 3,n = 3;
        Main obj = new Main();
        List<Integer> res = obj.numIslands2(m, n, pos);
        for(int i:res){
            System.out.println(i);
        }
    }
}
