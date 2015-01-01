if (typeof(window) === 'undefined') {
  var global = {};

  function consoleShim() {
    print(Array.prototype.join.call(arguments, ' '));
  }

  var console = {};
  ['debug', 'log', 'info', 'warn'].forEach(function(i) {
    console[i] = consoleShim;
  });
}

var React = require('react');

var A = React.createClass({
  render: function() {
    return React.DOM.div(null, '☃');
  }
});

if (typeof(window) === 'undefined') {
  // option 1 -> console.log -> capture stdout through duktape global
  capture(React.renderToString(React.createElement(A)));
}

// option 2 -> somehow get webpack bundle file to return a value (??)

// option 3 -> somehow get webpack bundle file to set a value that we can see
