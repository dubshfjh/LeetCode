Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.
(单词都由单个空格分开，但是考虑到代码的普适性，假设每个单词由多个空格分开，也就是说=。=完全参照151.cpp的代码)
For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?


class Solution {
public:
     void reverseWords(string s) {
        int i,j;//i用来遍历s；j用来将s中的每个word从多个space分离 左移成 1个space分离的格式 ;backup记录(pre word + 1 space)的后一个字符位置
        i = j = 0;
        while(true){
            if((s[i]==' '||s[i]=='\t') && i<s.length()){
                i++;
            }
            if(i == s.length()){
                break;
            }
            int backup = j;//记录(pre word+1 space)后方的位置
            while((s[i]!=' '&&s[i]!='\t') && i<s.length()){//将i发现的word左移到(pre word + 1 space)的后面
                s[j++] = s[i++];
            }
            reverse_word(s,backup,j-1);
            s[j++] = ' ';//在first word到last word 后方都补上 1 space
        }
        s.resize(j-1);//s的前j个字符子串为{word1 word2 ... wordn }，只需要取出前j-1个字符即可
        reverse_word(s,0,j-1);
    }

    void reverse(string s,int start,int end){
        char temp;
        while(start < end){
            temp = s[start];
            s[start++] = s[end];
            s[end--] = s[start];
        }
    }

};
