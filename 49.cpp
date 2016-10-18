#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
直接的思想，会超时：直接对每个strs[i]进行sort，然后比较字符串是否相等就好啦
改进：利用hash表存储sort之后的字符串
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
    	int i,index,str_index;
    	string temp;
        map<string,int> record;
        vector<vector<string>> res;
        for(i=0,index=0;i<strs.size();i++){
        	temp=strs[i];
        	sort(temp.begin(),temp.end());
        	if(record.count(temp)==0){
        		vector<string> str_arr;
        		record.insert(pair<string,int>(temp,index++));
        		str_arr.push_back(strs[i]);
        		res.push_back(str_arr);
        	}
        	else{
        		str_index=record[temp];
        		res[str_index].push_back(strs[i]);
        	}
        }
        return res;
    }
};