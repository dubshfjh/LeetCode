#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//辣鸡算法，耗时139ms，打败0.39%的用户
//由低到高分析n的32位数字，通过位操作'| &'将 (n[i] & 1)记录为res[32-i]
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        int i=0;
        uint32_t res = 0;
        uint32_t num = 1;//1<<32 overflows!!!由于参数类型为unsigned int，所以不存在符号位
        while(true){
            int temp = num&n;
            // cout<<++i<<",,,"<<((temp>0)?1:0)<<endl;
            //res |= (temp > 0)?1:0;//当第32位为1时，temp = 1<<32 < 0，则temp不满足>0的条件，所以必须将条件设置为(temp==0)
            res |= (temp == 0)?0:1;
            cout<<temp<<",,,"<<num<<",,,"<<res<<endl;

            if(num == 1<<31){////1<<0 to 1<<31，分析n从倒数第1位到到最高位的32位number.注意(1<<31)<<1 == 1<<32 == 0，会overflow
                break;
            }
            res<<=1;
            num<<=1;

        }
        // cout<<res<<endl;
        return res;
    }
};

换一种别人的精简思路，耗时减少10倍左右
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for(int i=0;i<32;i++){
            res = (res<<1) + ((n>>i) & 1);// (n>>i & 1) 等价于 (n[i] == 1)
        }
        // cout<<res<<endl;
        return res;
    }
};


int main(){
    uint32_t nums;
    // while(true){
        // cin>>nums;
        nums = 134;
        Solution sol=Solution();
        sol.reverseBits(nums);    
    // }
    return 0;
}