1. 动态规划，定义match[i][j]：s[0...i-1]与p[0...j-1]是否匹配
2. 状态转移方程：
    1) s[i-1]==p[j-1] or p[j-1]=='.'，则match[i][j] = match[i-1][j-1]
    2) j>=2 and p[j-1]=='*'，则 
        a) *代表增加2次以上出现，e.g s:aaaaa；p：a*，则match[5][2] = [4][2] = [3][2] = [2][2] = [2-1][2-1]
            match[i][j] = match[i-1][j]
        b) *代表增加1次出现，e.g s:aa；p:a*,则match[2][2] = [1][1]
            match[i][j] = match[i-1][j-1]
        c) *代表增加0次出现，e.g. s：a；p：a*，则match[1][2] = [1][1]
            match[i][j] = match[i][j-1]
        d) *代表抵消1次出现，e.g. s："b"；p："ba*"，则match[1][3] = [1][1]
            match[i][j] = match[i][j-2]
3. 初始化
    2.1 match[i][0] = false;
    2.2 a) j>=2 and p[j-1]=='*'，则match[0][j] = match[0][j-2]
        b) else：match[0][j] = false
4. 结果
    return match[s.length()][p.length()]
public class Solution {
    /**
     * @param s: A string
     * @param p: A string i，则ncludes "." and "*"
     * @return: A boolean
     */
    public boolean isMatch(String s, String p) {
        // write your code here
        if (s == null || s.length() == 0) {
            return p == null || p.length() == 0;
        }

        boolean[][] match = new boolean[s.length() + 1][p.length() + 1];
        match[0][0] = true;
        for (int i = 1; i <= p.length(); i++) {
            if (i >= 2 && p.charAt(i - 1) == '*') { //*代表抵消1次出现，即使得p[j-2]出现0次，e.g. s：""；p："a*"
                match[0][i] = match[0][i - 2];
            } else {
                match[0][i] = false;
            }
        }

        for (int i = 1; i <= s.length(); i++) {
            match[i][0] = false;
        }
        for (int i = 1; i <= s.length(); i++) {
            for (int j = 1; j <= p.length(); j++) {
                if (s.charAt(i - 1) == p.charAt(j - 1)) {
                    match[i][j] = match[i - 1][j - 1];
                } else {
                    if (p.charAt(j - 1) == '.') {
                        match[i][j] = match[i - 1][j - 1];
                    } else if (j >= 2 && p.charAt(j - 1) == '*') {
                        if (s.charAt(i - 1) == p.charAt(j - 2) || p.charAt(j - 2) == '.') {
                            //*代表增加2次以上出现，e.g s:aaaaa；p：a*，则match[5][2] = [4][2] = [3][2] = [2][2] = [2-1][2-1]
                            match[i][j] |= match[i - 1][j];
                            //*代表增加1次出现，e.g s:aa；p:a*,则match[2][2] = [1][1]
                            match[i][j] |= match[i - 1][j - 1]; // 用*抵消掉s[i-1]处的字符，此时相当于s[0...i-2] 匹配 p[0...j-2]
                            //*代表增加0次出现，e.g. s：a；p：a*，则match[1][2] = [1][1]
                            match[i][j] |= match[i][j - 1]; //*相当于不存在，于是s[0...i-1] 匹配 p[0...j-2]
                        }
                        //*代表抵消1次出现，e.g. s："b"；p："ba*"，则match[1][3] = [1][1]
                        match[i][j] |= match[i][j - 2]; //即使得p[j-2]出现0次，于是s[0...i-1] 匹配 p[0...j-3]
                    }
                }
            }
        }
//        for (boolean[] temp : match) {
//            for (boolean temp1 : temp) {
//                System.out.print(temp1 + " ");
//            }
//            System.out.println();
//        }
        return match[s.length()][p.length()];
    }
}