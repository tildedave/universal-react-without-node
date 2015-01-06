# Isomorphic React (without Node.js)

[![Build Status](https://travis-ci.org/tildedave/isomorphic-react-without-node.svg?branch=master)](https://travis-ci.org/tildedave/isomorphic-react-without-node)

This repository contains examples how you can render React both client and server-side without using a node.js backend.

Why might you want to do that?  Maybe after years of dealing with npm outages and unstable libraries you long for the simplicity of languages without package managers inside of package managers.  Maybe the recent node.js fork has you scared and evaluating other technology.  Maybe you just aren't allowed to use Node at your job.  Whatever your reasons are I'm certainly not going to judge.

This repository uses [Webpack](https://webpack.github.io/) to build a bundled JavaScript file, uses [Duktape](http://duktape.org) to execute it in a C module, and [SWIG](http://swig.org) to make the C module available to higher-level languages that most of the web is developed in.

# Diagram of the Technologies Involved

![](https://raw.githubusercontent.com/tildedave/isomorphic-react-without-node/master/diagram.png)

Still TODO:
* Show an example of how to initialize with server-side data (e.g. Flux stores)
* Profiling

Other languages TODO:
* Lua
* Go
* Non-node.js JavaScript

# Main Server-Side Rendering Concepts

**Rendering a Path**: You are using [react-router](https://github.com/rackt/react-router) or some similar concept.   Your app is rendered simply as a providing a path into which.

**Render an Element**: You have special views that are rendered from your server.

## Saturating Your Server-Side Data

If your views contain dynamic data you need a way to "pre-fill" data that they rely on on the server-side.  As an example of what may happen otherwise, you may render a not-logged-in page on the server that is immediately replaced by a logged-in page on the client after a few AJAX calls are made.  Ideally you are providing the same data to the client and server to render the same markup on client and server.

This repository does not yet contain examples of this.  For a good getting started guide on the general problem see the [Isomorphic Flux](https://speakerdeck.com/mridgway/isomorphic-flux) talk and the [`dispatchr`](https://github.com/yahoo/dispatchr) library.

# Disclaimer

I wouldn't run this code in production!  Even if you *can* do these things, should you really?  (I have no idea!)  This project came out of a feeling that it would be great if the React ecosystem supported a more diverse set of server-side technologies - why should you be locked in to a node.js solution on your backend?  This repo provides the homomorphisms from your JavaScript views into the server-side language of your choice.

(Yes node.js is still used to generate the bundle.)

## Other Things I've Found

* https://github.com/101loops/go-reactjs/ - React.js rendering in Golang using Otto
* https://github.com/augustl/react-nashorn-example - Renders React server-side using JDK8 + Nashorn
