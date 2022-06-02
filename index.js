const modelModule = require("./build/Release/model.node");
const express = require("express");
<<<<<<< HEAD
const busboy = require('connect-busboy');
const path = require('path');
const fs = require('fs-extra');
=======
const cors = require("cors");
>>>>>>> 846d9dc6fcb8321f36c2b792a296c1efc173bb99
const app = express();
app.use(busboy());
app.use(express.static(path.join(__dirname, 'public')));
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
<<<<<<< HEAD
app.route ('/upload').post(function(req, res, next){
  var fstream;
  req.pipe(req.busboy);
  req.busboy.on('file', function(filedname, file, filename){
    fs.readFile(filename, function(err, data){
      if (err) {
        console.log(err);
      }else{
        console.log(data);
        res.setHeader("Content-Type", "application/json");
        res.end(JSON.stringify({data: this.data}));
      }
    });
  });
});
=======

>>>>>>> 846d9dc6fcb8321f36c2b792a296c1efc173bb99
app.listen(port, () => {
  console.log(`Example app listening on port ${port}`);
});
