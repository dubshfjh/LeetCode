给出 n 个节点，标号分别从 0 到 n - 1 并且给出一个 无向 边的列表 (给出每条边的两个顶点), 写一个函数去判断这张｀无向｀图是否是一棵树

 注意事项

你可以假设我们不会给出重复的边在边的列表当中. 无向边　[0, 1] 和 [1, 0]　是同一条边， 因此他们不会同时出现在我们给你的边的列表当中。

您在真实的面试中是否遇到过这个题？ Yes
样例
给出n = 5 并且 edges = [[0, 1], [0, 2], [0, 3], [1, 4]], 返回 true.

给出n = 5 并且 edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], 返回 false.

树：无环连通图！首先检测 边数==n-1，然后用并查集检测是否有环出现，如果 无环&&边数==n-1，则该图必然是连通的

public class Solution {
    /**
     * @param n an integer
     * @param edges a list of undirected edges
     * @return true if it's a valid tree, or false
     */
    int[] father;
    int[] rank;
    public int find(int x){
        int bigFather = father[x];
        while (bigFather != father[bigFather]){
            bigFather = father[bigFather];
        }

        int curNode = x;
        while (curNode != father[curNode]){
            int curFather = father[curNode];
            father[curNode] = bigFather;
            curNode = curFather;
        }
        return bigFather;
    }

    public void union(int x, int y){
        int bigFatherX = find(x);
        int bigFatherY = find(y);
        if (bigFatherX != bigFatherY){
            if (rank[bigFatherX] < rank[bigFatherY]){
                father[bigFatherX] = bigFatherY;
            }
            else {
                father[bigFatherY] = bigFatherX;
                if (rank[bigFatherX] == rank[bigFatherY]){
                    rank[bigFatherX]++;
                }
            }
        }
    }

    public boolean validTree(int n, int[][] edges) {
        // Write your code here
        if (edges.length != n - 1){
            return false;
        }
        father = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++){
            father[i] = i;
            rank[i] = 1;
        }
        for (int[] edge : edges){
            int point0 = edge[0];
            int point1 = edge[1];
            if (find(point0) == find(point1)){
                return false; //存在环
            }
            union(point0, point1);
        }
        return true;
    }
}