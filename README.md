This repository contains examples how you can render React both client and server-side without using a node.js backend.

Why might you want to do that?  Maybe after years of dealing with npm outages and unstable libraries you long for the simplicity of languages without package managers inside of package managers.  Maybe the recent node.js fork has you scared and evaluating other technology.  Maybe you just aren't allowed to use Node at your job.  Whatever your reasons are I'm certainly not going to judge.

This repository uses [Webpack](https://webpack.github.io/) to build a bundled JavaScript file, uses [Duktape](http://duktape.org) to execute it in a C module, and [SWIG](http://swig.org) to make the C module available to higher-level languages that most of the web is developed in.

# Diagram of the Technologies Involved

![](https://raw.githubusercontent.com/tildedave/isomorphic-react-without-node/master/diagram.png)

Still TODO:
* Handle utf8 properly
* Easier setup/cleaner Makefile (SWIG and Duktape need to be installed)
* Figure out how to inject app server path through react-router
* Show an example of how to initialize with server-side data (e.g. Flux stores)
* Profiling

Other languages TODO:
* Lua
* Go
* Non-node.js JavaScript
