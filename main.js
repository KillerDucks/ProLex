const express = require("express");
const app = express();
const busboy = require("connect-busboy");
const fs = require("fs-extra");
const { exec } = require('child_process');

app.use(express.static(__dirname+"/views"));
app.use(busboy());

app.get("/", (req, res) => {
  res.send(__dirname+"/views/index.html");
})

app.post("/upload", function (req, res, next) {
  console.log("We are hit")
  let fstream;
  req.pipe(req.busboy);
  req.busboy.on('file', function (fieldname, file, filename){
    console.log("Uploading: " + filename);

    fstream = fs.createWriteStream(__dirname + '/code/' + filename);
    file.pipe(fstream);
    fstream.on('close', function(){
      console.log("Upload Finished of " + filename);
      res.redirect('back');
    })
  })
})

app.listen(8080, () => {
  console.log("dfigvnjd");
})


exec('cat *.js bad_file | wc -l', (err, stdout, stderr) => {
  if (err) {
    // node couldn't execute the command
    return;
  }

  // the *entire* stdout and stderr (buffered)
  console.log(`stdout: ${stdout}`);
  console.log(`stderr: ${stderr}`);
});