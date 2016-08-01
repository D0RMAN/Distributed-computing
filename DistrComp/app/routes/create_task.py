import os

from flask import render_template, request, redirect, url_for, flash
from flask.ext.login import login_required, current_user
from werkzeug import secure_filename
from sqlalchemy import desc

from app import flask_app, app_db
from app.forms.create_task import TaskForm
from app.models.task import Task
from app.routes import allowed_file


@flask_app.route('/create_task', methods=['GET', 'POST'])
@login_required
def create_task():
    form = TaskForm()
    if request.method == 'POST':
        if form.validate_on_submit():
            if allowed_file(form.library.data.filename):

                user_lib_filename = secure_filename(unicode(form.library.data.filename))

                new_task = Task(
                    creator_id = current_user.user_id,
                    title = form.title.data,
                    description = form.description.data,
                    status = 'Waiting for members',
                    lib_filename = user_lib_filename)

                user_lib_filename = \
                    str(current_user.user_id) + '_' + \
                    str(Task.query.order_by(desc(Task.task_id)).first().task_id + 1) + '_.' +  \
                    user_lib_filename;

                new_task.lib_filename = user_lib_filename

                user_lib_save_path = os.path.join(flask_app.root_path, flask_app.config['UPLOAD_FOLDER'], user_lib_filename)
                form.library.data.save(user_lib_save_path)


                app_db.session.add(new_task)
                app_db.session.commit()
                return redirect(url_for('tasks'))
            else:
                flash("Filename is not allowed")
        else:
            flash(form.errors)
    return render_template('create_task.html', title='Create Task', form=form)