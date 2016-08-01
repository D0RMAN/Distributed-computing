from app import flask_app
from flask import render_template

@flask_app.route('/base')
def base():
	return render_template('base.html', title = None)