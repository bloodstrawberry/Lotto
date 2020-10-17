const reset = document.getElementById("reset");
const btn7 = document.getElementById("btn7");
const btn8 = document.getElementById("btn8");
const btn9 = document.getElementById("btn9");
const btnplus = document.getElementById("btnplus");
const btn4 = document.getElementById("btn4");
const btn5 = document.getElementById("btn5");
const btn6 = document.getElementById("btn6");
const btnminus = document.getElementById("btnminus");
const btn1 = document.getElementById("btn1");
const btn2 = document.getElementById("btn2");
const btn3 = document.getElementById("btn3");
const btnmul = document.getElementById("btnmul");
const btn0 = document.getElementById("btn0");
const btnequal = document.getElementById("btnequal");
const btndivide = document.getElementById("btndivide");

const input = document.getElementById("input");

let saveResult = 0;
let btnCheck = false;
let btnStatus = "";

function handleClickReset()
{
    input.value = "0";
    saveResult = 0;
}

function handleClickBtn7()
{
    let temp = input.value * 1;
    
    if(btnStatus !== "") temp = 0;

    if(temp)
    {
        input.value = temp + "";
        input.value = temp + "7";
    }
    else
    {
        input.value = "7";   
    }
}

function handleClickBtn8()
{
    let temp = input.value * 1;

    if(btnStatus !== "") temp = 0;

    if(temp)
    {
        input.value = temp + "";
        input.value = temp + "8";
    }
    else
    {
        input.value = "8";   
    }
}

function handleClickBtn9()
{
    let temp = input.value * 1;
    
    if(btnStatus !== "") temp = 0;

    if(temp)
    {
        input.value = temp + "";
        input.value = temp + "9";
    }
    else
    {
        input.value = "9";   
    }
}
function handleClickBtnplus()
{
    saveResult = input.value * 1;
    btnStatus = "plus";

    if(btnCheck)
    {
        const inputValue = input.value * 1;
        const result = saveResult + inputValue;
        saveResult = result;

        input.value = result + "";
    }
    else
    {
        btnCheck = true;
    }
}
function handleClickBtn4()
{
    let temp = input.value * 1;
    
    if(btnStatus !== "") temp = 0;

    if(temp)
    {
        input.value = temp + "";
        input.value = temp + "4";
    }
    else
    {
        input.value = "4";   
    }
}
function handleClickBtn5()
{
    let temp = input.value * 1;
    
    if(btnStatus !== "") temp = 0;

    if(temp)
    {
        input.value = temp + "";
        input.value = temp + "5";
    }
    else
    {
        input.value = "5";   
    }
}
function handleClickBtn6()
{
    let temp = input.value * 1;
    
    if(btnStatus !== "") temp = 0;

    if(temp)
    {
        input.value = temp + "";
        input.value = temp + "6";
    }
    else
    {
        input.value = "6";   
    }
}
function handleClickBtnminus()
{
    saveResult = input.value * 1;
    btnStatus = "minus";

    if(btnCheck)
    {
        const inputValue = input.value * 1;
        const result = saveResult - inputValue;
        saveResult = result;

        input.value = result + "";
    }
    else
    {
        btnCheck = true;
    }
}
function handleClickBtn1()
{
    let temp = input.value * 1;
    
    if(btnStatus !== "") temp = 0;

    if(temp)
    {
        input.value = temp + "";
        input.value = temp + "1";
    }
    else
    {
        input.value = "1";   
    }
}
function handleClickBtn2()
{
    let temp = input.value * 1;
    
    if(btnStatus !== "") temp = 0;

    if(temp)
    {
        input.value = temp + "";
        input.value = temp + "2";
    }
    else
    {
        input.value = "2";   
    }
}
function handleClickBtn3()
{
    let temp = input.value * 1;
    
    if(btnStatus !== "") temp = 0;

    if(temp)
    {
        input.value = temp + "";
        input.value = temp + "3";
    }
    else
    {
        input.value = "3";   
    }
}
function handleClickBtnmul()
{
    saveResult = input.value * 1;
    btnStatus = "mul";

    if(btnCheck)
    {
        const inputValue = input.value * 1;
        const result = saveResult * inputValue;
        saveResult = result;

        input.value = result + "";
    }
    else
    {
        btnCheck = true;
    }
}
function handleClickBtn0()
{
    let temp = input.value * 1;
    
    if(btnStatus !== "") temp = 0;

    if(temp)
    {
        input.value = temp + "";
        input.value = temp + "0";
    }
    else
    {
        input.value = "0";   
    }
}
function handleClickBtnequal()
{
    btnCheck = false;

    if(btnStatus === "plus")
    {
        const inputValue = input.value * 1;
        const result = saveResult + inputValue;
        input.value = result + "";
    }
    else if(btnStatus === "minus")
    {
        const inputValue = input.value * 1;
        const result = saveResult - inputValue;
        input.value = result + "";
    }
    else if(btnStatus === "mul")
    {
        const inputValue = input.value * 1;
        const result = saveResult * inputValue;
        input.value = result + "";
    }
    else if(btnStatus === "div")
    {
        const inputValue = input.value * 1;
        const result = saveResult / inputValue;
        input.value = result + "";
    }


    saveResult = 0;
    btnStatus = "";
}
function handleClickBtndivide()
{
    saveResult = input.value * 1;
    btnStatus = "div";

    if(btnCheck)
    {
        const inputValue = input.value * 1;
        const result = saveResult / inputValue;
        saveResult = result;

        input.value = result + "";
    }
    else
    {
        btnCheck = true;
    }
}


reset.addEventListener("click", handleClickReset);
btn7.addEventListener("click", handleClickBtn7);
btn8.addEventListener("click", handleClickBtn8);
btn9.addEventListener("click", handleClickBtn9);
btnplus.addEventListener("click", handleClickBtnplus);
btn4.addEventListener("click", handleClickBtn4);
btn5.addEventListener("click", handleClickBtn5);
btn6.addEventListener("click", handleClickBtn6);
btnminus.addEventListener("click", handleClickBtnminus);
btn1.addEventListener("click", handleClickBtn1);
btn2.addEventListener("click", handleClickBtn2);
btn3.addEventListener("click", handleClickBtn3);
btnmul.addEventListener("click", handleClickBtnmul);
btn0.addEventListener("click", handleClickBtn0);
btnequal.addEventListener("click", handleClickBtnequal); 
btndivide.addEventListener("click", handleClickBtndivide);