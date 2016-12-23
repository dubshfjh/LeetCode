解法一：使用map记录各个元素的出现次数(PS：题目貌似默认single element出现次数<3)，耗时达到最高
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        map<int,int> count;
        for(int i=0;i<nums.size();i++){
            if(count.find(nums[i]) == count.end()){
                count[nums[i]] = 1;
            }
            else{
                count[nums[i]]++;
            }
        }

        for(map<int,int>::iterator it = count.begin();it!=count.end();it++){
            if((*it).second != 3){
                return (*it).first;
            }
        }
        return INT_MIN;
    }
};

解法二：先排序，再遍历找出孤异元素(由于至少存在4个元素，首先检测[0]!=[1],[size-2]!=[size-1]，如果出现则对应返回[0],[size-1]。然后对于i=1 to size-2，检测是否满足[i]==[i-1]&&[i]==[i+1]，若不满足则返回[i])


解法三：位操作。不管非孤异元素重复多少次，这是通用做法。将每个数字转换成同等位数的2进制数字，左侧用'0'补齐。

对于右数第i位，如果孤异元素该位为0，则该位为1的元素总数为3的整数倍。
    检测十进制数右数第i位是否为1的方法：(N & (1<<i)) ==1

如果孤异元素该位为1，则该位为1的元素总数不为3的整数倍（也就是余1）。

换句话说，如果第i位为1的元素总数不为3的整数倍，则孤异数的第i位为1，否则为0.

（如果非孤异元素重复n次，则判断是否为n的整数倍）


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int flag=1;//flag=1<<i，(nums[j] & (1<<i) != 0)用于检测nums[j]右数第i位是否为1，如果为1则(nums[i] & flag) = 1<<i
        int i = 0,res = 0;
        while(flag!=0){//由于singleNumber为int类型，所以flag只需要取1,2,4,8...,abs(INT_MIN)/2,INT_MIN,0即可。PS：INT_MIN<<1 = 0
            int i_onecount = 0;//记录nums数组左数第i位的1出现次数
            for(int j=0;j<nums.size();j++){
                if((nums[j] & flag) != 0){//nums[j]右数第i位为1
                    i_onecount++;
                }
            }
            if(i_onecount%3 != 0){//如果右数第i位出现1的num>0 而且不为 3的整数倍，则说明singlenumber在该位也为1，因此res += (1<<i)
                // res += flag;
                res |= flag;//因为flag = 1000...，res比flag少一位，所以res+flag等价于(0....)|(1000....)，即res|=flag
            }
            flag <<= 1;
        }
        return res;
    }
};