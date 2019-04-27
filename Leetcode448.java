import java.util.LinkedList;
import java.util.List;

public class Leetcode448 {
    class Solution {
        public List<Integer> findDisappearedNumbers(int[] nums) {
            List<Integer> result = new LinkedList<>();
            if (null == nums || 0 == nums.length) {
                return result;
            }
            int i = 0;
            while (i < nums.length) {
                int targetNumAndPos = nums[i] - 1;
                if (i != targetNumAndPos && nums[targetNumAndPos] != targetNumAndPos + 1) {
                    //nums[i]的正确位置为targetNumAndPos, 但nums[i]没在正确位置 && nums[targetNumAndPos]没在正确位置
                    //第1个条件：避免[2,3,1]->[3,2,1]后，第2轮直接分析nums[1]，而忽略了新的nums[0]也不在正确位置，而且再也不能分析到了
                    //第2个条件：避免[3-0,3-1,3-2]->[3-2,3-1,3-0]后，再次试图swap(3-2,3-0)，毕竟3-0已经在正确位置了，不应该再移动
                    swap(nums, i, targetNumAndPos);
                } else {
                    i++;
                }
            }
            // if nums=[3,1,3,3], then it'll change to[1,3,3,3], only one of 3 will be in true position
            // But the element in nums[1],nums[3] are disappeared elements
            for (i = 0; i < nums.length; i++) {
                if (nums[i] != i + 1) {
                    result.add(i + 1);
                }
            }
            return result;
        }

        private void swap(int[] arr, int i, int j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}
