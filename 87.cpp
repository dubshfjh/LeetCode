我的算法又出错啦！！！！

思路有偏差，认为s1_left的字符数应该为size/2，check(s1_left,s2_left)&&check(s1_right,s2_right)
或者 check(s1_left,s2_right)&&check(s1_right,s2_left)
s1_left,s2_left的长度应该依次为1，2....size-1

错误：划分left和right的方法不准确，Wrong Answer。而且没有剪枝，绝对会超时啊

Attetion：在进入递归前需要剪枝，判断两个字符串是否包含相同的字母（利用hash数组统计每个字母的次数）

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size()==0 || s2.size()==0){
            return true;
        }
        return check(s1,s2);
    }

    bool check(string s1,string s2){
        int len=s1.size();
        string s1_left,s1_right,s2_left,s2_right;
        if(len==1){
            if(s1==s2){
                return true;
            }
            else{
                return false;
            }
        }
        //首先尝试s1的左(len/2)个字符与s2的左(len/2)个字符匹配，以及s1的右(len/2)个字符玉s2的右(len/2)个字符
        s1_left = s1.substr(0,len/2);
        s1_right = s1.substr(len/2,len-len/2);

        s2_left = s2.substr(0,len/2);
        s2_right = s2.substr(len/2,len-len/2);
        cout<<"左匹配："<<s1_left<<",,,"<<s2_left<<endl;
        // cout<<s1_right<<",,,"<<s2_right<<endl;        
        bool left_match = check(s1_left,s2_left)&&check(s1_right,s2_right);


        //然后尝试s1的左(len/2)个字符与s2的右侧(len/2)个字符匹配，以及s1的右(len/2)个字符玉s2的左(len/2)个字符
        s2_right=s2.substr(len-len/2,len/2);
        s2_left=s2.substr(0,len-len/2);
        cout<<"右匹配："<<s1_left<<",,,"<<s2_right<<endl;
        // cout<<s1_right<<",,,"<<s2_left<<endl;
        bool right_match = check(s1_left,s2_right)&&check(s1_right,s2_left);

        
        return left_match||right_match;
    }
};

递归来做，也就是s1分为s1_left和s1_right，s2分为s2_left和s2_right。

判断isScramble(s1_left,s2_left)&&isScramble(s1_right,s2_right)或者isScramble(s1_left,s2_right)&&isScramble(s1_right,s2_left)

base case是字符串相同

另外在进入递归前需要剪枝，判断两个字符串是否包含相同的字母，O(n)复杂度。
class Solution {
public:
    bool isScramble(string s1, string s2) {
        string s1_left,s1_right,s2_left,s2_right;
        if(s1==s2){
            return true;
        }

        if(s1.size() != s2.size()){
            return false;
        }

        vector<int> letter_cnt(26,0);
        for(int i=0;i<s1.size();i++){
            letter_cnt[s1[i]-'a']++;
            letter_cnt[s2[i]-'a']--;
        }

        for(int i=0;i<26;i++){//说明s1,s2中的字符数目不一致
            if(letter_cnt[i]>0){
                return false;
            }
        }
        //s.substr(i,n)：字符串s从位置i开始的n个字符；s.subtr(i)：字符串s从i开始到最后一个字符
        for(int i=1;i<s1.size();i++){
            //匹配(s1的左侧i个字符，s2的左侧i个字符) && (s1的右侧size-i个字符,s2的右侧size-i个字符)
            bool left_match = isScramble(s1.substr(0,i),s2.substr(0,i)) && isScramble(s1.substr(i),s2.substr(i));

            //匹配(s1的左侧i个字符，s2的右侧i个字符) && (s1的右侧size-i个字符,s2的左侧size-i个字符)
            bool right_match = isScramble(s1.substr(0,i),s2.substr(s1.size()-i)) && isScramble(s1.substr(i),s2.substr(0,s1.size()-i));
            if(left_match || right_match){
                return true;
            }
        }
        return false;
    }
};