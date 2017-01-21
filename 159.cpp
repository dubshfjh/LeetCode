Given a string, find the length of the longest substring T that contains at most 2 distinct characters.
For example,Given s = “eceba”,
T is "ece" which its length is 3.

用HASHTABLE 记录 当前两个字符的数目, 如果遇到新字符, 移动start指针的位置, 直到新的start位置, 只包含两个字符. 这题思路很简单, 不知为何标为HARD. 也许有更优解, 不需要用extra space.
class Solution {  
public:
int lengthOfLongestSubstringTwoDistinct(string s) {
    int start,end,res;//start标识"Two distinct substring"的起始下标
    map<char,int> ch_num;//存储substring中每个字符出现的次数
    start = 0;
    res = 0;
    for(int i=0;i<s.length();i++){
       if(ch_num.find(s[i]) == ch_num.end()){
            if(ch_num.size() == 2){//使用一定的技巧使得substring中移除已有2字符中的1个
                while(start < i && ch_num.size() == 2){//跳出循环时start为first使得map.size()==1的下标
                    int num = ch_num[s[start]];
                    start++;
                    num--;
                    if(num == 0){
                        auto it = ch_num.find(s[start]);
                        ch_num.erase(it);
                    }
                    else{
                        ch_num[s[start]] = num;
                    }
                }
                ch_num[s[i]] = 1;
            }
            else{//加上该新字符仍然为"two distinct substring"
                ch_num[s[i]] = 1;
            }
       }
       else{//当前字符不是新字符
            ch_num[s[i]] += 1;
       }
       //此时{start...i-1}为1个"two distinct substring"
       res = max(res,i-start-1);
    }
    return res;
}
};