def initDict(phoneNum:str)->dict:
    phoneDict = {}
    for num in phoneNum:
        num = int(num)
        if(num in phoneDict):
            phoneDict[num] += 1
        else:
            phoneDict[num] = 1
    return phoneDict
def getCast(phoneDict:dict,sameNum:int,k:int):
    start = sameNum-1
    end = sameNum+1
    cast = 0
    hasStart = True
    hasEnd = True
    if(start<=-1):hasStart=False
    if(end>=10):hasEnd=False
    k -= phoneDict[sameNum]
    outFromStart = True
    while(hasStart or hasEnd):
        if(hasStart):
            if(start in phoneDict):
                if(k>=phoneDict[start]):
                    cast += (sameNum-start)*phoneDict[start]
                    k -= phoneDict[start]
                else:
                    cast += (sameNum-start)*k
                    outFromStart=True
                    end -= 1
                    break
            start -=1
            if(start==-1):hasStart=False
        if(hasEnd):
            if(end in phoneDict):
                if(k>=phoneDict[end]):
                    cast += (end-sameNum)*phoneDict[end]
                    k -= phoneDict[end]
                else:
                    cast += (end-sameNum)*k
                    outFromStart = False
                    start +=1
                    break
            end +=1
            if(end==10):hasEnd=False
    return cast,start,end,outFromStart
def getResult(phoneNum:str,sameNum:int,start:int,end:int,outFromStart:bool,k:int)->list:
    phoneNum = [int(i) for i in phoneNum]
    lastNum = -1
    if(outFromStart):
        lastNum = start
        start += 1
    else:
        lastNum = end
        end -= 1
    for index,Num in enumerate(phoneNum):
        if(k==0):break
        if(Num>=sameNum and Num<=end):
            phoneNum[index] = sameNum
            k -= 1
    for index,Num in enumerate(phoneNum[::-1]):
        if(k==0):break
        if(Num<sameNum and Num>=start):
            phoneNum[(index+1)*-1] = sameNum
            k -= 1
    if(outFromStart):
        for index,Num in enumerate(phoneNum[::-1]):
            if(k==0):break
            if(Num==lastNum):
                phoneNum[(index+1)*-1] = sameNum
                k -= 1
    else:
        for index,Num in enumerate(phoneNum):
            if(k==0):break
            if(Num==lastNum):
                phoneNum[index] = sameNum
                k -= 1
    return phoneNum

if __name__ == '__main__':
    n,k = map(int,input().split(" "))
    phoneNum = input()
    phoneDict = initDict(phoneNum)
    minCast = -1
    changeNum = -1
    outFromStart = True
    startNum = -1
    endNum = -1
    for sameNum in range(10):
        if(sameNum not in phoneDict):
            continue
        if(phoneDict[sameNum]>=k):
            changeNum = -1
            minCast=0
            break
        cast,start,end,outfromstart = getCast(phoneDict,sameNum,k)
        if(cast<minCast or minCast==-1):
            minCast = cast
            changeNum = sameNum
            outFromStart = outfromstart
            startNum = start
            endNum = end
    if(changeNum==-1):
        print("%d\n%s"%(0,phoneNum))
    else:
        result = getResult(phoneNum,changeNum,startNum,endNum,outFromStart,k)
        print("%d\n%s"%(minCast,"".join([str(i) for i in result])))


