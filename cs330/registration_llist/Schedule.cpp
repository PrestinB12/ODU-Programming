#include <utility>

#include "Schedule.h"

using namespace std::rel_ops;

Schedule::Node::Node(Course c)
    :data(c),
     next(nullptr)
{
}

//------------------------------------------------------------------------------
Schedule::Schedule()
    :head(nullptr),
     tail(nullptr),
     totalCredits(0)
{
}

/**
 * @todo implement this function (it is simliar to Review 01)
 */
Schedule::Schedule(const Schedule& src)

    :head(nullptr),
     tail(nullptr),
     totalCredits(0)
{
    this->head = nullptr;
    this->tail = nullptr;
    this-> totalCredits = 0;
     Node* srcIt = src.head;

    while (srcIt != nullptr)
    {
        this-> appendNoCheck(srcIt->data);
        srcIt = srcIt->next;
    }   // Copy the src Linked List **data**
}

/**
 * @todo implement this function (it is similar to Review 01)
 */
Schedule::~Schedule()
{
   Node *this_iterator = nullptr;
   Node *to_delete = nullptr;

   this_iterator = this->head;

   while (this_iterator != nullptr)
   {
       to_delete = this_iterator;

       this_iterator = this_iterator -> next;

       delete to_delete;
       to_delete = nullptr;

       std::cerr << "Deleting the Node" << "\n";
   }
   std::cerr << "Deleting the List" << "\n";

   
}

/**
 * @todo implement this function (it is similar to Review 01)
 */
void Schedule::appendNoCheck(Course course)
{
    Node *new_node = nullptr;

    new_node = new Node(course);

    if (this -> head = nullptr)
    {
        this -> head = new_node;
        this -> tail - new_node;
    }
    else
    {
        (this -> head) -> next = new_node;
        this -> tail = new_node;
    }
    //this -> totalCredits++;
    totalCredits+= course.getCredits();

    new_node = nullptr;
}

/**
 * @todo implement this function
 */
bool Schedule::wouldViolateCreditLimit(Course course) const
{
    if (course.getCredits() > 12)
    {
        return false;
    }
    else (course.getCredits());
    {
        return true;
    }
    
    // The following line is a placeholder (i.e., enough for the code to
    // compile). Remove it when you start implementing this function.
    
}

/**
 * @todo implement this function
 */
bool Schedule::alreadyInSchedule(Course course) const
{
     Node* it = head;


   while (it != nullptr)
   {
        if (it->data.getCrn() == course.getCrn())
        {
            std::cerr << "Course already in your schedule";
            return true;
        }
       it = it -> next;

       std::cerr << "Course is not already in your schedule" << "\n";
   }
   return false;
    
    // Check if the student is registered
    // for a different section of the same course

    // The following line is a placeholder (i.e., enough for the code to
    // compile). Remove it when you start implementing this function.
}

//------------------------------------------------------------------------------
void Schedule::display(std::ostream& outs) const
{
    Node* it = head;

    outs << "  (" << totalCredits << " Total Credits)" << "\n";

    while (it != nullptr) {
        outs << "  - " << (it->data) << "\n";

        it = it->next;
    }
}

//------------------------------------------------------------------------------
Schedule& Schedule::operator=(Schedule rhs)
{
    swap(*this, rhs);

    return *this;
}
