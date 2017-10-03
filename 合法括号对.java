合法括号对的字符串S满足：对于 i = 0...len - 1：s[0...i]这个子串中 Count(左括号) >= Count(右括号)
1. 递归的 越界 终止条件：Count(左括号) > n || Count(右括号) > n || Count(左括号) + Count(右括号) > 2n || Count(右括号) > Count(左括号)，这些不合法情况：直接返回
2. 递归的 边界 终止条件：Count(左括号) + Count(右括号) == 2n，则记录此时的结果
3. 对于每一层递归存在2种选择：{添加左括号；添加右括号}，在递归添加右括号时，别忘了移除 '('；在递归返回上一层时，别忘了移除本层的添加的所有字符，此时还剩下 ')'等待移除
PS: StringBuilder 没有pop()方法，只存在 deleteCharAt(int index) 方法
public class Solution {
    /*
     * @param n: n pairs
     * @return: All combinations of well-formed parentheses
     */
    public List<String> generateParenthesis(int n) {
        // write your code here
        List<String> record = new LinkedList<>();
        if (n <= 0) {
        	return record;
        }
        StringBuilder temp = new StringBuilder();
        helpGenerate(n, 0, 0, record, temp);
        return record;
    }

    private void helpGenerate(int n, int leftCnt, int rightCnt, List<String> record, StringBuilder temp) {
    	if (leftCnt > n || rightCnt > n || leftCnt < rightCnt) {
    		return;
    	} else if (leftCnt + rightCnt == (n << 1)) {
    		record.add(temp.toString());
    		return;
    	} else { //递归的每一层有2种选择：添加左括号；添加右括号
    		temp.append("(");
    		helpGenerate(n, leftCnt + 1, rightCnt, record, temp);
    		temp.deleteCharAt(temp.length() - 1);
    		
    		temp.append(")");
    		helpGenerate(n, leftCnt, rightCnt + 1, record, temp);
    		temp.deleteCharAt(temp.length() - 1); //递归返回上一层时，别忘了移除本层添加的字符
    	}
    }
}