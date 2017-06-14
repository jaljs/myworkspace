from bottle import route, run, template

@route('/hello')
def hello():
	return "hello world"
@route('/hi')
def hi():
	return "hi jason"

run(host='localhost', port=8080)
