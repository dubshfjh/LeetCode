Two Sum III

Design and implement a TwoSum class. It should support the following operations:add and find.
add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,
add(1); add(3); add(5);
find(4) -> true
find(7) -> false


class Solution{
public:
    unorderd_map<int,int> nums;//记录每个数字出现的次数
    void add(int number){
        if(nums.find(number) == nums.end()){
            nums[number] = 1;
        }
        else{
            nums[number]++;
        }
    }

    bool find(int value){//只是检测2个数字的sum是否为value，所以直接遍历Map一次即可。如果第2个数字remain == 当前数字，则检测当前数字出现次数是否>=2；如果remain !+ 当前数字，则检测remain是否在map中出现过
        for(auto it = nums.begin();it!=nums.end();it++{
            int remain = value - it->first;
            if(remain == it->first && it->second>=2){
                return true;
            }
            else if(remain != it->first && nums.find(remain)!=nums.end()){
                return true;
            }
        }
        return false;
    }

};

解决ThreeSum/FourSum...等KSum问题的初步思路(有缺陷)：
    用1个map记录每个数字的出现次数，并使用一个backup备份每个数字的出现次数，使用k重循环寻找remain，在每重循环中：遍历map计算remain=remain-(it->first)，然后用backup备份本重循环的map后
    更新map[remain]--;
