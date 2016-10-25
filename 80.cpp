在判断[i]元素是否与[i+1]相等时，必须要求i<size-1，否则提交不通过
很弱的思想：首先统计当前数字的出现次数count，若count>=2则执行两次[index++]=[i]；否则执行一次[index++]=[i]
其中index会成为下一个应该被赋值的元素
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
       int i,index,count;//index记录新数组中下一个需要被赋值的下标
       if(nums.size()<=1){
           return nums.size();
       }
       index=0;
       for(i=0;i<nums.size();i++){
           count=1;
           while(i<nums.size()-1 && nums[i]==nums[i+1]){//必须得判断i<size-1，否则就算结果正确也会Wrong answer，
               count++;//[0,0,1,1,2,3,4]，在这个test case下，Run Code统计了4的count为1；但是Submit就直接 count为4了，比较诡异
               i++;//猜测是因为i==size-1时，仍然进入了while循环，vector<int>中[size]及之后的元素在捣乱吧
           }
          // cout<<"index:"<<index<<",,,"<<count<<",,,"<<nums[i]<<endl;
           if(count>=2){//
               for(int j=0;j<2;j++){
                   nums[index++]=nums[i];
               }
           }
           else{
               nums[index++]=nums[i];
           }
       }
       cout<<index<<endl;
       return index;
    }
};

//当前有多少个不重复的元素，那么下一个不重复的元素直接覆盖到这个索引位就可以了。
//引入一个pre元素。可以避免僵硬的while循环套用。pre首先初始化为0，count初始化为1
//如果当前元素==pre，count++,如果count<=2，则[sum++]=[i]；如果当前元素!=pre，count=1,[sum++]=[i].
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i,sum,count,pre;
        if(nums.size()<=1){
           return nums.size();
        }
        sum=count=1;
        pre=nums[0];
        for(i=1;i<nums.size();i++){
            if(pre==nums[i]){
                count++;
                if(count<=2){
                    nums[sum++]=nums[i];
                }
            }
            else{
                count=1;
                pre=nums[i];
                nums[sum++]=nums[i];
            }
        }
        return sum;
    }
};