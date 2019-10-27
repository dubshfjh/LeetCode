import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

public class Leetcode433 {
    class Solution {
        private final char[] MUTATION = {'A', 'C', 'G', 'T'};
        /**
         * 利用BFS思想，第i层的BFS代表修改了i+1个字母，
         * 在每一层处理curWord时，将它的每一位依次修改为'A','C','G','T'，如果修改后的单词未访问&&处于bank，则添加到队列尾部，用于下一轮的BFS
         * @param start
         * @param end
         * @param bank
         * @return
         */
        public int minMutation(String start, String end, String[] bank) {
            if (null == start || null == end || null == bank || 0 == bank.length) {
                return -1;
            }
            if (start.equals(end)) {
                return 0;
            }
            Set<String> bankSet = new HashSet<>(bank.length);
            for (String oneWord : bank) {
                bankSet.add(oneWord);
            }
            if (!bankSet.contains(end)) {
                return -1;
            }
            Set<String> visitedWords = new HashSet<>();
            Queue<String> bfsQueue = new LinkedList<>();
            bfsQueue.offer(start);
            visitedWords.add(start);
            int step = 0;
            while (!bfsQueue.isEmpty()) {
                int curLevelSize = bfsQueue.size();
                step++;
                for (int i = 0; i < curLevelSize; i++) {
                    String curWord = bfsQueue.poll();
                    StringBuilder newWordBuilder = new StringBuilder(curWord);
                    String newWord = null;
                    for (int j = 0; j < curWord.length(); j++) {
                        for (int k = 0; k < MUTATION.length; k++) {
                            newWordBuilder.setCharAt(j, MUTATION[k]);
                            newWord = newWordBuilder.toString();
                            if (!visitedWords.contains(newWord) && bankSet.contains(newWord)) {
                                if (newWord.equals(end)) {
                                    return step;
                                }
                                visitedWords.add(newWord);
                                bfsQueue.offer(newWord);
                            }
                            newWordBuilder.setCharAt(j, curWord.charAt(j));
                        }
                    }
                }
            }
            return -1;
        }
    }

    Solution solution = new Solution();

    public static void main(String[] args) {
        Leetcode433 leetcode433 = new Leetcode433();
        String start = "AAAACCCC";
        String end = "CCCCCCCC";
        String[] bank = {"AAAACCCA","AAACCCCA","AACCCCCA","AACCCCCC","ACCCCCCC","CCCCCCCC","AAACCCCC","AACCCCCC"};
        System.out.println(leetcode433.solution.minMutation(start, end, bank));
    }
}
