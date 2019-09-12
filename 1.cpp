//
// Created by zb198 on 2019/9/12.
//
#include <iostream>
#include <algorithm>
#include <map>
void initMap(char* string,std::map<int,int >& numMap){
    int i = 0;
    while (string[i]!='\0'){
        if(numMap.count(string[i]-'0')==0){
            numMap[string[i]-'0'] = 1;
        } else{
            numMap[string[i]-'0'] += 1;
        }
        i++;
    }
}

int getCase(std::map<int,int >& numMap,int changeNum,int k,int& start,int& end,bool& outFromStart){//start和end的边界比较难定
    int cast = 0;
    k -= numMap[changeNum];
    start = changeNum-1;
    end = changeNum+1;
    bool haveStart,haveEnd;
    start>=0 ? haveStart=true : haveStart= false;
    end <= 9 ? haveEnd= true : haveEnd = false;
    while (haveStart||haveEnd){
        if (haveStart) {
            if(numMap.count(start)!=0) {
                if (k <= numMap[start]) {
                    cast += (changeNum - start) * k;
                    end--;
                    outFromStart = true;
                    break;
                } else {
                    cast += (changeNum - start) * numMap[start];
                    k -= numMap[start];
                }
            }
            start--;
            if(start==-1){haveStart= false;}
        }
        if(haveEnd){
            if(numMap.count(end)!=0) {
                if (k <= numMap[end]) {
                    cast += (end - changeNum) * k;
                    start++;
                    outFromStart= false;
                    break;
                } else {
                    cast += (end - changeNum) * numMap[end];
                    k -= numMap[end];
                }
            }
            end++;
            if(end==10){haveEnd = false;}
        }
    }
    return cast;
}
void getRsult(char* string,int start,int end,int changeNum,int k,int n,bool outFromStart){
    int i=0;
    while (string[i]!='\0'){
        if(k==0){ break;}
        if(string[i]-'0'>= changeNum&&string[i]-'0'<end&&string[i]-'0'>start){
            string[i]='0'+changeNum;
            k--;
        }
        i++;
    }
    for(int j=n-1;j>=0;j--) {
        if(k==0){ break;}
        if (string[j] - '0' < changeNum&&string[j]-'0'>start&&string[i]-'0'<end) {
            string[j] = '0' + changeNum;
            k--;
        }
    }
    if(!outFromStart){
        for(int l=n-1;l>=0;l--) {
            if(k==0){ break;}
            if (string[l] - '0'==start) {
                string[l] = '0' + changeNum;
                k--;
            }
        }
        int s=0;
        while (string[s]!='\0'){
            if(k==0){ break;}
            if(string[s]-'0'== end){
                string[s]='0'+changeNum;
                k--;
            }
            s++;
        }
    } else{
        int s=0;
        while (string[s]!='\0'){
            if(k==0){ break;}
            if(string[s]-'0'== end){
                string[s]='0'+changeNum;
                k--;
            }
            s++;
        }
        for(int l=n-1;l>=0;l--) {
            if(k==0){ break;}
            if (string[l] - '0'==start) {
                string[l] = '0' + changeNum;
                k--;
            }
        }
    }

}
int main(){
    int n,k;
    std::scanf("%d%d",&n,&k);
    char string[n+1];
    std::scanf("%s",string);
    std::map<int,int > numMap;
    initMap(string,numMap);
    int minCast = -1;
    int changeNum = -1;
    int start,end;
    bool outfromstart = true;
    for(int i=0;i<10;i++){
        int cast = -1;
        if(numMap.count(i)==0){
            continue;
        }
        if(numMap[i]>=k){
            changeNum = -1;
            minCast = 0;
            break;
        } else{
            int tempstart,tempend;
            bool outstart = true;
            cast = getCase(numMap,i,k,tempstart,tempend,outstart);
            if (cast<minCast||minCast==-1){
                minCast = cast;
                changeNum = i;
                start = tempstart;
                end = tempend;
                outfromstart=outstart;
            }
            }

    }
    if(changeNum==-1){
        std::printf("%d\n%s",minCast,string);
    }else {
        getRsult(string, start, end, changeNum, k, n,outfromstart);
        std::printf("%d\n%s", minCast, string);
    }
    return 0;
}
