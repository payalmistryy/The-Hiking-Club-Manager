/*
Payal Mistry
CS 302 - Programming Methodologies and
Software Implementation
Assignment 2 - The Hiking Club
April 27 2026
Filename: dll_Mistry.tpp

This file implements the templated Node and DLL classes
declared in dll_Mistry.h. The DLL's repetitive operations
(insert, remove, display, retrieve, remove_all) all use
private recursive helpers. Memory management uses raw
pointers; the rule of three handles deep copying and
cleanup.
*/



//*Node implementations*

//Default constructor for Node
//Initializes data with its default constructor and sets
//next and prev to nullptr.
//Input:none
//Output: a default-initialized Node
template <typename T>
Node<T>::Node() : data(), next(nullptr), prev(nullptr)
{
}


//Parameterized constructor for Node
//Initializes data from a_data; next and prev start null.
//Input: a_data - the value to store in this node
//Output: a Node holding a copy of a_data
template <typename T>
Node<T>::Node(const T & a_data)
    : data(a_data), next(nullptr), prev(nullptr)
{
}


//Modifiable accessor for data
//Input: none
//Output: reference to this node's data
template <typename T>
T & Node<T>::get_data()
{
    return data;
}


//Read-only accessor for data
//Input: none
//Output: const reference to this node's data
template <typename T>
const T & Node<T>::get_data() const
{
    return data;
}


//Reference accessor for the next pointer
//Returning by reference lets DLL helpers update next
//directly during insert and remove operations.
//Input: none
//Output: reference to the next pointer
template <typename T>
Node<T> * & Node<T>::get_next()
{
    return next;
}


//Reference accessor for the prev pointer
//Input: none
//Output: reference to the prev pointer
template <typename T>
Node<T> * & Node<T>::get_prev()
{
    return prev;
}


//*DLL rule of three and constructors*

//Default constructor
//Creates an empty list with head and tail both nullptr.
//Input: none
//Output: an empty DLL
template <typename T>
DLL<T>::DLL() : head(nullptr), tail(nullptr)
{
}


//Copy constructor
//Creates a new DLL as a deep copy of source. Walks
//source's chain and builds a parallel chain of fresh
//nodes. If source is empty, this DLL stays empty.
//Input: source - the DLL being copied
//Output: a new DLL with independent dynamic memory
template <typename T>
DLL<T>::DLL(const DLL<T> & source) : head(nullptr), tail(nullptr)
{
    copy_chain(head, source.head, tail);
}


//Destructor
//Releases every node in the list via remove_all_helper.
//Input: none
//Output: none — frees all dynamic memory
template <typename T>
DLL<T>::~DLL()
{
    remove_all_helper(head);
    tail = nullptr;
}


//Assignment operator
//Self-assignment safe. Releases the existing chain,
//then deep-copies source's chain into this DLL.
//Input: rhs - the DLL being assigned from
//Output: reference to *this
template <typename T>
DLL<T> & DLL<T>::operator=(const DLL<T> & rhs)
{
    if (this != &rhs)
    {
        remove_all_helper(head);
        tail = nullptr;
        copy_chain(head, rhs.head, tail);
    }
    return *this;
}


//Recursive helper for the copy constructor and operator=
//Walks source's chain. For each source node, allocates a
//new node holding the same data, links it into the chain
//being built, and updates dest_tail so the new DLL's tail
//is correct when recursion finishes.
//Input:  dest      - reference to the next pointer slot to fill
//        source    - the source node currently being copied
//        dest_tail - reference to the new DLL's tail pointer
//Output: none 
template <typename T>
void DLL<T>::copy_chain(Node<T> * & dest,
                        Node<T> * source,
                        Node<T> * & dest_tail)
{
    if (!source)
        return;

    dest = new Node<T>(source->get_data());
    dest_tail = dest;
    copy_chain(dest->get_next(), source->get_next(), dest_tail);

    if (dest->get_next())
        dest->get_next()->get_prev() = dest;
}


//*Public wrappers + recursive helpers for the five core ops*

//Insert a new node holding item at the back of the list
//Wrapper handles the empty list special case.
//Otherwise delegates to the recursive helper.
//Input: value inserted (item)
//Output: none
template <typename T>
void DLL<T>::insert(const T & item)
{
    if (!head)
    {
        head = new Node<T>(item);
        tail = head;
        return;
    }
    insert_at_back(head, nullptr, item);
}


