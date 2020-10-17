const range = document.getElementById("jsRange");
const h2 = document.querySelector("h2");
const playBtn = document.getElementById("jsPlay");
const div = document.getElementById("result");
const input = document.getElementById("input");

let choose = 10;

function handleRangeChange(event){
    //console.log(event.target.value);
    const size = event.target.value;
    choose = size;
    h2.innerText = `Generate a number between 0 and ` + size;
}

function handlePlayClick() {

    while ( div.hasChildNodes() ) { div.removeChild( div.firstChild ); }


    const h3 = document.createElement("h3");
    const h32 = document.createElement("h3");

    const random = Math.floor(Math.random() * choose);
    h3.innerText = `You chose: ` + input.value + `,the machine chose: ` + random + `.`;
    
    const comp = input.value * 1;

    if(comp === random)
    {
        h32.innerText = "You Win";
    }
    else
    {
        h32.innerText = "You Lose";
    }
    

    div.appendChild(h3);
    div.appendChild(h32);

}

range.addEventListener("input", handleRangeChange);
playBtn.addEventListener("click", handlePlayClick);
