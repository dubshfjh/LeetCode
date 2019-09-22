import java.util.ArrayList;
import java.util.List;

public class Leetcode442 {
    private Solution solution = new Solution();

    class Solution {
        public List<Integer> findDuplicates(int[] nums) {
            List<Integer> result = new ArrayList<>();
            if (null == nums || 0 == nums.length) {
                return result;
            }
            for (int i = 0; i < nums.length; i++) {
                int targetId = Math.abs(nums[i]) - 1;
                nums[targetId] = -nums[targetId];
                if (nums[targetId] > 0) {
                    result.add(Math.abs(nums[i]));
                }
            }
            return result;
        }
    }
//    class Solution {
//        /**
//         * 错误解法！！！对比Leetcode448 “寻找所有disappear的元素”，我们在swap整体完成后，
//         * 1. 当遇到nums[i] != i - 1时，知道i就是缺失元素，而且每个i都只会缺失1次
//         * 2. 但是，如果要找的是Duplicate元素，则遇到nums[i] != i - 1时，知道nums[i]是重复元素，但是nums[i]会被添加多次
//         *    而即使尝试在swap的过程中记录重复元素，我们也不知道nums[i]是第几次被分析了
//         *
//         * nums[i] = 1...n，因此尝试将每个nums[i]，都移动到第 nums[i] - 1个位置
//         * 1. 如果当前的nums[i] 就在第 nums[i] - 1个位置，则直接i++
//         * 2. 如果当前的nums[i] 位置不对，则检测 nums[nums[i] - 1]
//         *    2.1 如果nums[nums[i] - 1] == nums[i]，说明 nums[i] 出现了多次，直接i++
//         *    2.2 如果nums[nums[i] - 1] != nums[i]，则swap，由于之前的nums[nums[i] - 1]没在正确的位置，所以i保持不变
//         *        下一步仍然是分析新的nums[i]
//         * @param nums
//         * @return
//         */
//        public List<Integer> findDuplicates(int[] nums) {
//            List<Integer> result = new ArrayList<>();
//            if (null == nums || 0 == nums.length) {
//                return result;
//            }
//            int i = 0, targetId = -1;
//            while (i < nums.length) {
//                targetId = nums[i] - 1;
//                if (targetId == i) {
//                    i++;
//                } else {
//                    if (nums[i] == nums[targetId]) {
//                        // 因为“重复元素”可能被添加多次，例如[2,2,1] -> i = 1,[2,2,1]，添加1次"2"
//                        // -> i=2，[1,2,2]，但是下1轮分析的nums[i]“2”，不应该再次添加到result里了
//                         result.add(nums[i]);
//                        i++;
//                    } else {
//                        swap(nums, i, targetId);
//                    }
//                }
//            }
//            return result;
//        }
//
//        private void swap(int[] nums, int i, int j) {
//            int temp = nums[i];
//            nums[i] = nums[j];
//            nums[j] = temp;
//        }
//    }

    public static void main(String[] args) {
        Leetcode442 leetcode442 = new Leetcode442();
        int[] nums = {4,3,2,7,8,2,3,1};
        List<Integer> result = leetcode442.solution.findDuplicates(nums);
        for (int num : result) {
            System.out.print(num + ",");
        }
    }
}
