#!/usr/bin/env python3
from bottle import get,post,run,request,template

@get("/")
def index():
    return template("index")
@post("/cmd")
def cmd():
    print("按下了按钮: "+request.body.read().decode())
    return "OK"
@post("/mcmd")
def mcmd():
	print("pull-------------->"+request.body.read().decode())
run(host="0.0.0.0",post=8080)

