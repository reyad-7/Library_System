#include<bits/stdc++.h>
using namespace std;

// Global variables to store the number of records and headers
int book_no=0;
int  author_no=0;
char author_Name[50], author_id[13], authorCursor[5],author_Address[50], authorSiz[5];
char bookTitle[50], Author_ID[50], bookCursor[5], ISBN[30], bookSiz[5];
int header = -1, Authorheader=-1;


// Structures to define the record formats
struct Author
{
    char author_id[13];
    char author_Name[50];
    char author_Address[50];
    int authorSiz;

};
struct Book
{
    char ISBN[30];
    char bookTitle[50];
    char Author_ID[50];
    int bookSiz;

};


// Structures to define primary indices

struct Author_PriIndex
{
    char ID[13] , offset[10];
}Author_in[200], Author_temp;


struct bookPriIndex
{
    char id[30], ind[10];
}in[200], temp;



// Structures to define secondary indices
struct book_SecIndex
{
    char author_id[50],bookID[30];
}book_SIn[200], B_Stemp;



struct authorSecIndex
{
    char name[50],id[30];
}SIn[100], stemp;




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

void readEmpHeader()
{
    fstream HFile;
    HFile.open("Authorheader.txt", ios::in);
    HFile >> Authorheader;
    HFile.close();
}
void writeEmpHeader(int header)
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

void createAuthorPriIndex() {
    int current = 0;
    fstream file;
    file.open("Author_data.txt", ios::in);

    // Iterate through each author record
    for (int i = 0; i < author_no; i++) {
        file.getline(authorSiz, 5, '|');
        file.getline(author_Name, 50, '|');
        file.getline(author_id, 13, '|');
        file.getline(author_Address, 50, '|');

        // Convert current to string and store in authorCursor
        itoa(current, authorCursor, 10);

        // Store author ID and offset in Author_in array
        strcpy_s(Author_in[i].ID, author_id);
        strcpy_s(Author_in[i].offset, authorCursor);

        // Update current for the next record
        current += atoi(authorSiz);
    }
    // Close the file
    file.close();
}


void createBookPriIndex()
{
    int current =0;
    fstream file1;
    file1.open("book_data.txt", ios::in);

    // Iterate through each author record
    for (int i=0; i<book_no; i++)
    {
        file1.getline(bookSiz, 5, '|');
        file1.getline(ISBN, 30, '|');
        file1.getline(bookTitle, 50, '|');
        file1.getline(Author_ID, 50, '\n');

        // Convert current to string and store in authorCursor

        itoa(current, bookCursor, 10);

        // Store author ID and offset in Author_in array
        strcpy_s(in[i].id, ISBN);
        strcpy_s(in[i].ind, bookCursor);

        // Update current for the next record
        current+=atoi(bookSiz);
    }

    // Close the file
    file1.close();
}


void readAuthorPriIndex()
{
    Author_readRecNo();
    fstream f;
    f.open("authorPrimary_index.txt", ios::in);
    for(int i=0; i<author_no; i++)
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
    for(int i=0; i<book_no; i++)
    {
        ff.getline(in[i].id, 30, '|');
        ff.getline(in[i].ind, 10, '\n');

    }
    ff.close();
}

// Function to write the primary index of authors to file
void writeAuthorPriIndex() {
    Author_readRecNo(); // Read the number of authors
    fstream file;
    file.open("authorPrimary_index.txt", ios::out);

    // Iterate through each entry in the primary index
    for (int i = 0; i < author_no; i++) {
        file << Author_in[i].ID << "|" << Author_in[i].offset << "\n";
    }

    // Close the file
    file.close();
}


// Function to write the primary index of books to file
void writeBookPriIndex() {
    readRecNo(); // Read the number of books
    fstream file2;
    file2.open("bookPrimary_index.txt", ios::out);

    // Iterate through each entry in the primary index
    for (int i = 0; i < book_no; i++) {
        file2 << in[i].id << "|" << in[i].ind << "\n";
    }
    // Close the file
    file2.close();
}


// Function to create the secondary indices
//void createBookSecIndex()
//{
//    fstream recordFile;
//    recordFile.open("book_data.txt", ios::in);
////     Iterate through each book record
//    for (int i=0; i<book_no; i++)
//    {
//
//        recordFile.getline(bookSiz, 5, '|');
//        recordFile.getline(ISBN, 30, '|');
//        recordFile.getline(bookTitle, 50, '|');
//        recordFile.getline(Author_ID, 50, '\n');
//
//        strcpy_s(book_SIn[i].author_id, Author_ID);
//
//        strcpy_s(book_SIn[i].bookID, ISBN);
//
//    }
//    recordFile.close();
//
//}

void createBookSecIndex() {
    fstream recordFile;
    recordFile.open("book_data.txt", ios::in);

    // Iterate through each book record
    for (int i = 0; i < book_no; i++) {
        recordFile.getline(bookSiz, 5, '|');
        recordFile.getline(ISBN, 30, '|');
        recordFile.getline(bookTitle, 50, '|');
        recordFile.getline(Author_ID, 50, '\n');

        // Store author ID and book ID in book_SIn array
        strcpy_s(book_SIn[i].author_id, Author_ID);
        strcpy_s(book_SIn[i].bookID, ISBN);
    }
    recordFile.close();
}


void createAuthorSecIndex()
{
    fstream Record;
    Record.open("Author_data.txt", ios::in);
    for (int i=0; i<author_no; i++)
    {
        Record.getline(authorSiz, 5, '|');
        Record.getline(author_Name, 50, '|');
        Record.getline(author_id, 13, '|');
        Record.getline(author_Address, 50, '|');

        strcpy_s(SIn[i].name, author_Name);

        strcpy_s(SIn[i].id, author_id);

    }
    Record.close();

}


void writeAuthorSecIndex()
{
    fstream Sec;
    Sec.open("author_Secondary.txt", ios::out);
    for (int i=0; i<author_no; i++)
    {
        Sec << SIn[i].name << "|" << SIn[i].id << "\n";
    }
    Sec.close();
}



void writeBookSecIndex() {
    fstream SIndexFile;
    SIndexFile.open("book_Secondary.txt", ios::out);

    // Iterate through each entry in the secondary index
    for (int i = 0; i < book_no; i++) {
        SIndexFile << book_SIn[i].author_id << "|" << book_SIn[i].bookID << "\n";
    }
    SIndexFile.close();
}


void readAuthorSecIndex()
{
    fstream s;
    s.open("author_Secondary.txt", ios::in);

    int i = 0;
    while (!s.eof())
    {
        s.getline(SIn[i].name, 30, '|');
        s.getline(SIn[i].id, 13, '\n');
        i++;
    }
    s.close();
}


void readBookSecIndex()
{
    readRecNo();
    fstream ff;
    ff.open("book_Secondary.txt", ios::in);

    for(int i=0; i<book_no; i++)
    {
        ff.getline(book_SIn[i].author_id, 50, '|');
        ff.getline(book_SIn[i].bookID, 30, '\n');

    }
    ff.close();
}


void sortAuthorPriIndex()
{
    int i, j;
    for (i = 0;i < author_no - 1;i++)
    {
        for (j = 0;j < author_no - i - 1;j++)
        {
            if (strcmp(Author_in[j].ID, Author_in[j + 1].ID) > 0)
            {
                Author_temp = Author_in[j];
                Author_in[j] = Author_in[j + 1];
                Author_in[j + 1] = Author_temp;
            }
        }

    }

}


void sortBookPriIndex()
{
    int i, j;
    for (i = 0;i < book_no - 1;i++)
    {
        for (j = 0;j < book_no - i - 1;j++)
        {
            if (strcmp(in[j].id, in[j + 1].id) > 0)
            {
                temp = in[j];
                in[j] = in[j + 1];
                in[j + 1] = temp;
            }
        }

    }

}

void sortAuthorSecIndex()
{
    int i, j;
    for (i = 0;i < author_no - 1;i++)
    {
        for (j = 0;j < author_no - i - 1;j++)
        {
            if (strcmp(SIn[j].name, SIn[j + 1].name) > 0)
            {
                stemp = SIn[j];
                SIn[j] = SIn[j + 1];
                SIn[j + 1] = stemp;
            }
        }

    }

}

void sortBookSecIndex()
{
    int i, j;
    for (i = 0;i < book_no - 1;i++)
    {
        for (j = 0;j < book_no - i - 1;j++)
        {
            if (strcmp(book_SIn[j].author_id, book_SIn[j + 1].author_id) > 0)
            {
                B_Stemp = book_SIn[j];
                book_SIn[j] =book_SIn[j + 1];
                book_SIn[j + 1] = B_Stemp;
            }
        }

    }

}


int AddAuthor()
{
    fstream Record;
    Author A;

    cout<<"Enter Author Name: ";
    cin>>A.author_Name;

    cout<<"Enter Author ID: ";
    cin>>A.author_id;

    cout<<"Enter author Address: ";
    cin>>A.author_Address;


    A.authorSiz=0;
    A.authorSiz += strlen(A.author_Name);
    A.authorSiz += strlen(A.author_id);
    A.authorSiz += strlen(A.author_Address);
    A.authorSiz+=5;
    char s[5];
    itoa(A.authorSiz,s,10);

    A.authorSiz+=strlen(s);

    Record.open("Author_data.txt", ios::app | ios::out);
    Record << A.authorSiz<< "|" << A.author_Name  << "|" << A.author_id << "|" << A.author_Address << "|" << "\n";
    Record.close();

    Author_readRecNo();

    author_no++;

    Author_writeRecNo();

    createAuthorPriIndex();

    sortAuthorPriIndex();

    writeAuthorPriIndex();

    createAuthorSecIndex();

    sortAuthorSecIndex();

    writeAuthorSecIndex();
}

int AddBook()
{
    fstream recordFile;
    Book book;

    cout<<"Enter book Name: ";
    cin>>book.bookTitle;

    cout<<"Enter book ID: ";
    cin>>book.ISBN;

    cout<<"Enter Author id : ";
    cin>>book.Author_ID;


    book.bookSiz=0;
    book.bookSiz += strlen(book.bookTitle);
    book.bookSiz += strlen(book.ISBN);
    book.bookSiz += strlen(book.Author_ID);
    book.bookSiz+=4;
    char s[5];
    itoa(book.bookSiz,s,10);

    book.bookSiz+=strlen(s);

    recordFile.open("book_data.txt", ios::app | ios::out);
    recordFile << book.bookSiz<< "|" << book.ISBN << "|" << book.bookTitle << "|" << book.Author_ID << "\n";
    recordFile.close();

    readRecNo();

    book_no++;

    writeRecNo();

    createBookPriIndex();

    sortBookPriIndex();

    writeBookPriIndex();

    createBookSecIndex();

    sortBookSecIndex();

    writeBookSecIndex();
}



void author_retrive_record(char* offset)
{
    int x =atoi(offset);
    fstream ff;
    ff.open("Author_data.txt", ios::in);
    ff.seekg(x,ios::beg);
    ff.getline(offset, 10, '|');
    ff.getline(author_Name, 50, '|');
    ff.getline(author_id, 13, '|');
    ff.getline(author_Address, 50, '|');


    cout<<'\n'<<"Name   ID    Address   "<<endl;
    cout<<author_Name<<"    "<<author_id<<"    "<<author_Address<<'\n'<<endl;
    ff.close();
}


void retrive_record(char* ind)
{
    int x =atoi(ind);
    fstream ff;
    ff.open("book_data.txt", ios::in);
    ff.seekg(x,ios::beg);
    ff.getline(ind, 10, '|');
    ff.getline(ISBN, 30, '|');
    ff.getline(bookTitle, 50, '|');
    ff.getline(Author_ID, 50, '\n');

    cout<<'\n'<<"ID    book Title    author_id"<<endl;
    cout<<ISBN<<"    "<<bookTitle<<"    "<<Author_ID<<'\n'<<endl;
    ff.close();
}



//char * SearchEmployee_By_id(char* id, int low, int high)
//{
//    int mid;
//    while(low<high)
//    {
//        mid = (low+high)/2;
//        if (strcmp(E_in[mid].ID, id) == 0)
//        {
//            return E_in[mid].offset;
//        }
//        if(strcmp(E_in[mid].ID, id) > 0)
//        {
//            return SearchEmployee_By_id(id, low, mid);
//        }
//        if(strcmp(E_in[mid].ID, id) < 0)
//        {
//            return SearchEmployee_By_id(id, mid+1, high);
//        }
//
//    }
//    return NULL;
//}


//char * SearchDepartment(char* id, int low, int high)
//{
//    int mid;
//    while(low<high)
//    {
//        mid = (low+high)/2;
//        if (strcmp(in[mid].id, id) == 0)
//        {
//            return in[mid].ind;
//        }
//        if(strcmp(in[mid].id, id) > 0)
//        {
//            return SearchDepartment(id, low, mid);
//        }
//        if(strcmp(in[mid].id, id) < 0)
//        {
//            return SearchDepartment(id, mid+1, high);
//        }
//
//    }
//    return NULL;
//}


//void deleteEmpFromDataFile(char* st_id)
//{
//    readEmpHeader();
//    int x =atoi(st_id);
//    fstream ff;
//    ff.open("Emp_data.txt");
//    ff.seekp(x, ios::beg);
//    ff<<'*'<<Empheader<<'|';
//    ff.close();
//}


//void deleteDeptFromDataFile(char* ind)
//{
//    readHeader();
//    int x =atoi(ind);
//    fstream ff;
//    ff.open("data.txt");
//    ff.seekp(x, ios::beg);
//    ff<<'*'<<header<<'|';
//    ff.close();
//}


//void deleteEmpFromPriIndex(char* id)
//{
//    Emp_readRecNo();
//    readEmpPriIndex();
//    for(int i=0; i<Emp_no; i++)
//    {
//        if(strcmp(E_in[i].ID, id)==0)
//        {
//            int h = atoi(E_in[i].offset);
//            writeEmpHeader(h);
//            Emp_no--;
//            for(int j = i; j<Emp_no; j++)
//            {
//                strcpy(E_in[j].ID, E_in[j+1].ID);
//                strcpy(E_in[j].offset, E_in[j+1].offset);
//            }
//        }
//    }
//    Emp_writeRecNo();
//    writeEmpPriIndex();
//}




//void deleteDeptFromPriIndex(char* id)
//{
//    readRecNo();
//    readDeptPriIndex();
//    for(int i=0; i<Dept_no; i++)
//    {
//        if(strcmp(in[i].id, id)==0)
//        {
//            int h = atoi(in[i].ind);
//            writeHeader(h);
//            Dept_no--;
//            for(int j = i; j<Dept_no; j++)
//            {
//                strcpy(in[j].id, in[j+1].id);
//                strcpy(in[j].ind, in[j+1].ind);
//            }
//        }
//    }
//    writeRecNo();
//    writeDeptPriIndex();
//}


//void deleteEmployee()
//{
//    Emp_readRecNo();
//    readEmpPriIndex();
//    cout<<"Enter the id: ";
//    cin>>Emp_id;
//    if (SearchEmployee_By_id(Emp_id,0,Emp_no)!=NULL)
//    {
//        deleteEmpFromDataFile(SearchEmployee_By_id(Emp_id,0,Emp_no));
//
//        deleteEmpFromPriIndex(Emp_id);
//        cout<<"Deleted Successfully"<<endl;
//        return;
//    }
//    cout << "Deletion failed record not found"<<endl;
//}


//void deleteDepartment()
//{
//    readRecNo();
//    readDeptPriIndex();
//    cout<<"Enter the id: ";
//    cin>>DeptID;
//    if (SearchDepartment(DeptID,0,Dept_no)!=NULL)
//    {
//        deleteDeptFromDataFile(SearchDepartment(DeptID,0,Dept_no));
//
//        deleteDeptFromPriIndex(DeptID);
//        cout<<"Deleted Successfully"<<endl;
//        return;
//    }
//    cout << "deletion failed record not found\n";
//}
//


//char * SeachEmployeetByDeptid(char * Deptid,int low,int high)
//{
//    bool flag=false;
//    for(int i=0; i<Emp_no; i++)
//    {
//        if(strcmp(E_SIn[i].Dept_id, Deptid) == 0)
//        {
//            flag = true;
//            Emp_retrive_record(SearchEmployee_By_id(E_SIn[i].ID,0,Emp_no));
//        }
//    }
//    if(!flag)
//    {
//        return NULL;
//    }
//    else
//    {
//        return Deptid;
//    }
//}




//char * SeachDepartmentByName (char * name,int low,int high)
//{
//    int mid;
//    while(low<high)
//    {
//        mid = (high + low)/2;
//        if(strcmp(SIn[mid].name, name) == 0)
//        {
//            return SIn[mid].id;
//        }
//        if(strcmp(SIn[mid].name, name) > 0)
//        {
//            return SeachDepartmentByName(name,low,mid);
//        }
//        if(strcmp(SIn[mid].name, name) < 0)
//        {
//            return SeachDepartmentByName(name,mid+1,high);
//        }
//    }
//    return NULL;
//}




//void PrintEmptByDeptid()
//{
//    readEmpSecIndex();
//    readEmpPriIndex();
//
//    cout<<"Enter the Dept ID: ";
//    cin>>Emp_Dept_id;
//    char * id = SeachEmployeetByDeptid(Emp_Dept_id,0,Emp_no);
//    if(id==NULL)
//    {
//        cout<<"DeptID not found"<<endl;
//        return;
//    }
//}



//void PrintDeptByName()
//{
//    readDeptSecIndex();
//    readDeptPriIndex();
//
//
//    cout<<"Enter the name: ";
//    cin>>DeptName;
//    char * id = SeachDepartmentByName(DeptName,0,Dept_no);
//    cout<<id;
//    if(id!= nullptr)
//    {
//        if(SearchDepartment(id,0,Dept_no) != nullptr)
//        {
//            retrive_record(SearchDepartment(SeachDepartmentByName(DeptName,0,Dept_no),0,Dept_no));
//            return;
//        }
//    }
//    cout<<"Department not found"<<endl;
//    return;
//}



//void PrintDeptByID()
//{
//    readDeptPriIndex();
//    cout<<"Enter the id: ";
//    cin>>DeptID;
//    if(SearchDepartment(DeptID,0,Dept_no) != NULL)
//    {
//        retrive_record(SearchDepartment(DeptID,0,Dept_no));
//        return;
//    }
//    cout<<"Department not found"<<endl;
//    return;
//}




//void PrintEmpByID()
//{
//    readEmpPriIndex();
//    cout<<"Enter the id: ";
//    cin>>Emp_id;
//    if(SearchEmployee_By_id(Emp_id,0,Emp_no) != NULL)
//    {
//        Emp_retrive_record(SearchEmployee_By_id(Emp_id,0,Emp_no));
//        return;
//    }
//    cout<<"Employee not found"<<endl;
//    return ;
//}



//void writeQuery(string query)
//{
//    query=to_lower(query);
//    char ch[13];
//    string q=(query);
//    if(q=="select all employee where dept_id")
//    {
//        cout<<"Enter dept_id ";
//        cin>>ch;
//        Emp_retrive_record(SeachEmployeetByDeptid(ch,0,Emp_no));
//    }
//    else if(q=="select all employee where employee_id")
//    {
//        cout<<"Enter Employee_id ";
//        cin>>ch;
//        Emp_retrive_record(SearchEmployee_By_id(ch,0,Emp_no));
//    }
//    else if(q=="select all department where dept_id")
//    {
//        cout<<"Enter dept_id ";
//        cin>>ch;
//        retrive_record(SearchDepartment(ch,0,Dept_no));
//    }
//    else if(q=="select all department where dept_name")
//    {
//        cout<<"Enter dept_name ";
//        cin>>ch;
//        retrive_record(SeachDepartmentByName(ch,0,Dept_no));
//    }
//    else
//    {
//        cout<<"wrong Query";
//    }
//
//}



int main()
{
    int choice;
    string q;
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
        cin>>choice;

        switch(choice)
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
//                deleteEmployee();
                break;
            }
            case 4:
            {
//                deleteDepartment();
                break;
            }
            case 5:
            {
//                PrintEmpByID();
                break;
            }
            case 6:
            {
//                PrintEmptByDeptid();
                break;
            }
            case 7:
            {
//                PrintDeptByID();
                break;
            }
            case 8:
            {
//                PrintDeptByName();
                break;
            }
            case 9:
            {

                cout<<"Enter Query";
                cin>>q;
//                writeQuery(q);
                break;
            }

        }
    }
    while(choice!=10);


    return 0;
}