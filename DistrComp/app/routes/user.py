from flask import render_template
from flask.ext.login import login_required

from app import flask_app
from app.models.user import User


@flask_app.route('/user/<int:id>')
@login_required
def user(id):
    user = User.query.get(id)
    return render_template('user.html', title=user.nickname, user=user);
