public class Leetcode953 {
    class Solution {
        public boolean isAlienSorted(String[] words, String order) {
            if (null == words || 1 >= words.length || null == order) {
                return true;
            }
            int[] charOrder = new int[26];
            for (int i = 0; i < order.length(); i++) {
                charOrder[order.charAt(i) - 'a'] = i;
            }
            for (int i = 1; i < words.length; i++) {
                if (compareWords(words[i - 1], words[i], charOrder) < 0) {
                    return false;
                }
            }
            return true;
        }

        private int compareWords(String wordOne, String wordTwo, int[] charOrder) {
            int minWordLen = Math.min(wordOne.length(), wordTwo.length());
            for (int i = 0; i < minWordLen; i++) {
                // charOrder[i]越小，该字母优先级越高
                if (charOrder[wordOne.charAt(i) - 'a'] < charOrder[wordTwo.charAt(i) - 'a']) {
                    return 1;
                } else if (charOrder[wordOne.charAt(i) - 'a'] > charOrder[wordTwo.charAt(i) - 'a']) {
                    return -1;
                }
            }
            if (wordOne.length() == wordTwo.length()) {
                return 0;
            } else {
                // 更短的单词优先级更高
                return wordOne.length() == minWordLen ? 1 : -1;
            }
        }
    }
}
