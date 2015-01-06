var React = require('react');
var Router = require('react-router');

var registerElement, ReactElements;

if (typeof(Duktape) === 'object') {
    ReactElements = __ReactElements;
    registerElement = __registerElement;

    function consoleShim() {
        print(Array.prototype.join.call(arguments, ' '));
    }

    global.console = {};
    ['debug', 'log', 'info', 'warn', 'warning', 'error'].forEach(function(i) {
        global.console[i] = consoleShim;
    });
} else {
    ReactElements = {};
    registerElement = function(elementName, element) {
        ReactElements[elementName] = element;
    };
}

var renderPath, renderElement;

var __routes;
var registerRoutes = function(routes) {
    __routes = routes;
};

if (typeof(Duktape) === 'object') {
    renderPath = function(path) {
        var markup;
        Router.run(__routes, path, function(Handler) {
            markup = React.renderToString(<Handler />);
        });

        return markup;
    };

    renderElement = function(elementName, props) {
        // Wrapper must live outside of React or checksums mismatch
        return ('<div data-element="' + elementName + '">' +
                React.renderToString(
                    React.createElement(ReactElements[elementName], props)
                ) +
                '</div>');
    };

    // Also make these functions available for server-side rendering
    global.renderPath = renderPath;
    global.renderElement = renderElement;

} else {
    renderPath = function(path) {
        Router.run(__routes, Router.HistoryLocation, function(Handler) {
            React.render(<Handler />, document);
        });
    };

    renderElement = function(element, props, ele) {
        React.render(React.createElement(ReactElements[element], props), ele);
    };
}

module.exports = {
    registerElement: registerElement,
    ReactElements: ReactElements,
    renderPath: renderPath,
    renderElement: renderElement,
    registerRoutes: registerRoutes
};
