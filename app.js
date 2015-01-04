if (typeof(global) !== 'undefined') {
    function consoleShim() {
        print(Array.prototype.join.call(arguments, ' '));
    }

    var console = {};
    ['debug', 'log', 'info', 'warn', 'error'].forEach(function(i) {
        console[i] = consoleShim;
    });
}

var React = require('react');
var Link = require('react-router').Link;
var Route = require('react-router').Route;
var Router = require('react-router');
var RouteHandler = require('react-router').RouteHandler;
var DefaultRoute = require('react-router').DefaultRoute;
var NotFoundRoute = require('react-router').NotFoundRoute;

var A = React.createClass({
    render: function() {
        return <div>This is my content</div>;
    }
});

var Homepage = React.createClass({
    render: function() {
        return (
            <div>
                <h1>Hello Isomorphic React!</h1>
                <ul>
                    <li><Link to="red">red</Link></li>
                    <li><Link to="blue">blue</Link></li>
                </ul>
            </div>
        );
    }
});

var Red = React.createClass({
    render: function() {
        var style = { 'backgroundColor': '#900000' };

        return (
            <div style={style}>
                <h1>Hello, Red!</h1>
                <ul>
                    <li><Link to="home">home</Link></li>
                    <li><Link to="blue">blue</Link></li>
                </ul>
            </div>
        );
    }
});

var Blue = React.createClass({
    render: function() {
        var style = { 'backgroundColor': '#87cefa' };

        return (
            <div style={style}>
                <h1>Ohai, Blue!</h1>
                <ul>
                    <li><Link to="home">home</Link></li>
                    <li><Link to="red">red</Link></li>
                </ul>
            </div>
        );
    }
});

var NotFound = React.createClass({
    render: function() {
        return (
            <div>
                <h1>404 :(</h1>
                <img src="http://httpcats.herokuapp.com/404" />
            </div>
       );
    }
});

var App = React.createClass({
    render: function() {
        return (
            <html>
               <head>
                  <script type="text/javascript" src="/bundle.js"></script>
                  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css" />
               </head>
               <body>
                   <div className="container">
                       <RouteHandler />
                   </div>
               </body>
            </html>
        );
    }
});

var routes = (
    <Route handler={App} path="/">
        <DefaultRoute handler={Homepage} name="home" />
        <Route handler={Red} name="red" path="red" />
        <Route handler={Blue} name="blue" path="blue" />
        <NotFoundRoute handler={NotFound} />
    </Route>
);

if (typeof(window) === 'undefined') {
    global.render = function(path) {
        var markup;
        Router.run(routes, path, function(Handler) {
            markup = React.renderToString(<Handler />);
        });

        return markup;
    };
} else {
    Router.run(routes, Router.HistoryLocation, function(Handler) {
        React.render(<Handler />, document);
    });
}
