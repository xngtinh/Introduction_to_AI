

// Số thứ 2
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
function drawStroke_second(clientX_second, clientY_second) {
  // get mouse coordinates on canvas
  const rect_second = canvas_second.getBoundingClientRect();
  const x_second = clientX_second - rect_second.left;
  const y_second = clientY_second - rect_second.top;

  // draw
  inputBox_second.lineTo(x_second, y_second);
  inputBox_second.stroke();
  inputBox_second.moveTo(x_second, y_second);
}

/* Makes predictions */
function predict_second() {
  let values_second = getPixelData_second();
  let predictions_second = model_second.predict_second(values_second).dataSync();

  return predictions_second;
}

/* Returns pixel data from canvas after applying transformations */
function getPixelData_second() {
  smBox_second.drawImage(inputBox_second.canvas_second, 0, 0, smallCanvas_second.width, smallCanvas_second.height);
  const imgData_second = smBox_second.getImageData(0, 0, smallCanvas_second.width, smallCanvas_second.height);

  // preserve and normalize values from red channel only
  let values_second = [];
  for (let i = 0; i < imgData_second.data.length; i += 4) {
    values_second.push(imgData_second.data[i] / 255);
  }
  values_second = tf.reshape(values_second, [1, 28, 28, 1]);
  return values_second;
}

/* Displays predictions on screen */
function updateDisplay_second(predictions_second) {
  // Find index of best prediction, which corresponds to the predicted value
  const bestPred_second = predictions_second.indexOf(Math.max(...predictions_second));
  displayBox_second.innerText = bestPred_second;
}

document.getElementById('second-erase').addEventListener('click', erase_second);

/* Clears canvas */
function erase_second() {
  inputBox_second.fillStyle = 'black';
  inputBox_second.fillRect(0, 0, canvas_second.width, canvas_second.height);
  displayBox_second.innerText = '';
}

erase_second();
init_second();
