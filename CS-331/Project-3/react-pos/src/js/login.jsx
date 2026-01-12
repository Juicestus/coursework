import { useEffect } from "react";
import "../styles.css";
import { API_BASE } from "./apibase";
import LanguageSelectorDropdown from "./customer-components/languageSelector.jsx";

export default function Login({ validatingUser, setCurrentUser }) {

    const GUEST_CREDENTIALS = { 
        authenticated: true, 
        user: { id: 999, email: '', role: 'customer', display_name: 'Guest' }
    };

    // Get query parameters safely
    const params = new URLSearchParams(window.location.search);
    const isGuestMode = params.get("page") === "guest";

    // Auto-login as guest AFTER validation
    useEffect(() => {
        if (!validatingUser && isGuestMode) {
            setCurrentUser(GUEST_CREDENTIALS);
        }
    }, [validatingUser, isGuestMode]);

    if (validatingUser) {
        return (
            <div className="page-container-alt">
                <img src="/images/loading.gif" alt="Loading" />
            </div>
        );
    }

    return (
        <div>
            {!isGuestMode && (
                <div>
                    <LanguageSelectorDropdown />

                    <main className="home-wrap">
                        <h1>Log In?</h1>
                        <nav className="nav">
                            <button 
                                className="nav-btn" 
                                onClick={() => window.location.href = `${API_BASE}/auth/google`}
                            >
                                With Google
                            </button>

                            <button 
                                className="nav-btn"
                                onClick={() => setCurrentUser(GUEST_CREDENTIALS)}
                            >
                                Continue as Guest
                            </button>
                        </nav>
                    </main>
                </div>
            )}
        </div>
    );
}
