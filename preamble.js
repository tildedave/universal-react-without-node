if (typeof(global) !== 'undefined') {
    function consoleShim() {
        print(Array.prototype.join.call(arguments, ' '));
    }

    global.console = {};
    ['debug', 'log', 'info', 'warn', 'warning', 'error'].forEach(function(i) {
        global.console[i] = consoleShim;
    });
} else {
  var registerElement = function() {};
}
