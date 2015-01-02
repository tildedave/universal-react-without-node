(clojure.lang.RT/loadLibrary "react_render")
(react_render/initialize  "../bundle.js")
(println "Result of evaluating:" (react_render/render_element "Page"))
