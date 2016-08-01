from app import flask_app
from flask import redirect, url_for
from flask.ext.login import logout_user

@flask_app.route('/signout', methods=['GET', 'POST'])
def signout():
    logout_user()
    return redirect(url_for('signin'))