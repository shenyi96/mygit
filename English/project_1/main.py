import os
class file_open():
    def __init__(self,word_path):
        self.word_path = word_path
        self.data=[]
        self.dick={}
        self.dict = {}
        self.read_file()
        self.compare_word()
    def append_file(self):
        with open("./translate.txt","a",encoding='utf-8')as f:
            if self.dict == {}:
                self.compare_word()
            for i in self.dick:
                if i not in self.dict:
                    f.write(i+':'+self.dick[i]+"\n")
        self.compare_word()
    def write_file(self):
        with open("./translate.txt","w",encoding='utf-8')as f:
            for i in self.dick:
                f.write(i+':'+self.dick[i]+'\n')
    def compare_word(self):
        with open("./translate.txt","r",encoding='utf-8')as f:
            data = f.readlines()
            for i in data:
                if len(i) <2:
                    continue
                self.dict[i.split(':')[0]]=i.split(':')[1]
    def read_file(self):
        for i in os.listdir(self.word_path):
            with open(self.word_path+i,"r",encoding="GB2312")as f:
                data = f.readlines()
                for n in data:
                    if len(n.replace(' ', '')) < 3:
                        continue
                    if "." not in n:
                        temp = n.replace("\n", ' ')
                    else:
                        temp = temp + n.replace("\n", '')
                        self.data.append(temp)
                        temp = ''
        for i in self.data:
            self.dick[i[:i.find(" ")]]=i[i.find(' '):].replace(" ",'')
    def translate(self,word):
        if self.dict == {}:
            self.compare_word()
        if word in self.dict:
            return self.dict[word]
if __name__ == '__main__':
    word_path = "../word_list/"
    file = file_open(word_path)
    print(file.translate('intger'))




