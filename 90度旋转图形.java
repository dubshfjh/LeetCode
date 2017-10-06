经过观察 90度 旋转矩阵在 2 * 2；3 * 3 的例子，该过程可以拆解为2个步骤
1. 按照主对称轴，swap(a[i][j], a[j][i])
2. reverse(each row)
public class Solution {
    /*
     * @param matrix: a lists of integers
     * @return: 
     */
    public void rotate(int[][] matrix) {
        // write your code here
        if (matrix == null || matrix.length == 0) {
        	return;
        }
        if (matrix[0] == null || matrix[0].length == 0) {
        	return;
        }

        int rowColNum = matrix.length;
        for (int i = 0; i < rowColNum; i++) {
        	for (int j = 0; j < i; j++) {
        		swapTwoDimen(matrix, i, j);
        	}
        }

        for (int[] temp : matrix) {
        	reverse(temp);
        }
    }

    private void swapTwoDimen(int[][] matrix, int i, int j) {
    	int temp = matrix[i][j];
    	matrix[i][j] = matrix[j][i];
    	matrix[j][i] = temp;
    // 	System.out.println(i + "  " + j + "..." + matrix[i][j]);
    }

    private void reverse(int[] nums) {
    	for (int i = 0; i < (nums.length >> 1); i++) {
    // 		System.out.println(i + "  " + nums[i]);
    // 		swap(nums, i, nums.length - i);
            swap(nums, i, nums.length - 1 - i);
    	}
    }

    private void swap(int[] nums, int i, int j) {
    	int temp = nums[i];
    	nums[i] = nums[j];
    	nums[j] = temp;
    }
}