const modelModule = require("./build/Release/model.node");
const express = require("express");
const app = express();
const port = 3000;
console.log(modelModule.lemmatizer("свекруха"))
app.get("/api/lemmatizer/*", (req, res) => {
  const word = req?.params[0];
  const result = modelModule.lemmatizer(word);
  console.log("result", result);
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ data: result }));
});
app.get("/api/stemmer/*", (req, res) => {
  const word = req?.params[0];
  const result = modelModule.stemmer(word);
  console.log("result", result);
  res.setHeader("Content-Type", "application/json");
  res.end(JSON.stringify({ data: result }));
});
app.listen(port, () => {
  console.log(`Example app listening on port ${port}`);
});