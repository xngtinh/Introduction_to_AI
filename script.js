/*----------------------------------------Nhận dạng dấu----------------------------------------*/
function addition(){
  if (number1 === '' || number2 === ''){
    swal("Bạn chưa nhập đủ số!!", "", "warning");
  }
  else{
    document.getElementById('operator').innerText = '+';
    document.getElementById('result').innerText = number1 + number2;
  }
}

function subtraction(){
  if (number1 === '' || number2 === ''){
    swal("Bạn chưa nhập đủ số!!", "", "warning");
  }
  else{
    document.getElementById('operator').innerText = '-';
    document.getElementById('result').innerText = number1 - number2;
  }
}
function multiplication(){
  if (number1 === '' || number2 === ''){
    swal("Bạn chưa nhập đủ số!!", "", "warning");
  }
  else{
    document.getElementById('operator').innerText = '*';
    document.getElementById('result').innerText = number1 * number2;
  }
}
function division(){
  if (number1 === '' || number2 === ''){
    swal("Bạn chưa nhập đủ số!!", "", "warning");
  }
  else{
    if (number2 == 0){
      swal("Số chia phải khác 0", "", "error");
    }
    else{
      document.getElementById('operator').innerText = '/';
      document.getElementById('result').innerText = Math.round( number1 / number2 * 100 + Number.EPSILON ) / 100;
    }
  }
}


/*----------------------------------------Số thứ 1----------------------------------------*/
const canvas = document.getElementById('first-canvas');
const smallCanvas = document.getElementById('first-small-canvas');
const displayBox = document.getElementById('first-prediction');
const inputBox = canvas.getContext('2d');
const smBox = smallCanvas.getContext('2d');

let isDrawing = false;
let model;
var number1, number2;

/* Loads trained model */
async function init() {
  model = await tf.loadModel('https://xngtinh.github.io/model/model.json');
}

canvas.addEventListener('mousedown', event => {
  isDrawing = true;

  inputBox.strokeStyle = 'white';
  inputBox.lineWidth = '15';
  inputBox.lineJoin = inputBox.lineCap = 'round';
  inputBox.beginPath();
});

canvas.addEventListener('mousemove', event => {
  if (isDrawing) drawStroke(event.clientX, event.clientY);
});

canvas.addEventListener('mouseup', event => {
  isDrawing = false;
  updateDisplay(predict());
});

/* Draws on canvas */
function drawStroke(clientX, clientY) {
  // get mouse coordinates on canvas
  const rect = canvas.getBoundingClientRect();
  const x = clientX - rect.left;
  const y = clientY - rect.top;

  // draw
  inputBox.lineTo(x, y);
  inputBox.stroke();
  inputBox.moveTo(x, y);
}

/* Makes predictions */
function predict() {
  let values = getPixelData();
  let predictions = model.predict(values).dataSync();

  return predictions;
}

/* Returns pixel data from canvas after applying transformations */
function getPixelData() {
  smBox.drawImage(inputBox.canvas, 0, 0, smallCanvas.width, smallCanvas.height);
  const imgData = smBox.getImageData(0, 0, smallCanvas.width, smallCanvas.height);

  // preserve and normalize values from red channel only
  let values = [];
  for (let i = 0; i < imgData.data.length; i += 4) {
    values.push(imgData.data[i] / 255);
  }
  values = tf.reshape(values, [1, 28, 28, 1]);
  return values;
}

/* Displays predictions on screen */
function updateDisplay(predictions) {
  // Find index of best prediction, which corresponds to the predicted value
  const bestPred = predictions.indexOf(Math.max(...predictions));
  displayBox.innerText = bestPred;
  number1 = bestPred;
}

document.getElementById('first-erase').addEventListener('click', erase);

/* Clears canvas */
function erase() {
  inputBox.fillStyle = 'black';
  inputBox.fillRect(0, 0, canvas.width, canvas.height);
  displayBox.innerText = '';
  number1 = '';
  document.getElementById('result').innerText = '';
}

erase();
init();

/*----------------------------------------Số thứ 2----------------------------------------*/
const canvas_second = document.getElementById('second-canvas');
const smallCanvas_second = document.getElementById('second-small-canvas');
const displayBox_second = document.getElementById('second-prediction');

const inputBox_second = canvas_second.getContext('2d');
const smBox_second = smallCanvas_second.getContext('2d');

let isDrawing_second = false;
let model_second;

/* Loads trained model */
async function init_second() {
  model_second = await tf.loadModel('https://xngtinh.github.io/model/model.json');
}

canvas_second.addEventListener('mousedown', event => {
  isDrawing_second = true;

  inputBox_second.strokeStyle = 'white';
  inputBox_second.lineWidth = '15';
  inputBox_second.lineJoin = inputBox_second.lineCap = 'round';
  inputBox_second.beginPath();
});

canvas_second.addEventListener('mousemove', event => {
  if (isDrawing_second) drawStroke_second(event.clientX, event.clientY);
});

canvas_second.addEventListener('mouseup', event => {
  isDrawing_second = false;
  updateDisplay_second(predict_second());
});

/* Draws on canvas */
function drawStroke_second(clientX, clientY) {
  // get mouse coordinates on canvas
  const rect = canvas_second.getBoundingClientRect();
  const x = clientX - rect.left;
  const y = clientY - rect.top;

  // draw
  inputBox_second.lineTo(x, y);
  inputBox_second.stroke();
  inputBox_second.moveTo(x, y);
}

/* Makes predictions */
function predict_second() {
  let values = getPixelData_second();
  let predictions = model_second.predict(values).dataSync();

  return predictions;
}

/* Returns pixel data from canvas after applying transformations */
function getPixelData_second() {
  smBox_second.drawImage(inputBox_second.canvas, 0, 0, smallCanvas_second.width, smallCanvas_second.height);
  const imgData = smBox_second.getImageData(0, 0, smallCanvas_second.width, smallCanvas_second.height);

  // preserve and normalize values from red channel only
  let values = [];
  for (let i = 0; i < imgData.data.length; i += 4) {
    values.push(imgData.data[i] / 255);
  }
  values = tf.reshape(values, [1, 28, 28, 1]);
  return values;
}

/* Displays predictions on screen */
function updateDisplay_second(predictions) {
  // Find index of best prediction, which corresponds to the predicted value
  const bestPred = predictions.indexOf(Math.max(...predictions));
  displayBox_second.innerText = bestPred;
  number2 = bestPred;
}

function number(predictions) {
  // Find index of best prediction, which corresponds to the predicted value
  const bestPred = predictions.indexOf(Math.max(...predictions));
  return bestPred;
}

document.getElementById('second-erase').addEventListener('click', erase_second);

/* Clears canvas */
function erase_second() {
  inputBox_second.fillStyle = 'black';
  inputBox_second.fillRect(0, 0, canvas_second.width, canvas_second.height);
  displayBox_second.innerText = '';
  number2 = '';
  document.getElementById('result').innerText = '';
}

erase_second();
init_second();

function all_erase() {
  erase();
  erase_second();
  document.getElementById('operator').innerText = '';
}


