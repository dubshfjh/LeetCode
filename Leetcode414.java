public class Leetcode414 {
    Solution solution = new Solution();
    class Solution {
        /**
         * 1.利用nums[i]在first，second，third 所处的区间位置，更新这3个pivot值。
         *   由于判断区间位置，是检测nums[i] > 这3个位置中的哪个数字，所以3者应初始化为min(nums[])，而不能直接初始化为Integer.MIN_VALUE
         * 2.nums[i] == first or second or third，则不应该将 3个pivot 进行替换，避免用重复数字挤走了之前的某个值
         * 3.nums[i] > first，说明nums[i]是新的first。newThird = second，newSecond = first，newFirst = nums[i]
         * 4.nums[i] > second，或者 (nums[i] > third && second == first)，说明nums[i]是新的second，则newSecond = nums[i]
         *  如果nums[i] > second，则还需要额外执行newThird = second
         * 5.nums[i] > third，或者 (nums[i] < third && third == second)，说明nums[i]是新的third，则newThird = nums[i]
         *
         * 优化步骤：初始化3个pivot为null，由于nums[i]与3个pivot相等时不执行操作，所以 second == third，first == second这类情况不会再出现
         * 对应的情况变成了 second == null || nums[i] > second
         * @param nums
         * @return
         */
        public int thirdMax(int[] nums) {
            if (null == nums || 0 >= nums.length) {
                return 0;
            }
            int minValue = Integer.MAX_VALUE;
            for (int number : nums) {
                minValue = Math.min(minValue, number);
            }
            int first = minValue, second = minValue, third = minValue;
            for (int i = 0; i < nums.length; i++) {
                if (nums[i] == first || nums[i] == second || nums[i] == third) {
                    continue;
                }
                if (nums[i] > first) {
                    third = second;
                    second = first;
                    first = nums[i];
                } else if (nums[i] > second) {
                    // (> second) || (> third && second == first)
                    third = second;
                    second = nums[i];
                } else if (nums[i] > third) {
                    if (second == first) {
                        second = nums[i];
                    } else {
                        // (> third && second != first) || (< third && third == second)
                        third = nums[i];
                    }
                } else if (third == second) {
                    third = nums[i];
                }
            }
            if (first == second || second == third) {
                return first;
            }
            return third;
        }
    }

    public int thirdMax(int[] nums) {
        Integer max1 = null;
        Integer max2 = null;
        Integer max3 = null;
        for (Integer n : nums) {
            if (n.equals(max1) || n.equals(max2) || n.equals(max3)) continue;
            if (max1 == null || n > max1) {
                max3 = max2;
                max2 = max1;
                max1 = n;
            } else if (max2 == null || n > max2) {
                max3 = max2;
                max2 = n;
            } else if (max3 == null || n > max3) {
                max3 = n;
            }
        }
        return max3 == null ? max1 : max3;
    }

    public static void main(String[] args) {
        Leetcode414 leetcode414 = new Leetcode414();
//        int[] nums = {4, 5, 4, 3, 2, 2, 1};
//        int[] nums = {3, 3, 3};
        int[] nums = {1, 2, -2147483648, 2147483647};
        leetcode414.solution.thirdMax(nums);
    }
}
