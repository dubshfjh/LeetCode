public class Lintcode512 {
    class Solution {
        /**
         * @param s: a string,  encoded message
         * @return: an integer, the number of ways decoding
         */
        public int numDecodings(String s) {
            // 序列型DP，1)状态：dp[i]代表 s[0...i-1]的decoding ways
            //2) 转移方程,根据最后1步推出：
            //2.1)如果s[n] == '0'，则当1<=s[n-1, n]<=26时，dp[n] = dp[n - 2]，否则dp[n]=0
            //2.2)如果s[n] != '0'，则当1<=s[n-1, n]<=26时, dp[n] = dp[n - 1] + dp[n -2]，否则dp[n] = dp[n-1]
            //3) 初始化dp[0],dp[1]: 如果s[0] == '0'，则dp[0]=0；否则dp[0]=1；如果 1<=s[0,1]<=26，则dp[1]=2，否则dp[1] = d[0]
            //4) 结果：dp[s.length() -1]
            if (null == s || 0 == s.length()) {
                return 0;
            }
            int[] dp = new int[s.length()];
            dp[0] = s.charAt(0) == '0' ? 0 : 1;
            if (s.length() == 1) {
                // 由于没有设置dummy dp[0]，导致要额外避免数组越界的问题
                return dp[0];
            }
            if (s.charAt(1) == '0') {
                dp[1] = isTwoNumInOneChar(s, 0) ? 1 : 0;
            } else {
                dp[1] = isTwoNumInOneChar(s, 0) ? dp[0] + 1 : dp[0];
            }
            for (int i = 2; i < s.length(); i++) {
                if (s.charAt(i) == '0') {
                    //s[i]本身不能作为1种解法，所以"dp[i-1]种方法解析s[0...i-1]，组合上s[i]本身" 这个分支相当于不存在
                    dp[i] = isTwoNumInOneChar(s, i - 1) ? dp[i - 2] : 0;
                } else {
                    dp[i] = isTwoNumInOneChar(s, i - 1) ? dp[i - 2] + dp[i - 1] : dp[i - 1];
                }
            }
            return dp[s.length() - 1];
        }

        /**
         * if 1 <= s[i, i+1] <= 26, return true
         *
         * @param s
         * @param i
         * @return
         */
        private boolean isTwoNumInOneChar(String s, int i) {
            return s.charAt(i) == '1' || (s.charAt(i) == '2' && s.charAt(i + 1) <= '6');
        }
    }
}
