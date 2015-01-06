import react_render
import json

react_render.set_debug(1)
react_render.initialize("../bundle.router.js")
print("Result of rendering {0}: {1}".format("/", react_render.render_path("/")))
print("Result of rendering {0}: {1}".format("/blue", react_render.render_path("/blue")))
print("Result of rendering {0}: {1}".format("/red", react_render.render_path("/red")))
print("Result of rendering {0}: {1}".format("/notfound", react_render.render_path("/notfound")))

react_render.set_debug(1)
react_render.initialize("../bundle.element.js")

print("Result of rendering {0}: {1}"
      .format("UnicodeView",
              react_render.render_element("UnicodeView", None)))
print("Result of rendering {0}: {1}"
      .format("PropsView",
              react_render.render_element("PropsView", json.dumps({ 'name': 'Sarah' }))))
