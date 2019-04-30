import java.util.Arrays;

public class Lintcode638 {
    class Solution {
        /**
         * @param s: a string
         * @param t: a string
         * @return: true if the characters in s can be replaced to get t or false
         */
        public boolean isIsomorphic(String s, String t) {
            // write your code here
            if (null == s || null == t) {
                return null == s && null == t;
            }
            if (s.length() != t.length()) {
                return false;
            }
            int[] dictionary = new int[256];
            Arrays.fill(dictionary, -1);
            // analyse "aac"->"bdc", record a->b&&a->d, so return false
            if (!checkMappingChar(dictionary, s, t)) {
                return false;
            }

            Arrays.fill(dictionary, -1);
            // analyse "adc"->"bbc", record b->a&&b->d, so return false
            return checkMappingChar(dictionary, t, s);
        }

        private boolean checkMappingChar(int[] dictionary, String first, String second) {
            for (int i = 0; i < first.length(); i++) {
                if (dictionary[first.charAt(i)] == -1) {
                    dictionary[first.charAt(i)] = second.charAt(i);
                } else {
                    if (dictionary[first.charAt(i)] != second.charAt(i)) {
                        return false;
                    }
                }
            }
            return true;
        }
    }
}
