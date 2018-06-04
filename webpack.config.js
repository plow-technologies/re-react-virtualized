const path = require('path');
const webpack = require('webpack');
const CompressionPlugin = require('compression-webpack-plugin');
const ClosureCompilerPlugin = require('webpack-closure-compiler');
const StatsWriterPlugin = require('webpack-stats-plugin').StatsWriterPlugin;
const ManifestPlugin = require('webpack-manifest-plugin');
const ShakePlugin = require('webpack-common-shake').Plugin;
const SWPrecacheWebpackPlugin = require('sw-precache-webpack-plugin');
const rollupPluginNodeResolve = require('rollup-plugin-node-resolve');

const prod = process.env.NODE_ENV == 'production';
const dev = !prod && process.env.DEV !== '0';
const analyze = process.env.NODE_ENV == 'analyze';
const useRollup = prod || process.env.ROLLUP == '1';
const useShakePlugin = process.env.SHAKE == '1';
const useClosureCompiler = process.env.CLOSURE === '1';

let publicUrl = '';

module.exports = {
  context: __dirname,
  entry: useRollup ? './lib/es6/example/src/Index' : './lib/js/example/src/Index',
  output: {
    filename: '[name].js',
    path: path.join(__dirname, './example/dist/build'),
    publicPath: '/build/',
  },
  devServer: {
    contentBase: path.resolve(__dirname, 'example/public'),
  },
  resolve: {
    alias: {
      src: path.resolve(__dirname, 'src/'),
      example: path.resolve(__dirname, 'example/src/'),
      "re-react-onping-ui": path.resolve(__dirname, '.')
    },
  },
  module: {
    loaders: [
      {
        test: /\.png$/,
        loader: 'file-loader',
      },
      {
        test: /\.css$/,
        use: [{ loader: 'style-loader' }, { loader: 'css-loader' }],
      },
      useRollup
        ? {
          test: /\.js$/,
          loader: 'rollup-loader',
          options: {
            plugins: [rollupPluginNodeResolve({ module: true })],
          },
        }
        : null,
    ].filter(Boolean),
  },
  node: {
    fs: 'empty',
    net: 'empty',
    tls: 'empty',
  },
  plugins: [
    // Generate a service worker script that will precache, and keep up to date,
    // the HTML & assets that are part of the Webpack build.
    new SWPrecacheWebpackPlugin({
      // By default, a cache-busting query parameter is appended to requests
      // used to populate the caches, to ensure the responses are fresh.
      // If a URL is already hashed by Webpack, then there is no concern
      // about it being stale, and the cache-busting can be skipped.
      dontCacheBustUrlsMatching: /\.\w{8}\./,
      filename: 'service-worker.js',
      minify: prod || analyze,
      navigateFallback: publicUrl + '/index.html',
      staticFileGlobsIgnorePatterns: [/\.map$/, /asset-manifest\.json$/],
    }),

    // Generate a manifest file which contains a mapping of all asset filenames
    // to their corresponding output file so that tools can pick it up without
    // having to parse `index.html`.
    new ManifestPlugin({
      fileName: 'asset-manifest.json',
    }),
    new webpack.DefinePlugin({
      'process.env': {
        NODE_ENV: JSON.stringify(!dev ? 'production' : null),
        PUBLIC_URL: JSON.stringify(publicUrl + '/build'),
      },
    }),
    useClosureCompiler
      ? new ClosureCompilerPlugin({
        compiler: {
          language_in: 'ECMASCRIPT6',
          language_out: 'ECMASCRIPT5',
        },
        concurrency: 3,
      })
      : null,
    prod ? new webpack.optimize.UglifyJsPlugin() : null,
    analyze
      ? new webpack.optimize.UglifyJsPlugin({
        compress: {
          warnings: false,
        },
        comments: /^\**!|^ [0-9]+ $|@preserve|@license/,
      })
      : null,
    true
      ? new CompressionPlugin({
        asset: '[path].gz[query]',
        algorithm: 'gzip',
        test: /\.(js|css)$/,
        threshold: 10240,
        minRatio: 0.8,
      })
      : null,
    true
      ? new StatsWriterPlugin({
        filename: 'stats.json',
        fields: null,
        transform: function (data) {
          data.modules.forEach(function (m) {
            delete m.source;
          });
          delete data.children;
          return JSON.stringify(data, null, 2);
        },
      })
      : null,
    useShakePlugin ? new ShakePlugin() : null,
  ].filter(Boolean),
};
