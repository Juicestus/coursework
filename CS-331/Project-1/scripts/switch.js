const STYLE_KEY = "stylePrefix"; // "styles1" or "styles2"
// Match ".../styles1/..." or at start "styles1/..."
const RX_A = /(^|\/)styles1\//;
const RX_B = /(^|\/)styles2\//;

function setStylePrefix(prefix) {
  const links = document.querySelectorAll('link[rel="stylesheet"]');

  links.forEach(link => {
    const href = link.getAttribute("href");
    if (!href) return;

    let newHref = href;

    if (prefix === "styles2") {
      // swap styles1 -> styles2 anywhere in the path
      if (RX_A.test(href)) newHref = href.replace(RX_A, "$1styles2/");
    } else {
      // swap styles2 -> styles1 anywhere in the path
      if (RX_B.test(href)) newHref = href.replace(RX_B, "$1styles1/");
    }

    if (newHref !== href) {
      link.setAttribute("href", newHref);
    }
  });

  // Button label + extras
  const btn = document.querySelector(".switch-style-btn");
  if (btn) {
    btn.textContent = (prefix === "styles2") ? "S" : "Switch Style";
  }
  if (prefix === "styles2" && typeof updateBorderLines === "function") {
    updateBorderLines();
  }

  localStorage.setItem(STYLE_KEY, prefix);
}

function getCurrentPrefix() {
  // Look at the first stylesheet that contains styles1/ or styles2/
  const link = document.querySelector(
    'link[rel="stylesheet"][href*="styles1/"], link[rel="stylesheet"][href*="styles2/"]'
  );
  if (!link) return "styles2"; // prefer styles2 by default
  const href = link.getAttribute("href") || "";
  if (RX_A.test(href)) return "styles1";
  if (RX_B.test(href)) return "styles2";
  return "styles2";
}

function toggleStyle() {
  const current = getCurrentPrefix();
  const next = (current === "styles1") ? "styles2" : "styles1";
  setStylePrefix(next);
  console.log("Toggled style to:", next);
}

// --- Apply saved OR default (styles2) immediately and on DOM ready ---
(function initStyle() {
  const saved = localStorage.getItem(STYLE_KEY);
  const prefix = (saved === "styles1" || saved === "styles2") ? saved : "styles2";

  // Ensure default is stored on first visit
  if (!saved) localStorage.setItem(STYLE_KEY, "styles2");

  // Run now (in case links already in DOM)
  setStylePrefix(prefix);
  // Run again when DOM is ready (covers cases where links/buttons load later)
  document.addEventListener("DOMContentLoaded", () => setStylePrefix(prefix));
})();
