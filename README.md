# 🚆 Indian Railway Reservation System (C++ Console Project)

A **menu-driven, file-based Railway Reservation System** developed in **C++**, inspired by real-world **IRCTC workflows**.  
This project supports **Admin & User roles**, secure validations, route-based fare calculation, and complete train management.

---

## 📌 Project Overview

This project is a **console-based Railway Reservation System** inspired by real-world IRCTC workflows.

The system is designed with **role-based access control** for **Users** and **Administrators**, ensuring secure operations, data consistency, and realistic reservation behavior.

It simulates core railway reservation functionalities including:

- Train search with exact & partial route matching
- Dynamic class-wise fare calculation
- Seat availability tracking
- Ticket booking, printing & cancellation
- Admin-controlled train lifecycle management
- Revenue monitoring and reporting
- File-based persistent storage
- Robust validation, confirmations & error handling


---

## 🛠️ Technologies Used

- **Language:** C++
- **Concepts:** OOPs, STL, File Handling
- **Compiler:** g++
- **Platform:** Windows (Console Application)

---

### 👤 User Functionalities

The User module allows passengers to interact with the reservation system using validated and guided workflows.

Users can perform the following operations:

---

#### 🎟️ Book Ticket
- Book tickets with:
  - Valid Train Number
  - Source & Destination
  - Date of Journey (DOJ)
  - Coach Class
- Generates a **unique 10-digit PNR**
- Performs strict validations:
  - Route validity
  - Running day verification
  - Seat availability check
- Updates seat count immediately after booking

---

#### ❌ Cancel Ticket
- Cancel a booked ticket using valid PNR
- Restores seat availability upon cancellation
- Prevents duplicate or invalid cancellation attempts
- Displays confirmation before final cancellation

---

#### 🖨️ Print Ticket
- Retrieve and display ticket details using PNR
- Shows:
  - Passenger details
  - Train information
  - Journey route
  - Fare breakdown
- Printed in **IRCTC-inspired ticket format**

---

#### 🚆 View Train Information
- View detailed train details including:
  - Train Number & Name
  - Source, Destination & Intermediate Stations
  - Running Days
  - Available Coach Classes
- Displays information in an **IRCTC-style structured format**

---

#### 💺 Check Seat Availability
- View class-wise seat availability for a selected train
- Displays:
  - Available seats
  - Total seats per class
- Prevents invalid class selection
- Ensures real-time consistency with booked tickets

---

#### 🔍 Find Train
- Search trains by:
  - Source & Destination (Exact & Partial Route Match)
  - Train Number
- Displays matching trains in categorized format
- Shows indicative class-wise fare for available routes

---

#### ✔ User-Level Validations
- Input validation for Train Number, DOJ, Class
- Past date & invalid journey prevention
- Route and class consistency checks
- Clear error, warning & info messages at each step

---

### 🛠️ Admin Functionalities

Administrators are provided with full system control, with **strict validations and safeguards** to maintain data integrity and operational correctness.

The Admin module supports the following operations:

---

#### ➕ Add New Train
- Create a new train service with:
  - Train Number & Train Name
  - Source, Destination & Intermediate Stations
  - Running Days
  - Coach Classes with Seat Allocation
- Prevents duplicate Train Numbers
- Validates station names, routes, and seat configuration before saving

---

#### ✏️ Update Train Details
- Modify existing train information including:
  - Train Name
  - Route (Source, Destination & Stoppages)
  - Running Days
  - Coach Classes & Seat Configuration
- Displays **explicit warnings** before resetting existing data
- Requires **final confirmation** before applying updates
- **Restricted if tickets are already booked** to avoid data inconsistency

---

#### 🗑️ Delete Train
- Remove a train service from the system
- Prevents deletion if tickets exist for the train
- Requires confirmation before permanent removal

---

#### 📄 View All Trains
- Displays a complete list of all registered trains
- Includes:
  - Train Number
  - Train Name
  - Source & Destination
  - Available Classes
  - Running Days

---

#### 🔍 View Train Details
- View detailed information of a specific train:
  - Full route with stoppages
  - Distance and pricing reference
  - Coach-wise seat availability
  - Running days
- Handles invalid train numbers gracefully

---

#### 💰 Earnings & Revenue Report
- View total system earnings
- View train-wise revenue details
- Displays structured earning reports in **IRCTC-style format**
- Intended for internal administrative analysis

---

#### ✔ Admin-Level Validations & Controls
- Input format validation (Train Number, Stations, Seats)
- Duplicate prevention mechanisms
- Safe file handling and atomic updates
- Restriction checks based on booking status
- Clear error, warning, and info messages for every action


> ⚠️ All administrative operations are protected by multi-level validations and confirmation prompts to prevent accidental or unauthorized data modification.
