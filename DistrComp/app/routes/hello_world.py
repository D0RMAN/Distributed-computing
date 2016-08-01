from app import flask_app
from flask import render_template

@flask_app.route('/')
@flask_app.route('/hello_world/<user_name>')
def hello_world(user_name = None):
	return render_template('hello_world.html', user = user_name, title = user_name)