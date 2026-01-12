import React from "react";
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend } from "recharts";

export default function Graph({ xaxis, yaxis, data, xLabel = "X-Axis", yLabel = "Y-Axis", width = 600, height = 300, chartTitle = "Line chart" }) {
  const hasData = Array.isArray(data) && data.length > 0;

  return (
    <figure role="figure" aria-label={chartTitle}>
      <figcaption className="sr-only">{chartTitle}: showing {yLabel} by {xLabel}</figcaption>

      {hasData ? (
        <>
          <LineChart width={width} height={height} data={data} role="img" aria-hidden="true">
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis dataKey={xaxis} label={{ value: xLabel, position: "insideBottom", offset: -5 }} />
            <YAxis label={{ value: yLabel, angle: -90, position: "insideLeft" }} />
            <Tooltip />
            <Legend verticalAlign="bottom" align="center" wrapperStyle={{ paddingTop: 15 }} />
            <Line type="monotone" dataKey={yaxis} stroke="#000000ff" />
          </LineChart>

          <table className="sr-only">
            <caption>{chartTitle} data</caption>
            <thead>
              <tr>
                <th scope="col">{xLabel}</th>
                <th scope="col">{yLabel}</th>
              </tr>
            </thead>
            <tbody>
              {data.map((row, i) => (
                <tr key={i}>
                  <td>{row[xaxis]}</td>
                  <td>{row[yaxis]}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </>
      ) : (
        <p role="alert">No data available for this chart.</p>
      )}
    </figure>
  );
}