(ns isomorphic-react.core.handler
  (:require [compojure.core :refer :all]
            [compojure.route :as route]
            [ring.middleware.defaults :refer [wrap-defaults site-defaults]]))

(clojure.lang.RT/loadLibrary "react_render")
(react_render/set_debug 1)
(react_render/initialize  "../../bundle.js")

(defroutes app-routes
  (route/resources "/bundle.js")
  (GET "/favicon.ico" [] "Not Found")
  (GET "*" {:keys [uri]} (react_render/render_path uri)))

(def app
  (wrap-defaults app-routes site-defaults))
