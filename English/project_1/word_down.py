import requests,re
import main
header={
'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleW'
              'ebKit/537.36 (KHTML, like Gecko) Chrome/97.0.4692.71 Safari/537.36'
}
proxy={"http": "http://124.112.174.237:8080"}
class data_space():
    def __init__(self,url):
        self.url_dict={}
        self.word={}
        self.dict = {}
        self.url=url
    def request(self,url):
        try:
            requests.adapters.DEFAULT_RETRIES = 5 #最大请求连接数
            session = requests.session() #创建请求设备字符
            session.keep_alive = False #关闭多余连接
            data = session.get(url,headers=header,proxies=proxy) #请求数据
        except:
            data = None
            print('error!')
        return data
    def analyse(self):
        page_data= self.request(self.url)
        if page_data is None:
            print('error!')
            return
        page_data = page_data.text
        analyse_data='<a href="(.*?)"><li>(.*?)</li></a>'
        data=re.findall(analyse_data,page_data)
        for i in data:
            if(len(i[0])<1) | (len(i[1])<0):
                continue
            self.url_dict[i[1]]='https://danci.3gifs.com'+i[0]
    def request_result(self):
        for i in self.url_dict:
            data=self.request(self.url_dict[i])
            if data is None:
                print('error!')
                return
            data= data.text
            analyse_data = '<span class=\"gray mr\">(.*?)</span>'
            data=re.findall(analyse_data,data)[0]
            self.word[i]=data
    def append(self,file):
        file.dick=self.word
        file.append_file()

if __name__=='__main__':
    url = 'http://danci.3gifs.com/cet4_list/'
    s=data_space(url)
    s.analyse()
    s.request_result()
    word_path = "../word_list/"
    file = main.file_open(word_path)
    print(file.translate('success'))
    # print(s.word)
