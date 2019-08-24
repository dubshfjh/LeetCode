public class Leetcode31 {
    /**
     * 以数字1325871为例，从右往左分析
     * 1. [i - 1] >= [i]，说明将[i - 1],[i]进行置换，不能得到更大的数字
     * 2. [i - 1] < [i]，说明将[i - 1]，[j]（j 为[i], [i + 1]...[n - 1] 中恰好> [i - 1]的数字 ）进行置换，能得到next larger number
     * @param nums
     */
    public void nextPermutation(int[] nums) {
        if (null == nums || 0 == nums.length) {
            return;
        }
        int i = nums.length - 1;
        int firstLargerIndex = -1;
        for (; i >= 1; i--) {
            if (nums[i - 1] < nums[i]) {
                firstLargerIndex = searchFirstLargerNum(nums, i, nums.length - 1, nums[i - 1]);
                break;
            }
        }
//        System.out.println("i = " + i + ", j = " + firstLargerIndex);
        if (i == 0) {
            reverseArray(nums, 0, nums.length - 1);
        } else {
            // 14320，此时[i] = 1, [firstLargerIndex] = 2，应该将“14320”->“20134”
            // 拆分为2步：“14320”->“2(4310)”->“2(0134)”
            swapElement(nums, i - 1, firstLargerIndex);
            reverseArray(nums, i, nums.length - 1);
        }
    }

    /**
     * 二分搜索[left, right]范围中，首个 > targetVal 的数字index，其中nums为降序排列
     * @param nums
     * @param left
     * @param right
     * @param targetVal
     * @return
     */
    private int searchFirstLargerNum(int[] nums, int left, int right, int targetVal) {
        int middle = -1;
        while (left < right - 1) {
            middle = left + ((right - left) >> 1);
            if (nums[middle] <= targetVal) {
                right = middle;
            } else {
                left = middle;
            }
        }
        if (nums[left] <= targetVal) {
            return -1;
        } else {
            return nums[right] > targetVal ? right : left;
        }
    }

    private void reverseArray(int[] nums, int left, int right) {
        while (left < right) {
            swapElement(nums, left, right);
            left++;
            right--;
        }
    }

    private void swapElement(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public static void main(String[] args) {
        Leetcode31 leetcode31 = new Leetcode31();
//        int[] nums = {1, 4, 3, 2, 0};
        int[] nums = {4, 3, 2, 1};
        leetcode31.nextPermutation(nums);
        for (int number : nums) {
            System.out.print(number);
        }
    }
}
