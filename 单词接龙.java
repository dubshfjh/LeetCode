吸取的经验 & 教训
一、 DFS 在路径搜索时，需要使用 1 个 visited 避免搜索路径出现回环；标准的 BFS 对每个节点只遍历 1 次，因此不需要 visited 数组 
二、 除非是求所有可行解，否则优先使用BFS，
三、 标准的 BFS 无法提供记录"搜索路径"长度的功能，因此转化为"层次遍历"的思想，每一层上的路径长度都是一致的，当前处于第 i 层 <==> 当前搜索路径长度为 i
四、 BFS 的 "层次遍历格式"，任意节点 A 在同一层次中可能出现多次(毕竟节点 A 可能作为多个上层节点的 neighbors)
      因此也需要 visited 数组，防止 本层次 or 子孙层次搜索出环

1. 提前计算出"字典中每个单词"的邻居列表，然后使用BFS搜索出抵达 end 的路径
2. 将 start 和 end 本身添加到字典中，避免在搜索 单词路径 时，还需要通过计算 editDistance 寻找 {路径上第2个节点(也就字典中第 1 个节点), 
    以及路径上倒数第2个节点(也就是字典中最后 1 个节点)}，将它们本身添加到 字典中 后，路径上的第i个节点就 对应 字典中的第i个节点了
    避免再使用 editDistance
3. BFS 搜索时要计算每条路径的长度有一点困难，转化为"层次遍历"的思想，每一层上的路径长度都是一致的，
    第 j 层节点回搜到 第 0 ... j - 1层的节点，造成回环只需要避免 
public class Solution {
    /**
      * @param start, a string
      * @param end, a string
      * @param dict, a set of string
      * @return an integer
      */
    public int ladderLength(String start, String end, Set<String> dict) {
        // write your code here
        Map<String, List<String>> neighbors = new HashMap<>();
        if (start.equals(end)) {
            return 1;
        }
        //将 start 和 end 本身添加到字典中
        dict.add(start);
        dict.add(end);
        for (String s : dict) {
            neighbors.put(s, getNeighbors(s, dict));
        }
        Queue<String> path = new LinkedList<>();
        Set<String> visited = new HashSet<>(); // 防止 BFS 的第 j 层节点回搜到 第 0 ... j - 1层的节点，造成回环
        path.add(start);
        visited.add(start);

        int resLen = Integer.MAX_VALUE;
        int curLevel = 0;

        while (!path.isEmpty()) { //BFS搜索时，每一层上的路径长度都是一致的，转化为"层次遍历"的思想
            curLevel++;
            int nodeNum = path.size();
            for (int i = 0; i < nodeNum; i++) {
                String curWord = path.poll();

                for (String nextword : neighbors.get(curWord)) {
                    if (nextword.equals(end)) {
                        resLen = Math.min(resLen, 1 + curLevel);
                        return resLen; //由于第i层的路径长度为i ，当第一次在某层遇到的nextword为终点单词时，其实就是最短长度的路径
                    }
                    if (!visited.contains(nextword)) {
                        path.offer(nextword);
                        visited.add(nextword);
                    }
                }
            }
        }
        return (resLen == Integer.MAX_VALUE) ? -1 : resLen;
    }

    private List<String> getNeighbors(String s, Set<String> dict) {
        List<String> neighbors = new LinkedList<>();
        for (int i = 0; i < s.length(); i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                String nextword = changeWord(s, i, c);
                if (dict.contains(nextword)) {
                    neighbors.add(nextword);
                }
            }
        }
        return neighbors;
    } 

    private String changeWord(String s, int i, char c) {
        StringBuilder tmp = new StringBuilder(s);
        tmp.setCharAt(i, c);
        return tmp.toString();
        /*
        char[] tmp = s.toCharArray();
        tmp[i] = c;
        return new String(tmp);
        */
    }

}

以下算法"逻辑有错误"，而且在计算字典中单词的邻居时可能存在重复计算！！！还是先提前计算出"字典中每个单词"的邻居列表，然后使用BFS搜索出抵达 end 的路径，简单明了

