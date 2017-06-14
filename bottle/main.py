#/usr/bin/env python
#coding = utf-8

from bottle import route,run,template

@route('/login')
def login():
	return template('login')
@route('/info')
def info():
	name ='jason'
	age = '20'
	blog = 'www.helllo.com'
	qq = '123312312'
	return template('info',tname=name,tage=age,tblog=blog,tqq=qq)
run(host="192.168.0.105",port=8080)


