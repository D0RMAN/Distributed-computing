from app import flask_app, app_db

with flask_app.app_context():
    app_db.drop_all()
    app_db.create_all()
