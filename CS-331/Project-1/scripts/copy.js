// import React, { useState } from "react";
// import "./CopyBox.css";

// const CopyBox = ({ value }) => {
//     const [copied, setCopied] = useState(false);

//     const handleCopy = () => {
//         navigator.clipboard.writeText(value).then(() => {
//             setCopied(true);
//             // setTimeout(() => setCopied(false), 1500);
//         });
//     };

//     return (
//         <div className="copy-box">
//             <input type="text" value={value} readOnly className="copy-input" />
//             <button onClick={handleCopy} className="copy-button" onMouseEnter={() => setCopied(false)}>
//                 <span style={{ visibility: copied ? "hidden" : "visible", position: "absolute" }}>Copy</span>
//                 <span style={{ visibility: copied ? "visible" : "hidden" }}>✓ Copied</span>
//             </button>
//         </div>
//     );
// };

// export default CopyBox;

const copyStates = {};

document.addEventListener("DOMContentLoaded", function() {
    const copyBoxes = document.querySelectorAll(".copy-box");
    copyBoxes.forEach((box, index) => {
        copyStates[index] = false;
    });
});

function copyBtnOnClick(button) {
    const box = button.closest(".copy-box");
    const span = button.querySelector("span");
    const input = box.querySelector(".copy-input");
    if (!input) return;

    navigator.clipboard.writeText(input.value).then(() => {
        copyStates[box.dataset.copyId] = true;
        span.innerHTML = "&#10003; Copied"; // Checkmark
    });
}

function copyBtnOnMouseEnter(button) {
    const box = button.closest(".copy-box");
    copyStates[box.dataset.copyId] = false;
    const span = button.querySelector("span");
    span.innerHTML = "Copy";
}
    