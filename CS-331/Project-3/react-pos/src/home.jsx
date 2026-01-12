import { useState, useEffect } from "react";
import "./styles.css";
import Login from "./js/login.jsx";
import Customer from "./js/customer.jsx"
import Employee from "./js/employee.jsx";
import Manager from "./js/manager.jsx";
import { API_BASE } from "./js/apibase.js";
import Menu from "./js/menu.jsx";
import LanguageSelectorDropdown from "./js/customer-components/languageSelector.jsx";

export default function Home() {

    
    const [ currentScreen, setScreen ] = useState();
    const [ currentUser, setCurrentUser ] = useState(null);
    const [ validatingUser, setValidatingUser ] = useState(true);

    const [holidayMode, setHolidayMode] = useState(false);

    useEffect(() => {
        const saved = window.localStorage.getItem("holiday-mode");
        if (saved === "on") {
            setHolidayMode(true);
        }
    }, []);

    useEffect(() => {
        const root = document.documentElement; // <html>
        const body = document.body;

        if (holidayMode) {
            root.classList.add("holiday");
            body.classList.add("holiday-bg");
            window.localStorage.setItem("holiday-mode", "on");
        } else {
            root.classList.remove("holiday");
            body.classList.remove("holiday-bg");
            window.localStorage.setItem("holiday-mode", "off");
        }
    }, [holidayMode]);

    useEffect(() => {
        async function checkAuth() {
            try {
                const response = await fetch(`${API_BASE}/auth/me`, {credentials: "include"});
                const data = await response.json();
                setCurrentUser(data);
            }
            catch (err) {
                console.error("Error validating authentication", err);
            }
            finally {
                setValidatingUser(false);
            }
        }
        checkAuth();
    }, []);

    if (!currentUser || currentUser.authenticated !== true) return <Login validatingUser={validatingUser} setCurrentUser={setCurrentUser}/>
    if (currentScreen === "Customer" || currentUser.user.display_name === "Guest") return <Customer />;
    if (currentScreen === "Employee" && (currentUser.user.role === "cashier" || currentUser.user.role === "manager")) return <Employee />;
    if (currentScreen === "Manager" && currentUser.user.role === "manager") return <Manager />;
    if (currentScreen === "Menu" && currentUser.user.role === "manager") return <Menu />;

    return (
        <div>
                        <LanguageSelectorDropdown />
            <main className="home-wrap">
                <h1>Welcome {' ' + currentUser.user.display_name}</h1>
                <nav className="nav">
                    {/* If customer: only display "Place Order", otherwise use "Customer Kiosk and Cashier POS wording" */}
                    {(currentUser.user.role !== "cashier" && currentUser.user.role !== "manager") && (
                        <button className="nav-btn" onClick={() => setScreen("Customer")}>
                            Place Order
                        </button>
                    )}

                    {(currentUser.user.role === "cashier" || currentUser.user.role === "manager") && (
                        <button className="nav-btn" onClick={() => setScreen("Customer")}>
                            Customer Kiosk
                        </button>
                    )}

                    {(currentUser.user.role === "cashier" || currentUser.user.role === "manager") && (
                        <button className="nav-btn" onClick={() => setScreen("Employee")}>
                            Cashier POS
                        </button>
                    )}

                    {currentUser.user.role === "manager" && (
                        <button className="nav-btn" onClick={() => setScreen("Manager")}>
                            Manager Dashboard
                        </button>
                    )}

                    {currentUser.user.role === "manager" && (
                        <button className="nav-btn" onClick={() => setScreen("Menu")}>
                            Non-Interactive Menu
                        </button>
                    )}
                </nav>
            </main>

            {/* Footer area with logout + holiday toggle stacked on the right */}
            <div className="home-footer">
                <button
                    className="logout-btn"
                    onClick={() => (
                        setCurrentUser(null),
                            fetch(`${API_BASE}/auth/logout`, {
                                credentials: "include",
                                method: "POST"
                            })
                    )}
                >
                    Log Out
                </button>

                <div className="holiday-toggle">
                    <span>{holidayMode ? "Holiday Mode" : "Normal Mode"}</span>
                    <button
                        type="button"
                        className={`holiday-toggle-button ${holidayMode ? "on" : ""}`}
                        onClick={() => setHolidayMode(m => !m)}
                    >
                        <span className="holiday-toggle-button-knob" />
                    </button>
                </div>
            </div>
        </div>
    );


}