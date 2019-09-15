public class Leetcode754 {
    class Solution {
        // 内存超限制的解法，得将空间复杂度下降为O(n)以下，时间复杂度得到达O(n) or O(logn)
        public int reachNumber(int target) {
            // number[i][j]：执行第i步跳跃时，能否拼凑出数字j
            // 为拼凑出target，最多执行2*target次跳跃，E.g. (-1+2)+(-3+4)...
            // 由于j = [-target,target]不好表示，考虑所有坐标右移到[0, target]
            boolean[][] number = new boolean[2][2 * target + 1];
            number[0][target] = true;
            for (int i = 1; i <= 2 * target; i++) {
                for (int j = 0; j <= 2 * target; j++) {
                    // 第i次跳跃可以选择-i，或者+i
                    if (j >= i) {
                        number[i % 2][j] = number[i % 2][j] || number[(i - 1) % 2][j - i];
                    }
                    if (j <= 2 * target - i) {
                        number[i % 2][j] = number[i % 2][j] || number[(i - 1) % 2][j + i];
                    }
                    if (j == 2 * target && number[i % 2][j]) {
                        return i;
                    }
                }
            }
            return 2 * target;
        }
    }

    // 贪心法：先找出1+2+3+...+i >= target，设这些数字的和为Sum，
    // 1. 如果Sum-target为偶数，那么将(1,2...i)中选择几个“和为0.5 *(Sum - target)”数字 reverse，那么这些数字的贡献从 +0.5*(sum-target)，变成了 -0.5*(sum-target)，正好使得Sum -> target
    // 2. 如果Sum-target为奇数，那么至少要额外再走1步，然后检查Sum+(i+1) - target是否为偶数，如果为偶数则进入Step1，如果为奇数则再次致谢Step2
    public int reachNumber(int target) {
        target = Math.abs(target);
        int i = 1, sum = 0, step = 0;
        while (sum < target) {
            step++;
            sum += i++;
        }
        while ((sum - target) % 2 != 0) {
            // sum-target为奇数，则额外引入i+1后，再次检查sum-target是否为偶数
            step++;
            sum += i++;
        }
        // sum-target为偶数，则不需要再走额外的步数
        return step;
    }
}
