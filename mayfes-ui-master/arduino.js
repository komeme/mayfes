var express = require('express');
var bodyParser = require('body-parser');
var app = express();
app.use(bodyParser.urlencoded({ extended: true }));

var SerialPort = require("serialport");
var serialPort = new SerialPort('COM13', {
  baudrate: 9600
});

serialPort.on('open', function () {
  console.log('serial open');
});

app.post('/send', function(req, res) {
  console.log('send cmd: ' + req.body.cmd);
  serialPort.write(req.body.cmd, function(err, results) {
    if (err) {
      console.log('err ' + err);
      console.log('results ' + results);
    }
  });
});

app.listen(8080, function() {
  console.log('Server running at http://127.0.0.1:8080/');
});
