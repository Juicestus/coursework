
function toggleStyle() {
    console.log("Toggling style");
    const element = document.getElementById("style-link");
    if (element.getAttribute("href") === "styles-dark.css") {
        element.setAttribute("href", "styles-light.css");
    } else {
        element.setAttribute("href", "styles-dark.css");
    }
}