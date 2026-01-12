import { useEffect, useState } from "react";
import Table from "./table";
import EditDialog from "./editDialog";
import { MANAGER_BASE_URL } from "../manager";

// Displays default manager page which contains a table and buttons to add or edit the table data
export default function Editor({
  title,
  fields,
  headers,
  basePath,
  extractValues,
  buildPayload,
  requiredFields = [],
  numericFields = [],
  defaultValues = {}
}) {
  const [items, setItems] = useState([]);
  const [showDialog, setShowDialog] = useState(false);
  const [dialogMode, setDialogMode] = useState("new");
  const [selectedItem, setSelectedItem] = useState(null);
  const [errorMessage, setErrorMessage] = useState("");

  const TABLE_HEADERS = [
    ...headers,
    {
      display: "Actions",
      key: "actions",
      render: (item) => (
        <div style={{ display: "flex", gap: "0.5rem" }}>
          <button
            onClick={() => openEditDialog(item)}
            aria-label={`Edit ${title} with ID ${item.id}`}
          >
            Edit
          </button>
          <button
            onClick={() => handleDelete(item.id)}
            aria-label={`Delete ${title} with ID ${item.id}`}
          >
            Del
          </button>
        </div>
      )
    }
  ];

  useEffect(() => {
    fetchItems();
  }, []);

  async function fetchItems() {
    try {
      const res = await fetch(`${MANAGER_BASE_URL}/${basePath}`, {
        credentials: "include"
      });
      const data = await res.json();
      setItems(Array.isArray(data) ? data : []);
    } catch (err) {
      console.error(`Error fetching ${basePath}:`, err);
    }
  }

  async function handleDelete(id) {
    try {
      await fetch(`${MANAGER_BASE_URL}/${basePath}/del`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        credentials: "include",
        body: JSON.stringify({ id })
      });
      setItems(items.filter((item) => item.id !== id));
    } catch (err) {
      console.error(`Error deleting ${basePath}:`, err);
    }
  }

  function openNewDialog() {
    setDialogMode("new");
    setErrorMessage("");

    const values = Array(fields.length).fill("");

    // Apply default values by index
    for (const [index, value] of Object.entries(defaultValues)) {
      values[parseInt(index)] = value;
    }
    setSelectedItem({ __prefill: true, values });
    setShowDialog(true);
  }

  function openEditDialog(item) {
    setDialogMode("edit");
    setSelectedItem(item);
    setErrorMessage("");
    setShowDialog(true);
  }

  async function handleDialogSubmit(values) {
    if (basePath === "menu") {
      values[5] = values[5]?.trim() ? values[5] : "/images/placeholder.png";
    }

    const missingFields = requiredFields.filter((i) => {
      const val = values[i];
      return (
        val === undefined ||
        val === null ||
        (typeof val === "string" && val.trim() === "")
      );
    });

    const invalidNumericFields = numericFields.filter((i) =>
      isNaN(parseFloat(values[i]))
    );

    if (missingFields.length > 0 || invalidNumericFields.length > 0) {
      const missingLabels = missingFields.map((i) => fields[i]);
      const invalidLabels = invalidNumericFields.map((i) => fields[i]);

      let message = "";

      if (missingLabels.length > 0) {
        message += `Please fill in the required fields: ${missingLabels.join(", ")}. `;
      } else if (invalidLabels.length > 0) {
        message += `Please enter valid numbers for: ${invalidLabels.join(", ")}.`;
      }

      setErrorMessage(message.trim());
      return;
    }

    const payload = buildPayload(
      values,
      dialogMode === "edit" ? selectedItem.id : null
    );

    const method = "POST";
    const endpoint = dialogMode === "new" ? "add" : "update";

    try {
      const res = await fetch(`${MANAGER_BASE_URL}/${basePath}/${endpoint}`, {
        method,
        headers: { "Content-Type": "application/json" },
        credentials: "include",
        body: JSON.stringify(payload)
      });

      if (!res.ok) {
        const errorText = await res.text();
        const parsed = JSON.parse(errorText);
        if (res.status === 400 && parsed?.error?.includes("required")) {
          setErrorMessage("Please fill in all required fields.");
        } else {
          setErrorMessage(`Server error: ${parsed?.error || "Unknown error"}`);
        }
        return;
      }

      const result = await res.json();
      if (dialogMode === "new") {
        setItems([...items, result]);
      } else {
        await fetchItems();
      }
      setShowDialog(false);
      setErrorMessage("");
    } catch (err) {
      console.error(`Error saving ${basePath}:`, err);
      setErrorMessage("Unexpected error occurred.");
    }
  }

  return (
    <section className="editor-container" style={{ marginLeft: "20px" }}>
      <h1 id={`${basePath}-editor-title`}>{title} Editor</h1>
      <button onClick={openNewDialog} aria-label={`Add new ${title}`}>
        + New {title}
        {title === "Employee" ? "" : " Item"}
      </button>

      {/* Accessible table */}
      <Table
        headers={TABLE_HEADERS}
        data={items}
        caption={`${title} records table`}
      />

      {/* Error messages */}
      {errorMessage && (
        <div role="alert" style={{ color: "red", marginTop: "1rem" }}>
          {errorMessage}
        </div>
      )}

      {showDialog && (
        <EditDialog
          title={dialogMode === "new" ? `New ${title}` : `Edit ${title}`}
          fields={fields}
          requiredFields={requiredFields}
          initialValues={
            dialogMode === "edit"
              ? extractValues(selectedItem)
              : selectedItem?.__prefill
              ? selectedItem.values
              : []
          }
          onSubmit={handleDialogSubmit}
          onClose={() => setShowDialog(false)}
          errorMessage={errorMessage}
        />
      )}
    </section>
  );
}