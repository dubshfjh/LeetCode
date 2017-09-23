本质：求连通子图的数量，从每个取值为 1 的 grid[i][j] 出发，执行BFS搜索，每次搜索将路径上经过的 "1" 设置为 "0" 避免往回搜索路径，导致搜索出环
1. BFS 中队列应该保存图中节点的"下标"
2. 在分析邻居节点的越界情况时，一定要记得"左边界"越界！！ (neighborI <= 0 || neighborI >= rowNum) || (neighborJ <= 0 || neighborJ >= colNum)
public class Solution {
    /*
     * @param grid: a boolean 2D matrix
     * @return: an integer
     */
    public static int[][] dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    public int numIslands(boolean[][] grid) {
        // write your code here
    	if (grid == null || grid.length == 0) {
    		return 0;
    	}    
    	if (grid[0] == null || grid[0].length == 0) {
    		return 0;
    	}

    	int islandNum = 0;
    	for (int i = 0; i < grid.length; i++) {
    		for (int j = 0; j < grid[0].length; j++) {
    			if (grid[i][j] == true) {
    				search(grid, i, j);
    				islandNum++;
    			}
    		}
    	}
    	return islandNum;
    }

    public void search(boolean[][] grid, int startI, int startJ) {
    	Queue<Integer> queue = new LinkedList<Integer>();
    	queue.add(startI * grid[0].length + startJ);
    	grid[startI][startJ] = false;
    	while (!queue.isEmpty()) {
    		int curIndex = queue.poll();
    		int curI = curIndex / grid[0].length;
    		int curJ = curIndex % grid[0].length;
    // 		System.out.println(curI + "..." + curJ);
    		for (int i = 0; i < 4; i++) {
    			int neighborI = curI + dir[i][0];
    			int neighborJ = curJ + dir[i][1];
    			if (neighborI < 0 || neighborI >= grid.length || neighborJ >= grid[0].length || neighborJ < 0) {
    			    continue;
    			}
    			if (grid[neighborI][neighborJ] != true) {
    				continue;
    			} else {
    				grid[neighborI][neighborJ] = false;
    				queue.add(neighborI * grid[0].length + neighborJ);
    			}
    		}
    	}
    }
}