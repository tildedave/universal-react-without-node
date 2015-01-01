// Forces React into node.js mode
var global = {};

function consoleShim() {
  print(Array.prototype.join.call(arguments, ' '));
}

var console = {};
['debug', 'log', 'info', 'warn'].forEach(function(i) {
  console[i] = consoleShim;
});
