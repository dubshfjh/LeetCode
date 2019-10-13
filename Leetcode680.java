public class Leetcode680 {
    class Solution {
        /**
         * 拥有1次删除字母的资格，而且需要O(n)复杂度，则考虑双指针碰撞的思想
         * 1.[start] == [end], start++, end--
         * 2.[start] != [end]
         *   2.1 考虑删除[start]字母，则s{start + 1, start + 2...end} 必须为回文串，因为无法再删除别的字母
         *   2.2 考虑删除[end]字母，则s{start...end-1}必须为回文串
         * @param s
         * @return
         */
        public boolean validPalindrome(String s) {
            if (null == s || 1 >= s.length()) {
                return true;
            }
            int start = 0, end = s.length() - 1;
            while (start < end) {
                if (s.charAt(start) == s.charAt(end)) {
                    start++;
                    end--;
                } else {
                    return isPanlidrome(s, start + 1, end) || isPanlidrome(s, start, end - 1);
                }
            }
            return true;
        }

        private boolean isPanlidrome(String s, int start, int end) {
            while (start < end) {
                if (s.charAt(start) == s.charAt(end)) {
                    start++;
                    end--;
                } else {
                    return false;
                }
            }
            return true;
        }
    }

    Solution solution = new Solution();
    public static void main(String[] args) {
        Leetcode680 leetcode680 = new Leetcode680();
        String s = "abc";
        leetcode680.solution.validPalindrome(s);
    }
}
