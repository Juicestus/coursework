module.exports = {
  async getWeather(lat, lon) {
    const url = `https://api.open-meteo.com/v1/forecast?latitude=${lat}&longitude=${lon}&current_weather=true&hourly=precipitation`;

    const response = await fetch(url);
    if (!response.ok) {
      throw new Error("Weather API request failed");
    }

    const data = await response.json();

    return {
      temperature: data.current_weather.temperature,
      precipitation: data.hourly.precipitation[0] || 0
    };
  }
};
