import react_render

react_render.set_debug(1)
react_render.initialize("../bundle.js")
a = react_render.render_element("/")

print "We got back a string"
print "It is %s" % a
