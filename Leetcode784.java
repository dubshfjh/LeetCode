import java.util.LinkedList;
import java.util.List;

public class Leetcode784 {
    class Solution {
        public List<String> letterCasePermutation(String S) {
            List<String> result = new LinkedList<>();
            if (null == S || 0 == S.length()) {
                return result;
            }
            permutation(result, S, 0, new StringBuilder());
            return result;
        }

        private void permutation(List<String> result, String S, int curIndex, StringBuilder temp) {
            if (S.length() == curIndex) {
                result.add(temp.toString());
                return;
            }
            char curChar = S.charAt(curIndex);
            temp.append(curChar);
            permutation(result, S, curIndex + 1, temp);
            temp.deleteCharAt(curIndex);
            if (curChar < '0' || curChar > '9') {
                // 字母
                char anotherChar = curChar > 'Z' ? (char) (curChar - ('a' - 'A')) : (char) (curChar + ('a' - 'A'));
                temp.append(anotherChar);
                permutation(result, S, curIndex + 1, temp);
                temp.deleteCharAt(curIndex);
            }
        }
    }
}
