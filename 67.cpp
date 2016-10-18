class Solution {
public:
    string addBinary(string a, string b) {
        int i,num,size,temp,flag;
        string res;
        char int_ch[2]={'0','1'};
        //首先对a,b中较短的字符串在首部补充'0'，直到2者长度相等
        if(a.size()>b.size()){
        	num=a.size()-b.size();
        	for(i=0;i<num;i++){
        		b='0'+b;
        	}
        }
        else{
        	num=b.size()-a.size();
        	for(i=0;i<num;i++){
        		a='0'+a;
        	}
        }
        size=max(a.size(),b.size());
        flag=0;
        for(i=size-1;i>=0;i--){
        	temp=(a[i]-'0')+(b[i]-'0')+flag;//temp记录2个二进制数相加的和
        	flag=temp/2;
        	if(temp>=2){
        		temp%=2;
            }
        	res=int_ch[temp]+res;
        }
        if(flag>0){//即最高位的(两位数之和+flag)>=2
        	res='1'+res;//填充最高位为1
        }
        return res;
    }
};