from flask import Flask, request, abort
import json
import react_render

app = Flask(__name__, static_folder="..")
app.debug = True;

@app.route('/favicon.ico')
def favicon():
    abort(404)

@app.route("/bundle.js")
def bundle():
    return app.send_static_file("bundle.element.js")

@app.route('/')
def root():
    return (react_render.render_element('UnicodeView', None) +
            react_render.render_element('PropsView', json.dumps({'name': 'Sarah'})) +
            react_render.render_element('PropsView', json.dumps({'name': 'Mark'})) +
            react_render.render_element('UnicodeView', None) +
            '<script type="text/javascript" src="/bundle.js"></script>')

if __name__ == "__main__":
    react_render.initialize("../bundle.element.js")
    react_render.set_debug(1)

    app.run()
