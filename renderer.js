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
        var re = /data-reactid="([^"]*)"/;
        var markup = React.renderToString(
            React.createElement(ReactElements[elementName], props)
        );
        var id = re.exec(markup)[1];

        var propsAsString = null;
        if (props) {
            propsAsString = '"' + encodeURIComponent(JSON.stringify(props)) + '"';
        }

        // Wrapper must live outside of React or checksums mismatch
        var scriptTag = (
            '<script type="text/javascript">' +
            'window.__reactElements = window.__reactElements || []; ' +
            'window.__reactElements.push(["' + id + '", "' + elementName + '", JSON.parse(decodeURIComponent(' + propsAsString + '))]);' +
            '</script>'
        );

        return ('<div>' + markup + '</div>' + scriptTag);
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

    document.addEventListener('DOMContentLoaded', function() {
        window.__reactElements.forEach(function(eleData) {
            var ele = document.querySelector('[data-reactid="' + eleData[0] + '"]');
            renderElement(eleData[1], eleData[2], ele.parentNode);
        });
    });
}

module.exports = {
    registerElement: registerElement,
    ReactElements: ReactElements,
    renderPath: renderPath,
    renderElement: renderElement,
    registerRoutes: registerRoutes
};
