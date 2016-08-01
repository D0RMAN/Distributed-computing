from app import flask_app, app_db

class Task(app_db.Model):
    task_id = app_db.Column(app_db.Integer, primary_key=True, autoincrement=True)
    creator_id = app_db.Column(app_db.Integer, app_db.ForeignKey('user.user_id'), unique=False)
    title = app_db.Column(app_db.String(100), unique=False)
    description = app_db.Column(app_db.Text)
    status = app_db.Column(app_db.String(20), unique=False)
    lib_filename = app_db.Column(app_db.String(30))

    def __init__(self, creator_id, title, description, status, lib_filename):
        self.creator_id = creator_id
        self.title = unicode(title)
        self.description = unicode(description)
        self.status = status
        self.lib_filename = lib_filename
