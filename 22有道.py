import random
import json
import requests
from hashlib import md5
import time

"""
代码  （反爬机制就是下面这串代码，data里面的数据就是下面的代码导致变化）
var r = function(e) {
        var t = n.md5(navigator.appVersion)
          , r = "" + (new Date).getTime()
          , i = r + parseInt(10 * Math.random(), 10);
        return {
            ts: r,
            bv: t,
            salt: i,
            sign: n.md5("fanyideskweb" + e + i + "Tbh5E8=q6U3EXe+&L[4c@")
        }
    };
"""
#------------------------------------解密过程-------------------------------------
#将js代码转换成python代码
# appVersion = "5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4302.0 Safari/537.36"（放在js代码里面的appVersion上面显示出来的）
# def r(e):
#     t = md5(appVersion.encode()).hexdigest()  #第一个解密出来bv(是由js使用md5方式将请求头进行了加密)
#     print(t)
#
#     r = time.time()
#     print(r)
#     #1607429023383  js console里面执行 "" + (new Date).getTime()
#     #1607429136.9202993   py  执行time.time
#     #分析可以得出js里面多三位
#     r = str(int(time.time() * 1000))      #int出去小数 js 里面是字符串
#     print(r)        #第二个解密出来lts（r）
#
#     #开始分析第三个
#     #拿着r + parseInt(10 * Math.random(), 10)去js console里面执行  拿到"16074289694056"
#     #由于r上面已经分析出来了    js console 里面发现parseInt(10 * Math.random(), 10)是随机生成0，10的整数
#     i = r + str(random.randint(0,9))
#     print(i)    #第三个解密出来 salt（i）
#
#     #开始分析第四个 sign
#     #同第一个解密   使用md5加密
#
#     return {
#         "ts": r,
#         "bv": t,
#         "salt": i,
#         "sign": md5(('fanyideskweb' + e + i + 'Tbh5E8=q6U3EXe+&L[4c@').encode()).hexdigest(),
#     }
#     print(r("hello"))  # data数据全部解密得到
#

class YouDao:
    def __init__(self,word):
        bv = md5("5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4302.0 Safari/537.36".encode()).hexdigest()  #第一个解密出来bv(是由js使用md5方式将请求头进行了加密)
        lts = str(int(time.time() * 1000))      #js 里面是字符串
        salt = lts + str(random.randint(0,9))
        sign = md5(('fanyideskweb' + word + salt + 'Tbh5E8=q6U3EXe+&L[4c@').encode()).hexdigest()

        self.url="http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule"

        self.headers = {
            "Accept": "application/json, text/javascript, */*; q=0.01",
            "Accept-Encoding": "gzip, deflate",
            "Accept-Language": "zh-CN,zh;q=0.9",
            "Connection": "keep-alive",
            "Content-Length": "236",
            "Content-Type": "application/x-www-form-urlencoded; charset=UTF-8",
            "Cookie": "OUTFOX_SEARCH_USER_ID=-1447334812@10.169.0.102; JSESSIONID=aaaiyLnkDD5GwdtRVEbzx; OUTFOX_SEARCH_USER_ID_NCOO=1082445973.6792932; ___rl__test__cookies=1607425735418",
            "Host": "fanyi.youdao.com",
            "Origin": "http://fanyi.youdao.com",
            "Referer": "http://fanyi.youdao.com/",
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4302.0 Safari/537.36",
            "X-Requested-With": "XMLHttpRequest",
        }

        self.data = {
            "i":word,
            "from":"AUTO",
            "to": "AUTO",
            "smartresult": "dict",
            "client": "fanyideskweb",
            "salt": salt,
            "sign": sign,
            "lts": lts,
            "bv": bv,
            "doctype": "json",
            "version": "2.1",
            "keyfrom": "fanyi.web",
            "action": "FY_BY_REALTlME",
        }

    def get_data(self):
        response = requests.post(self.url,headers=self.headers,data=self.data)
        return response.content.decode()

    def run(self):
        response = self.get_data()
        try:
            print(json.loads(response)["smartResult"]["entries"][1])     #英译汉
        except:
            print(response)   #   汉译英

if __name__ == '__main__':
    while True:
        word = input("请输入你要翻译的:")
        youdao = YouDao(word)
        youdao.run()    