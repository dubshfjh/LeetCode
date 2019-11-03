import java.util.ArrayList;
import java.util.List;

public class Leetcode1023 {
    class Solution {
        public List<Boolean> camelMatch(String[] queries, String pattern) {
            List<Boolean> result = new ArrayList<>();
            if (null == queries || 0 == queries.length) {
                return result;
            }
            for (String queryWord : queries) {
                result.add(match(queryWord, pattern));
            }
            return result;
        }

//        /**
//         * 利用动态规划思想，类比为s1 通过insert/update/delete 变为s2的问题
//         * 1) queryWord[i]为小写字母：此时可以在pattern中插入字母来匹配queryWord[i]
//         *    dp[i][j] = dp[i-1][j]（ps:用插入的字母来匹配queryWord[i]） || (dp[i-1][j-1] && queryWord[i]==pattern[j]) (ps:直接用pattern[j]来匹配queryWord[i]）
//         * 2) queryWord[i]为答谢字母：此时只能使用patern[j]来匹配queryWord[i]
//         * @param queryWord
//         * @param pattern
//         * @return
//         */
//        private boolean match(String queryWord, String pattern) {
//            boolean[][] match = new boolean[queryWord.length() + 1][pattern.length() + 1];
//            // match[0][1...n] = false, match[1..m][0] 视queryWord[i]是否为小写字母而定
//            match[0][0] = true;
//            for (int i = 1; i <= queryWord.length(); i++) {
//                if ('a' <= queryWord.charAt(i - 1) && 'z' >= queryWord.charAt(i - 1)) {
//                    match[i][0] = match[i - 1][0];
//                } else {
//                    break;
//                }
//            }
//            for (int i = 1; i <= queryWord.length(); i++) {
//                for (int j = 1; j <= pattern.length(); j++) {
//                    match[i][j] = match[i - 1][j - 1] && queryWord.charAt(i - 1) == pattern.charAt(j - 1);
//                    if ('a' <= queryWord.charAt(i - 1) && 'z' >= queryWord.charAt(i - 1)) {
//                        match[i][j] = match[i][j] || match[i - 1][j];
//                    }
//                }
//            }
//            return match[queryWord.length()][pattern.length()];
//        }

        /**
         * 动态规划思想的瑕疵在于：不太好中途剪枝，考虑使用双指针+剪枝法
         * 1. j<pattern.length && queryWord[i] == pattern[j]，直接i++，j++，因为即使当前字母为小写，可以用"插入新字母"的方式匹配掉，
         *    下一步patter[j]也需要与queryWord[i+1]匹配才行；它的等价思想是：用patter[j]匹配掉queryWord[i]，用"插入新字母"的方式匹配掉queryWord[i+1]
         * 2. j==pattern.length 或者 二者不相等，如果此时queryWord[i]为小写字母，则i++，j保持不变，即"插入新字母"的方式匹配掉queryWord[i]，下一步检测patter[j]与queryWord[i+1]
         *    如果此时queryWord[i]为大写字母，则直接返回false
         * @param queryWord
         * @param pattern
         * @return
         */
        private boolean match(String queryWord, String pattern) {
            int i = 0, j = 0;
            while (i < queryWord.length()) {
                if (j < pattern.length() && queryWord.charAt(i) == pattern.charAt(j)) {
                    i++;
                    j++;
                } else if ('a' <= queryWord.charAt(i) && 'z' >= queryWord.charAt(i)) {
                    // 如果pattern[j]已经到了最后1个字母，那么只能期望queryWord[i...m-1]全部为小写字母，否则就直接进入第3个子判断返回false
                    i++;
                } else {
                    return false;
                }
            }
            return j == pattern.length();
        }
    }

    Solution solution = new Solution();

    public static void main(String[] args) {
        Leetcode1023 leetcode1023 = new Leetcode1023();
        String[] queries = {"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"};
        String pattern = "FB";
        leetcode1023.solution.camelMatch(queries, pattern).forEach(s -> System.out.print(s + ","));
    }
}
