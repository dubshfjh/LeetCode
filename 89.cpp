个人思路（充满了暴力，还是直接看下方的改进算法吧）：
每两位视为1层，对于每一层依次取正向"00->01->11->10",反向"10->11->01->00"，然后正向...(保证为grey code)，
如果最高位只剩1位数则取"0->1"
最后计算得到每个二进制数对应的十进制存起来

缺陷：时间复杂度极高，优化推测：应该更好地利用Grey Code之间的对称关系，而不是强行构造数字的字符串
class Solution {
public:
    string twogray[4]={"00","01","11","10"};
    string ongray[2]={"0","1"};
    vector<int> res;
    vector<int> grayCode(int n) {//每两位视为1层，对于每一层依次取正向"00->01->11->10",反向"10->11->01->00"，然后正向...(保证为grey code)，如果最高位只剩1位数则取"0->1"
        int flag=0;//flag=0则正向取twogray，flag=1则反向取twogray[每一层次都是正向一次，反向一次]，
        string s="";
        queue<string> temp;
        temp.push(s);
        if(n%2!=0){//最高层次只有1位数字，依次取0,1即可
            temp.pop();
            for(int i=0;i<2;i++){
                temp.push(ongray[i]);
                n--;
            }
        }
        
        while(n>0){
            int size=temp.size();//本层的元素个数为size
            while(size--){
                string s=temp.front();
                temp.pop();
                if(flag==0){//每层依次取正向->反向->正向->...
                    for(int i=0;i<4;i++){
                        temp.push(s+twogray[i]);
                    }
                    flag=1;    
                }
                else{
                    for(int i=3;i>=0;i--){
                        temp.push(s+twogray[i]);
                    }
                    flag=0;
                }
            }
            flag=0;//为下一层次的顺序复位
            n-=2;
        }


        while(!temp.empty()){
            res.push_back(cal_binary(temp.front()));
            temp.pop();
        }
        //get_binary(s,n);
        return res;
    }

    int cal_binary(string s){
        // cout<<s<<endl;
        double res=0;
        for(int i=s.size()-1;i>=0;i--){
            res+=(s[i]-'0')*pow(2,s.size()-i-1);
        }
        return (int)res;
    }

    //下面的递归算法会得到"000","100","001","101"....
    //而不是真正需要的"000","001","011","010","1 10","1 11","1 01","1 00"
    // void get_binary(string s,int n){
    //     cout<<"n: "<<n<<endl;
    //     if(n==0){
    //         res.push_back(cal_binary(s));
    //     }
    //     else if(n==1){
    //         get_binary("0"+s,n-1);
    //         get_binary("1"+s,n-1);
    //     }
    //     else{
    //         for(int i=0;i<4;i++){
    //             get_binary(twogray[i]+s,n-2);
    //         }
    //     }
    // }
};

分析如下:
手动地写写n=3时候的情况，会发现。n=3的结果如下:
000
001
011
010  ↑
--------
110  ↓
111
101
100
可看成是上下对称的2部分。上半部分是n=2时候的结果再在最高位加"0"的结果。
下半部分是n=2时候的结果逆序之后再在最高位加"1"的结果。

class Solution {
public:
    vector<int> grayCode(int n) {
        if(n==0){
            vector<int> a(1,0);
            return a;
        }

        vector<int> last_res = grayCode(n-1);//获得上一层的计算结果
        //例如分析过程中 (n=3的结果可以由 n=2的结果保持原序，前方加上'0'构成前半部分；然后将 n=2的结果由后往前(反向遍历)，前方加上'1'构成后半部分
        
        vector<int> cur_res(last_res);//赋值n-1时候的结果，作为本次结果的前半部分
        for(int i=last_res.size()-1;i>=0;i--){//反向遍历上一层结果，构建后半部分
            int cur = last_res[i]+pow(2,n-1);
            cur_res.push_back(cur);
        }
        return cur_res;
    }   
};