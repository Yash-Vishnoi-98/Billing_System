# ☕ Yash Cafe Billing System

A **C-based billing application** for managing customer orders, generating invoices, and tracking sales at a cafe. This project includes features like password protection, formatted bill export, invoice lookup, and sales analytics

---

## 📦 Features

- 🔐 **Admin Authentication** with password protection
- 🧾 **Invoice Generation** with discount and GST
- 📁 **Binary & Text Bill Storage** (`YashCafe.txt` + exported `.txt` in `bills/`)
- 🔍 **Search Customer Invoices**
- 📊 **Sales Reports** (revenue, most sold item, etc.)

---

## 🗂️ Directory Structure

```
YashCafe/
├── yash_cafe.c          # Main source file
├── YashCafe.txt         # Binary storage of all bills
├── bills/               # Exported readable invoice text files
└── README.md            # This file
```

---

## 🧰 Requirements

- C Compiler (e.g., gcc)
- `conio.h` (for getch, available on Turbo C++ or Windows)
- `time.h` for date and time handling
- Works on: **Windows**, or use platform-specific adjustments for Unix

---

## ⚙️ Compile & Run

```bash
gcc yash_cafe.c -o yash_cafe
./yash_cafe
```

> Ensure the `bills/` folder exists in the same directory to store invoice files.

---

## 🔐 Admin Login

- Default Password: `YashVishnoi123`
- Maximum 3 login attempts

---

## 📄 Exported Bill Example

```
==================================YASH CAFE===========================
---------------------------------------------------------------------------

 Date: Jul  1 2025
 Invoice to Yash Vishnoi
------------------------------------------------------------------------------
Items           Quantity                Total
----------------------------------------------------------------------------------

Chole            1                      50.00

----------------------------------------------------------------------------------

 Subtotal                       50.00
 Discount (10%)                 5.00
---------------------------------------------------------------------------
 Net Total                      45.00
 GST (18%)                      8.10
---------------------------------------------------------------------------

 Grand Total                    53.10


```

---

## 📈 Sample Sales Report

```
===================== SALES REPORT =====================
Total Customers Served: 3
Total Revenue: Rs.410.00
Average Bill Amount: Rs.136.67
Most Sold Item: Chai (3 units)
========================================================
```

---

## About

Developed by: **Yash Vishnoi**  
Language: **C**  
Use case:

- Store bills securely.
- Export and archive for bookkeeping or tax purposes.
- View total revenue and average billing.
- Identify most frequently ordered item.
- Access restricted to authorized users via password.
- Blocks after 3 incorrect login attempts.

---
