import java.util.HashMap;
import java.util.Map;

public class Lintcode676 {
    /**
     * 1. dp[n] = dp[n-2]*(s[n-1, n]的decodingways) + dp[n-1]*(s[n]的decodingways)
     * 2. 根据s[n] = '0';'1...9';'*' 三种情况，分析s[n-1, n]和s[n]的decodingWays
     * 3. 注意大数字计算时，一定要声明为Long!!!!并在每次运算时都mod CountNum，否则在任何一步都可能出现int溢出!!!!
     * @param s
     * @return
     */
    public int numDecodings(String s) {
        if (null == s || 0 == s.length() || 0 == s.charAt(0)) {
            return 0;
        }
        // 设置1位dummy，避免为s.length==1单独return结果，dp[i]代表s[0...i]的decodingWays
        long[] dp = new long[s.length() + 1];
        dp[0] = 1;
        if (s.charAt(0) == '*') {
            dp[1] = 9;
        } else {
            dp[1] = 1;
        }
        int modCount = 1000000007;
        for (int i = 2; i <= s.length(); i++) {
            if (s.charAt(i - 1) == '0') {
                //s[i-1]本身的decodingways = 0，因此{dp[i-1], s[i-1]}不可行
                //寻找 1 <= s[i-2,i-1] <= 26的情况，考虑{dp[i-2],s[i-2,i-1]}的decodingways
                if (s.charAt(i - 2) == '*') {
                    // *为1,2时，s[i-2,i-1]可取值为10,20
                    dp[i] = 2 * (dp[i - 2] % modCount);
                } else if (s.charAt(i - 2) == '1' || s.charAt(i - 2) == '2') {
                    //s[i-2]=1,则s[i-2,i-1]取值为10；s[i-2]=2，则s[i-2,i-1]取值为20
                    dp[i] = (dp[i - 2] % modCount);
                } else {
                    return 0;
                }
            } else if (s.charAt(i - 1) >= '1' && s.charAt(i - 1) <= '9') {
                // 此时s[i - 1]必然提供1种解码方法，因此{dp[i-1], s[i-1]}必然可行
                dp[i] = dp[i - 1] % modCount;
                // 分析1 <= s[i-2, i-1] <= 26的情况，考虑{dp[i-2],s[i-2,i-1]}的decodingways
                if (s.charAt(i - 2) == '1' || (s.charAt(i - 2) == '2' && s.charAt(i - 1) <= '6')) {
                    //此时1<=s[i-2,i-1]<=26
                    dp[i] += (dp[i - 2] % modCount);
                } else if (s.charAt(i - 2) == '*') {
                    // s[i-2]为*，则它取值为1时，满足1<=s[i-2,i-1]<=26；
                    // 它取值为2时，如果s[i-1]<=6，也能满足1<=s[i-2,i-1]<=26；
                    if (s.charAt(i - 1) <= '6') {
                        dp[i] += 2 * (dp[i - 2] % modCount);
                    } else {
                        dp[i] += (dp[i - 2] % modCount);
                    }
                }
            } else {
                //此时s[i-1]为*，s[i - 1]本身能提供9种decodingways，因此{dp[i-1], s[i-1]}必然可行
                dp[i] = 9 * (dp[i - 1] % modCount);
                // 分析1<= s[i-2,i-1] <=26的场景，考虑{dp[i-2],s[i-2,i-1]}的decodingways
                if (s.charAt(i - 2) == '1') {
                    // s[i-2,i-1]可取值：11,12...19
                    dp[i] += 9 * (dp[i - 2] % modCount);
                } else if (s.charAt(i - 2) == '2') {
                    // s[i-2,i-1]可取值：21,22...26
                    dp[i] += 6 * (dp[i - 2] % modCount);
                } else if (s.charAt(i - 2) == '*'){
                    // s[i-2,i-1]可取值：11,12...19,21,22...26
                    dp[i] += 15 * (dp[i - 2] % modCount);
                }
            }
            dp[i] %= modCount;
        }
        return (int) dp[s.length()];
    }
    /**
     * Wrong Answer，思考得过于复杂，希望穷举出任意两个字符的decodingways，导致出现了各种逻辑错误
     * 直接分析s[i]='0', '1-9', '*'的情况即可
     */
//    class Solution {
//        /**
//         * @param s: a message being encoded
//         * 1. dp[n] == '0', dp[n] = dp[n-2]*(s[n-1,n]的decodingways)
//         * 2. dp[n] != '0',dp[n] = dp[n-2]*(s[n-1, n]的decodingways) + dp[n-1]*(s[n]的decodingways)
//         * 此时方程1可以合并到2，因为s[n]=='0'时，s[n]的decodingways = 0
//         * 为了避免重复计算，需要记录每个s[n] or s[n-1,n]的decodingways
//         * @return: an integer
//         */
//        public int numDecodings(String s) {
//            if (null == s || 0 == s.length()) {
//                return 0;
//            }
//            Map<String, Integer> substrDecodingWays = new HashMap<>();
//            int[] dp = new int[s.length()];
//            dp[0] = calSubstrLessThan2CharDecodingWays(substrDecodingWays, s.substring(0, 1));
//            if (s.length() == 1) {
//                return dp[0];
//            }
//            // int modNum = 1000000000;
//            dp[1] = calSubstrLessThan2CharDecodingWays(substrDecodingWays, s.substring(0, 2));
//            for (int i = 2; i < s.length(); i++) {
//                dp[i] = dp[i - 1] * calSubstrLessThan2CharDecodingWays(substrDecodingWays, s.substring(i, i + 1))
//                        + dp[i - 2] * calSubstrLessThan2CharDecodingWays(substrDecodingWays, s.substring(i - 1, i + 1));
//                // dp[i] = dp[i] % modNum + 7;
//            }
//            return dp[s.length() - 1];
//        }
//
//        private int calSubstrLessThan2CharDecodingWays(Map<String, Integer> substrDecodingWays, String s) {
//            if (substrDecodingWays.containsKey(s)) {
//                return substrDecodingWays.get(s);
//            }
//            int result = 0;
//            if (s.length() == 1) {
//                if (s.charAt(0) == '0') {
//                    result = 0;
//                } else if (s.charAt(0) == '*') {
//                    result = 9;
//                } else {
//                    result = 1;
//                }
//            } else if (s.length() == 2) {
//                //s[1]和s[0]单独decode
//                result = calSubstrLessThan2CharDecodingWays(substrDecodingWays, s.substring(0, 1))
//                        * calSubstrLessThan2CharDecodingWays(substrDecodingWays, s.substring(1));
//                //s[0,1]整体decode，15种
//                if (s.charAt(1) == '*') {
//                    // s[0]* 的组合情况
//                    if (s.charAt(0) == '*') {
//                        result += 15;
//                    } else if (s.charAt(0) == '1') {
//                        result += 9;
//                    } else if (s.charAt(1) == '2') {
//                        result += 6;
//                    }
//                } else {
//                    if (s.charAt(0) == '*') {
//                        // *s[1]，而且s[1]!='*'的情况
//                        if (s.charAt(1) == '0') {
//                            result += 2;
//                        } else if (s.charAt(1) <= '6') {
//                            result += 2;
//                        } else {
//                            result += 1;
//                        }
//                    }
//                }
//            }
//            substrDecodingWays.put(s, result);
//            return result;
//        }
//    }
}
