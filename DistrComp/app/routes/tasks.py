from flask import render_template
from sqlalchemy import desc
from flask.ext.login import login_required

from app import flask_app
from app.models.task import Task

@flask_app.route('/tasks')
@login_required
def tasks():
    all_tasks = Task.query.order_by(desc(Task.task_id))
    return render_template(
                    'tasks.html', 
                    title = 'Tasks', 
                    tasks = [(task.author.nickname, task) for task in all_tasks]);
