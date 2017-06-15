public class Solution {
    public int longestValidParentheses(String s) {
        int length = s.length();
        if(length <= 1){
            return 0;
        }
        //用栈来消除匹配括号串，但我们需要的是不符要求括号的下标，两个选择：1.栈中每个元素包括字符和下标（信息大量冗余）  2.栈中只保存下标，需要字符时直接用s.charAt(栈中下标)即可
        Stack<Integer> wrongPos = new Stack<Integer>();
//        int prelen = 0;//记录i左侧连续括号串的前一个')'位置，如果ic能构成新的()，则dp[i]=dp[start]+2;
        for(int i=0;i<length;i++){
            if(s.charAt(i) == '('){
                wrongPos.add(i);
            }
            else{
                if(wrongPos.empty() || s.charAt(wrongPos.peek())!='('){
                    wrongPos.add(i);
                }
                else{
                    wrongPos.pop();
                }
            }
        }

        int endWrongPos = length,res = 0,tempindex=0; //初始化不合法位置为 length
        while(!wrongPos.empty()){
            tempindex = wrongPos.pop();
            res = Math.max(res, endWrongPos-tempindex-1);
            endWrongPos = tempindex;
        }
        res = Math.max(res,endWrongPos-(-1)-1); //[0...第一个不合法位置-1] 为第一段合法括号串，其长度为 (第一个不合法位置 - (-1) -1)
        return res;
    }
}