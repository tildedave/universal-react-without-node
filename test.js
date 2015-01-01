var React = global.React;

var A = React.createClass({
  render: function() {
    return React.DOM.div(null, 'This is my content');
  }
});

console.log(React.renderToString(React.createElement(A)));
