public class Leetcode547 {
    /**
     * 类似在无向图中，求连通块的数目，标准的并查集问题
     * @param M
     * @return
     */
    public int findCircleNum(int[][] M) {
        if (null == M || 0 == M.length || M.length != M[0].length) {
            return 0;
        }
        int[] parent = new int[M.length];
        for (int i = 0; i < M.length; i++) {
            parent[i] = i;
        }
        for (int i = 0; i < M.length; i++) {
            for (int j = 0; j < M[0].length; j++) {
                if (i != j && M[i][j] == 1) {
                    union(parent, i, j);
                }
            }
        }
        int result = 0;
        for (int i = 0; i < parent.length; i++) {
            if (parent[i] == i) {
                result++;
            }
        }
        return result;
    }

    /**
     * 1.找到i的“老大哥”，也就是它所在群组的Ancestor（Ancestor的parent就是它自己）
     * 2.将寻找路径上的所有节点，都修改parent 为Ancestor本身，实现下次搜索时的路径压缩
     * @param parent
     * @param i
     * @return
     */
    public int find(int[] parent, int i) {
        int ancestor = i;
        while (parent[ancestor] != ancestor) {
            ancestor = parent[ancestor];
        }
        int temp = -1;
        while (parent[i] != i) {
            temp = parent[i];
            parent[i] = ancestor;
            i = temp;
        }
        return ancestor;
    }

    public void union(int[] parent, int i, int j) {
        int ancestorI = find(parent, i);
        int ancestorJ = find(parent, j);
        if (ancestorI != ancestorJ) {
            parent[ancestorI] = ancestorJ;
        }
    }
}
