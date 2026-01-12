import { API_BASE } from '../apibase';

// Fetches menu data for cashier interface and returns it
export async function fetchMenu() {
  try {
    const response = await fetch(API_BASE + "/cashier/menu", {credentials: 'include'});
    const data = await response.json(); 
    console.log(data);
    return data;                           
  } catch (err) {
    console.error("Error fetching menu:", err);
    return [];
  }
}

/*
 * param orderData must include:
 *
 *   order_time: string,
 *   employee_id: number,
 *   menu_ids: number[],
 *   quantities: number[],
 *   totals: number[],
 *   card_number: string,
 *   card_expr_m: number,
 *   card_expr_y: number,
 *   card_holder: string
 * 
 */
export async function createOrder(orderData) {
  try {
    const response = await fetch(API_BASE + "/cashier/order", {
      method: "POST",
      credentials: "include",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify(orderData)
    });

    const data = await response.json();
    return data;

  } catch (err) {
    console.error("Error creating order:", err);
    return { error: "Network error" };
  }
}
