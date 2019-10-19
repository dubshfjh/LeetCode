public class Leetcode605 {
    class Solution {
        /**
         * 由于最多能插入N朵花时，一定也能通过调整花的位置，插入N-1, N-2...朵花，因此N >= 参数n即返回true
         * 如果flowerbed[i] == 0，而且它的左右邻居（超出边界 or 为0），即可将flowerbed[i]置为1，N++
         * @param flowerbed
         * @param n
         * @return
         */
        public boolean canPlaceFlowers(int[] flowerbed, int n) {
            if (null == flowerbed || 0 == flowerbed.length) {
                return 0 == n;
            }
            int maxFlowers = 0;
            for (int i = 0; i < flowerbed.length; i++) {
                if (flowerbed[i] == 1) {
                    continue;
                }
                if ((i == 0 || flowerbed[i - 1] == 0)
                        && (i == flowerbed.length - 1 || flowerbed[i + 1] == 0)) {
                    flowerbed[i] = 1;
                    maxFlowers++;
                }
            }
            return maxFlowers >= n;
        }
    }
}
