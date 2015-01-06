require('./renderer');

var registerElement = require('./renderer').registerElement;
var React = require('react');

var UnicodeView = React.createClass({
    onClick: function() {
        alert('Snowmen are the best!');
    },

    render: function() {
        return (
            <div>
                <h1>Unicode Snowman for You ☃</h1>
                <a onClick={this.onClick}>Click here</a>
            </div>
       );
    }
});

var PropsView = React.createClass({
    render: function() {
        return (
            <div>
                <h1>Hello, {this.props.name}!</h1>
            </div>
       );
    }
});

// Make these views available for server-side rendering
// These statements could be automatically generated as part of the build (e.g. through
// a transform-loader that files to detect certain formatted statements)
//
// React Router views are not included here - they need to be rendered within a Router.run
// block to really work.

registerElement("PropsView", PropsView);
registerElement("UnicodeView", UnicodeView);
