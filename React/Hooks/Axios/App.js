import React, { useState, useEffect, useRef } from "react";
import ReactDOM from "react-dom";
import useAxios from "./useAxios";
import "./styles.css";

const App = () => {
  const { loading, error, data, refetch } = useAxios({
    url: "https://yts.am/api/v2/list_movies.json"
  });
  console.log(loading, error, JSON.stringify(data));
  console.log(JSON.stringify(data));

  return (
    <div className="App" style={{ height: "1000vh" }}>
      <h1>{data && data.status}</h1>
      <h2>{loading ? "loading" : "unloading"}</h2>

      <button onClick={refetch}>hello</button>
    </div>
  );
};

export default App;
