(clojure.lang.RT/loadLibrary "react_render")
(react_render/initialize  "../bundle.router.js")
(println "Hello, Clojure!")
(println "Result of evaluating:" (react_render/render_path "/"))
(println "Result of evaluating:" (react_render/render_path "/abc"))
(println "Result of evaluating:" (react_render/render_path "/red"))
(println "Result of evaluating:" (react_render/render_path "/blue"))

(react_render/reset)
(react_render/initialize  "../bundle.element.js")
(println "Hello, Clojure!")
(println "Result of evaluating:" (react_render/render_element "UnicodeView" nil))
(println "Result of evaluating:" (react_render/render_element "PropsView" nil))
