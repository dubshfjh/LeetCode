将大问题 拆解为 小问题，即分析每一步的滑动窗口更新问题，设 start 和 end 为包含"当前元素左邻居[i-1]" 的 MAX滑动窗口 的左右边界；
	设 resS, resE 为 分析完元素[i] 后， {0...i}这个范围的 整体 MAX活动窗口 的左右边界
对于元素[i]，其中当前元素[i]就是局部滑动窗口的右边界end
	1.1. 如果 包含左邻居[i-1] 的最大滑动窗口的 Sum < 0，则左侧的元素整体只能拖后腿，于是更新 start = end，sum = A[end]
	1.2. 如果 包含左邻居[i-1] 的最大滑动窗口的 Sum < 0，则左侧元素 可以起到正面作用，于是更新 sum += A[end]
	2. 分析完元素[i]后，如果局部滑动窗口的 Sum > {resS, resE} 整体MAX滑动窗口的 maxSum，则更新 {resS, resE} 为 当前局部滑动窗口{start, end}，以及更新maxSum 为 sum
public class Solution {
    /**
     * @param A an integer array
     * @return  A list of integers includes the index of the first number and the index of the last number
     */
    public ArrayList<Integer> continuousSubarraySum(int[] A) {
        // Write your code here
        int start, end, resS, resE, sum, maxSum;
        start  = end = sum = resS = resE = 0;
        maxSum = Integer.MIN_VALUE;
        while (start <= end && end < A.length) {
        	if (sum >= 0) {
        		sum += A[end];
        	} else {
        		start = end;
        		sum = A[end];
        	}

        	if (sum > maxSum) {
        		maxSum = sum;
        		resS = start;
        		resE = end;
        	}
        	end++;
        }
        ArrayList<Integer> res = new ArrayList<>();
        res.add(resS);
        res.add(resE);
        return res;
    }
}