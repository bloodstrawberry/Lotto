// <⚠️ DONT DELETE THIS ⚠️>
import "./styles.css";
// <⚠️ /DONT DELETE THIS ⚠️>

const PENDING_LS = "peding";
const FINISHED_LS = "finished";

const input = document.querySelector("#js-taskInput");
const pendingUl = document.querySelector("#js-pendingUl");
const finishedUl = document.querySelector("#js-finishedUl");
const pendingJSON = localStorage.getItem(PENDING_LS);
const finishedJSON = localStorage.getItem(FINISHED_LS);

function loadPending() {
  const pending = JSON.parse(pendingJSON);
  pending.forEach((li) => {
    addPending(li);
  });
}
function loadFinished() {
  const finished = JSON.parse(finishedJSON);
  finished.forEach((li) => {
    addFinished(li);
  });
}

function savePending() {
  const pendingLi = pendingUl.querySelectorAll("li");
  const liArray = [];
  pendingLi.forEach(function (li) {
    liArray.push(li.firstChild.wholeText);
  });
  const jsonArray = JSON.stringify(liArray);
  localStorage.setItem(PENDING_LS, jsonArray);
}
function saveFinished() {
  const finishedLi = finishedUl.querySelectorAll("li");
  const liArray = [];
  finishedLi.forEach(function (li) {
    liArray.push(li.firstChild.wholeText);
  });
  const jsonArray = JSON.stringify(liArray);
  localStorage.setItem(FINISHED_LS, jsonArray);
}
function save() {
  savePending();
  saveFinished();
}

function addPending(text) {
  const li = document.createElement("li");
  const deleteButton = document.createElement("button");
  const finishedButton = document.createElement("button");
  li.innerText = text;
  deleteButton.innerText = "❌";
  deleteButton.style.margin = "5px 5px";
  deleteButton.onclick = function () {
    li.remove();
    save();
  };
  li.appendChild(deleteButton);
  finishedButton.innerText = "✅";
  finishedButton.style.margin = "5px 5px";
  finishedButton.onclick = function () {
    li.remove();
    addFinished(text);
  };
  li.appendChild(finishedButton);
  pendingUl.appendChild(li);
  save();
}
function addFinished(text) {
  const li = document.createElement("li");
  const deleteButton = document.createElement("button");
  const finishedButton = document.createElement("button");
  li.innerText = text;
  deleteButton.innerText = "❌";
  deleteButton.style.margin = "5px 5px";
  deleteButton.onclick = function () {
    li.remove();
    save();
  };
  li.appendChild(deleteButton);
  finishedButton.innerText = "⛔";
  finishedButton.style.margin = "5px 5px";
  finishedButton.onclick = function () {
    li.remove();
    addPending(text);
  };
  li.appendChild(finishedButton);
  finishedUl.appendChild(li);
  save();
}

input.onkeyup = function (event) {
  if (event.code === "Enter" && event.target.value) {
    addPending(event.target.value);
    input.value = "";
  }
};

function init() {
  if (pendingJSON) {
    loadPending();
  }
  if (finishedJSON) {
    loadFinished();
  }
}
init();
