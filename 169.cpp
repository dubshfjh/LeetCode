兑子思想：用count变量记录当前元素ele的尚未抵消数量，如果后方的元素==ele 则增加ele的数量(count++)，否则兑掉1次ele(count--)。一旦到了位置i，count==0说明到{0...i}这个子数组段中ele出现次数必然<=n/2，
    当临时major的count在[i]处被抵消完毕时，将major更新成nums[i+1]，再往后检测nums[i+1]是否可能为major
如果元素value为major(即出现次数>n/2)，则不管value如何分布(最坏情况：value都在数组左侧，即所有的其它元素都会抵消value)，到最后一个元素时，value都不可能被兑子完毕，
    而且在遍历过程中value必然会抵消掉取值不为value的临时major
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int major,count;
        major = nums[0];
        count = 1;
        for(int i=1;i<nums.size();i++){
            if(count == 0){//说明在位置[i-1]处前一个临时major被抵消完毕了
                count = 1;
                major = nums[i];
            }
            else if(nums[i] == major){
                count++;
            }
            else{
                count--;
            }
        } 
        return major;     
    }
};


分治法：由于Major出现次数>n/2，则在分治法建立的二叉树中，每个父节点和子节点组成的(1,2,3)个节点中至少有2个取值为major。考虑将mid本身作为左子树的一部分
    1.如果父子节点数目为1(即没有子节点)，则nums[left]为当前子树的major

    2.1 如果左子Major==右子Major，则当前树的Major自然确定了。
    2.2 如果左子Major != 右子Major，则考虑当前树向右延伸一位(因为左子树元素数 >= 右子树元素数)。由于major出现次数>n/2，则平衡了左右子树元素数后{left..mid..right,right+1}中major必然出现更多次
        因此left_major和right_major在{left...right+1}段中出现次数较多的就是当前树的Major

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int size = nums.size();
        return findmajor(nums,0,size-1);
    }
    
    int findmajor(vector<int>& nums,int left,int right){
        if(left == right){//当前subarray的大小为1
            return nums[left];
        }
        
        int mid = left+((right-left)>>1);
        int left_major = findmajor(nums,left,mid);//将mid作为左子树的部分进行考虑
        int right_major = findmajor(nums,mid+1,right);

        if(left_major == right_major){
            return left_major;
        }

        auto it = nums.begin();//考虑将当前子树向右延伸一位，
        int left_count = count(it+left, it+right+1, left_major);
        int right_count = count(it+left,it+right+1, right_major);
        return (left_count > right_count)?left_major:right_major;
    }
};