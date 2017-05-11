var express = require('express');
var bodyParser = require('body-parser');
var app = express();
app.use(bodyParser.urlencoded({ extended: true }));

/*
var SerialPort = require("serialport");
var serialPort = new SerialPort("COM13", {
  baudrate: 9600
});

serialPort.on('open', function () {
  if (serialport)
  console.log('serial open');
});
*/

app.post('/send', function(req, res) {
  res.send('You sent the name "' + req.body.name + '".');
  console.log("test");
  /*
  serialPort.write("s\n", function(err, results) {
    console.log('err ' + err);
    console.log('results ' + results);
  });
  */
});

app.listen(8080, function() {
  console.log('Server running at http://127.0.0.1:8080/');
});
