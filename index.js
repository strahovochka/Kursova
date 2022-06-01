const modelModule = require("./build/Release/model.node");
const express = require("express");
const cors = require("cors");
const app = express();
const port = 3000;

const allowedOrigins = ["www.example1.com", "www.example2.com"];
app.use(
  cors({
    origin: function (origin, callback) {
      if (!origin) return callback(null, true);
      // if (allowedOrigins.indexOf(origin) === -1) {
      //   const msg =
      //     "The CORS policy for this site does not allow access from the specified Origin.";
      //   return callback(new Error(msg), false);
      // }
      return callback(null, true);
    },
  })
);

app.get("/api/lemmatizer/*", (req, res) => {
  const word = req?.params[0];
  const result = modelModule.lemmatizer(word);
  console.log("result", result);
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ data: result }));
});

app.get("/api/stemmer/*", (req, res) => {
  const word = req?.params[0];
  console.log(req?.path);
  const result = modelModule.stemmer(word);
  console.log("result", result);
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ data: result }));
});

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`);
});
