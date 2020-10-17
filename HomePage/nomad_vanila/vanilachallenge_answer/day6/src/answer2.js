// <⚠️ DONT DELETE THIS ⚠️>
import "./styles.css";
// <⚠️ /DONT DELETE THIS ⚠️>

const generateNum = document.querySelector(".js-generated-num"),
  range = document.querySelector(".js-range"),
  guessNum = document.querySelector(".js-num"),
  play = document.querySelector(".js-btn"),
  choosenNum = document.querySelector(".js-choose-num"),
  result = document.querySelector(".js-game-result");

function printGeneratedNumb() {
  const changedRange = event.target.value;
  generateNum.innerText = `: Generate a number between 0 and ${changedRange}`;
}

function getRandomInt() {
  const changedRange = JSON.parse(range.value);
  const number = Math.floor(Math.random() * changedRange + 1);
  return number;
}

function playGame() {
  const changedRange = JSON.parse(range.value); //string --> number
  let guessedNumer = JSON.parse(guessNum.value);
  const randomNumber = getRandomInt();
  if (
    guessedNumer % 1 === 0 &&
    0 <= guessedNumer &&
    guessedNumer <= changedRange
  ) {
    if (guessedNumer === randomNumber) {
      choosenNum.innerText = ` You chose: ${guessedNumer}, the machine chose: ${randomNumber} `;
      result.innerText = "You win!";
      result.style.color = "red";
    } else {
      choosenNum.innerText = ` You chose: ${guessedNumer}, the machine chose: ${randomNumber} `;
      result.innerText = "You Loose~";
      result.style.color = "black";
    }
  } else if (guessedNumer % 1 !== 0) {
    choosenNum.innerText = `You have to choose the integer  ex) 1.4 ❌ --> 1 ⭕️ `;
    result.innerText = "";
  } else {
    choosenNum.innerText = `Please choose the number between 0 and ${changedRange}.`;
    result.innerText = "";
  }
}

function init() {
  range.addEventListener("change", printGeneratedNumb);
  play.addEventListener("click", playGame);
}

init();
