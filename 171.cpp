class Solution {
public:
    int titleToNumber(string s) {
        int res=0;
        /* 字母A-Z转换成数字1-26
        char temp;
        for(temp='A';temp!='Z'+1;temp++){
            cout<<temp-'A'+1<<endl;
        }
        */
        for(int i=0;i<s.length();i++){//'s[0]...s[n-1]' = (s[0]-'A'+1)*26^(n-1) + ... + (s[n-1]-'A'+1)*26^0
            res = 26*res + (1+(s[i]-'A'));
        }
        return res;
    }
};