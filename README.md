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
- Performs strict validations:
  - Route validity
  - Running day verification
  - Seat availability check
- Updates seat count immediately after booking
- Generates a **unique 10-digit PNR**

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

---

## 📸 Application Screenshots (Execution Flow)

## Main Page

![Main Page](MainPage.png)



## 👨‍💼 Admin Module

### 🔐 Admin Login & Dashboard

![Admin Login & Dashboard](AdminLogin&Dashboard.png)



### ➕ Add Train

![Add Train Image 1](AddTrain1.png)

![Add Train Image 2](AddTrain2.png)



### 🔄 Update Train

![Update Train Image 1](UpdateTrain1.png)

![Update Train Image 2](UpdateTrain2.png)



### ❌ Delete Train

![Delete Train](DeleteTrain.png)



### 📄 View All Trains

![View All Trains](ViewAllTrain.png)



### 🔍 View Train Details

![View Train Details Image 1](AdminTrainDetails1.png)

![View Train Details Image 2](AdminTrainDetails2.png)



### 📊 Total Earnings

![Total Earnings Image 1](TotalEarnings1.png)

![Total Earnings Image 2](TotalEarnings2.png)



---

## 👤 User Module

### 🔐 User Login & Dashboard

![User Login & Dashboard](UserLogin&Dashboard.png)



### 🎫 Book Ticket

![Book Ticket Image 1](BookTicket1.png)

![Book Ticket Image 2](BookTicket2.png)

![Book Ticket Image 3](BookTicket3.png)



### ❌ Cancel Ticket

![Cancel Ticket](TicketCancel.png)



### 🖨️ Print Ticket

![Print Ticket](PrintTicket.png)



### 🚆 View Train Information

![View Train Information](UserTrainInfo.png)



### 💺 Check Seat Availability

![Check Seat Availability](CheckSeatAvailability.png)



### 🔎 Find Train

![Find Train Image 1](FindTrain1.png)

![Find Train Image 2](FindTrain2.png)



---

## ✨ Key Features

- ✔️ Exact & Partial Route Matching
- ✔️ Class-wise Fare Calculation
- ✔️ Seat Reset Warnings (IRCTC-style)
- ✔️ Input Validation (Date, Station, Train No)
- ✔️ Data Integrity Protection
- ✔️ Modular Code Architecture

---

## 📂 File-Based Storage

All data is stored persistently using text files:

- `trains.txt` - Train details
- `UsersCredentials.txt` - User accounts
- `BookedTickets.txt` - Ticket records
- `CancelledTickets.txt` - Cancelled Ticket records

---

## 🔑 Sample Login Credentials

### Admin
- Username: `admin`
- Password: `admin123`

### User
- Username: `user1`
- Password: `user123`

---

## ⚠️ Edge Cases & Validations Handled

- Booking on non-running days
- Invalid source–destination routes
- Past date journey prevention
- Seat exhaustion handling
- Duplicate PNR prevention
- Cancellation of already cancelled tickets
- Train update restriction when bookings exist
- Safe deletion checks for trains

---

## 🚧 Current Limitations

- Console-based UI (no GUI)
- Single-user access (no concurrency)
- File-based storage instead of database
- No real-time payment integration

---

## 🎯 Learning Outcomes

- Applied real-world IRCTC workflows in C++
- Strong understanding of OOP & STL
- File-based data persistence & consistency
- Validation-driven system design
- Modular & scalable architecture thinking
