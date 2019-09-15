public class Leetcode134 {
    //class Solution {
    //    public int canCompleteCircuit(int[] gas, int[] cost) {
    //        if (null == gas || 0 == gas.length
    //            || null == cost || 0 == cost.length) {
    //            return -1;
    //        }
    //        for (int i = 0; i < gas.length; i++) {
    //            if (checkComplete(gas, cost, i)) {
    //                return i;
    //            }
    //        }
    //        return -1;
    //    }
    //
    //    private boolean checkComplete(int[] gas, int[] cost, int startId) {
    //        int length = gas.length;
    //        int remainGas = 0;
    //        for (int i = 0; i < length; i++) {
    //            remainGas += (gas[(startId + i) % length] - cost[(startId + i) % length]);
    //            if (remainGas < 0) {
    //                return false;
    //            }
    //        }
    //        return true;
    //    }
    //}

    /**
     * 实际上仍然是双指针问题！因为在分析end->start->end 这个区间时，每次可以“放弃掉 必然不会出现可行解的一半区间”
     */
    class Solution {
        public int canCompleteCircuit(int[] gas, int[] cost) {
            if (null == gas || 0 == gas.length
                || null == cost || 0 == cost.length) {
                return -1;
            }
            int start = 0;
            int end = cost.length - 1;
            int remainGas = gas[end] - cost[end];
            while (start < end) {
                // end 逐渐逼近 start，直到二者相等，达成1个圆圈
                if (remainGas < 0) {
                    // 说明end不可能到达start-1，得尝试从end-1到达start-1
                    end--;
                    remainGas += gas[end] - cost[end];
                } else {
                    // 说明end能够到达start-1，下一步尝试从end到达start
                    remainGas += gas[start] - cost[start];
                    start++;
                }
            }
            // 最终start == end，在退出循环的最后1步
            // 1. remainGas < 0，end 从 start + 1 退后一步到达 start，remainGas += gas[start] - cost[start]，计算了从start->length-1->start中，第1步的花销
            // 2. remainGas >= 0，remainGas += gas[start - 1] - cost[start - 1]，计算了start->length-1->start中，最后1步的花销
            return remainGas >= 0 ? end : -1;
        }
    }
}
