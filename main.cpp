#include <bits/stdc++.h>
using namespace std;

// Global variables to store the number of records and headers
int book_no = 0;
int author_no = 0;
char author_Name[50], author_id[13], authorCursor[5], author_Address[50], authorSiz[5];
char bookTitle[50], Author_ID[50], bookCursor[5], ISBN[30], bookSiz[5];
int header = -1, authorHeader = -1;

multimap<string, string> invertedListAuthor;
multimap<string, string> invertedListBook;

// Structures to define the record formats
struct Author
{
    char author_id[13]; // primary Key
    char author_Name[50];
    char author_Address[50];
    int authorSiz;
};
struct Book
{
    char ISBN[30]; // primary Key
    char bookTitle[50];
    char Author_ID[50]; // secondary Key
    int bookSiz;
};

// Structures to define primary indices

struct Author_PriIndex
{
    char ID[13], offset[10];
} Author_in[200], Author_temp;

struct bookPriIndex
{
    char id[30], ind[10];
} in[200], temp;

// Structures to define secondary indices
struct bookLinkedList
{
    char ind[50], bookID[30],next[30];
} bookLinkedList[200],bookLinkedList_temp;


struct book_SecIndex
{
    char authorId[50], ind[30];
} book_SIn[200], B_Stemp;


struct authorSecIndex
{
    char name[50], id[30];
} SIn[100], stemp;

void readHeader()
{
    fstream HFile;
    HFile.open("header.txt", ios::in);
    HFile >> header;
    HFile.close();
}

void writeHeader(int header)
{
    fstream HFile;
    HFile.open("header.txt", ios::out);
    HFile << header;
    HFile.close();
}

void readAuthorHeader()
{
    fstream HFile;
    HFile.open("Authorheader.txt", ios::in);
    HFile >> authorHeader;
    HFile.close();
}
void writeAuthorHeader(int header)
{
    fstream HFile;
    HFile.open("Authorheader.txt", ios::out);
    HFile << header;
    HFile.close();
}

// Functions to read and write the number of records

void Author_readRecNo()
{
    fstream nFile;
    nFile.open("Author_no.txt", ios::in);
    nFile >> author_no;
    nFile.close();
}
void Author_writeRecNo()
{
    fstream nFile;
    nFile.open("Author_no.txt", ios::out);
    nFile << author_no;
    nFile.close();
}

void readRecNo()
{
    fstream nFile;
    nFile.open("book_no.txt", ios::in);
    nFile >> book_no;
    nFile.close();
}

void writeRecNo()
{
    fstream nFile;
    nFile.open("book_no.txt", ios::out);
    nFile << book_no;
    nFile.close();
}

// Function to create primary index from data file

void createAuthorPriIndex()
{
    // Initialize a variable to keep track of the current offset in the data file
    int current = 0;
    fstream file;
    file.open("Author_data.txt", ios::in);

    // Iterate through each author record
    for (int i = 0; i < author_no; i++)
    {
        file.getline(authorSiz, 5, '|');
        file.getline(author_Name, 50, '|');
        file.getline(author_id, 13, '|');
        file.getline(author_Address, 50, '|');

        // Convert current to string
        // and store in authorCursor
        itoa(current, authorCursor, 10);

        // Store author ID and offset in Author_in(Primary index) array
        strcpy_s(Author_in[i].ID, author_id);
        strcpy_s(Author_in[i].offset, authorCursor);

        // Update the current offset for the next record
        current += atoi(authorSiz);
    }
    // Close the file
    file.close();
}

void createBookPriIndex()
{
    // Initialize a variable to keep track of the current offset in the data file
    int current = 0;
    fstream file1;
    file1.open("book_data.txt", ios::in);

    // Iterate through each author record
    for (int i = 0; i < book_no; i++)
    {
        file1.getline(bookSiz, 5, '|');
        file1.getline(ISBN, 30, '|');
        file1.getline(bookTitle, 50, '|');
        file1.getline(Author_ID, 50, '\n');

        // Convert current to string and
        // store in bookCursor
        itoa(current, bookCursor, 10);

        // Store author ID and offset in in(primary index ) array
        strcpy_s(in[i].id, ISBN);
        strcpy_s(in[i].ind, bookCursor);

        // Update current for the next record
        current += atoi(bookSiz);
    }

    // Close the file
    file1.close();
}

void readAuthorPriIndex()
{
    Author_readRecNo();
    fstream f;
    f.open("authorPrimary_index.txt", ios::in);
    for (int i = 0; i < author_no; i++)
    {
        f.getline(Author_in[i].ID, 13, '|');
        f.getline(Author_in[i].offset, 10, '\n');
    }
}

void readBookPriIndex()
{
    readRecNo();
    fstream ff;
    ff.open("bookPrimary_index.txt", ios::in);
    for (int i = 0; i < book_no; i++)
    {
        ff.getline(in[i].id, 30, '|');
        ff.getline(in[i].ind, 10, '\n');
    }
    ff.close();
}

// Function to write the primary index of authors to file
void writeAuthorPriIndex()
{
    Author_readRecNo(); // Read the number of authors
    fstream file;
    file.open("authorPrimary_index.txt", ios::out);

    // Iterate through each entry in the primary index
    for (int i = 0; i < author_no; i++)
    {
        file << Author_in[i].ID << "|" << Author_in[i].offset << "\n";
    }

    // Close the file
    file.close();
}

// Function to write the primary index of books to file
void writeBookPriIndex()
{
    readRecNo(); // Read the number of books
    fstream file2;
    file2.open("bookPrimary_index.txt", ios::out);

    // Iterate through each entry in the primary index
    for (int i = 0; i < book_no; i++)
    {
        file2 << in[i].id << "|" << in[i].ind << "\n";
    }
    // Close the file
    file2.close();
}

void sortAuthorPriIndex()
{

    for (int i = 0; i < author_no - 1; i++)
    {
        for (int j = 0; j < author_no - i - 1; j++)
        {
            if (strcmp(Author_in[j].ID, Author_in[j + 1].ID) > 0) // I want to sort them in an ascending way
            {                                                     // if (next id < current id) -> swap
                Author_temp = Author_in[j];
                Author_in[j] = Author_in[j + 1];
                Author_in[j + 1] = Author_temp;
            }
        }
    }
}

void sortBookPriIndex()
{
    for (int i = 0; i < book_no - 1; i++)
    {
        for (int j = 0; j < book_no - i - 1; j++)
        {
            if (strcmp(in[j].id, in[j + 1].id) > 0) // I want to sort them in an ascending way
            {                                       // if (next id < current id) -> swap
                temp = in[j];
                in[j] = in[j + 1];
                in[j + 1] = temp;
            }
        }
    }
}
void createAuthorSec(Author A)
{
    fstream secAuthor;
    secAuthor.open("author_Secondary.txt", ios::out);

    fstream linkedList;
    linkedList.open("linkedListAuthor.txt", ios::out);

    invertedListAuthor.insert({A.author_Name, A.author_id});

    for (int i = 0; i < invertedListAuthor.size(); i++)
    {

        const auto &pair1 = *next(invertedListAuthor.begin(), i);
        const auto &pair2 = *next(invertedListAuthor.begin(), i - 1);
        const auto &pair3 = *next(invertedListAuthor.begin(), i + 1);

        if (i == 0 || pair1.first != pair2.first)
        {
            secAuthor << pair1.first << "|" << i << "|" << endl;
        }
        if (pair1.first != pair3.first)
        {
            linkedList << i << "|" << pair1.second << "|" << -1 << endl;
        }

        if (pair1.first == pair3.first)
        {
            linkedList << i << "|" << pair1.second << "|" << i + 1 << endl;
        }
    }
    secAuthor.close();
    linkedList.close();
}
void createBookSec(Book B)
{
    fstream secBook;
    secBook.open("book_Secondary.txt", ios::out);

    fstream linkedList;
    linkedList.open("linkedListBook.txt", ios::out);

    invertedListBook.insert({B.Author_ID, B.ISBN});

    for (int i = 0; i < invertedListBook.size(); i++)
    {

        const auto &pair1 = *next(invertedListBook.begin(), i);
        const auto &pair2 = *next(invertedListBook.begin(), i - 1);
        const auto &pair3 = *next(invertedListBook.begin(), i + 1);

        if (i == 0 || pair1.first != pair2.first)
        {
            secBook << pair1.first << "|" << i << "|" << endl;
        }
        if (pair1.first != pair3.first)
        {
            linkedList << i << "|" << pair1.second << "|" << -1 << endl;
        }

        if (pair1.first == pair3.first)
        {
            linkedList << i << "|" << pair1.second << "|" << i + 1 << endl;
        }
    }
    secBook.close();
    linkedList.close();
}

// Function to read the book secondary index file into the book_SecIndex structure
// to use it in search for SearchBookByAuthorId

void readBookSecIndex()
{
    fstream secBook;
    secBook.open("book_Secondary.txt", ios::in);

    for (int i = 0; i < 200 && !secBook.eof(); i++)
    {
        secBook.getline(book_SIn[i].authorId, 50, '|');
        secBook.getline(book_SIn[i].ind, 30, '\n');
    }

    secBook.close();
}

// Function to read the linked list file into the bookLinkedList structure

void readBookLinkedList()
{
    fstream linkedList;
    linkedList.open("linkedListBook.txt", ios::in);

    for (int i = 0; i < 200 && !linkedList.eof(); i++)
    {
        linkedList.getline(bookLinkedList[i].ind, 50, '|');
        linkedList.getline(bookLinkedList[i].bookID, 30, '|');
        linkedList.getline(bookLinkedList[i].next, 30, '\n');
    }

    linkedList.close();
}



char *SearchAuthorById(char *id, int low, int high)
{
    int mid;
    while (low < high)
    {
        mid = (low + high) / 2;
        if (strcmp(Author_in[mid].ID, id) == 0)
        {
            return Author_in[mid].offset;
        }
        if (strcmp(Author_in[mid].ID, id) > 0)
        {
            return SearchAuthorById(id, low, mid);
        }
        if (strcmp(Author_in[mid].ID, id) < 0)
        {
            return SearchAuthorById(id, mid + 1, high);
        }
    }
    return NULL;
}

char *SearchBookById(char *id, int low, int high)
{
    int mid;
    while (low < high)
    {
        mid = (low + high) / 2;
        if (strcmp(in[mid].id, id) == 0)
        {
            return in[mid].ind;
        }
        if (strcmp(in[mid].id, id) > 0)
        {
            return SearchBookById(id, low, mid);
        }
        if (strcmp(in[mid].id, id) < 0)
        {
            return SearchBookById(id, mid + 1, high);
        }
    }
    return NULL;
}

int AddAuthor()
{
    fstream Record;
    Author A;

    cout << "Enter Author Name: ";
    cin >> A.author_Name;

    cout << "Enter Author ID: ";
    cin >> A.author_id;

    if (SearchAuthorById(A.author_id, 0, author_no) != NULL)
    {
        cout << "Author ID already exists. Please use a different ID.\n";
        return -1;
    }

    cout << "Enter author Address: ";
    cin >> A.author_Address;

    A.authorSiz = 0;
    A.authorSiz += strlen(A.author_Name);
    A.authorSiz += strlen(A.author_id);
    A.authorSiz += strlen(A.author_Address);
    A.authorSiz += 5;
    char s[5];
    //    converts the integer A.authorSiz to a string and stores it in character s.
    itoa(A.authorSiz, s, 10);

    //    Update A.authorSiz by adding the length of the string representation of the original size.
    A.authorSiz += strlen(s);

    Record.open("Author_data.txt", ios::app | ios::out);
    Record << A.authorSiz << "|" << A.author_Name << "|" << A.author_id << "|" << A.author_Address << "|"
           << "\n";
    Record.close();

    // Read the current number of authors
    Author_readRecNo();

    // Increment the author count
    author_no++;

    // Update the author count in the file
    Author_writeRecNo();

    createAuthorPriIndex();

    sortAuthorPriIndex();

    writeAuthorPriIndex();

    createAuthorSec(A);
}

int AddBook()
{
    fstream recordFile;
    Book book;

    cout << "Enter book Name: ";
    cin >> book.bookTitle;

    cout << "Enter book ID: ";
    cin >> book.ISBN;

    if (SearchBookById(book.ISBN, 0, book_no) != NULL)
    {
        cout << "Book ID already exists. Please use a different ID.\n";
        return -1;
    }

    cout << "Enter Author id : ";
    cin >> book.Author_ID;

    if (SearchAuthorById(book.Author_ID, 0, author_no) == NULL)
    {
        cout << "Author ID doesn't exist. Please add the author first.\n";
        return -1;
    }

    book.bookSiz = 0;
    book.bookSiz += strlen(book.bookTitle);
    book.bookSiz += strlen(book.ISBN);
    book.bookSiz += strlen(book.Author_ID);
    book.bookSiz += 4;

    char s[5];
    itoa(book.bookSiz, s, 10);
    book.bookSiz += strlen(s);

    recordFile.open("book_data.txt", ios::app | ios::out);
    recordFile << book.bookSiz << "|" << book.ISBN << "|" << book.bookTitle << "|" << book.Author_ID << "\n";
    recordFile.close();

    // Read the current number of authors
    readRecNo();

    // Increment the author count
    book_no++;

    // Update the author count in the file
    writeRecNo();

    createBookPriIndex();

    sortBookPriIndex();

    writeBookPriIndex();

    createBookSec(book);
}






void retriveAuthorRecord(char *offset)
{
    int x = atoi(offset);
    fstream ff;
    ff.open("Author_data.txt", ios::in);
    ff.seekg(x, ios::beg);
    ff.getline(offset, 10, '|');
    ff.getline(author_Name, 50, '|');
    ff.getline(author_id, 13, '|');
    ff.getline(author_Address, 50, '|');

    cout << '\n'
         << "Name   ID    Address   " << endl;
    cout << author_Name << "    " << author_id << "    " << author_Address << '\n'
         << endl;
    ff.close();
}

void retriveAuthorName(char *offset)
{
    int x = atoi(offset);
    fstream ff;
    ff.open("Author_data.txt", ios::in);
    ff.seekg(x, ios::beg);
    ff.getline(offset, 10, '|');
    ff.getline(author_Name, 50, '|');
    ff.getline(author_id, 13, '|');
    ff.getline(author_Address, 50, '|');

    cout << '\n'
         << "Name" << endl;
    cout << author_Name << endl;
    ff.close();
}

//used to search in the secondary book index to get the ind for this book

char* SearchBookByAuthorId(char* authorId, int low, int high) {
    readBookSecIndex();

    int mid;

    while (low < high) {
        mid = (low + high) / 2;
        if (strcmp(book_SIn[mid].authorId, authorId) == 0) {
            return book_SIn[mid].ind;
        }
        if (strcmp(book_SIn[mid].authorId, authorId) > 0) {
            high = mid; // Adjust high to continue searching in the left half
        } else {
            low = mid + 1; // Adjust low to continue searching in the right half
        }
    }
    return NULL;
}


void retriveBookRecord(char *ind)
{
    int x = atoi(ind);
    fstream ff;
    ff.open("book_data.txt", ios::in);
    ff.seekg(x, ios::beg);
    ff.getline(ind, 10, '|');
    ff.getline(ISBN, 30, '|');
    ff.getline(bookTitle, 50, '|');
    ff.getline(Author_ID, 50, '\n');

    cout << '\n'
         << "ID    book Title    author_id" << endl;
    cout << ISBN << "    " << bookTitle << "    " << Author_ID << '\n'
         << endl;
    ff.close();
}


