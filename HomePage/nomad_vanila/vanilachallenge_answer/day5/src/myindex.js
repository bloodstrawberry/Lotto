const jsForm = document.querySelector(".js-Form");
const pendingInput = jsForm.querySelector("input");
const pendingList = document.querySelector(".pending-List");
const finishList = document.querySelector(".finish-List");

const PENDING_LS = 'pendings';
const FINISH_LS = 'finishes';


let pendings = [];
let finishes = [];



function filterFn(toDo){

}

function deletePending(event) {

    const btn = event.target;
    const li = btn.parentNode;
    pendingList.removeChild(li);
    const cleanToDos = pendings.filter(function(toDo){
        return toDo.id !== parseInt(li.id);
    });

    console.log(cleanToDos);
    pendings = cleanToDos;
    savePendings();
}

function deleteFinish(event) {

  const btn = event.target;
  const li = btn.parentNode;
  finishList.removeChild(li);
  const cleanToDos = finishes.filter(function(toDo){
      return toDo.id !== parseInt(li.id);
  });

  console.log(cleanToDos);
  finishes = cleanToDos;
  saveFinishes();
}


function savePendings() {
    localStorage.setItem(PENDING_LS, JSON.stringify(pendings));
}

function saveFinishes() {
  localStorage.setItem(FINISH_LS, JSON.stringify(finishes));
}

function moveFinish(text) {
  FinishToDo(text);
}

function movePending(text) {
  paintToDo(text);
}

function paintToDo(text){

    const li = document.createElement("li");
    const delBtn = document.createElement("button");
    const moveBtn = document.createElement("button");

    delBtn.innerText = "X";
    //delBtn.addEventListener("click",deletePending);
    
    moveBtn.innerText = "V";
    moveBtn.addEventListener("click", deletePending);
    moveBtn.addEventListener("click", function(){
      moveFinish(text);
    });
    
    const span = document.createElement("span");
    span.innerText = text;
    const newId = pendings.length + 1;

    li.appendChild(span);
    li.appendChild(delBtn);
    li.appendChild(moveBtn);
    
    li.id = newId;
    pendingList.appendChild(li);

    const toDoObj = {
        text: text,
        id: newId
    };
    pendings.push(toDoObj);
    savePendings();
}

function FinishToDo(text){
  const li = document.createElement("li");
  const delBtn = document.createElement("button");
  const moveBtn = document.createElement("button");

  delBtn.innerText = "X";
  delBtn.addEventListener("click", deleteFinish);
  moveBtn.innerText = "V";
  moveBtn.addEventListener("click", deleteFinish);
  moveBtn.addEventListener("click", function(){
    movePending(text);
  });
  
  const span = document.createElement("span");
  span.innerText = text;
  const newId = finishes.length + 1;

  li.appendChild(span);
  li.appendChild(delBtn);
  li.appendChild(moveBtn);
  
  li.id = newId;
  finishList.appendChild(li);

  const toDoObj = {
      text: text,
      id: newId
  };
  finishes.push(toDoObj);
  saveFinishes();
}

function handleSubmit(event) {
    event.preventDefault();
    const currentValue = pendingInput.value;
    console.log(currentValue);

    if(currentValue === "") return;


    paintToDo(currentValue);
    pendingInput.value = "";
}

function loadMyList() {
    const loaded = localStorage.getItem(PENDING_LS);
    const floaded = localStorage.getItem(FINISH_LS);

    if(loaded !== null) {
        const parsedToDos = JSON.parse(loaded);

        parsedToDos.forEach(function(toDo) {
            paintToDo(toDo.text);
        });  
    } 

    if(floaded !== null) {
      const parsedToDos = JSON.parse(floaded);

      parsedToDos.forEach(function(toDo) {
        FinishToDo(toDo.text);
      });  
  } 
}

function init(){
    loadMyList();
    jsForm.addEventListener("submit", handleSubmit)
}

init();

