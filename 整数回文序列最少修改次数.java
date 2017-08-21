由于所有的nums[i] > 0，所以对于 s[i] 与 它的对称元素s[n - 1 - i]，如果二者不相等，则
较小的元素需要 不断地 与其相邻元素累加，直到它增加到与右边对称元素相等 or 指针移到对称元素上位置
题目的本质为 对撞型双指针 问题，设置start 和 end 双指针。
while(start < end)
1. [start] < [end]，左侧元素需要变大，[start] 累加到相邻元素 [start + 1]上，左指针右移一次，即start++
2. [start] > [end]，右侧元素需要变大，[end] 累加到相邻元素 [end - 1]上，右指针左移一次，即end--
3. [start] == [end]，则当前的左右元素匹配，start++, end--

import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            int n = sc.nextInt();
            int[] nums = new int[n];
            for (int i = 0; i < n; i++) {
                nums[i] = sc.nextInt();
            }
            Main obj = new Main();
            int res = obj.minChangeNum(nums);
            System.out.println(res);
        }
    }

    private int minChangeNum(int[] nums) {
        if (nums.length <= 1) {
            return 0;
        }
        int start = 0;
        int end = nums.length - 1;
        int minNum = 0;
        while (start < end) {
            if (nums[start] < nums[end]) {
                nums[start + 1] += nums[start];
                start++;
                minNum++;
            } else if (nums[start] > nums[end]) {
                nums[end - 1] += nums[end];
                end--;
                minNum++;
            } else {
                start++;
                end--;
            }
        }
        return minNum;
    }
}