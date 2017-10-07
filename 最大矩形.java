本题大致有两种解法：直方图解法，{动态规划 + 左右上延伸思想}解法

Solution 1：直方图解法
1. 使用height[i][j]记录第i行从{j, j - 1...first取值为 0 的列}的高度
2. 由于height[i]本质上就是以 第i行 为地基的直方图
3. 因此分析height[0]...height[n - 1]对应的 n 个直方图中最大矩形面积即可

public class Solution {
    /*
     * @param matrix: a boolean 2D matrix
     * @return: an integer
     */
    public int maximalRectangle(boolean[][] matrix) {
        // write your code here
        if (matrix == null || matrix.length == 0) {
        	return 0;
        }
        if (matrix[0] == null || matrix[0].length == 0) {
        	return 0;
        }
        int rows = matrix.length;
        int cols = matrix[0].length;
        // int[][] height = new int[rows][cols];
        int[][] height = new int[rows][cols + 1]; // 在计算直方图时，我们将 高度<=height[栈顶] 的元素当做分界点
        // 因此添加1个高度为0的 dummy，以应对高度递增序列中 找不到分界点的情况
        for (int i = 0; i < rows; i++) {
        	for (int j = 0; j < cols; j++) {
        		if (!matrix[i][j]) {
        			height[i][j] = 0;
        		} else {
        			height[i][j] = (i == 0) ? 1 : 1 + height[i - 1][j];
        		}
        	}
        }

        int maxArea = 0;
        for (int[] histo : height) {
        	maxArea = Math.max(maxArea, calHistoArea(histo));
        }
        return maxArea;
    }

    private int calHistoArea(int[] histo) { //计算一层直方图的最大矩形//本质就是为每个元素[i]寻找 左侧第一个<[i] 的元素，即寻找 高度为[i] 的矩形左边界
    	//本质就是为每个元素[i]寻找 左侧第一个<[i] 的元素，即寻找 高度为[i] 的矩形左边界
    	//反向思考：只需要为每个高度 h 寻找能提供该高度矩形的右边界即可
    	int maxArea = 0;
    	Stack<Integer> higherIndex = new Stack<>(); //存放元素下标，而且 height[栈底] <= height[栈底 + 1] <= ... <= height[栈顶]
    	
    	for (int i = 0; i < histo.length;) {
    		if (higherIndex.isEmpty() || histo[higherIndex.peek()] <= histo[i]) {
    			higherIndex.add(i); // 如果当前元素[i]至少提供histo[栈顶元素]的高度，则说明[i]仍然能提供 histo[栈顶元素] 的高度
    			i++;
    		} else { //如果此时的[i] < [栈顶元素]，那么说明 {第2个元素 + 1, 第2个元素 + 2 ... 栈顶, 1 + 栈顶...i - 1}的高度都 >= [栈顶]，计算好"不能再向右侧延伸的矩形"面积
    				// 然后不停地pop掉栈顶，直到出现 first [i] >= [栈顶元素]，也就是找到first [i]能提供的高度，此时i再次入栈
    			int preIndex = higherIndex.pop();
    			int widthForPreIndex = (higherIndex.empty()) ? i : i - 1 - higherIndex.peek();
    			int areaForStackTopHeight = widthForPreIndex * histo[preIndex];
    			maxArea = Math.max(maxArea, areaForStackTopHeight);
    			//此时 i 不能自增，还需要分析当前的[i]与心得栈顶元素之间的关系
    		}
    	}
    	return maxArea;
    }
}

Solution 2: 动态规划 + 左侧,上侧,右侧延伸
1. 设置 left[i][j], up[i][j], right[i][j] 分别记录以元素[i][j]为起点，向左、向上、向右能延伸的最长距离
2. 分析每个元素[i][j]，计算以它为底座的最大矩形面积：up[i][j] * (left[i][j] + right[i][j] - 1)