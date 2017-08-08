个人认为本题为区间dp，设置局部最优解 and 全局最优解 两个dp数组
public class Solution {
    /*
     * @param : An array of non-negative integers
     * @return: The maximum amount of money you can rob tonight
     */
    public long houseRobber(int[] A) {
        // write your code here
        int length = A.length;
        if (length == 0) {
        	return 0;
        }
        long[] local = new long[length + 1]; //local[i]：必须选择A[i-1]时，最大的收益
        long[] global = new long[length + 1];
        local[0] = global[0] = 0;
        local[1] = global[1] = A[0];

        for (int i = 2; i <= length; i++) {
        	local[i] = global[i - 2] + A[i - 1];
        	//local[i] = local[i - 2] + A[i - 1]; 当必须选择[i - 1]时, 前一步可以为{0...i-3}的全局最优解
        	global[i] = Math.max(global[i - 1], local[i]);
        }
        return global[length];
    }
};


由于本题的特殊性，每个A[i]>=0，选择A[i] or 不选择A[i] 这两种的情况的 前一步dp：都可以取全局最优解，于是局部最优解没有必要存在
PS：然而 global[i] 与 local[i] 并不会完全一致！！！

public class Solution {
    /*
     * @param : An array of non-negative integers
     * @return: The maximum amount of money you can rob tonight
     */
    public long houseRobber(int[] A) {
        // write your code here
        int length = A.length;
        if (length == 0) {
        	return 0;
        }
        long[] global = new long[length + 1];
        global[0] = 0;
        global[1] = A[0];

        for (int i = 2; i <= length; i++) {
        	global[i] = Math.max(global[i - 1], global[i - 2] + A[i - 1]);
        }

        return global[length];
    }
};

滚动数组优化空间复杂度到O(1)
public class Solution {
    /*
     * @param : An array of non-negative integers
     * @return: The maximum amount of money you can rob tonight
     */
    public long houseRobber(int[] A) {
        // write your code here
        int length = A.length;
        if (length == 0) {
        	return 0;
        }
        long[] global = new long[2];
        global[0] = 0;
        global[1] = A[0];

        for (int i = 2; i <= length; i++) {
        	global[i % 2] = Math.max(global[(i - 1) % 2], global[(i - 2) % 2] + A[i - 1]);
        	// [i % 2] = max{ [(i - 1) % 2], [(i - 2) % 2] + A[i - 1]} 
        }

        return global[length % 2];
    }
};