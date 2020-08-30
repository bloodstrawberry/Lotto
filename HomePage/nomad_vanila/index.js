//const title = document.getElementById("title");
const title = document.querySelector("#title"); //.title << class

console.log(title)


title.style.color = 'red';

title.innerHTML = "HI FROM JS"

document.title = "refresh"

function handleClick() {
    title.style.color = "blue";
}

window.addEventListener("click", handleClick);