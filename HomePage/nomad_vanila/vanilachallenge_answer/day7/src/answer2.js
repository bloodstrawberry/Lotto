// <⚠️ DONT DELETE THIS ⚠️>
//import "./answer2.css";
// <⚠️ /DONT DELETE THIS ⚠️>

const inputValue = document.querySelector(".input-value");
const clearBtn = document.querySelector(".btn-clear");
const buttons = document.querySelectorAll(".btn");

let firstNumber = "";
let secondNumber = "";
let inputOperator = "";

function handleClear() {
  inputValue.innerText = "";
  firstNumber = "";
  secondNumber = "";
  inputOperator = "";
}

function handleCalc() {
  const firstValue = parseInt(firstNumber, 10);
  const secondValue = parseInt(secondNumber, 10);
  let result = 0;
  switch (inputOperator) {
    case "+":
      result = firstValue + secondValue;
      break;
    case "-":
      result = firstValue - secondValue;
      break;
    case "*":
      result = firstValue * secondValue;
      break;
    case "/":
      result = firstValue / secondValue;
      break;
    default:
      return;
  }
  handleClear();
  inputValue.innerText = result;
  return String(result);
}

function clickOperator(operator) {
  const number = inputValue.innerText;
  if (!number) {
    return;
  } else {
    if (firstNumber && secondNumber && inputOperator) {
      firstNumber = handleCalc();
      inputOperator = operator;
    } else {
      if (!firstNumber) {
        firstNumber = secondNumber;
        secondNumber = "";
        inputOperator = operator;
      } else {
        secondNumber = "";
        inputOperator = operator;
      }
    }
  }
}

function clickNumber(number) {
  const input = inputValue.innerText;

  if (!input) {
    inputValue.innerText = number;
    secondNumber = number;
  } else {
    if (inputOperator) {
      if (!secondNumber) {
        inputValue.innerText = number;
        secondNumber = number;
      } else {
        inputValue.innerText += number;
        secondNumber += number;
      }
    } else {
      if (input === "0") {
        inputValue.innerText = number;
        secondNumber = number;
      } else {
        inputValue.innerText += number;
        secondNumber += number;
      }
    }
  }
}

function init() {
  buttons.forEach((button) => {
    button.addEventListener("click", () => {
      switch (button.classList[1]) {
        case "btn-number":
          const number = button.innerText;
          clickNumber(number);
          break;
        case "btn-operator":
          const operator = button.innerText;
          clickOperator(operator);
          break;
        case "btn-equals":
          if (secondNumber) {
            firstNumber = handleCalc();
          }
          break;
        case "btn-clear":
          handleClear();
          break;
        default:
          break;
      }
    });
  });
}

init();
