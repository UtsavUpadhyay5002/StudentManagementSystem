# 🎓 Student Grade Management System

A terminal-based C application to manage student records and grade data, developed as a final project for CS2263 - System Software Development at the University of New Brunswick.

## 📌 Project Overview

This menu-driven system allows users (e.g., instructors, TAs) to:
- Add and manage student records
- Enter and update grades
- View performance bar charts
- Calculate GPA and assign letter grades
- Save/load data persistently via CSV files

Built entirely in C, this project showcases practical use of **linked lists**, **dynamic memory**, **file I/O**, and **recursion**, with robust validation and memory safety.

## 🚀 Features

- ✅ Add, delete, and display student profiles  
- 🔍 Partial name search and ID-based lookup  
- 🧮 GPA calculation and letter grade assignment  
- 📊 Bar chart visualization (colored using ANSI codes)  
- 🗂 Persistent data storage using `.csv` files  
- 🔁 Recursively free memory to avoid leaks  
- 🔐 Validation for input format, ranges, and duplicates  
- 🧪 Test suite (`test.c`) for key operations and edge cases

## 🛠 Technologies & Concepts

- **Programming Language:** C
- **Data Structures:** Linked Lists (`struct` based)
- **Memory Management:** `malloc`, `free`, recursion
- **File Handling:** CSV File I/O using `fopen`, `fprintf`, etc.
- **Testing:** Manual test cases and Valgrind memory check

## 📎 Resources

- 📘 [User Guide](https://github.com/UtsavUpadhyay5002/StudentManagementSystem/blob/main/Student%20Grade%20Management%20System%20-%20User%20Guide.pdf)  
- 📊 [Final Presentation Slides](./Student_Grade_Management_System_Presentation.pdf)  
- 📝 [Final Project Report](https://github.com/UtsavUpadhyay5002/StudentManagementSystem/blob/main/STUDENT%20GRADE%20MANAGEMENT%20SYSTEM%20-%20Final%20Report.pdf)  

## 📌 Known Limitations

- No GUI — text-only terminal interface
- Works only in terminal/command-line environments
- Uses plain text CSVs instead of binary for storage

## 🌱 Future Improvements

- Role-based login (Admin vs Student)
- Weighted GPA with credit hours
- GUI with graphics support (e.g., GTK)
- Binary file I/O for performance and security

