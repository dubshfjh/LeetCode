1. 首先基于Hash表的思想，使用 int[256] needToFind 统计target中每个字符的出现次数，使用 int[256] hasFound 记录 source中每个字符出现次数
	在第一次满足 hasFound 完全覆盖 needToFind后，始终维持 hasFound 对 needToFind 的覆盖。
	然后使用变量 findCharsCnt 记录 hasFound中被完全覆盖了的字符总数量，用于判断两个窗口的重叠程度
2. 遍历 source 字符串，不论 source[i] 是否属于 needToFind，都执行 hasFound[source[i]] += 1，
	但只对source中属于 needToFind  的字符执行 step 3 to 4  
3.  如果 hasFound[字符i] == needToFind[字符i]，说明字符i再次被完全覆盖, findCharsCnt += needToFind[字符i]

4.1 如果 findCharsCnt == target.length()，即整个 target 再次被完全覆盖，则需要记录此时的 "最小子串(极限压缩子串的左边界startIdx，
	更新 hasFound，直到子串删除[startIdx]会导致hasFound不能完全覆盖needToFind)"，即hasFound[startIdx] == needToFind[startIdx])
4.2 在极限压缩子串左边界完成后，需要将当前最小子串的左边界再右移1次，findCharsCnt--，从而寻找下一个最小子串

5. 从 4.1 得到的所有最小子串中，调选长度最小的子串

public class Solution {
    /*
     * @param source : A string
     * @param target: A string
     * @return: A string denote the minimum window, return "" if there is no such a string
     */
    public String minWindow(String source , String target) {
        // write your code here
        if (source == null || source.length() < target.length()) {
            return "";
        }

        int findCharsCnt = 0;
        int[] needToFind = new int[256];
        int[] hasFound = new int[256]; //我们只需要统计 needToFind[] 中出现过的字符数量
        int startIdx = 0;
        List<String> substrList = new LinkedList<>();
        for (char c : target.toCharArray()) {
            needToFind[c]++;
        }

        for (int i = 0; i < source.length(); i++) {
            int curCharIdx = source.charAt(i);
            hasFound[curCharIdx]++;
            if (needToFind[curCharIdx] > 0) { //只分析真正需要的字母
                if (needToFind[curCharIdx] == hasFound[curCharIdx]) { //某个字符的数量第一次到达所需值
                    findCharsCnt += needToFind[curCharIdx];
                    if (findCharsCnt == target.length()) { //此时{startIdx...i}再一次找到所需的全部字符
                        // 右移子串的左边界直到极限，直到某个hasFound[所需字符] 即将< needToFind[所需字符]
                        boolean windowReachLimit = false;

                        //while (startIdx < i && !windowReachLimit) { //由于target长度可能为1，所以判断条件应该是 startIdx <= i，而不是 <
                        while (startIdx <= i && !windowReachLimit) {  //
                            int deleteCharIdx = source.charAt(startIdx);
                            if (needToFind[deleteCharIdx] > 0 && hasFound[deleteCharIdx] == needToFind[deleteCharIdx]) { //因为hasFound[]每个字符的发现数量 >= needToFind[]每个字符的所需数量，所以此时左边界压缩到了极限
                                String oneRes = source.substring(startIdx, i + 1); //先记录此时的结果
                                System.out.println(oneRes);
                                substrList.add(oneRes);
                                findCharsCnt--;
                                startIdx++;
                                windowReachLimit = true;
                            } else { //当{字符不属于needToFind || 扣减完这个字符仍然能够抵消所有needToFind时，都可以继续右移左边界
                                startIdx++;
                            }
                            hasFound[deleteCharIdx]--; //将当前的字符移除


//                            if (needToFind[deleteCharIdx] == 0) { 判断条件不够，
//                                startIdx++;
//                            }
                        }
                    }
                }
            }
        }
        return getMinSubstr(substrList);
    }

    private String getMinSubstr(List<String> substrs) {
        if (substrs == null || substrs.size() == 0) {
            return "";
        }
        Collections.sort(substrs, new Comparator<String>() {
            @Override
            public int compare(String o1, String o2) {
                return o1.length() - o2.length(); //当o1, o2长度相等时，o1这个起始Index较小的字符串应该在左侧
            }
        });
        return substrs.get(0);
    }
    public static void main(String[] args) {
        String source = "abc";
        String target = "a";
        Solution obj = new Solution();
        System.out.println(obj.minWindow(source, target));
    }
}
