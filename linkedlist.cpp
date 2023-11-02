//  Alley Hernandez and Trang Nguyen
//  Alley Hernandez: 887879294
//  Trang Nguyen: 805587227
//  Project-2 : Linked Lists
//  Due Date: 10/31/2023
//  Fall 2023 CPSC 131-14
//      Description: For this project, your task is to develop and implement a linked         
//                   list, along with its various operations, specifically tailored for a web browser      
//                   application. A starter template, complete with all the necessary test cases has       
//                   been provided
//      In simpler terms:
//                        - Develop a linked list for a web browser.
//                        - Use the provided starter template and test cases.
//                        - Create the linked list and add the specified functions.
//                        - Do not alter the main function provided.


#include<iostream>
#include<memory>
#include<vector>
#include<string>
// This is our template class Tab
// Instructions:    Make a class named "Tab" to represent each node in a linked list,                     
//                  with three attributes and two pointers.
//                  The attributes are:
//                  - url (string): Holds the website's URL.
//                  - name (string): Holds the website's name.
//                  - memory (generic type): Holds the amount of memory the website uses.
//                  The two pointers are:
//                  - next: Points to the next node in the list.
//                  - prev: Points to the previous node in the list.

// The template class was worked on by both Alley Hernandez and Trang Nguyen
template <typename T>
class Tab {
public:
    std::string url; // Alley Hernandez
    std::string name; // Alley Hernandez
    T memory; // Alley Hernandez
    Tab* next; // Trang Nguyen
    Tab* prev; // Trang Nguyen
    Tab(std::string u, std::string n, T m)
        : url(u), name(n), memory(m), next(nullptr), prev(nullptr) {} // Trang Nguyen
};

// This is our template class Browser
// Instructions:    create a "Browser" class to manage the tabs, ensuring it can handle                   
//                  operations in a doubly linked list manner. Make sure to have pointers                 
//                  for the beginning and end of the list, and feel free to add any extra                 
//                  pointers needed for the specific functions you plan to implement.

// The template class was worked on by both Alley Hernandez and Trang Nguyen
template <typename T>
class Browser {
private:
    Tab<T>* head; // Trang Nguyen
    Tab<T>* tail; // Trang Nguyen
    Tab<T>* current; // Trang Nguyen
    std::vector<std::pair<std::string, std::string>> bookmarks; // Alley Hernandez

public:
    Browser() : head(nullptr), tail(nullptr), current(nullptr) {} // Trang Nguyen
    
    
    // The addNewTab() function creates a new tab with the given details and adds it to the end of a linked list. 
    // The addNewTab() function was worked on by Trang Nguyen
    void addNewTab(const std::string& url, const std::string& name, T memory) {
        // Create a new tab using smart pointers and initialize it with provided values.
        Tab<T>* newTab = new Tab<T>(url, name, memory);
        // If the browser is empty set the new tab as the first, last, and current tab.
        if (!head) {
            head = tail = current = newTab;
        }
        // If there are already tabs in the browser, link the new tab to the current last tab.
        // then set the new tab's previous pointer to the current last tab. Update the tail (last tab) 
        // to be the new tab. set the new tab as the current tab
        else {
            tail->next = newTab;
            newTab->prev = tail;
            tail = newTab;
            current = newTab;
        }
    }

    // The switchToPrevTab() function moves the focus from the current tab to the one before it.If a previous tab 
    // exists, it shows the tab's details such as its URL, name, and memory usage. If not, it tells the user that 
    // there is no previous tab available.
    // The switchToPrevTab() function was worked on by Alley Hernandez
    void switchToPrevTab() {
        // check if the current tab is nullptr or if the previous tab is a nullptr
        if (!current || !current->prev) {
            // if true then prompt message that there is no previous tab.
            std::cout << "No previous tab" << std::endl;
        }
        // If there is a previous tab, then move the focus to the previous tab and print out the details of the previous tab,
        // including its URL, name, and memory usage.
        else {
            current = current->prev;
            std::cout << "URL: " << current->url << ", Name: " << current->name << ", Memory: " << current->memory << std::endl;
        }
    }

