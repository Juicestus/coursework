import Editor from "../manager-components/editor";
import { useEffect } from "react";

export default function MenuPage() {
  useEffect(() => {
    document.title = "Manager - Menu Editor Page";
  }, []);

  return (
    <main role="main" aria-labelledby="menu-page-title">
      {/* <h1 id="menu-page-title">Menu Editor Page</h1> */}
      <Editor
        title="Menu"
        basePath="menu"
        fields={["Drink", "Price", "Category", "Tea", "Milk", "Picture URL"]}
        requiredFields={[0,1,2,5]}
        numericFields={[1]}
        defaultValues={{5:"/images/placeholder.png"}}
        headers={[
          { display: "ID", key: "id" },
          { display: "Drink", key: "drink_name" },
          { display: "Price", key: "price" },
          { display: "Category", key: "category" },
          { display: "Tea", key: "tea_type" },
          { display: "Milk", key: "milk_type" },
          { display: "Image", key: "picture_url" }
        ]}
        extractValues={(item) => [
          item.drink_name,
          item.price,
          item.category,
          item.tea_type,
          item.milk_type,
          item.picture_url
        ]}
        buildPayload={(values, id) => {
          const pictureUrl = values[5] && values[5].trim() !== "" ? values[5] : "/images/placeholder.png";
          return {
            id,
            drink_name: values[0],
            price: parseFloat(values[1]),
            category: values[2],
            tea_type: values[3],
            milk_type: values[4],
            picture_url: pictureUrl
          };
        }}
      />
    </main>
  );
}