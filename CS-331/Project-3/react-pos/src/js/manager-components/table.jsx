import React from "react";

// Dynamically populates table with passed in headers and data
export default function Table({ headers, data, caption = "Data table" }) {
  return (
    <table className="menu">
      <caption className="sr-only">{caption}</caption>
      <thead>
        <tr>
          {headers.map((header, index) => (
            <th key={index} scope="col">
              {header.display}
            </th>
          ))}
        </tr>
      </thead>
      <tbody>
        {Array.isArray(data)
          ? data.map((row, rowIndex) => (
              <tr
                key={rowIndex}
                style={{
                  backgroundColor: rowIndex % 2 === 0 ? "#dfdfdf" : "#ffffff",
                }}
              >
                {headers.map((header, colIndex) => (
                  <td key={colIndex}>
                    {header.render ? header.render(row) : row[header.key]}
                  </td>
                ))}
              </tr>
            ))
          : null}
      </tbody>
    </table>
  );
}
