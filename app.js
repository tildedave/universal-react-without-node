if (typeof(global) !== 'undefined') {
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
        return <div>This is my content</div>;
    }
});

var Homepage = React.createClass({
    render: function() {
        return (
            <html>
            <head>
               <script type="text/javascript" src="/bundle.js"></script>
               <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css" />
            </head>
            <body>
                <div className="container">
                    <h1>Hello Isomorphic React!</h1>
                </div>
            </body>
            </html>
        );
    }
});

if (typeof(window) === 'undefined') {
    // option 1 -> capture markup directly
    //   I don't like this because it is super mysterious
    //capture(React.renderToString(React.createElement(A)));

    // option 2 -> somehow get webpack bundle file to return a value (??)
    //   this is probably not happening

    // option 3 -> somehow get webpack bundle file to make React available in global scope
    global.React = React;
    global.ReactElements = {
        'A': A,
        'Homepage': Homepage
    };

    // Still TODO - an example of calling Router.run from duktape
} else {
  window.onload = function() {
    // Ideally this reads from window.location in order to determine which page is
    // rendered
    React.render(<Homepage />, document);
  };
}