//Recursive helper for insert
//Walks to the end of the chain. When current is null, the
//previous step's next pointer slot is where the new node
//goes. Sets prev_node as the new node's prev pointer and
//updates the DLL's tail pointer.
//Input:  current   - reference to the next-pointer slot being walked
//        prev_node - the node whose next pointer is being filled
//        item      - the value to insert
//Output: none 
template <typename T>
void DLL<T>::insert_at_back(Node<T> * & current,
                            Node<T> * prev_node,
                            const T & item)
{
    if (!current)
    {
        current = new Node<T>(item);
        current->get_prev() = prev_node;
        tail = current;
        return;
    }
    insert_at_back(current->get_next(), current, item);
}


//Remove the first node whose data equals item
//Throws EmptyList if the list is empty. Throws ItemNotFound
//if no node matches. Otherwise unlinks and deletes the node.
//Input:  item - the value to find and remove
//Output: none
template <typename T>
void DLL<T>::remove(const T & item)
{
    if (!head)
        throw EmptyList{};
    if (!remove_helper(head, item))
        throw ItemNotFound{};
}


//Recursive helper for remove
//Walks the chain looking for a node whose data equals item.
//When found, unlinks the node by routing the previous node's
//next pointer past it, then deletes the node. Returns true if
//a node was removed, false if the end of the chain was reached
//without finding a match.
//Input:  current - reference to the next-pointer slot being walked
//        item    - the value to find
//Output: true if removed, false if not found
template <typename T>
bool DLL<T>::remove_helper(Node<T> * & current, const T & item)
{
    if (!current)
        return false;

    if (current->get_data() == item)
    {
        Node<T> * to_delete = current;
        Node<T> * next_node = current->get_next();

        current = next_node;
        if (next_node)
            next_node->get_prev() = to_delete->get_prev();
        else
            tail = to_delete->get_prev();

        delete to_delete;
        return true;
    }

    return remove_helper(current->get_next(), item);
}


//Display every node's data, one per line
//Wrapper passes head to the recursive helper. If the list
//is empty, the helper's base case handles it.
//Input: none
//Output: none — writes to cout
template <typename T>
void DLL<T>::display() const
{
    display_helper(head);
}


//Recursive helper for display
//Prints the current node's data, then recurses on next.
//Input: current - the node currently being displayed
//Output: none — writes to cout
template <typename T>
void DLL<T>::display_helper(Node<T> * current) const
{
    if (!current)
        return;
    std::cout << current->get_data() << "\n";
    display_helper(current->get_next());
}


//Retrieve a copy of the data in the first node matching item
//Throws EmptyList if the list is empty. Throws ItemNotFound
//if no node matches. Returns a copy by value, not a reference,
//Input:  item - the value to search for
//Output: a copy of the matching node's data
template <typename T>
T DLL<T>::retrieve(const T & item) const
{
    if (!head)
        throw EmptyList{};
    return retrieve_helper(head, item);
}


//Recursive helper for retrieve
//Walks the chain. If current is null, throws ItemNotFound.
//If current matches, returns a const reference
//Input:  current - the node currently being checked
//        item    - the value to search for
//Output: const reference to the matching node's data
template <typename T>
const T & DLL<T>::retrieve_helper(Node<T> * current, const T & item) const
{
    if (!current)
        throw ItemNotFound{};
    if (current->get_data() == item)
        return current->get_data();
    return retrieve_helper(current->get_next(), item);
}


//Remove every node from the list
//Wrapper delegates to the recursive helper which deletes
//each node from head to tail. Resets head and tail to null
//on completion.
//Input:  none
//Output: none — empties the list
template <typename T>
void DLL<T>::remove_all()
{
    remove_all_helper(head);
    tail = nullptr;
}


//Recursive helper for remove_all
//Walks the chain deleting each node. Sets the head pointer
//to null after the cleanup so the caller doesn't reuse a
//dangling pointer.
//Input: current - reference to the head pointer being emptied
//Output: none — frees memory and nulls the pointer
template <typename T>
void DLL<T>::remove_all_helper(Node<T> * & current)
{
    if (!current)
        return;
    remove_all_helper(current->get_next());
    delete current;
    current = nullptr;
}


//Returns true if the list contains no nodes
//Input: none
//Output: true if empty, false otherwise
template <typename T>
bool DLL<T>::is_empty() const
{
    return head == nullptr;
}
