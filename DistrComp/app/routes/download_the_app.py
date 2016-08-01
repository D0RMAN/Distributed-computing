import os

from flask import send_from_directory

from app import work_app_filename, work_app_rel_path
from app import flask_app

@flask_app.route('/download_the_app')
def download_the_app():
    path_to_app = os.path.join(flask_app.root_path, work_app_rel_path)
    return send_from_directory(path_to_app, work_app_filename)
