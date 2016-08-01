import os

from flask import send_from_directory

from app import flask_app

@flask_app.route('/download_lib/<lib_filename>')
def download_lib(lib_filename):
    path_to_lib = os.path.join(flask_app.root_path, flask_app.config['UPLOAD_FOLDER'])
    return send_from_directory(path_to_lib, lib_filename)