    // The switchToNextTab() function changes your view from the current open tab to the next one. If there is a tab after 
    // the current one, it will show you the information of that tab. If there isn’t another tab to go to, it will tell you 
    // “No next tab” instead.
    // The switchToNextTab() function was worked on by Alley Hernandez
    void switchToNextTab() {
        // check if the current tab is not null and if there is a next tab in the list.
        if (!current || !current->next) {
            // if true then prompt message
            std::cout << "No next tab" << std::endl;
        }
        // If there is a next tab, update the current tab pointer to point to the next tab in the list.
        // Then, print the details of the new current tab.
        else {
            current = current->next;
            std::cout << "URL: " << current->url << ", Name: " << current->name << ", Memory: " << current->memory << std::endl;
        }
    }

    // The closeCurrentTab() function removes the present tab in the browser and automatically switches to the next tab. 
    // It then displays a message stating “Now the current tab = ” followed by the name of this new current tab.
    // The closeCurrentTab() was worked on by both Alley Hernandez and Trang Nguyen
    void closeCurrentTab() {
        // Check if there is no current tab open
        // Trang Nguyen
        if (!current) {
            std::cout << "No tab is open to close!" << std::endl; 
            return; 
        }
        // If this is the only tab in the browser
        // Trang Nguyen
        if (head == tail) {
            delete current;
            head = tail = current = nullptr;
            std::cout << "All tabs are closed now!" << std::endl;
            return;
        }

        Tab<T>* temp = current;

        // If current tab is the first tab
        // Alley Hernandez
        if (current == head) {
            head = head->next;
            head->prev = nullptr;
            current = head;  // Setting the next tab as current
        }
        // If current tab is the last tab
        // Alley Hernandez
        else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
            current = tail;  // Setting the previous tab as current
        }
        // If current tab is in the middle
        // Alley Hernandez
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;  // Setting the next tab as current
        }

        // Tram Nguyen
        std::cout << "Closed tab: " << temp->name << std::endl;
        std::cout << "Now the current tab = " << current->name << std::endl;
        delete temp;
    }
       

    // The bookmarkCurrent() function bookmarks the current tab, saving its name and URL as a pair 
    // in a vector, but only if the tab is still open. This function also checks for duplicates. If there
    // is a duplicate the message “The bookmark is already added!!” will be displayed
    // The bookmarkCurrent() function was worked on by Trang Nguyen
    void bookmarkCurrent() {
        // Check if there is a current tab open. If not, print a message and return from the function.
        if (!current) {
            std::cout << "No current tab to bookmark!" << std::endl;
            return;
        }

        // Iterate through the existing bookmarks to check for duplicates.
        for (const auto& bookmark : bookmarks) {
            if (bookmark.first == current->name && bookmark.second == current->url) {
                std::cout << "The bookmark is already added!!" << std::endl;
                return;
            }
        }

        // If no duplicate was found, add the current tab's name and URL as a new bookmark.
        bookmarks.emplace_back(current->name, current->url);
        // Print a confirmation message, showing which tab was bookmarked.
        std::cout << "Bookmark added: " << current->name << " (" << current->url << ")" << std::endl;
    }

    // The showBookmarkTab() shows the list of bookmarks
    // The showBookmarkTab() function was worked on by Trang Nguyen
    void showBookmarkTab() const {
        // Check if there are no bookmarks. If the bookmarks list is empty, print a message and return.
        if (bookmarks.empty()) {
            std::cout << "No bookmarks available." << std::endl;
            return;
        }

        std::cout << "Bookmarks:" << std::endl;
        for (const auto& bookmark : bookmarks) {
            std::cout << bookmark.first << " (" << bookmark.second << ")" << std::endl;
        }
    }

    // The moveCurrentToFirst() functions moved the current tab to the first position
    // The moveCurrentToFirst() function was worked on by Trang Nguyen
    void moveCurrentToFirst() {
        // Check if there is a current tab selected. If not, notify the user and return.
        if (!current) {
            std::cout << "No current tab to move!" << std::endl;
            return;
        }

        // If current has a next tab, update its previous pointer; else update the tail.
        if (current == head) {
            std::cout << "Current tab is already at the first position." << std::endl;
            return;
        }

        // Remove current tab from its position
        current->prev->next = current->next;

        if (current->next) {
            current->next->prev = current->prev;
        }
        else {
            tail = current->prev; // Update tail if current was the last tab
        }

        // Move current tab to the first position
        current->prev = nullptr;
        current->next = head;
        head->prev = current;
        head = current;

        std::cout << "Moved " << current->name << " to the first position." << std::endl;
    }

    // The total_memory() function adds up and returns the total memory used by the browser.
    // The total_memory() function was worked on by Alley Hernandez
    T total_memory() const {
        // Initialize a variable to keep track of the total memory consumption, starting at 0.
        T totalMemory = 0;
        Tab<T>* currentTab = head;

        // Iterate through the linked list of tabs.
        while (currentTab != nullptr) {
            totalMemory += currentTab->memory;
            currentTab = currentTab->next;
        }
        std::cout << "Total Memory Consumption = " << totalMemory << "MB" << std::endl;
        return totalMemory;
    }

    // The deleteTab() function was worked on by Alley Hernandez
    // The deleteTab() function deletes the tab with the highest memory consumption
    void deleteTab() {
        // First, check if there are any tabs open. If not, inform the user and exit the function.
        if (!head) {
            std::cout << "Browser is empty. Cannot delete a tab." << std::endl;
            return;
        }

        Tab<T>* tabToDelete = head;
        Tab<T>* iterator = head->next;

        // Traverse the list of tabs.
        // If the current tab uses more memory than the current 
        // maxMemoryTab, update maxMemoryTab.
        while (iterator) {
            if (iterator->memory > tabToDelete->memory) {
                tabToDelete = iterator;
            }
            iterator = iterator->next;
        }

        // Remove tab from list
        if (tabToDelete->prev) {
            tabToDelete->prev->next = tabToDelete->next;
        }
        else {
            head = tabToDelete->next;
        }

        if (tabToDelete->next) {
            tabToDelete->next->prev = tabToDelete->prev;
        }
        else {
            tail = tabToDelete->prev;
        }

        // Update current if necessary
        if (current == tabToDelete) {
            current = tabToDelete->next ? tabToDelete->next : tabToDelete->prev;
        }

        std::cout << "Deleted tab " << tabToDelete->name << " with memory consumption " << tabToDelete->memory << "MB" << std::endl;

        delete tabToDelete;
    }

    //Add display method in Browser template class
    void display() {
        auto curr = head;
        std::cout << "Browser tab list = " << std::endl;
        while (curr) {
            std::cout << "| " << curr->name << " x|-->";
            curr = curr->next;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    
};

int main() {
    Browser<double> b1;
    b1.addNewTab("https://www.google.com", "Google", 23.45);
    b1.display();
    std::cout << "Switch to previous tab = " << std::endl;
    b1.switchToPrevTab();
    std::cout << "Switch to Next tab = " << std::endl;
    b1.switchToNextTab();
    b1.addNewTab("https://www.youtube.com", "YouTube", 56);
    b1.bookmarkCurrent();
    b1.display();
    b1.addNewTab("https://www.geeksforgeeks.com", "GeeksForGeeks", 45.78);
    b1.bookmarkCurrent();
    b1.addNewTab("https://chat.openai.com", "ChatGPT", 129);
    b1.addNewTab("https://linkedin.com", "LinkedIn", 410);
    b1.bookmarkCurrent();
    b1.addNewTab("https://github.com", "Github", 110);
    b1.addNewTab("https://kaggle.com", "Kaggle", 310);
    b1.bookmarkCurrent();
    b1.display();
    std::cout << "Total memory consumption = " << b1.total_memory() << "MB" << std::endl;
    b1.showBookmarkTab();
    b1.moveCurrentToFirst();
    b1.display();
    b1.deleteTab();
    b1.display();
    std::cout << "Switch to next tab = " << std::endl;
    b1.switchToNextTab();
    std::cout << "Switch to previous tab = " << std::endl;
    b1.switchToPrevTab();
    b1.closeCurrentTab();
    b1.display();
    std::cout << "Switch to previous tab = " << std::endl;
    b1.switchToPrevTab();
    b1.closeCurrentTab();
    b1.display();
    b1.showBookmarkTab();
    std::cout << "Total Memory Consumption = " << b1.total_memory() << "MB" << std::endl;
    b1.deleteTab();
    b1.display();
    b1.addNewTab("https://docs.google.com/", "Google Docs", 102.34);
    b1.display();
    std::cout << "Switch to previous tab = " << std::endl;
    b1.switchToPrevTab();
    std::cout << "Switch to previous tab = " << std::endl;
    b1.switchToPrevTab();
    std::cout << "Switch to previous tab = " << std::endl;
    b1.switchToPrevTab();
    b1.bookmarkCurrent();
    b1.showBookmarkTab();
    b1.total_memory();
    b1.deleteTab();
    b1.display();
    return 0;
}