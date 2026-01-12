import { useEffect, useState } from "react";
import { getWeather } from "../customer-pages/menu"; // ✅ adjust path if needed

export default function Weather() {
  const [weather, setWeather] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    function success(position) {
      const lat = position.coords.latitude;
      const lon = position.coords.longitude;
      fetchWeather(lat, lon);
    }

    function fail() {
      setError("Location access denied");
      setLoading(false);
    }

    if (!navigator.geolocation) {
      setError("Geolocation not supported");
      setLoading(false);
    } else {
      navigator.geolocation.getCurrentPosition(success, fail);
    }
  }, []);

  async function fetchWeather(lat, lon) {
    try {
      const data = await getWeather(lat, lon);
      setWeather(data);
    } catch (err) {
      setError("Failed to load weather");
    } finally {
      setLoading(false);
    }
  }

  return (
<div className="weather-box">
      <p id="weatherHeading">Local Weather</p>

      {loading && <p>Loading weather...</p>}

      {error && <p style={{ color: "black" }}>{error}</p>}

      {weather && (
        <div>

          <p>🌡 Temperature: <strong>{Math.round(weather.temperature * (9/5) + 32)}°F</strong></p>
          <p>🌧 Precipitation: <strong>{weather.precipitation} mm</strong></p>
          </div>
      )}
        </div>
  );
}
