require('./renderer');

var registerElement = require('./renderer').registerElement;
var React = require('react');

var UnicodeView = React.createClass({
    render: function() {
        return (
            <div>
                <h1>Unicode Snowman for You ☃</h1>
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


if (typeof(window) === 'object') {
    var elements = document.querySelectorAll("[data-element]");
    Array.prototype.forEach.call(elements, function(ele) {
        // TODO: props
        require('./renderer').renderElement(ele.dataset.element, null, ele);
    });
}
