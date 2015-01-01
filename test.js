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
    return React.DOM.div(null, 'This is my content');
  }
});

console.log(React.renderToString(React.createElement(A)));
