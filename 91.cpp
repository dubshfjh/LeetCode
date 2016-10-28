预期解法，回溯，dp["123"]=dp["23"]+dp["3"]（剪枝不够，分析太详尽，直接超时）
因此，只能使用正规的动态规划(即纯粹计算的数学归纳法)来减少时间（而且没必要分析这么多的......）

难点：数字'0'没有解决方案，当本层第一个字符为'0'则return 0;当本层size>=2时，对于sec_num=='0'需要进行分析
思想：本层size==0则return 0；本层只有1个字符时,对于'1-9'则return 1,对于'0'则return 0；本层有2个以上字符时，对于first_num为'0'则return 0

对于sec_num为'0'则区分两种情况：一、first_num为'1,2'，此时本层2字符只有一种解决方案，如果size==2则return 1，size>2则return (s.substr(2))；
二、first_num为'3,4,...9'，则return 0
Attention：dp["10"]=1,dp["1010"]=dp["10"]=1,dp["100"]=dp["0"]=0


对于first_num,sec_num不为'0'的情况：对于"11-26"，如果size==2，则return 1+(s.substr(1));如果size>2，则return s.substr(1)+s.substr(2)

class Solution {
public:
    // int flag=0;//flag=1：标识上一层的最后一个数字为0,flag=2标识无法构成任何解的情况
    int numDecodings(string s) {
        if(s.size()==0){
            return 0;
        }
        return dec_onechar(s);     
    }

    int dec_onechar(string s){
        char first_num,sec_num;
        // cout<<s<<endl;
        // if(s.size()==0){
        //     return 0;
        // }          
        if(s.size()==1){
            if(s[0]=='0'){//可以推断出上一层size为3(s.substr(2)) 或者 2(s.substr(1))，只但要本层的first字符为'0'就不可能decode
                return 0;
            }
            else{
                return 1;
            }
        }
        else{//size>=2
            first_num=s[0];        
            sec_num=s[1];
            if(first_num=='0'){//可以推断出上一层size为3(s.substr(1)) 或者 4(s.substr(2))，只要本层的first字符为'0'就不可能decode，只能回溯上一层看能否换一种decode方案
                return 0;
            }
            else if(sec_num=='0'){//10,20,30....90，此时只有10和20可能有解决方案(而且只能将这2个字符共同decode),dp["10"]=1,dp["1010"]=dp["10"]=1,dp["100"]=dp["0"]=0
                if(first_num>='1' && first_num<='2'){//当第2个字母为'0'时，只有"10"和"20"可以组合成一个字母
                    if(s.size()>2){//size>2时，本层的2字母只有一种decode方案，所以本层是否有方案取决于下层是否有方案
                        return dec_onechar(s.substr(2));
                    }
                    else{//后方无字符啦，本层字符(即最后2个字符)拥有1种decode方案
                        return 1;
                    }
                }
                else{
                    return 0;
                }
            }
            else{//11,12...19 21...29 31...(没有20，30，40....)
                if(first_num>'2' || (first_num=='2'&&sec_num>='7')){//前2位字符构成的数字>26，只有将第1个字符decode这一种方案
                    return dec_onechar(s.substr(1));
                }
                else{//只有11-26时，这两个字符算一种decode方案，第一个字符也可以decode一次
                    if(s.size()>2){
                        return dec_onechar(s.substr(1))+dec_onechar(s.substr(2));
                    }
                    else{//当size==2时，s.substr(2)=""，会漏掉本身这一种decode方案
                        return 2;
                        // return 1+dec_onechar(s.substr(1));
                    }
                }
            }
        }
    }
};


动态规划，考虑只取当前一位是否成立，当前位与前一位构成的两位数是否成立。
class Solution {
public:
    bool check(char c){
        if(c-'0'>0){
            return true;
        }
        return false;
    }

    bool check(char c1,char c2){//c1为前一位字符
        if(c1=='1' || (c1=='2'&&c2<='6')){
            return true;
        }
        return false
    }

    int numDecodings(string s) {
        if(s.size()==0 || s[0]=='0'){
            return 0;
        }

        vector<int> dp(s.length+1,0);//dp[i]表示当前结束字符为s[i-1]时，decode的方案数
        dp[0]=1;

        for(int i=1;i<=s.length;i++){
            if(check(s[i-1])){//s[i-1]本身就成立，以s[i-1]为结束字符的方案数dp[i]+=dp[i-1]（即结束字符为s[i-2]时的方案数)
                dp[i] += dp[i-1];
            }
            if(i>=2 && check(s[i-2],s[i-1])){//"s[i-2]s[i-1]"也成立，以s[i-1]为结束字符的方案数dp[i]=dp[i-1]+dp[i-2]（后者为结束字符为s[i-3]时的方案数)
                dp[i] += dp[i-2];
            }
        }
        return dp[s.length];
    }
};