public class Leetcode1017 {
    class Solution {
        public String baseNeg2(int N) {
            if (N == 0) {
                return "0";
            }
            StringBuilder result = new StringBuilder();
            int modNum, divideNum;
            while (N != 0) {
                // 将N拆分为 divideNum * (-2) + modNum，但是modNum必须为0/1，所以不能直接利用 N % -2 计算modNum
                modNum = Math.abs(N) & 1;
                divideNum = (N - modNum) / -2;
                result.append(modNum);
                // System.out.println(divideNum + ", modNum:" + modNum);
                N = divideNum;
            }
            return result.reverse().toString();
        }

    }
}
