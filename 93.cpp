class Solution {
public:
    vector<string> res;
    vector<string> restoreIpAddresses(string s) {
        if(s.length()<3 ||s.length()>12){
            return res;
        }
        construct(s,"",1);
        return res;
    }

    void construct(string s,string temp,int index){//构建第index个点分十进制数
        int number;
        // cout<<index<<",,,"<<s<<endl;
        if(index==4){//index=4时，尝试构建整体IP地址
            if(s.size()>=4||s.size()==0||(s.size()>1 && s[0]=='0')){//剩余0位 or 剩余超过3位 or 剩余s为"00..."(初始字符为'0' && size>=2)
                return;
            }
            else{
                number=atoi(s.c_str());//如果剩余的1-3位字符串处于"0-255"，则当前IP地址合法
                if(number>=0 && number<=255){
                    temp+=s;
                    res.push_back(temp);
                }
                return;
            }
        }
        if(s[0]=='0'){//对每一层：如果初始字符为'0'，则只能将"0."作为本层的十进制数，像"00."这种是不合法的
            // temp=temp+'0.';
            construct(s.substr(1),temp+"0.",index+1);
            // temp=temp.substr(temp.length()-3);
        }
        else{//如果首字符不为'0'，则尝试为本层分配s.substr(0,i)，i=1/2/3，为了剪枝必须保证下一层的剩余字符数(s.length()-i)>=剩余十进制的个数(4-index)
            for(int i=1;i<=3 && (s.size()-i>=4-index);i++){//s的剩余位数必须>=(4-index)
                number=atoi(s.substr(0,i).c_str());
                if(number>=0 && number<=255){//如果本层的构建字符处于"0-255"则将s.substr(i)作为下一层的剩余字符串
                    construct(s.substr(i),temp+s.substr(0,i)+".",index+1);
                }
            }    
        }
        
    }
};