import Editor from "../manager-components/editor";
import { useEffect } from "react";

export default function EmployeePage() {
  useEffect(() => {
    document.title = "Manager - Employee Editor Page";
  }, []);

  return (
    <main role="main" aria-labelledby="employee-page-title">
      {/* <h1 id="employee-page-title">Employee Editor Page</h1> */}
      <Editor
        title="Employee"
        basePath="employee"
        fields={["Name", "Role"]}
        requiredFields={[0, 1]}
        numericFields={[1]}
        headers={[
          { display: "Employee ID", key: "id" },
          { display: "Name", key: "name" },
          { display: "Role", key: "role", render: (item) => (item.role == 0 ? "Customer" : "Manager")}
        ]}
        extractValues={(item) => [
          item.name,
          item.role,
          item.schedule
        ]}
        buildPayload={(values, id) => {
          let roleValue = values[1];
          if (typeof roleValue === "string") {
            const normalized = roleValue.trim().toLowerCase();
            if (normalized === "customer") roleValue = 0;
            else if (normalized === "manager") roleValue = 1;
          }
          return {
            id,
            name: values[0],
            role: values[1],
            schedule: 0
          };
        }}
      />
    </main>
  );
}
