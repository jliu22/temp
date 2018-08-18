# From zhihu.com Jeffersli
#!/usr/bin/python

import re
import json
import requests
from time import sleep

print('hello')
print('how are you')
replys = raw_input("topic:")
while 1:
    info = replys
    replysa = replys
    resp = requests.get("http://api.qingyunke.com/api.php", {'key': 'free', 'appid': 0, 'msg': info})
    # resp.encoding = 'utf-8'
    resp = resp.json()
    resp = re.sub("{br}", "", resp['content'])
    print '111:', resp.encode('utf-8')
    sleep(1)

    api_url = 'http://www.tuling123.com/openapi/api'
    apikey = '4fede3c4384846b9a7d0456a5e1e2943'
    req = requests.post(api_url, data={'key': apikey, 'info': resp}).text
    replys = json.loads(req)['text']
    if replys != replysa:
        print '222:', replys.encode('utf-8')
        sleep(1)
    else:
        replys = "change topic:"

'''
test result like:

[root@dc1efbcc5307 /]# python test.py 
hello
how are you
topic:weather
111: 先告诉菲菲您在哪个城市，让我帮您查天气吧
222: 亲爱的，当天请求次数已用完。
111: 都啥年代了，还一句句的亲爱的
111: 咱是中国人，请讲中文，谢谢！
222: 亲爱的，当天请求次数已用完。
111: 网友好肉麻的说
111: 咱是中国人，请讲中文，谢谢！
222: 亲爱的，当天请求次数已用完。
111: 网友好肉麻的说
111: 发的什么呀你，乱打的吧
222: 亲爱的，当天请求次数已用完。
111: 能不能别老是亲爱亲爱的呀，听着烦呢

'''
