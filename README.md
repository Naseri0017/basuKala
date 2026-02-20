#  BasuKala - Advanced Store Management System

BasuKala is a high-performance store management simulator developed in **C++**. It demonstrates the practical application of complex data structures to handle product inventory, user balances, and prioritized order processing.



##  Key Features

-   **Multi-Structure Inventory:** Products are organized into 5 categories, each managed by a **Binary Search Tree (BST)**.
-   **Intelligent Search:** A **Trie (Prefix Tree)** implementation allows for lightning-fast product searching by name.
-   **Real-time Trending:** A **Max-Heap** tracks product sales to instantly display the top-selling items.
-   **Stable Order Processing:** A custom-built **Stable Priority Queue** handles orders based on user scores, ensuring fairness (FIFO) for equal scores.
-   **Local Shopping Cart:** An **Undo/Redo** system implemented using a **Stack** for managing the cart before checkout.
-   **Data Persistence:** Automatic synchronization with `products_db.txt` and binary storage for user data (`info.bin`).

## 🛠 Data Structures Used

| Feature | Data Structure | Why? |
| :--- | :--- | :--- |
| **Category Management** | Binary Search Tree (BST) | Fast alphabetical sorting and $O(\log n)$ retrieval. |
| **Best Sellers** | Max-Heap | Efficiently maintaining the highest sales value at the root. |
| **Search Engine** | Trie | $O(L)$ search complexity where $L$ is the length of the string. |
| **Order Queue** | Stable Priority Queue | Prioritizing high-score users while maintaining arrival order. |
| **Purchase History** | Linked List | Dynamic storage of historical transactions. |



##  Project Structure

```text
BasuKala/
├── include/           # Header files (.hpp)
├── src/               # Source files (.cpp)
├── files/             # Database (products_db.txt, info.bin)
└── CMakeLists.txt     # Build configuration
