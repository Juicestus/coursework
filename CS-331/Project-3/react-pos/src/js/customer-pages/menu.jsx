import { API_BASE } from '../apibase';

// Fetches menu data for kiosk interface and returns it
export async function fetchMenu() {
  try {
    const response = await fetch(API_BASE + "/customer/menu", {credentials: 'include'});
    const data = await response.json(); 
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
 *   menu_ids: number[],
 *   quantities: number[],
 *   totals: number[],
 *   card_number: string,
 *   card_expr_m: number,
 *   card_expr_y: number,
 *   card_holder: string
 */
export async function createOrder(orderData) {
  try {
    const response = await fetch(API_BASE + "/customer/order", {
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

export async function fetchCustomizations(menuItemID) {
  try {
    const response = await fetch(API_BASE + `/customer/customizations?menuItemID=${menuItemID}`);
    const data = response.json();
    return data;
  }
  catch (err) {
    console.error("Error fetching customizations:", err);
    return [];
  }
}

export async function getCouponCode(code) {
 try {
    const response = await fetch(API_BASE + "/customer/coupon?code=" + code, {credentials: 'include'});
    const data = await response.json(); 
    if (data.length > 0)
      return data[0]['pct_off'];
    else return 0;
  } catch (err) {
    console.error("Error fetching menu:", err);
    return [];
  }



}

export async function getWeather(latitude, longitude) {
  try {
    const response = await fetch(
      `${API_BASE}/customer/weather?latitude=${latitude}&longitude=${longitude}`,
      { credentials: "include" }
    );

    const data = await response.json();
    return data;
  } catch (err) {
    console.error("Error fetching weather:", err);
    return { error: "Network error" };
  }
}
export async function translateOne(text, target) {
  try {
    const response = await fetch(
      `${API_BASE}/customer/translate?text=${encodeURIComponent(text)}&target=${encodeURIComponent(target)}`,
      {
        credentials: "include"
      }
    );

    if (!response.ok) {
      throw new Error(`Translation API failed with status: ${response.status}`);
    }

    const data = await response.json();
    return data.translated;
  } catch (err) {
    console.error("Error translating text:", err);
    return null;
  }
}

export async function translateBatch(textArray, target) {
  try {
    const textStr = textArray.join("|||");

    const response = await fetch(
      `${API_BASE}/customer/translate?text=${encodeURIComponent(textStr)}&target=${encodeURIComponent(target)}`,
      {
        credentials: "include"
      }
    );

    if (!response.ok) {
      throw new Error(`Translation API failed with status: ${response.status}`);
    }

    const data = await response.json();

    // Split translated results back into array
    return data.translated.split("|||");
  } catch (err) {
    console.error("Error translating batch:", err);
    return [];
  }
}

