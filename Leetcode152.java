/**
 * 空间复杂度较高，可以对locaMin,localMax 都使用size为2的滚动数组
 * E.g. localMin[i % 2] = Math.min(nums[i], Math.min(nums[i] * localMin[(i - 1) % 2], nums[i] * localMax[(i - 1) % 2]));
 */
public class Leetcode152 {
    class Solution {
//        public int maxProduct(int[] nums) {
//            if (null == nums || 0 == nums.length) {
//                return 0;
//            }
//            // localMin[i]，以nums[i]结尾的min product
//            int[] localMin = new int[nums.length];
//            // localMax[i]，以nums[i]结尾的max product
//            int[] localMax = new int[nums.length];
//            localMin[0] = localMax[0] = nums[0];
//            int result = nums[0];
//            for (int i = 1; i < nums.length; i++) {
//                localMin[i] = Math.min(nums[i], Math.min(nums[i] * localMin[i - 1], nums[i] * localMax[i - 1]));
//                localMax[i] = Math.max(nums[i], Math.max(nums[i] * localMin[i - 1], nums[i] * localMax[i - 1]));
//                result = Math.max(result, localMax[i]);
//            }
//            return result;
//        }

        public int maxProduct(int[] nums) {
            if (null == nums || 0 == nums.length) {
                return 0;
            }
            // localMin[i]，以nums[i]结尾的min product
            int[] localMin = new int[2];
            // localMax[i]，以nums[i]结尾的max product
            int[] localMax = new int[2];
            localMin[0] = localMax[0] = nums[0];
            int result = nums[0];
            for (int i = 1; i < nums.length; i++) {
                localMin[i % 2] = Math.min(nums[i], Math.min(nums[i] * localMin[(i - 1) % 2], nums[i] * localMax[(i - 1) % 2]));
                localMax[i % 2] = Math.max(nums[i], Math.max(nums[i] * localMin[(i - 1) % 2], nums[i] * localMax[(i - 1) % 2]));
                result = Math.max(result, localMax[i % 2]);
            }
            return result;
        }
    }
}
