采用记忆化搜索策略，[i][j]：记忆从该点出发的 最长上path的长度，只要对[i][j]执行过1次dfs，则必然得到全局最优解
1. 从每个点出发搜索最长递增path，但由于记忆化搜索导致每个点只计算1次，所以时间复杂度O(n^2)
2. 如果当前节点的 记忆数组[i][j] != init_value，则直接返回 记忆数组[i][j]，因此记忆数组 必须定义为 1次dfs就能计算得到全局最优解
3.1 使用分治法，先分离：记录(4个邻居中 {没有越界 && >=当前元素}) 递归返回的最优解，
3.2 再merge：从[i][j]出发递增path的最大长度 = 1 + MAX(从上下左右 4个邻居出发的递增path的最大长度)
public class Solution {
	int maxLen;
	int[][] fromNodeLen; //采用记忆化搜索策略，[i][j]：记忆从该点出发的 最长上path的长度，只要对[i][j]执行过1次dfs，则必然得到全局最优解
    int[][] dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //上下左右 4个方向
    public int longestIncreasingPath(int[][] matrix) {
        if (matrix.length == 0) {
        	return 0;
        }
        maxLen = 1;
        fromNodeLen = new int[matrix.length][matrix[0].length];
        for (int i = 0; i < matrix.length; i++) {
            for (int  j = 0; j < matrix[0].length; j++) {
                helpSearch(matrix, i, j); //从每个点出发搜索最长递增path，但由于记忆化搜索导致每个点只计算1次，所以时间复杂度O(n^2)
            }
        }
        return maxLen;
    }

    private int helpSearch(int[][] matrix, int i, int j) { //curLen + 1代表递子路径的长度
    	if (fromNodeLen[i][j] != 0) { //记忆化搜索模板！！！
    		return fromNodeLen[i][j];
    	}
    	int curMaxLen = 1;
    	for (int[] direction : dirs) {
    		int neighborX = i + direction[0];
    		int neighborY = j + direction[1];
    		if (neighborX < 0 || neighborX >= matrix.length || neighborY < 0 || neighborY >= matrix[0].length
    		 || matrix[neighborX][neighborY] <= matrix[i][j]) { //如果邻居越界 or [邻居] <= 当前元素
    			continue;
    		}
    		curMaxLen = Math.max(curMaxLen, 1 + helpSearch(matrix, neighborX, neighborY)); //分治法
    	}
    	//从[i][j]出发递增path的最大长度 = 1 + MAX(从上下左右 4个邻居出发的递增path的最大长度)
    	fromNodeLen[i][j] = curMaxLen;
    	maxLen = Math.max(maxLen, curMaxLen);
        // System.out.println(i + " , " + j + " : " + curMaxLen);
    	return curMaxLen;
    }
}