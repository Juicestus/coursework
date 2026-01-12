import { useEffect, useRef, useState } from "react";
import { translateBatch } from "../customer-pages/menu.jsx";
import { translateOne } from "../customer-pages/menu.jsx";


let __translateAllVisibleText = null;

export async function globalTranslateAllVisibleText() {
    if (__translateAllVisibleText === null) {
        console.log("__translateAllVisibleText is NULL");
        return;
    }
    console.log("Asked for global render");
    // setTimeout(() => __translateAllVisibleText(), 500);
}

// ✅ Global translated alert
export async function transAlert(message) {
    try {
        const lang = localStorage.getItem("lang") || "en";

        if (lang === "en") {
            window.__nativeAlert(message);
            return;
        }

        const translated = await translateOne(message, lang);
        window.__nativeAlert(translated || message);
    } catch (err) {
        console.error("Translated alert failed:", err);
        window.__nativeAlert(message); // Safe fallback
    }
}


export default function LanguageTranslator() {
    const [currentLanguage, setCurrentLanguage] = useState(() => {
        return localStorage.getItem("lang") || "en";
    });

    const availableLanguages = [
        { code: "en", label: "English" },
        { code: "es", label: "Español" },
        { code: "fr", label: "Français" }
    ];

    const originalTextMap = useRef(new WeakMap());
    const observerRef = useRef(null);

    useEffect(() => {
        // ✅ Store the real browser alert once
        if (!window.__nativeAlert) {
            window.__nativeAlert = window.alert;
        }

        // ✅ Override global alert
        window.alert = (msg) => {
            transAlert(msg);
        };

        return () => {
            // ✅ Restore if component ever unmounts
            if (window.__nativeAlert) {
                window.alert = window.__nativeAlert;
            }
        };
    }, []);


    // ✅ Persist language
    useEffect(() => {
        localStorage.setItem("lang", currentLanguage);
    }, [currentLanguage]);

    async function translateInputAttributes(lang) {
        const inputs = document.querySelectorAll("input[placeholder], textarea[placeholder]");

        const originals = [];
        inputs.forEach(input => {
            const original = input.getAttribute("placeholder");
            if (!originalTextMap.current.has(input)) {
                originalTextMap.current.set(input, { placeholder: original });
            }
            originals.push(original);
        });

        if (lang === "en") {
            inputs.forEach(input => {
                const saved = originalTextMap.current.get(input);
                if (saved?.placeholder) input.setAttribute("placeholder", saved.placeholder);
            });
            return;
        }

        try {
            const translated = await translateBatch(originals, lang);
            inputs.forEach((input, i) => {
                if (translated[i]) input.setAttribute("placeholder", translated[i]);
            });
        } catch (err) {
            console.error("Placeholder translation failed:", err);
        }
    }


    // ✅ Core DOM translation logic (reusable)
    async function internalTranslateAllVisibleText() {

        console.log("Translate");
        const walker = document.createTreeWalker(
            document.body,
            NodeFilter.SHOW_TEXT,
            {
                acceptNode: (node) => {
                    if (!node.nodeValue.trim()) return NodeFilter.FILTER_REJECT;

                    if (
                        node.parentElement.closest("[data-no-translate]") ||
                        node.parentElement.closest("script, style, textarea, input, select, option")
                    ) {
                        return NodeFilter.FILTER_REJECT;
                    }

                    return NodeFilter.FILTER_ACCEPT;
                }
            }
        );

        const textNodes = [];
        let node;

        while ((node = walker.nextNode())) {
            textNodes.push(node);
        }

        if (textNodes.length === 0) return;

        // ✅ Restore English
        if (currentLanguage === "en") {
            textNodes.forEach((node) => {
                const original = originalTextMap.current.get(node);
                if (original) node.nodeValue = original;
            });
            return;
        }

        // ✅ Cache original text
        const originals = textNodes.map((node) => {
            if (!originalTextMap.current.has(node)) {
                originalTextMap.current.set(node, node.nodeValue);
            }
            return node.nodeValue;
        });

        try {
            const translated = await translateBatch(
                originals.map((t) => t.trim()),
                currentLanguage
            );

            textNodes.forEach((node, i) => {
                if (translated[i]) node.nodeValue = translated[i];
            });
        } catch (err) {
            console.error("Batch DOM translation failed:", err);
        }

        await translateInputAttributes(currentLanguage);
    }

    async function translateAllVisibleText() {
        setTimeout(() => internalTranslateAllVisibleText(), 10);
    }
    __translateAllVisibleText = internalTranslateAllVisibleText;

    // ✅ Run when language changes
    useEffect(() => {
        translateAllVisibleText();
    }, [currentLanguage]);

    // ✅ Observe for dynamically added content (menu, modals, etc.)
    useEffect(() => {
        observerRef.current = new MutationObserver(() => {
            if (currentLanguage !== "en") {
                translateAllVisibleText();
            }
        });

        observerRef.current.observe(document.body, {
            childList: true,
            subtree: true
        });

        return () => observerRef.current?.disconnect();
    }, [currentLanguage]);

    return (
        <nav aria-label="Language selector">
        <div className="language-selector" data-no-translate>
            <select
                value={currentLanguage}
                onChange={(e) => setCurrentLanguage(e.target.value)}
                aria-label="Choose language"
            >
                {availableLanguages.map((lang) => (
                    <option key={lang.code} value={lang.code}>
                        {lang.label}
                    </option>
                ))}
            </select>
        </div>
        </nav>
    );
}
