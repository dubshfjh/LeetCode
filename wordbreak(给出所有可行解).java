记忆化搜索思想：使用Map记录每个String对应的可行解List，每层递归在对上一层传过来的子串s做分析之前，首先判断s在之前已经有可行解，如果有则直接返回Map.get(s)
如果没有则将s分割为左子串：s[0...leftLen-1]；右子串：s[leftLen...s.length()-1]，只有当字典.contains(其中1个子串)时，才递归获取(另一侧的子串)的List，
	将子串 与 List 组合后的结果作为本层递归分析的结果返回，并记录在Map中

关于递归分析 左侧子串 还是 右侧子串 的问题：时间复杂度本质好像是相同的，但最开始的时候 { 在字典中查找左子串，递归分析右子串 }导致了超时，这可能是递归分析右子串时最大长度没控制号

Test Case："aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa"]，此时字典中单词最大长度为maxLen=7
1. 如果递归分析右子串：则 leftLen = 0...maxLen的情况下，7个左子串都包含在dict中，于是首先递归分析 s[1...]，然后递归分析s[2...],s[3...],s[4...]。
	虽然采用了记忆化搜索，但由于首先递归分析s[1...]，看上去并不能用到打小抄记录的结果(但实际上的复杂度并没有增加)

但根据记忆化搜索的原理，以"aaaa"为例，{"aaaa","aaa","aa","a"}中的每个子串都只会递归搜索一次，较短子串的结果也是直接从Map中取到的，不需要重复递归Solution树


2. 如果递归分析右子串，由于 leftLen + rightLen = s.length()，而且 0 <= rightLen <= maxLen，于是 leftLen = max(0, s.length() - maxLen); leftLen < s.length(); leftLen++
	此时 被递归的右子串长度从 maxLen 遍历到 1，实质上也是先递归分析最长的子串，再递归较短的子串，但是时间复杂度应该并不比 "先递归较短子串，再递归较长子串"差

public class Solution {
    /**
     * @param s a string
     * @param wordDict a set of words
     */
    Map<String, List<String>> record;
    public List<String> wordBreak(String s, Set<String> wordDict) {
        // Write your code here
        int maxLen = 0;
        for (String temp : wordDict) {
            maxLen = Math.max(maxLen, temp.length());
        }
        record = new HashMap<>();
        return helpWordBreak(s, wordDict, maxLen);
    }

    private List<String> helpWordBreak(String s, Set<String> wordDict, int maxLen) {
        List<String> res = new ArrayList<String>();
        if (s == null || s.length() == 0) {
            return res;
        } else if (record.containsKey(s)) {
            return record.get(s);
        } else { //从字典中搜索右侧单词：[leftLen...s.length()-1] ； 递归获取左侧单词的List：[0...leftLen-1]
            int minLeftLen = Math.max(s.length() - maxLen, 0); //因为rightWord 长度<=maxLen,所以leftLen >= s.length() - maxLen
            for (int leftLen = minLeftLen; leftLen < s.length(); leftLen++) {
                String rightWord = s.substring(leftLen);
                if (wordDict.contains(rightWord)) {
                    if (leftLen == 0) {
                        res.add(rightWord);
                    } else {
                        List<String> leftList = helpWordBreak(s.substring(0, leftLen), wordDict, maxLen); //
                        for (String leftWord : leftList) {
                            res.add(leftWord + " " + rightWord);
                        }
                    }
                }
            }
            record.put(s, res);
            return res;
            /* 这段代码：当字典中包含左侧字符串时，递归分析右半侧子串，这样的话对于“aaaaaaaa”：由于"a"存在于字典，会先递归分析"7个a"；
                然后由于"aa"存在于字典，会先递归分析"6个a"；由于"aaa"存在于字典，会接着递归分析"4个a"...
                先递归分析长子串，再递归分析短子串，达不到DP打小抄的作用！！！
                【因此换方向思考，首先在字典中查找右侧子串，如果存在于字典，再递归分析左侧的较短子串！！！！】
            StringBuilder curWord = new StringBuilder();
            for (int i = 0; i < maxLen && i < s.length(); i++) {
                curWord.append(s.charAt(i));
                if (wordDict.contains(curWord.toString())) {
                    if (i == s.length()) {
                        res.add(s);
                    } else {
                        List<String> rightList = helpWordBreak(s.substring(i + 1), wordDict, maxLen);
                        for (String rightStr : rightList) {
                            res.add(curWord.toString() + " " + rightStr);
                        }
                    }
                }
            }
            */
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            String s = sc.nextLine();
//            sc.nextLine();
            int n = sc.nextInt();
            Set<String> dict = new HashSet<>();
            sc.nextLine();
            for (int i = 0; i < n; i++) {
                dict.add(sc.nextLine());
            }
            Solution obj = new Solution();
            List<String> res = obj.wordBreak(s, dict);
            System.out.println(res);
        }
    }
}


递归版超时代码：对于 helpWordBreak(s, dict, path, index)，for j = index...index+maxLen，如果dict包含 s[index...j]，则在path中添加字符串，递归分析j+1
但是遇到超时case："aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]

 这种情况下，如果不使用DP思想打小抄，则会重复地遍历Solution Tree中的相同子树

// public class Solution {
//     /**
//      * @param s a string
//      * @param wordDict a set of words
//      */
//     private List<String> res;
//     private int maxLen;
//     public List<String> wordBreak(String s, Set<String> wordDict) {
//         // Write your code here
//         res = new ArrayList<>();
//         // List<String> path = new ArrayList<String>();
//         StringBuilder path = new StringBuilder();
//         if (s == null || s.length() == 0 || wordDict.size() == 0) {
//             return res;
//         }
        // for (String temp : wordDict) {
        //     maxLen = Math.max(maxLen, temp.length());
        // }
//         helpWordBreak(s, wordDict, path, 0);
//         return res;
//     }

//     private void helpWordBreak(String s, Set<String> wordDict, StringBuilder path, int index) {
//         if (index == s.length()) {
//             res.add(path.toString());
//             return;
//         }
//         StringBuilder curWord = new StringBuilder();
//         for (int i = index; i < index + maxLen && i < s.length(); i++) {
//             curWord.append(s.charAt(i));
//             String curwordStr = curWord.toString();
//             if (wordDict.contains(curwordStr)) {
//                 int oldSize = path.length();
//                 if (oldSize == 0) {
//                     path.append(curwordStr);
//                 } else {
//                     path.append(" " + curwordStr);
//                 }
//                 helpWordBreak(s, wordDict, path, i + 1);
//                 path.delete(oldSize, path.length());
//             }
//         }
//     }

//     // public static void main(String[] args) {
//     //     Scanner sc = new Scanner(System.in);
//     //     while (sc.hasNext()) {
//     //         String s = sc.nextLine();
//     //         int n = sc.nextInt();
//     //         Set<String> dict = new HashSet<>();
//     //         sc.nextLine();
//     //         for (int i = 0; i < n; i++) {
//     //             dict.add(sc.nextLine());
//     //         }
//     //         Solution obj = new Solution();
//     //         obj.wordBreak(s, dict);
//     //     }
//     // }
// }
