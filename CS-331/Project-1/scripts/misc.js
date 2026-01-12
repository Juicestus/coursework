function registerActiveFunction(activeFunction) {
  window.addEventListener('resize', activeFunction);
  window.addEventListener('scroll', activeFunction);
  window.addEventListener('DOMContentLoaded', activeFunction);
  window.addEventListener('load', activeFunction);
  window.addEventListener('pageshow', activeFunction);
  window.addEventListener('visibilitychange', activeFunction);
}

function swapOrder(id1, id2) {
  const el1 = document.querySelector(`#${id1}`);
  const el2 = document.querySelector(`#${id2}`);
  if (el1 && el2 && el1.parentNode === el2.parentNode) {
    el1.parentNode.insertBefore(el2, el1);
  }
}

function updateBorderLines() {
  const container = document.querySelector('.frame');
  const leftLine = document.querySelector('#left-border-line');
  const rightLine = document.querySelector('#right-border-line');
  if (!container || !leftLine || !rightLine) {
    console.error("One or more elements not found");
    return;
  }
  const rect = container.getBoundingClientRect();
  leftLine.style.left = `${rect.left}px`;
  rightLine.style.left = `${rect.right - 1}px`; // -1 for 1px width
}

let isMobile = false;

registerActiveFunction(function() {

    if (window.innerWidth <= 640 && !isMobile) {
        isMobile = true;
    }
    if (window.innerWidth > 640 && isMobile) {
        isMobile = false;
    }

    updateBorderLines();

});