import React, { useState, useEffect, useRef } from "react";
import ReactDOM from "react-dom";
import "./styles.css";

const useNotification = (title, options) => {
  console.log("here2");
  if (!("Notification" in window)) return;
  console.log("here");
  const fireNotif = () => {
    console.log("click", Notification.permission);
    if (Notification.permission !== "granted") {
      Notification.requestPermission().then((permission) => {
        if (permission === "granted") {
          new Notification(title, options);
        } else {
          return;
        }
      });
    } else {
      console.log(title, options);
      new Notification(title, options);
    }
  };
  return fireNotif;
};

const App = () => {
  const triggerNotif = useNotification("Can I ?", { body: "can you?" });

  return (
    <div className="App" style={{ height: "1000vh" }}>
      <button onClick={triggerNotif}>hello</button>
    </div>
  );
};

export default App;
