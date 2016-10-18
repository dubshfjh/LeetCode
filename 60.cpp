以图例n=3进行说明：构建数组v={1,2,3}

确定最高位：ind=(k-1)/2, v[ind]的初值为ind+1

注：分母"2"是指每个最高位持续的排列数。由于除了最高位之外还有n-1=2位，一共可以出现2!种排列。

ind指的是所求的第k个排列会落在哪一个最高位的覆盖范围内。

k==1,2时，ind==0，最高位为v[ind]==1

k==3,4时，ind==1，最高位为v[ind]==2

k==5,6时，ind==2，最高位为v[ind]==3

即：在每一层子树上(当前子树下方还有n-1层节点)：k=1,2,...,(n-1)!：index=0,此时选取该层的第0+1个节点,即num[index]； k=(n-1)!+1....(n-1)*2!：index=1，此时选取该层的第1+1个节点,即num[index]

其余数位如上思路逐位确定。

注意：

1、k的更新。

2、vector<int> v的更新。

class Solution {
public:
    string getPermutation(int n, int k) {
    	vector<int> num(n);
    	string res="";
    	for(int i=0;i<n;i++){
    		num[i]=i+1;//num[0]=1,num[1]=2,...,num[n-1]=n
    	}
    	while(n>0){// x*(n-1)!< k <= (x+1)*(n-1)!时，index=x，因此num[index]为当前num数组中的第index+1个数
    		int index=(k-1)/factor(n-1);//index依次从最高位取到最低位，初始情况下针对第一层子树，每个节点的子树节点数目为(n-1)!，因此应该选取第(k/factor(n-1))个节点,即num[(k-1)/factor(n-1)]
    		res+=(num[index]+'0');
    		k-=index*factor(n-1);

    		//巧妙地避免了visited数组的使用，首先通过元素左移覆盖掉[index]，然后pop掉多余的最后一个元素
    		for(int i=index+1;i<n;i++){//从nums[index]开始，每个元素其右侧节点覆盖
    			num[i-1]=num[i];
    		}
    		num.pop_back();//再pop掉最右侧多余的num[size-1]，因为num[size-1]出现了2次{size-2,size-1}
    		n--;
    	}
    	return res;
    }

    int factor(int n){
        int res=1;
        for(int i=1;i<=n;i++){
            res*=i;
        }    
        return res;
    }
};




吐槽：回溯个毛线啊！！！！！
class Solution {
public:
	string num_str[10]={"0","1","2","3","4","5","6","7","8","9"};
	string res="";
    string getPermutation(int n, int k) {
    	int i;
  		vector<int> visited;
  		backtrace(visited,n,k);
  		return res;
    }
    
    int factor(int n){
        int res=1;
        for(int i=1;i<=n;i++){
            res*=i;
        }    
        return res;
    }
    
    bool backtrace(vector<int>& visited,int n,int k){//之所以设置为bool返回值，是早期为了避免回溯每一个节点。但后来的解法就是直接计算出每层的正确节点，所以bool实际上无效了=。=
        int size,temp,nodeindex;//temp：本层应该选取第temp棵子树
        size=visited.size();
    	if(size==n){
    		if(k==0){
    			for(int i=0;i<visited.size();i++){
    				res+=num_str[visited[i]];
    			}
	   			return false;
    		}
    	}
        temp=k/factor(n-size-1);//本层visited已经有size个节点，本层每个节点的子树node_num为(n-size-1)!
    // 	cout<<"Size is: "<<size<<",,,"<<"Old k is: "<<k<<endl;
        k-=temp*factor(n-size-1);//k：所选节点位于下层子树的第k个节点
        if(k==0 && temp==0){//temp==0 && k==0：接下来的每一层都需要选择当前层次的最右侧节点
        	for(int i=n;i>=1;i--){//从最右侧开始寻找节点
	    		if(find(visited.begin(),visited.end(),i)==visited.end()){
	    			visited.push_back(i);
	    			backtrace(visited,n,k);
        			return false;
	    		}
	    	}
        }

        if(k==0 && temp>0){//temp=1,2,... && k==0：本层应该选择第temp个节点的最右侧子树，下一层中将导致k==0,temp==0
           temp--;//由于nodeindex初值为0，所以temp--
        }
        //temp=0,1,2...&& k>0：本层应该选择第temp+1个节点的某棵子树，由于nodeindex初值为0，所以不需要temp--
        
        nodeindex=0;
        // cout<<"temp is: "<<temp<<endl;
        // cout<<"k is: "<<k<<endl;
    	for(int i=1;i<=n;i++){
    		if(find(visited.begin(),visited.end(),i)==visited.end()){
    		    if(nodeindex==temp){
    		       visited.push_back(i);
    		      // cout<<"i is:"<<i<<endl;
        			if(backtrace(visited,n,k)){//由于每一层直接计算了正确节点，所以不用再检测当前层次的所选节点是否无效，直接参照line 35-40的结构将backtrace设置为void即可
        				visited.pop_back();
        			}
        			else{
        				return false;
        			} 
    		    }
    			nodeindex++;
    		}
    	}
    	return true;
    }
};

