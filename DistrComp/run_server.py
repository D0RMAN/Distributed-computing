from app import flask_app

# flask_app.debug = True
# flask_app.run(port = 8081, host='localhost')

flask_app.debug = False
flask_app.run(port = 8081, host = '0.0.0.0')