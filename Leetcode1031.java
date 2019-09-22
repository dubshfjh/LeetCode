public class Leetcode1031 {
    class Solution {
        /**
         * 本题看上去像是双指针，但确实不能够每次放弃一半，两个指针start和end，会让问题变得极为复杂
         * 考虑只使用1个坐标，作为第1个子数组，第2个子数组的整体右边界。
         * 问题的实质，针对每个下标i：Max({L个元素}...i-M{M个元素}i，{M个元素}...i-L{L个元素}i)
         * 因此，只需要针对每个下标i，记录i-M左侧的Max(L个元素)，i-L左侧的Max(M个元素)即可
         * @param A
         * @param L
         * @param M
         * @return
         */
        public int maxSumTwoNoOverlap(int[] A, int L, int M) {
            if (null == A || 0 == A.length) {
                return 0;
            }
            int[] preSum = new int[A.length];
            preSum[0] = A[0];
            for (int i = 1; i < A.length; i++) {
                preSum[i] = preSum[i - 1] + A[i];
            }
            int result = preSum[L + M - 1];
            // Max Lsum Before i-M
            int maxLsum = preSum[L - 1];
            // Max Msum Before i-L
            int maxMsum = preSum[M - 1];
            for (int i = L + M; i < A.length; i++) {
                // i-L-M+1 ... i-L（长度为M）；i-L+1...i
                maxMsum = Math.max(maxMsum, preSum[i - L] - preSum[i - L - M]);
                result = Math.max(result, maxMsum + preSum[i] - preSum[i - L]);

                // i-L-M+1 ...i-M（长度为L）；i-M+1...i
                maxLsum = Math.max(maxLsum, preSum[i - M] - preSum[i - L - M]);
                result = Math.max(result, maxLsum + preSum[i] - preSum[i - M]);
            }
            return result;
        }
    }
}
