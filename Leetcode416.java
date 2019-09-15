import java.util.ArrayList;
import java.util.List;

public class Leetcode416 {
    class Solution {
        public boolean canPartition(int[] nums) {
            if (null == nums || 1 >= nums.length) {
                return false;
            }
            int sum = 0;
            for (int number : nums) {
                sum += number;
            }
            if ((sum & 1) != 0) {
                return false;
            }
            int target = sum >> 1;
            // 前i件物品，拼凑出重量j是否可行
            boolean[][] weight = new boolean[nums.length + 1][target + 1];
            weight[0][0] = true;
            for (int i = 1; i <= nums.length; i++) {
                for (int j = 0; j <= target; j++) {
                    weight[i][j] = weight[i - 1][j];
                    if (!weight[i][j] && j >= nums[i - 1]) {
                        weight[i][j] = weight[i - 1][j - nums[i - 1]];
                    }
                }
            }
            if (weight[nums.length][target]) {
                generatePath(weight, nums);
            }
            return weight[nums.length][target];
        }

        private void generatePath(boolean[][] weight, int[] nums) {
            List<Integer> path = new ArrayList<>();
            int target = weight[0].length;
            for (int i = nums.length; i > 0; i--) {
                if (target >= nums[i - 1] && weight[i - 1][target - nums[i - 1]]) {
                    // 选择了nums[i - 1]
                    path.add(nums[i - 1]);
                } else {
                    continue;
                }
            }
            int sum = 0;
            for (int number : path) {
                sum += number;
                System.out.println(number);
            }
            System.out.println("Sum is: " + sum);
        }
    }
}
