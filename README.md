# Library System: A Text-Based Catalog

## Introduction
This project entails the development of a rudimentary library management system utilizing C++. The system relies on file manipulation techniques for data storage and retrieval.

### Core Concepts Explored:
- Efficient manipulation of logical and physical files.
- Implementation of primary and secondary indexes for enhanced search functionality.
- Integration of multilevel indexes to optimize data retrieval.

## Functionality and Interface

### 1. Add New Author
Enables administrators to seamlessly integrate new author records into the system. It intelligently utilizes the AVAIL LIST to allocate available record slots while ensuring index consistency.

### 2. Add New Book
Facilitates the addition of new book records with ease. The system intelligently references the AVAIL LIST to allocate available slots for new entries and maintains index coherence.

### 3. Update Author Name by Author ID
Empowers administrators to modify non-key fields within existing author records. It imposes size constraints to ensure data integrity and synchronizes index updates accordingly.

### 4. Update Book Title by ISBN
Allows for the alteration of book titles based on their unique ISBN identifiers. It upholds data integrity by enforcing size limitations and ensures index congruity post-update.

### 5. Delete Book by ISBN
Employs a non-physical deletion approach by marking records with a distinctive (*) marker instead of outright removal. It adeptly manages the AVAIL LIST and indexes to reflect the changes.

### 6. Delete Author by Author ID
Offers a streamlined mechanism to remove authors from the system based on their unique identifier. It orchestrates the removal process meticulously, updating indexes and the AVAIL LIST accordingly.

### 7. Print Author Data by Author ID
Facilitates the retrieval and display of comprehensive author information based on their unique identifier. It ensures accurate data representation and retrieval.

### 8. Print Book Data by ISBN
Enables administrators to access and print detailed book information based on their unique ISBN identifiers. It ensures the accuracy and completeness of the retrieved data.

### 9. Write Query
Provides a versatile query interface enabling administrators to retrieve specific data subsets efficiently. Supported queries include:

- Retrieve all authors with a specific Author ID.
- Retrieve all books associated with a particular Author ID.
- Retrieve Author Names based on Author ID.

### 10. Exit

This option concludes the interaction with the library management system, allowing users to gracefully exit the application.

This revamped README aims to present the functionalities of the library management system in a fresh and engaging manner while retaining the essence of the original concepts.


## Contributers
- [Mohamed Ahmad Reyad ](https://github.com/reyad-7)
- [Ahmed shaban Youssef ](https://github.com/sh3boo)
- [Sara Adel](https://github.com/saraadel6)
- [Mai Mohamed](https://github.com/MaiMuhammad)




## Contact
If you have any questions, suggestions, or feedback, feel free to reach out to us
