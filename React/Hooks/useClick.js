import React, { useState, useEffect, useRef } from "react";
import "./styles.css";

const useClick = (onClick) => {
  if (typeof onClick !== "function") return;

  const element = useRef();
  useEffect(() => {
    //mount/update 되면 아래 if가 실행
    if (element.current) {
      element.current.addEventListener("click", onClick);
    }

    //component will unmount 시 실행
    return () => {
      if (element.current) {
        element.current.removeEventListener("click", onClick);
      }
    };
  }, []);
  return element;
};

const App = () => {
  const sayHello = () => console.log("say hello");
  const sayHello2 = () => console.log("say hello2");

  const title = useClick(sayHello);
  const title2 = useClick(sayHello2);

  return (
    <div className="App">
      <h1 ref={title}>hello</h1>
      <h2 ref={title2}>hello</h2>
    </div>
  );
};

export default App;
