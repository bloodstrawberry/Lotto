import React, { useState, useEffect, useRef } from "react";
import "./styles.css";

const useConfirm = (message = "", onConfirm, onCancel) => {
  if (!onConfirm || typeof onConfirm !== "function") return;
  if (onCancel && typeof onCancel !== "function") return;

  const confirmAction = () => {
    if (confirm(message)) {
      onConfirm();
    } else {
      onCancel();
    }
  };

  return confirmAction;
};

const App = () => {
  const deleteWorld = () => console.log("deleteing world");
  const abort = () => console.log("abort");
  const confirmDelete = useConfirm("Are you sure?", deleteWorld, abort);
  return (
    <div className="App">
      <button onClick={confirmDelete}>delete world</button>
    </div>
  );
};

export default App;
