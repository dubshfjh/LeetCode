需要change为'X'的点具有特征：这些点无法通过搜索只有'O'的路径, 最终到达边界的'O'点
因此换位思考，不需要change为'X'的'O'具有特征：从边界上的某个'O'点出发搜索只包含'O'的路径，可以到达他们
1. 从上下左右4个边界的'O'出发，搜索所有只包含'O'的路径，并将路径上的所有节点设置为'$'
2. 搜索完毕后，如今的'$'代表从边界'O'可搜索到达的'O'点；如今的'O'代表从无法从边界'O'搜索到达的点
3. 遍历整个棋盘, 将此时的 'O' 全部改为 'X'； 将 '$' 全部改为 'O'
public class Solution {
    /*
     * @param board: board a 2D board containing 'X' and 'O'
     * @return: nothing
     */
    private int[][] dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    public void surroundedRegions(char[][] board) {
        // write your code here
    	if (board == null || board.length == 0) {
    		return;
    	}

    	if (board[0] == null || board[0].length == 0) {
    		return;
    	}

    	int rowNum = board.length;
    	int colNum = board[0].length;
    	for (int i = 0; i < colNum; i++) { //遍历上下边界
    		if (board[0][i] == 'O') {
    			search(board, 0, i);
    		}

    		if (board[rowNum - 1][i] == 'O') {
    		    search(board, rowNum - 1, i);
    		}
    	}

    	for (int i = 0; i < rowNum; i++) {
    		if (board[i][0] == 'O') {
    			search(board, i, 0);
    		}

    		if (board[i][colNum - 1] == 'O') {
    			search(board, i, colNum - 1);
    		}
    	}

    	for (int i = 0; i < rowNum; i++) {
    		for (int j = 0; j < colNum; j++) {
    			if (board[i][j] == '$') {
    				board[i][j] = 'O';
    			} else if (board[i][j] == 'O') {
    				board[i][j] = 'X';
    			}
    		}
    	}
    }

    private void search(char[][] board, int startI, int startJ) {
    	board[startI][startJ] = '$';
    	Queue<Integer> queue = new LinkedList<>();
    	queue.offer(getOneDimenIdx(board, startI, startJ));
    	while (!queue.isEmpty()) {
    		int curIndex = queue.poll();
    		int curI = curIndex / board[0].length;
    		int curJ = curIndex % board[0].length;
    		for (int i = 0; i < 4; i++) {
    			int neighborI = curI + dir[i][0];
    			int neighborJ = curJ + dir[i][1];
    			if (neighborI < 0 || neighborI >= board.length || neighborJ < 0 || neighborJ >= board[0].length) {
    				continue;
    			}
    			if (board[neighborI][neighborJ] != 'O') {
    				continue;
    			}
    			board[neighborI][neighborJ] = '$';
    			queue.offer(getOneDimenIdx(board, neighborI, neighborJ));
    		}
    	}
    }

    private int getOneDimenIdx(char[][] board, int i, int j) {
    	return i * board[0].length + j;
    }
}