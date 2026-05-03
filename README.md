# 📚 Library Management System using Hash Table 

## 📌 Overview
This project is a **Library Management System implemented in C** using a **hash table with chaining**. It allows efficient storage and retrieval of books and supports operations like adding, updating, deleting, searching, issuing, returning books, and checking overdue fines.

This is a **console-based application** designed to demonstrate core **data structures and algorithms concepts**.

---

## 🚀 Features

- Add new books  
- Update book details  
- Delete books  
- Display all books  
- Search books by:
  - ISBN
  - Title
  - Author  
- Issue books to students  
- Return books  
- Check overdue books and calculate fines  

---

## 🧠 Data Structures Used

### Hash Table
- Used for fast access to books  
- Index calculated using ISBN  
- Table size: 100  

### Linked List (Chaining)
- Handles collisions in hash table  
- Each bucket contains a linked list of books  

---

## ⚙️ How It Works

### 🔑 Hash Function

```
index = sum_of_ascii_values % TABLE_SIZE
```

### 🔎 Search Operation

- Finds correct bucket using hash function
- Traverses linked list in that bucket

### 📋 Menu Options

```
1. Add Book
2. Update Book
3. Delete Book
4. Display Books
5. Search Book
6. Issue Book
7. Return Book
8. Check Overdue
0. Exit
```

## 📌 Functional Details

### ✅ Add Book
- Ensures unique ISBN  
- Validates author name (only alphabets allowed)  

### 🔄 Update Book
- Updates title and author using ISBN  

### ❌ Delete Book
- Removes book from the system  

### 🔍 Search Book
- ISBN → Fast search using hashing  
- Title → Linear search  
- Author → Linear search  

### 📦 Issue Book
- Assigns student ID and due date  
- Marks book as issued  

### 🔄 Return Book
- Marks book as available  
- Clears student details  

### ⏰ Overdue Calculation
- Converts dates into days  
- Calculates fine:

```
fine = days_late * base_fee;
```
