from flask import Flask, request
import react_render

app = Flask(__name__, static_folder="..")
app.debug = True;

@app.route("/bundle.js")
def bundle():
    return app.send_static_file("bundle.js")

@app.route("/")
def root():
    return react_render.render_element("Homepage")

if __name__ == "__main__":
    react_render.initialize("../bundle.js")
    react_render.set_debug(1)

    app.run()
