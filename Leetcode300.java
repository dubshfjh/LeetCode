public class Leetcode300 {
    class Solution {
//        public int lengthOfLIS(int[] nums) {
//            if (null == nums || 0 == nums.length) {
//                return 0;
//            }
//            int result = 1;
//            int[] length = new int[nums.length];
//            for (int i = 0; i < nums.length; i++) {
//                length[i] = 1;
//                for (int j = 0; j < i; j++) {
//                    if (nums[j] < nums[i]) {
//                        length[i] = Math.max(length[i], length[j] + 1);
//                    }
//                }
//                result = Math.max(result, length[i]);
//            }
//            return result;
//        }

        /**
         * 要将时间复杂度压缩到nlogn，则需要引入二分查找的思想
         * 以tail[i] 记录长度为"i + 1"的上升子序列中，取值最小的尾部元素
         * E.g. 数组为[4,5,6,3]，可以看出tails数组必然是递增的，可以采用二分
         * len = 1   :      [4], [5], [6], [3]   => tails[0] = 3
         * len = 2   :      [4, 5], [5, 6]       => tails[1] = 5
         * len = 3   :      [4, 5, 6]            => tails[2] = 6
         * 那么针对元素nums[i]
         * 1）只要检测到tail[j] < nums[i] <= tail[j + 1]，那么 "tail[j]所处的子序列 + nums[i]" 可以拼接出长度为"j + 1"的新子序列
         *    此时，需要更新tail[j + 1]为nums[i]
         * 2）如果tail[size] < nums[i]，则说明出现了长度为"size + 1"的新子序列，更新tail[size + 1] = nums[i]，size = size + 1
         * @param nums
         * @return
         */
        public int lengthOfLIS(int[] nums) {
            if (null == nums || 0 == nums.length) {
                return 0;
            }
            int[] tail = new int[nums.length];
            int lisMaxLength = 0;
            for (int i = 0; i < nums.length; i++) {
                int start = 0, end = lisMaxLength;
                while (start < end) {
                    int mid = start + (end - start) / 2;
                    if (tail[mid] < nums[i]) {
                        start = mid + 1;
                    } else {
                        end = mid;
                    }
                }
                //start：最左侧的 >= target的元素，PS：寻找最右侧的 <= target的元素，原理类似，只不过是将start 移动到 mid
                tail[start] = nums[i];
                if (start == lisMaxLength) {
                    lisMaxLength++;
                }
            }
            return lisMaxLength;
        }
    }

    Solution solution = new Solution();

    public static void main(String[] args) {
        Leetcode300 leetcode300 = new Leetcode300();
        int[] nums = {10,9,2,5,3,7,101,18};
//        int[] nums = {2, 2, 2};
//        int[] nums = {-2, -1};
        System.out.println(leetcode300.solution.lengthOfLIS(nums));
    }
}
