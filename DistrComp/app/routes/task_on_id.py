from flask import render_template
from flask.ext.login import login_required

from app import flask_app
from app.models.task import Task


@flask_app.route('/task/<int:id>')
@login_required
def task(id):
    task = Task.query.get(id)
    author = task.author
    return render_template('task_on_id.html', title='Task', task=task, author=author);
