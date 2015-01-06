from flask import Flask, request, abort
import react_render

app = Flask(__name__, static_folder="..")
app.debug = True;

@app.route('/favicon.ico')
def favicon():
    abort(404)

@app.route("/bundle.js")
def bundle():
    return app.send_static_file("bundle.router.js")

@app.route('/', defaults={'path': ''})
@app.route('/<path:path>')
def root(path):
    return react_render.render_path(str(request.path))

if __name__ == "__main__":
    react_render.initialize("../bundle.router.js")
    react_render.set_debug(1)

    app.run()
