一、定义 rectangle 的左上，右上，左下，右下 4 个corner点坐标，画图看(这4个点作为右下角)矩形的面积差 即可 类比范围Sum，
	其中"面积" 类比为 [0][0]...[i][j] 范围Sum

二、 res = 右下点Sum - (左下点Sum + 右上点Sum) + 左上点Sum + (整体矩形的左edge + 整体矩形的上edge)
	其中：矩形的上edge {即第row1行的{col1...col2} ， 矩形的左edge {第col1列的{row1...row2}}

踩到的坑：右下corner 关联的矩形 对 整体rectangle 的 {左edge, 上edge} 的元素累加了 1 次， 左上corner 的矩形 与 {左edge, 上edge}无关 
	-(右上corner 和 左上corner) 使得 {左edge, 上edge} 的元素 减去了 2 次
因此：在 res = 右下点Sum - (左下点Sum + 右上点Sum) 之后，还需要 再累加 1 次 (整体矩形的左edge + 整体矩形的上edge)


1. 使用sumFromOrigin[i][j]记录：从原点[0][0]到当前元素[i][j]的累加和
2. 使用rowSum[i][j]记录：第i+1行中，到[i][j]为止的累加和
3. 使用colSum[i][j]记录：第i+1列中，到[i][j]为止的累加和
public class NumMatrix {
    private boolean nullMatrix = false;
    private int[][] matrix;
	private int[][] sumFromOrigin; //从原点[0][0]到当前元素[i][j]的累加和
	private int[][] rowSum; //[i][j]：第i+1行中，到[i][j]为止的累加和
	private int[][] colSum; //第i+1列中，到[i][j]为止的累加和
    public NumMatrix(int[][] matrix) {
    	if (matrix == null || matrix.length == 0) {
    	    nullMatrix = true;
    		return;
    	}
    	this.matrix = matrix;
    	int rowNum = matrix.length;
    	int colNum = matrix[0].length;
    	sumFromOrigin = new int[rowNum][colNum]; //sumFromOrigin[i][j]：sum([0][0]+...+[i][j])
    	rowSum = new int[rowNum][colNum];
    	colSum = new int[rowNum][colNum];
    	rowSum[0][0] = colSum[0][0] = sumFromOrigin[0][0] = matrix[0][0];
    	for (int i = 1; i < colNum; i++) {
    		sumFromOrigin[0][i] = sumFromOrigin[0][i - 1] + matrix[0][i];
    		rowSum[0][i] = sumFromOrigin[0][i];
    		// System.out.print(sumFromOrigin[0][i] + " ");
    	}
		// System.out.println();

    	for (int i = 1; i < rowNum; i++) {
    		int curRowSum = matrix[i][0];
			sumFromOrigin[i][0] = sumFromOrigin[i - 1][0] + curRowSum;
			rowSum[i][0] = matrix[i][0];
    		for (int j = 1; j < colNum; j++) {
    			curRowSum += matrix[i][j];
    			sumFromOrigin[i][j] = sumFromOrigin[i - 1][j] + curRowSum;

    			rowSum[i][j] = rowSum[i][j - 1] + matrix[i][j];
	    		// System.out.print(sumFromOrigin[i][j] + " ");
    		}
    		// System.out.println();
    	}

    	for (int j = 0; j < colNum; j++) {
    		colSum[0][j] = matrix[0][j];
    		for (int i = 1; i < rowNum; i++) {
    			colSum[i][j] = colSum[i - 1][j] + matrix[i][j];
    		}
    	}
    }
    
    public int sumRegion(int row1, int col1, int row2, int col2) {
        if (nullMatrix) {
            return 0;
        }
    	int[] leftUp = {row1, col1};
    	int[] rightUp = {row1, col2};
    	int[] leftDown = {row2, col1};
    	int[] rightDown = {row2, col2};
    	// res = 右下点Sum - (左下点Sum + 右上点Sum) + 左上点Sum + (矩形的左edge + 矩形的上edge)
    	// 画图看这4个作为右下角的矩形的面积差 即可 类比范围Sum，其中"面积" 类比为 [0][0]...[i][j] 范围Sum
    	int res = sumFromOrigin[rightDown[0]][rightDown[1]] - 
    		(sumFromOrigin[leftDown[0]][leftDown[1]] + sumFromOrigin[rightUp[0]][rightUp[1]])
    		+ sumFromOrigin[leftUp[0]][leftUp[1]]; //右下点Sum - (左下点Sum + 右上点Sum) + 左上点Sum 

    	res += (rowSum[rightUp[0]][rightDown[1]] - rowSum[leftUp[0]][leftUp[1]]) +
    			(colSum[leftDown[0]][leftDown[1]] - colSum[leftUp[0]][leftUp[1]]) +
    			matrix[row1][col1]; //res += 矩形的上edge{即第row1行的{col1...col2} + 矩形的左edge {第col1列的{row1...row2}}
    	return res;
    }

}

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */