// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


//custom exception which extends from std::exception
//allows for custom message
struct trembleyException : public std::exception {
    const char* what() const throw() {
        return "Trembley custom exception occured";
    }
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception
    //Uses 'throw' to throw an exception from std::exception
    throw std::exception();

    std::cout << "Running Even More Custom Application Logic." << std::endl;
     

    return true;
}
void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {

        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    //if do_custom_application_logic() fails, catch std:: excpetion and display a message
    catch (const std::exception& exception) {
        std::cout << "do_custom_application_logic - Error from exception: " << exception.what() << std::endl;
    }
    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main
    
    throw trembleyException();
    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    if (den == 0) {
        throw std::runtime_error("Division by 0"); //standard C++ exception
    }
    return (num / den);
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;

    //Handle division by 0 by catching with std::exception
    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::exception& exception) {
        std::cout << "do_division - Error from exception: " << exception.what() << std::endl;
    }
}


  // TODO: Create exception handlers that catch (in this order):
  //  your custom exception
  //  std::exception
  //  uncaught exception 
  //  that wraps the whole main function, and displays a message to the console.
int main()
{
    try {
        std::cout << "Exceptions Tests!" << std::endl;
        do_division();
        do_custom_application_logic();
    }
    //custom exception
    catch (const trembleyException& exception) {
        std::cout << "Catch: " << exception.what() << std::endl;
    }
    //std::exception
    catch (const std:: exception & exception) {
        std::cout << "Standard exception occured, Catch: " << exception.what() << std::endl;
    }
    //unhandled exceptions
    catch(...){
        std::cout << "Unexpected exception has been caught" << std::endl;
    }
    

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu