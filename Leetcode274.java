public class Leetcode274 {
    class Solution {
        /**
         * hIndex，保证正好有h篇文章的引用数 >= h，并且找到最后1个h
         * 1. 不能使用pivot的思想！！！因为Pivot的核心在于“可以放弃掉pivot左半元素，或者右半元素”，但是本题中pivot左侧和右侧都可能出现可行解
         * 2. 要寻找 " >= h 的元素正好有h个"，因此考虑用bucket的思想，在每个Bucket中记录取值==bucket的元素数目，
         *    从右往左计算Bucket中元素数目的afterSum（>= bucket下标的元素总数目）
         * 3. 如果在计算到某个Bucket_i时，发现afterSum[i+1...n-1] + bucket[i] >= i
         *    则说明加上当前Bucket中的0到多个取值为"i"的元素后，必然能凑出 ">=i 的元素数目 == i" 这个场景
         * @param citations
         * @return
         */
        public int hIndex(int[] citations) {
            if (null == citations || 0 == citations.length) {
                // 当数组为空时，确实满足“>=0 的元素数为 0个”这个条件
                return 0;
            }
            int bucketNum = citations.length;
            int[] count = new int[bucketNum + 1];
            for (int citation : citations) {
                if (citation <= bucketNum) {
                    count[citation]++;
                } else {
                    count[bucketNum]++;
                }
            }
            int afterSum = 0;
            for (int i = bucketNum; i >= 0; i--) {
                afterSum += count[i];
                if (afterSum >= i) {
                    return i;
                }
            }
            return -1;
        }
    }
}
