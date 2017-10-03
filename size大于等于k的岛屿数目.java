求解所有连通子图中 (节点数 >= k) 中的子图数目，每次从 1 个尚未访问过的节点出发执行 BFS, 
并返回该连通子图内的节点数目nodeNum, 从而判断该子图是否 nodeNum >= k
public class Solution {
    /*
     * @param : a 2d boolean array
     * @param : an integer
     * @return: the number of Islands
     */
    private static int[][] dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    public int numsofIsland(boolean[][] grid, int k) {
        // Write your code here
        if (grid == null || grid.length == 0) {
        	return 0;
        }
        if (grid[0] == null || grid[0].length == 0) {
        	return 0;
        }

        int bigIsland = 0;
        for (int i = 0; i < grid.length; i++) {
        	for (int j = 0; j < grid[0].length; j++) {
        		if (grid[i][j]) {
        			if (search(grid, i, j) >= k) {
        				bigIsland++;
        			}
        		}
        	}
        }
        return bigIsland;
    }

    private int search(boolean[][] grid, int startI, int startJ) {
    	Queue<Integer> queue = new LinkedList<Integer>();
    	queue.offer(getOneDimenIndex(grid, startI, startJ));
    	grid[startI][startJ] = false;
    	int nodeNum = 1;
    	while (!queue.isEmpty()) {
    		int curIndex = queue.poll();
    		int curI = curIndex / grid[0].length;
    		int curJ = curIndex % grid[0].length;
    		for (int i = 0; i < 4; i++) {
    			int neigborI = curI + dir[i][0];
    			int neigborJ = curJ + dir[i][1];
    			if (neigborI < 0 || neigborI >= grid.length || neigborJ < 0 || neigborJ >= grid[0].length) {
    				continue;
    			} else {
    				if (grid[neigborI][neigborJ]) {
    					nodeNum++;
	    				grid[neigborI][neigborJ] = false;
	    				queue.offer(getOneDimenIndex(grid, neigborI, neigborJ));
	    			}
    			}
    		}
    	}
    	return nodeNum;
    }

    private int getOneDimenIndex(boolean[][] grid, int i, int j) {
    	return i * grid[0].length + j;
    }
};