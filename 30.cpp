#include <iostream>
#include <vector>
#include <string>
using namespace std;
看错了题目意思，words是可以乱序的，以下代码只是单纯地实现了KMP算法
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words){
    	int i,j,index;
    	vector<int> res;
        string pattern="";
        for(i=0;i<words.size();i++){
        	pattern+=words[i];
        }
		vector<int> next(pattern.size(),-1);
        getNext(pattern,next,pattern.size());
        i=j=0;
        while(i<s.size()){
        	j=0;
        	while(j<pattern.size()&&i<s.size()){
        		if(s[i]==pattern[j]){
        			i++;
        			j++;
        		}
        		else{
        			if(j==0){
        				i++;
        			}
        			else{
        				j=next[j-1]+1;
        			}
        		}
        	}
        	if(i==s.size()){
        		break;
        	}
        	if(j==pattern.size()){
        		index=i-pattern.size();
        		//i=i-next[j-1]-1;
        		res.push_back(index);
        	}
        }
		for(i=0;i<res.size();i++){
			cout<<res[i]<<endl;
		}
        return res;
    }

    void getNext(string pattern,vector<int>& next,int len){
    	int j,k;
    	next[0]=-1;
		cout<<len<<endl;
    	for(j=1;j<len;j++){   
    		k=next[j-1];
    		while(pattern[k+1]!=pattern[j]&&k>=0){
    			k=next[k];
    		}
    		if(pattern[k+1]==pattern[j]){
    			next[j]=k+1;
    		}
    		else{
    			next[j]=-1;
    		}
    	}
    }
};


#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
    	int i,j,size_1,size_2,len,temp_i,index;
        map<string,int> temp,word_num;
        map<string,int>::iterator it;
        vector<int> res;
        string substring;
        size_1=s.size();
        size_2=words.size();
        len=words[0].size();
        if(size_1==0||size_2==0){
        	return res;
        }
        for(i=0;i<size_2;i++){
        	if(word_num.count(words[i])==0){
        		word_num.insert(pair<string,int>(words[i],1));
        	}
        	else{
        		word_num[words[i]]+=1;
        	}
			//cout<<words[i]<<",,,"<<word_num[words[i]]<<endl;
        }
        temp=word_num;
        for(i=0;i<=size_1-size_2*len;i++){//判断从s的第0个字符出发，到第(size_1-words总体长度)个元素是否能匹配所有元素
        	temp_i=i;
        	while(word_num.size()>0){
        		substring=s.substr(i,len);
    			it=word_num.find(substring);
				/*
				if(it!=word_num.end()){
					cout<<substring<<",,,"<<(*it).first<<",,,"<<(*it).second<<endl;
				}
				*/
    			if(it==word_num.end()){//word_num没有出现当前子串，或者之前已经将words中该子串的全部次数匹配完了
    				i=temp_i;//从本次的temp_i不可能匹配所有元素，i复归原处
    				break;
    			}
    			else{
					
    				if(word_num[substring]>=1){//匹配成功了words中某个元素
    					word_num[substring]-=1;//减少words中该元素出现次数
    					i+=len;//i向右推进len个字符，取下一个子串
    					if(word_num[substring]==0){
    						word_num.erase(it);
    					}
    				}
    				/*在上段代码中，一旦某个word的num为0，则移除了该元素，所以无需再分析当前word的出现次数<=0的情况
    				else{
    					i=temp_i;
    					word_num.clear();
    					break;
    				}
    				*/
    			}
    		}
    		if(word_num.size()==0){//words中所有元素都匹配了，当前i向后延伸的整体字符串正好一次，被erase掉了
    			index=i-size_2*len;
    			res.push_back(index);
    			word_num.clear();
    			word_num=temp;//word_num回滚到未匹配任何元素的初始状态
    		}
    		else{//从本次的i出发匹配失败后，回滚word_num即可
    			word_num.clear();
    			word_num=temp;//word_num回滚到未匹配任何元素的初始状态
    		}
    		i=temp_i;//i复位，本次for循环运行一次，i++
        }
		
        return res;
    }
};


int main(){
    string s="barfoothefoobarman";
    vector<string> pattern;
    vector<int> res;
    pattern.push_back("foo");
    pattern.push_back("bar");
    Solution sol=Solution();
    res=sol.findSubstring(s,pattern);
    for(int i=0;i<res.size();i++){
    	cout<<res[i]<<endl;
    }
    return 0;
}
