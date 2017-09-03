将每个(i, j)当做出发点DFS搜索上下左右4个邻居，将 (i * 列数 + j) 作为当前节点的唯一id，
1. 利用HashSet将"检测DFS Path上是否已经有当前节点"的时间复杂度优化到 O(1)，整体的时间复杂度为 O(n^2 * 4 * word.length())
2. reuse visit这个HashSet，将visit使用的空间复杂度控制在 O(word.length())

算法流程：在dfs递归的每一层
1. 判断当前节点(i, j)是否越界，越界则返回 false
2. 检查(i, j)对应的唯一标识是否已经在 visit 中出现过，如果 dfs Path 出现了环，则返回 false
3. 检查(i, j)对应字符 == word.charAt("已经匹配长度")，为了避免visit频繁pop，只在word中尚有字符未匹配时，
	才将当前(i, j)加入visit，因此"word已经匹配长度" = visit.size()
4. 如果第 3 步匹配，则检查 word 是否已经匹配了所有字符，如果是则不需要再更新 visit，直接返回 true
5. 如果还存在字符未匹配完毕，则 Visit 中添加(i, j)；然后上下左右 4 个方向 dfs；在返回上一层时 从 Visit 中移除(i, j) 
public class Solution {
    /**
     * @param board: A list of lists of character
     * @param word: A string
     * @return: A boolean
     */
    private int[][] dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    public boolean exist(char[][] board, String word) {
        // write your code here
        if (board == null || board.length == 0 || board[0].length == 0) {
        	return false;
        }
        if (word.length() == 0) {
        	return true;
        }
		Set<Integer> visit = new HashSet<>(); //利用HashSet将"检测DFS Path上是否已经有当前节点"的时间复杂度优化到O(1)
        for (int i = 0; i < board.length; i++) {
        	for (int j = 0; j < board[0].length; j++) {
        		// List<Integer> path = new LinkedList<>();
        		if (search(board, word, i, j, visit)) {
        			return true;
        		}
        	}
        }
        return false;
    }

    private boolean search(char[][] board, String word, int i, int j, Set<Integer> visit) {
    	if (i < 0 || i >= board.length || j < 0 || j >= board[0].length) { //越界
    		return false;
    	}
		int visitIdx = i * board[0].length + j;
		if (visit.contains(visitIdx)) { //当前节点已访问，避免dfs搜索路径出现环
			return false;
		}

    // 	int curWordIdx = visit.size() - 1; //只有当本层字符匹配，而且即将dfs搜索邻居时，visit才添加本层节点
        int curWordIdx = visit.size();
    	if (word.charAt(curWordIdx) != board[i][j]) { //当前字符 不匹配
    		return false;
    	} else if (curWordIdx == word.length() - 1) { //当前字符已经是word 最后1个字符
    		return true;
    	} else {
    		visit.add(visitIdx);
    		for (int k = 0; k < 4; k++) { //搜索4个邻居
	    		int nextI = i + dir[k][0];
	    		int nextJ = j + dir[k][1];
	    		if (search(board, word, nextI, nextJ, visit)) {
	    			visit.remove(visitIdx);
	    			return true;
	    		}
	    	}
	    	visit.remove(visitIdx);
	    	return false;
    	}
    }
}