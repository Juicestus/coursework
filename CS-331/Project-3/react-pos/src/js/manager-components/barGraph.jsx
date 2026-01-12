import React from "react";
import { BarChart, Bar, XAxis, YAxis, CartesianGrid, Tooltip, Legend } from "recharts";

export default function BarGraph({ xaxis, yaxis, data, xLabel = "X-Axis", yLabel = "Y-Axis", width = 600, height = 300, barColor = "#8884d8", chartTitle = "Bar chart" }) {
  const hasData = Array.isArray(data) && data.length > 0;

  return (
    <figure role="figure" aria-label={chartTitle}>
      <figcaption className="sr-only">{chartTitle}: showing {yLabel} by {xLabel}</figcaption>

      {hasData ? (
        <>
          <BarChart
            width={width}
            height={height}
            data={data}
            margin={{ top: 20, right: 30, left: 60, bottom: 100 }}
            role="img"
            aria-hidden="true"
          >
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis
              dataKey={xaxis}
              label={{ value: xLabel, position: "insideBottom", offset: -85, style: { fontSize: 14 } }}
              interval={0}
              angle={-45}
              textAnchor="end"
              height={100}
            />
            <YAxis label={{ value: yLabel, angle: -90, position: "insideLeft", offset: -20, dy: 50 }} />
            <Tooltip />
            <Legend verticalAlign="top" align="center" wrapperStyle={{ marginTop: -10 }} />
            <Bar dataKey={yaxis} fill={barColor} />
          </BarChart>

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