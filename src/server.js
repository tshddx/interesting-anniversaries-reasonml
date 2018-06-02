const express = require("express");
const bodyParser = require("body-parser");
const path = require("path");
const http = require("http");

const app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

app.use(express.static(path.join(__dirname, "client")));

app.get("/app.js", (req, res) => {
  res.sendFile(path.join(__dirname, "../build/app.js"));
});

app.get("*", (req, res) => {
  res.sendFile(path.join(__dirname, "../build/index.html"));
});

const port = process.env.PORT || "4400";
app.set("port", port);

const server = http.createServer(app);
server.listen(port, () => console.log(`running on localhost: ${port}`));