采用 {记忆化搜索 + dfs搜索单词路径}，其中路径的起点和终点分别为 start & end，只需要分析单词路径上位于 字典内部 的单词
每层递归都返回 当前word -> end 的最短路径

1. 由于(起始单词 != 终止单词)，字典中的起始单词一定是start的neighbor，但是终止单词可能为{end本身 || end的neighbor}
2. 如果 from 是 to 的邻居节点，则返回 1；如果 from.equals(to)，则 返回 0！！！
3. 对当前单词 word, 对每个字母遍历 [0] ... [len - 1] 处的字符，对每个字符使用 'a' -> 'z' 进行替换得到 len * 26 个 nextword
    为每个 nextword 开启下一层递归搜索，分治法 Merge 每个子递归的结果后，返回 1 + Min{子递归路径长度}  

ps：注意 dfs 搜索时要用 1 个 visit 数组，防止搜索出环
public class Solution {
    /**
     * @param start, a string
     * @param end, a string
     * @param dict, a set of string
     * @return an integer
     */
    private Map<String, Integer> memory;

    public int ladderLength(String start, String end, Set<String> dict) {
        // write your code here
        memory = new HashMap<>();
        for (String s : dict) {
            memory.put(s, -1);
        }
        int wordIndex = 0;
        int minLen = Integer.MAX_VALUE;
        Set<String> path = new HashSet<String>();
        path.add(start);
        for (String s : dict) {
            if (editDistance(start, s) == 1) { //字典中的起始单词一定是start的neighbor，但是终止单词可能为{end本身 || end的neighbor}
                int nextChangeNum = search(s, end, dict, path);
                if (nextChangeNum < Integer.MAX_VALUE) { //从当前s->end存在可行解
                    int changeNum = 1 + nextChangeNum;
                    minLen = Math.min(minLen, 1 + changeNum); //start->a->end,change 2 次,变更序列长度为3
                }
            }
        }
        return (minLen == Integer.MAX_VALUE) ? 0 : minLen;
    }

    private int editDistance(String from, String to) {
        if (from.length() != to.length()) {
            return -1;
        }
        int dis = 0;
        for (int i = 0; i < from.length(); i++) {
            if (from.charAt(i) != to.charAt(i)) {
                dis++;
            }
        }
        return dis;
    }

    private int search(String from, String to, Set<String> dict, Set<String> path) {
        if (memory.get(from) != -1) {
            return memory.get(from);
        }
        //minState
        if (editDistance(from, to) == 1) { //终止单词为end的neighbor
            memory.put(from, 1);
            return 1;
        } else if (from.equals(to)) { //终止单词可能为end本身,e.g. dict:a,b,c;start:a;end:c. 此时可达路径为 a->b(属于dict, 为end的邻居)->c(end)；a->c(属于dict, 为end本身)
            memory.put(from, 0);
            return 0;
        }

        path.add(from);
        int minChange = Integer.MAX_VALUE;
        for (int i = 0; i < from.length(); i++) {
            for (char j = 'a'; j <= 'z'; j++) {
                StringBuilder temp = new StringBuilder(from);
                temp.setCharAt(i, j);
                String nextWord = temp.toString();
                if (dict.contains(nextWord) && !path.contains(nextWord)) {
                    int nextChangeNum = search(nextWord, to, dict, path);
                    if (nextChangeNum < Integer.MAX_VALUE) {
                        minChange = Math.min(minChange, 1 + nextChangeNum); //1 + 2146473847 = -2147483648，会导致计算错误
                    }
                    // minNum = Math.min(minNum, 1 + search(nextWord, to, dict, path));
                }
            }
        }
        path.remove(from);
        memory.put(from, minChange);
        return minChange;
    }

    public static void main(String[] args) {
        Set<String> dict = new HashSet<>();
        dict.add("hit");
        dict.add("hot");
        dict.add("dot");
        dict.add("dog");
        dict.add("cog");
        String start = "hit";
        String end = "cog";
        Solution obj = new Solution();
        int res = obj.ladderLength(start, end, dict);
        System.out.println(res);
    }
}