import React from "react";
import { TableVirtuoso } from "react-virtuoso";

export default function VirtuosoTable({ headers, data, height = 400, onRowDoubleClick, caption = "Data table" }) {
  return (
    <div style={{ padding: "1rem" }}>
      <TableVirtuoso
        data={data}
        style={{ height, width: "100%" }}
        components={{
          Table: (props) => (
            <table
              {...props}
              style={{ width: "100%", borderCollapse: "collapse" }}
            >
              {/* Accessible caption, visually hidden */}
              <caption className="sr-only">{caption}</caption>
              {props.children}
            </table>
          ),
          TableBody: React.forwardRef((props, ref) => <tbody {...props} ref={ref} />),
          TableRow: (props) => (
            <tr
              {...props}
              tabIndex={0} // make row focusable
              onKeyDown={(e) => {
                if (e.key === "Enter" && onRowDoubleClick) {
                  onRowDoubleClick(props.item);
                }
              }}
              onDoubleClick={() => onRowDoubleClick && onRowDoubleClick(props.item)}
              style={{
                cursor: "pointer",
                backgroundColor: props["data-index"] % 2 === 0 ? "#dfdfdf" : "#ffffff",
              }}
            >
              {props.children}
            </tr>
          ),
          TableCell: (props) => (
            <td
              {...props}
              style={{
                padding: "0.5rem",
                borderBottom: "1px solid #eee",
              }}
            >
              {props.children}
            </td>
          ),
          TableHead: (props) => <thead {...props} />,
          TableFoot: (props) => <tfoot {...props} />,
        }}
        fixedHeaderContent={() => (
          <tr>
            {headers.map((header) => (
              <th
                key={header.key}
                scope="col"
                style={{
                  textAlign: "left",
                  padding: "0.5rem",
                  borderBottom: "2px solid #ccc",
                  backgroundColor: "#f5f5f5",
                }}
              >
                {header.display}
              </th>
            ))}
          </tr>
        )}
        itemContent={(index, item) =>
          headers.map((header) => {
            let value = item[header.key];
            if (header.key === "order_time" && value) {
              value = new Date(value).toLocaleString();
            }
            return <td key={header.key}>{value}</td>;
          })
        }
      />
    </div>
  );
}