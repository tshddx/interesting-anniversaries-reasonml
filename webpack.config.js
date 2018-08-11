const path = require("path");
const outputDir = path.join(__dirname, "build");

const isProd = process.env.NODE_ENV === "production";

module.exports = {
  entry: "./lib/js/src/Index.bs.js",
  mode: isProd ? "production" : "development",
  output: {
    path: outputDir,
    publicPath: "/",
    filename: "app.js"
  },
  module: {
    rules: [
      {
        test: /\.html$|\.png$/,
        use: [
          {
            loader: "file-loader",
            options: { name: "[name].[ext]" }
          }
        ]
      },
      {
        test: /\.scss$/,
        use: ["style-loader", "css-loader", "sass-loader"]
      }
    ]
  },
  devServer: {
    contentBase: outputDir,
    compress: true,
    port: 9000,
    historyApiFallback: true
  }
};
