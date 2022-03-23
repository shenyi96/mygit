
import os
import re
import time
class tranlate():
    def __init__(self):
        self.binary = {}
        self.data = ""
        with open("C:/Users/yshen1/Desktop/EnglishToChaese.txt", "r", encoding="utf-8") as f:
            self.data = f.read()
            self.data = self.data.replace(" ", "")
            self.data = self.data.replace("\t", "").replace("\n", "")
        temporary = self.data

        for i in self.data:
            if(len(temporary)<=2):
                break
            binary = temporary[:temporary.find("}")]
            binary = binary[binary.rfind("{")+1:]         #.replace("\",","\"\",")
            binary = binary.split("\",")
            for n in binary:
                if(n == ""):
                    break
                temp = n.split(":")
                self.binary[temp[0]] = temp[1].replace("\"","")
            temporary = temporary[temporary.find("}")+1:]
        # print(temporary)
        # temp = []
        # temp = re.findall("(.*?):{(.*?)},",temporary)
        # for i in temp:
        #     dic = {}
        #     temp_1 = i[1]
        #     temp_1 = temp_1.split(",")
        #
        #
        #     print(temp_1)
            # temp = re.findall("(.*?):{(.*?),",i)
            # print(temp)
    def json_analysis(self,tran_target):
        result = ""
        data = self.data
        satrt = data[data.find(tran_target[0]+":"):]
        data = satrt[satrt.find("{")+1:satrt.find("}")]
        data = data.split(",")
        for i in data:
            if(tran_target == i[:i.find(":")]):
                result = i[i.find(":")+1:]
        return result
    def violent_analysis(self,tran_target):
        data = self.data
        data = data[data.find(tran_target+":\""):]
        data = data[:data.find("\",")+1]
        result = data[data.find(":")+1:]
        return result
    def circulation_analysis(self,tran_target):
        for i in self.binary:
            if(i == tran_target):
                return self.binary[tran_target]
if __name__ == "__main__":
    while True:
        tran = tranlate()
        print(tran.binary)
        serach = input("输入需要翻译的东西:")
        if(serach == "exit()"):
            break
        result = tran.circulation_analysis(serach)
        if (result == ""):
            print(f"'{serach}' : 没有找到翻译结果！")
        else:
            print(f"'{serach}' translate result : {result}")

        # result = tran.json_analysis(serach)
        # print("%s : %s"%(serach,result))
    #
    # start  = time.time()
    # result = tran.violent_analysis(serach)
    # end    = time.time()
    # print("%s:%s  %0.10f"%(serach,result,(end-start)*10000000))

