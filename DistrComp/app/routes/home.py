from app import flask_app
from flask import render_template
from flask.ext.login import login_required

@flask_app.route('/home', methods=['GET'])
@login_required
def home():
    return render_template('home.html', title='Home')