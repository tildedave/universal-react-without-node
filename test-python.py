import react_render

react_render.initialize("bundle.js")
a = react_render.render_element("A")

print "We got back a string"
print "It is %s" % a
