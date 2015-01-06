module.exports = {
  entry: {
    'bundle.element': './app.element.js',
    'bundle.router': './app.router.js'
  },
  output: {
    filename: '[name].js'
  },
  module: {
    loaders: [
      { test: /\.js$/, loader: 'jsx-loader?harmony' }
    ]
  }
};