void updateAuthorName()
{
    char authorU[13];

    cout << "Enter the ID of the author to update: ";
    cin >> authorU;

    // Open the data file in read mode
    ifstream inputFile("Author_data.txt");

    // Check if the file is open
    if (!inputFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    // Create a temporary file
    ofstream tempFile("temp_Author_data.txt");

    // Check if the temporary file is open
    if (!tempFile.is_open())
    {
        cout << "Error creating temporary file!" << endl;
        inputFile.close();
        return;
    }

    // Variables to store record data
    char authorSiz[5], author_Name[50], author_id[13], author_Address[50];

    // Variable to check if the record is found
    bool Found = false;

    // Read the first record
    inputFile.getline(authorSiz, 5, '|');
    while (inputFile.getline(author_Name, 50, '|'))
    {
        inputFile.getline(author_id, 13, '|');
        inputFile.getline(author_Address, 50, '\n');

        // Check if the author ID matches
        if (strcmp(author_id, authorU) == 0)
        {
            // Display the existing record
            cout << "Existing Record:\n";
            cout << "Name   ID    Address" << endl;
            cout << author_Name << "    " << author_id << "    " << author_Address << '\n' << endl;

            // Get the new author name
            cout << "Enter the new author name: ";
            cin >> author_Name;

            // Calculate the size of the updated record
            int updatedSize = strlen(authorSiz) + strlen(author_Name) + strlen(author_id) + strlen(author_Address) + 3;

            // Write the updated record to the temporary file
            tempFile << updatedSize << "|" << author_Name << "|" << author_id << "|" << author_Address << "\n";

            // Set the flag to indicate that the record is found and updated
            Found = true;

            cout << "Author name updated successfully!" << endl;
        }
        else
        {
            // Write the unchanged record to the temporary file
            tempFile << authorSiz << "|" << author_Name << "|" << author_id << "|" << author_Address << "\n";
        }

        // Read the next record size
        inputFile.getline(authorSiz, 5, '|');
    }

    // Check if the record is not found
    if (!Found)
    {
        cout << "Author not found. Unable to update." << endl;
    }

    // Close the input and temporary files
    inputFile.close();
    tempFile.close();

    // Replace the original file with the temporary one
    if (remove("Author_data.txt") != 0)
    {
        cout << "Error deleting original file!" << endl;
        return;
    }

    if (rename("temp_Author_data.txt", "Author_data.txt") != 0)
    {
        cout << "Error renaming temporary file!" << endl;
        return;
    }
}


void updateBookTitle()
{
    char ISBNU[30];

    cout << "Enter the ISBN of the book to update: ";
    cin >> ISBNU;

    // Open the data file in read mode
    ifstream inputFile("book_data.txt");

    // Check if the file is open
    if (!inputFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    // Create a temporary file
    ofstream tempFile("temp_book_data.txt");

    // Check if the temporary file is open
    if (!tempFile.is_open())
    {
        cout << "Error creating temporary file!" << endl;
        inputFile.close();
        return;
    }

    // Variables to store record data
    char bookSiz[5], ISBN[30], bookTitle[50], Author_ID[50];

    // Variable to check if the record is found
    bool Found = false;

    // Read the first record
    inputFile.getline(bookSiz, 5, '|');
    while (inputFile.getline(ISBN, 30, '|'))
    {
        inputFile.getline(bookTitle, 50, '|');
        inputFile.getline(Author_ID, 50, '\n');

        // Check if the ISBN matches
        if (strcmp(ISBN, ISBNU) == 0)
        {
            // Display the existing record
            cout << "Existing Record:\n";
            cout << "ID    book Title    author_id" << endl;
            cout << ISBN << "    " << bookTitle << "    " << Author_ID << '\n' << endl;

            // Get the new book title
            cout << "Enter the new book title: ";
            cin >> bookTitle;

            // Calculate the size of the updated record
            int updatedSize = strlen(bookSiz) + strlen(ISBN) + strlen(bookTitle) + strlen(Author_ID) + 3;

            // Write the updated record to the temporary file
            tempFile << updatedSize << "|" << ISBN << "|" << bookTitle << "|" << Author_ID << "\n";

            // Set the flag to indicate that the record is found and updated
            Found = true;

            cout << "Book title updated successfully!" << endl;
        }
        else
        {
            // Write the unchanged record to the temporary file
            tempFile << bookSiz << "|" << ISBN << "|" << bookTitle << "|" << Author_ID << "\n";
        }

        // Read the next record size
        inputFile.getline(bookSiz, 5, '|');
    }

    // Check if the record is not found
    if (!Found)
    {
        cout << "Book not found. Unable to update." << endl;
    }

    // Close the input and temporary files
    inputFile.close();
    tempFile.close();

    // Replace the original file with the temporary one
    if (remove("book_data.txt") != 0)
    {
        cout << "Error deleting original file!" << endl;
        return;
    }

    if (rename("temp_book_data.txt", "book_data.txt") != 0)
    {
        cout << "Error renaming temporary file!" << endl;
        return;
    }
}

// void deleteAuthorFromDataFile(char* st_id)
//{
//     readAuthorHeader();
//     int x =atoi(st_id);
//     fstream ff;
//     ff.open("Author_data.txt");
//     ff.seekp(x, ios::beg);
//     ff<<'*'<<authorHeader<<'|';
//     ff.close();
// }


void PrintBookByID(char *ISBN)
{
    readBookPriIndex();
    if (SearchBookById(ISBN, 0, book_no) != NULL)
    {
        retriveBookRecord(SearchBookById(ISBN, 0, author_no));
        return;
    }
    cout << "Book not found" << endl;
    return;
}

void PrintAuthorByID()
{
    readAuthorPriIndex();
    cout << "Enter the id: ";
    cin >> Author_ID;
    if (SearchAuthorById(Author_ID, 0, author_no) != NULL)
    {
        retriveAuthorRecord(SearchAuthorById(Author_ID, 0, author_no));
        return;
    }
    cout << "Author not found" << endl;
    return;
}


// Function to print all books for a given author ID from the inverted list
//void PrintBooksByAuthorID(const char* ind) {
//    fstream linkedListFile;
//    readBookLinkedList();
//    linkedListFile.open("linkedListBook.txt", ios::in);
//
//    if (SearchBookByAuthorId==NULL){
//        cout << "author id not found in the secondary index \n";
//        return;
//    }
//    else{
//        while (!linkedListFile.eof()) {
//            linkedListFile.getline(bookLinkedList_temp.ind, 10, '|');
//            linkedListFile.getline(bookLinkedList_temp.bookID, 30, '|');
//            linkedListFile.getline(bookLinkedList_temp.next, 30, '\n');
//
//            if (strcmp(bookLinkedList_temp.ind, ind) == 0) {
//                // Call the function to print the book details
//                PrintBookByID(bookLinkedList_temp.bookID);
//
//                if (strcmp(bookLinkedList_temp.next, "-1") != 0) {
//                    // Continue printing the remaining books for this author ID
//                    PrintBookByID(bookLinkedList_temp.next);
//                }
//                return;
//            }
//        }
//
//    }
//    linkedListFile.close();
//}


void PrintBooksByAuthorID(const char* ind) {
    fstream linkedListFile;
    readBookLinkedList();
    linkedListFile.open("linkedListBook.txt", ios::in);

    if (ind == NULL) {
        cout << "Author id not found in the secondary index.\n";
        return;
    } else {
        while (!linkedListFile.eof()) {
            linkedListFile.getline(bookLinkedList_temp.ind, 10, '|');
            linkedListFile.getline(bookLinkedList_temp.bookID, 30, '|');
            linkedListFile.getline(bookLinkedList_temp.next, 30, '\n');

            if (strcmp(bookLinkedList_temp.ind, ind) == 0) {
                // Call the function to print the book details
                PrintBookByID(bookLinkedList_temp.bookID);

                if (strcmp(bookLinkedList_temp.next, "-1") != 0) {
                    // Continue printing the remaining books for this author ID
                    PrintBooksByAuthorID(SearchBookByAuthorId(bookLinkedList_temp.next, 0, book_no));
                }
                return;
            }
        }
    }

    linkedListFile.close();
}





void deleteBookFromDataFile(char* ind)
{
    readHeader();
    int x =atoi(ind);
    fstream ff;
    ff.open("book_data.txt");
    ff.seekp(x, ios::beg);
    ff<<'*'<<header<<'|';
    ff.close();
}

void deleteAuthorFromPriIndex(char* id)
{
    Author_readRecNo();
    readAuthorPriIndex();
    for(int i=0; i<author_no; i++)
    {
        if(strcmp(Author_in[i].ID, id)==0)
        {
            int h = atoi(Author_in[i].offset);
            writeAuthorHeader(h);
            author_no--;
            for(int j = i; j<author_no; j++)
            {
                strcpy(Author_in[j].ID, Author_in[j+1].ID);
                strcpy(Author_in[j].offset, Author_in[j+1].offset);
            }
        }
    }
    Author_writeRecNo();
    writeAuthorPriIndex();
}

void deleteBookFromPriIndex(char* id)
{
    readRecNo();
    readBookPriIndex();
    int low = 0;
    int high = book_no - 1;
    int mid, foundIndex = -1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (strcmp(in[mid].id, id) == 0) {
            foundIndex = mid;
            break;
        } else if (strcmp(in[mid].id, id) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (foundIndex != -1) {
        int h = atoi(in[foundIndex].ind);
        writeHeader(h);

        for (int j = foundIndex; j < book_no - 1; j++) {
            strcpy(in[j].id, in[j + 1].id);
            strcpy(in[j].ind, in[j + 1].ind);
        }

        book_no--;
        writeRecNo();
        writeBookPriIndex();
    } else {
        cout << "Book not found" << endl;
    }
}


void readBookSIn()
{
    readRecNo();
    fstream f;
    f.open("book_Secondary.txt", ios::in);
    for (int i = 0; i < book_no; i++)
    {
        f.getline(book_SIn[i].authorId, 13, '|');
        f.getline(book_SIn[i].ind, 10, '\n');
    }
    f.close();

}

void deleteBookFromSIn(char* id) {
    readRecNo();
    readBookSIn();
    int low = 0;
    int high = book_no - 1;
    int mid, foundIndex = -1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (strcmp(book_SIn[mid].authorId, id) == 0) {
            foundIndex = mid;
            break;
        } else if (strcmp(book_SIn[mid].authorId, id) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
        cout<<"id " <<book_SIn[mid].authorId<<endl;

    }

}
void deleteBook()
{
    readRecNo();
    readBookPriIndex();
    cout<<"Enter the id: ";
    cin>>ISBN;
    if (SearchBookById(ISBN,0,book_no)!=NULL)
    {
        deleteBookFromDataFile(SearchBookById(ISBN,0,book_no));
        deleteBookFromPriIndex(ISBN);
        cout<<"Deleted Successfully"<<endl;
        return;
    }
    cout << "deletion failed record not found\n";
}

void PrintBookByID()
{
    readBookPriIndex();
    cout << "Enter the id: ";
    cin >> ISBN;
    if (SearchBookById(ISBN, 0, book_no) != NULL)
    {
        retriveBookRecord(SearchBookById(ISBN, 0, author_no));
        return;
    }
    cout << "Book not found" << endl;
    return;
}

//void PrintAuthorByID()
//{
//    readAuthorPriIndex();
//    cout << "Enter the id: ";
//    cin >> Author_ID;
//    if (SearchAuthorById(Author_ID, 0, author_no) != NULL)
//    {
//        retriveAuthorRecord(SearchAuthorById(Author_ID, 0, author_no));
//        return;
//    }
//    cout << "Author not found" << endl;
//    return;
//}




void loadInvertedList() {
    ifstream secFile("author_Secondary.txt");
    ifstream llFile("linkedListAuthor.txt");


    int i, secPointer, llPointer, x;
    string id;

    while (secFile >> i >> secPointer) {
        llFile.clear();
        llFile.seekg(0, ios::beg);

        while (llFile >> llPointer >> id >> x) {
            if (secPointer == llPointer) {
                invertedListAuthor.insert({to_string(i), id});
                while (x != -1) {
                    llFile >> llPointer >> id >> x;
                    invertedListAuthor.insert({to_string(i), id});
                }
                break;
            }
        }
    }
    secFile.close();
    llFile.close();
}

void deleteAuthorID(string ID) {
    loadInvertedList();
    auto it = invertedListAuthor.find(ID);
    if (it != invertedListAuthor.end()) {
        invertedListAuthor.erase(it);
    }
    for (it = invertedListAuthor.begin(); it != invertedListAuthor.end(); ++it){
        cout<<it->first<<" "<<it->second;
    }

    ofstream f("author_Secondary.txt", ios::trunc);
    ofstream LLFile("linkedListAuthor.txt", ios::trunc);

    int i = 0;
    for (it = invertedListAuthor.begin(); it != invertedListAuthor.end(); ++it, ++i) {
        if (i == 0 || it->first != prev(it)->first) {
            f << it->first << "|" << i << endl;
        }

        if (next(it) != invertedListAuthor.end() && it->first == next(it)->first) {
            LLFile << i << "|" << it->second << "|" << i + 1 << endl;
        } else {
            LLFile << i << "|" << it->second << "|" << -1 << endl;
        }
    }

    f.close();
    LLFile.close();
}

void deleteAuthorName(char name[], char id[]) {
    loadInvertedList();
    auto range = invertedListAuthor.equal_range(name);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == id) {
            invertedListAuthor.erase(it);
            break;
        }
    }

    ofstream f("author_Secondary.txt", ios::trunc);
    ofstream LLFile("linkedListAuthor.txt", ios::trunc);

    auto it = invertedListAuthor.begin();

    for (int i = 0; it != invertedListAuthor.end(); ++it, ++i) {
        if (i == 0 || it->first != prev(it)->first) {
            f << it->first << " " << i << endl;
        }

        if (it->first == next(it)->first) {
            LLFile << i << "|" << it->second << "|" << i + 1 << endl;
        } else {
            LLFile << i << "|" << it->second << "|" << -1 << endl;
        }
    }
    LLFile.close();
    f.close();
}


void deleteAuthor(char* id) {
    string headerList;
    ifstream f;
    f.open("Authorheader.txt", ios::in | ios::out);
    f >> headerList;
    f.close();
    char *currentOffset = SearchAuthorById(id, 0, author_no);
    if(currentOffset!=NULL){
        deleteAuthorFromPriIndex(id);

        fstream file;
        file.open("Author_data.txt", ios::in | ios::out | ios::binary);
        file.seekg(atoi(currentOffset), ios::beg);
        stringstream lengthStream;
        char sizeBytes[3];
        file >> sizeBytes;
        sizeBytes[2] = '\0';
        int size = atoi(sizeBytes);
        file.seekg(atoi(currentOffset) + 2, ios::beg);
        file << "\n" << "*" << headerList << "|" << size << "|";
        for (int i = 0; i < size - headerList.size(); i++) {
            file << " ";
        }
        headerList = currentOffset;
        ofstream f1;
        f1.open("Authorheader.txt", ios::trunc);
        f1.seekp(0, ios::beg);
        f1 << headerList;
        size = 0;
        file.close();
    }

}




void writeQuery() {
    cout << "Enter Query: ";
    cin.ignore(); // Clear any remaining characters in the input buffer
    string query;
    string tolowerQuery;
    getline(cin,query); // Read the entire line including spaces

// Convert the query to lowercase for case-insensitive matching
    for (int i = 0; i < query.size(); ++i) {
        tolowerQuery+= tolower(query[i]);
    }

    cout << "\n" <<tolowerQuery<<"\n";

    if (tolowerQuery.find("select all from authors where author id=") != string::npos) {
        cout << "case 1\n";
        PrintAuthorByID();
    }

    else if (tolowerQuery.find("select all from books where author id=") != string::npos) {
        cout << "case 2\n";
        char authorId[50];
        cout << "Enter Author ID: ";
        cin >> authorId;
        PrintBooksByAuthorID(SearchBookByAuthorId(authorId,0,author_no));

        //        PrintBookByID(authorId);
        ////        retriveBookRecord(SearchBookById(authorId, 0, book_no));
    }

    else if (tolowerQuery.find("select author name from authors where author id=")!=string::npos) {
        cout << "case 3\n";
        char authorId[50];
        cout << "Enter Author ID: ";
        cin >> authorId;
        if (SearchAuthorById(authorId, 0, author_no) != NULL)
        {
            retriveAuthorName(SearchAuthorById(authorId, 0, author_no));
            return;
        }
        cout << "Author not found" << endl;
        return;
    }

    else {
        cout << "Invalid Query" << endl;
    }
}


int main()
{
    Author_readRecNo();
    readRecNo();

    int choice;
    do
    {
        cout << "\nwelcome to our library system :) \nAvailable Options :\n"
                "1- Add New Author\n"
                "2- Add New Book \n"
                "3- Update Author Name (Author ID) \n"
                "4- Update Book Title (ISBN) \n"
                "5- Delete Book (ISBN) \n"
                "6- Delete Author (Author ID) \n"
                "7- Print Author (Author ID) \n"
                "8- Print Book (ISBN) \n"
                "9- Write Query \n"
                "10- Exit\n";
        cout << "\nchoose from options above: \n";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            AddAuthor();
            break;
        }
        case 2:
        {
            AddBook();
            break;
        }
        case 3:
        {
        updateAuthorName();
            break;
        }
        case 4:
        {
        updateBookTitle();
            break;
        }
        case 5:
        {
                       deleteBook();
            break;
        }
        case 6:
        {
//                            deleteAuthor();
            break;
        }
        case 7:
        {
            PrintAuthorByID();
            break;
        }
        case 8:
        {
            char id[12] ;
            cout << "enter id : ";
            cin >> id;
            PrintBookByID(id);
            break;
        }
        case 9:
        {
            writeQuery();
            break;
        }
        }
    } while (choice != 10);

    return 0;
}
