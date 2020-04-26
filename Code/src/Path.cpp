/**
 * This file contains the implementation of the Path class and all associated member functions that are included in the Path.h file.
 * The Path class is used to hold dimensions of the mower and lawn, and to generate a set of instructions based on these values.
 * 
 * TODO: Add comments describing each method in terms of usage, parameters, and return value
 */

#include "Path.h"
#include <iostream>
#include <cmath>
#include <string>

Path::Path(double length, double width, double carDiameter, double bladeDiameter) {
    m_length = length;
    m_width = width;
    m_carDiameter = carDiameter;
    m_bladeDiameter = bladeDiameter;

    generatePath();
}

Path::~Path() {

}

double Path::getLength() {
    return m_length;
}

double Path::getWidth() {
    return m_width;
}

double Path::getCarDiameter() {
    return m_carDiameter;
}

double Path::getBladeDiameter() {
    return m_bladeDiameter;
}

std::deque<Instruction> Path::getInstructions() {
    return m_instructions;
}

int Path::setLength(double length) {
    m_length = length;
    generatePath();

    return 0;
}

int Path::setWidth(double width) {
    m_width = width;
    generatePath();

    return 0;
}

int Path::generatePath() {
    double firstMoveDistance = 0;
    double secondMoveDistance = 0;
    /*
    m_instructions.push_back("MF3");
    m_instructions.push_back("TR90");
    m_instructions.push_back("MF5");
    m_instructions.push_back("TR90");
    m_instructions.push_back("ur dope <3");
    */

    std::cout << "m_length: " << m_length << std::endl;
    std::cout << "m_width: " << m_width << std::endl;
    std::cout << "m_carDiameter: " << m_carDiameter << std::endl;
    std::cout << "m_bladeDiameter: " << m_bladeDiameter << std::endl;
    std::cout << "\nBegin Path: \n" << std::endl;
    
    // Mower will always start with short side on left (could be input as length or width, depending on user)
    if (m_length > m_width) {
        firstMoveDistance = m_width - m_carDiameter;
        secondMoveDistance = m_length - m_carDiameter * 2;
    } else {
        firstMoveDistance = m_length - m_carDiameter;
        secondMoveDistance = m_width - m_carDiameter * 2;
    }

    // TODO: calc seconds based on firstMoveDistance

    // move forward ___ seconds based on firstMoveDistance
    std::cout << "MF" << firstMoveDistance << std::endl;

    // turn right 90 degrees
    std::cout << "TR90" << std::endl;

    // move forward ___ seconds based on secondMoveDistance
    std::cout << "MF" << secondMoveDistance << std::endl;


    //replaced with helper function
    /*
    m_instructions.push_back("MF"+to_string(firstMoveDistance));
    m_instructions.push_back("TR90");
    m_instructions.push_back("MF"+to_string(secondMoveDistance)) ;
    */

    addAFew("MF", firstMoveDistance, "TR", 90, "MF", secondMoveDistance);


    int loopCount = 0;
    double remainder = 0.0;

    // Calculate number of strips we need to cut (lengthwise)
    // The remainder is the width of the final strip that we need to cut
    if (m_length > m_width) {
        loopCount = std::ceil((m_width - m_carDiameter) / m_bladeDiameter);
        remainder = calculateRemainder(m_width - m_carDiameter, m_bladeDiameter);
    } else {
        loopCount = std::ceil((m_length - m_carDiameter) / m_bladeDiameter);
        remainder = calculateRemainder(m_length - m_carDiameter, m_bladeDiameter);
    }

    // TODO: subtract buffer amount from stripWidth (to avoid missing small lines of grass)
    double stripWidth = m_bladeDiameter; // amount to move forward between strips (moving down)
    double stripLength = secondMoveDistance - m_bladeDiameter; // amount to move forward for each strip

    // Generate instructions for each strip of grass that we need to cut
    for (int i = 0; i < loopCount - 1; i++) {

        // Mower will turn left/right, depending on if we are cutting an even or odd numbered strip
        if (i % 2 == 0) {
            std::cout << "TR90" << std::endl;
            std::cout << "MB" << m_carDiameter - stripWidth << std::endl;
            std::cout << "TR100" << std::endl;

            //replaced with helper function
            /*
            m_instructions.push_back("TR90");
            m_instructions.push_back("MF"+to_string(stripWidth));
            m_instructions.push_back("TR90");
            */
            addAFew("TR", 90, "MB", m_carDiameter - stripWidth, "TR", 100);

        } else {
            std::cout << "TL90" << std::endl;
            std::cout << "MB" << m_carDiameter - stripWidth << std::endl;
            std::cout << "TL100" << std::endl;

            //replaced with helper function
            /*
            m_instructions.push_back("TL90");
            m_instructions.push_back("MF"+to_string(stripWidth));
            m_instructions.push_back("TL90");
            */

            addAFew("TL", 90, "MB", m_carDiameter - stripWidth, "TL", 100);
        }
        
        std::cout << "MF" << stripLength << std::endl;
        //m_instructions.push_back("MF"+std::to_string(stripLength));
        addAFew("MF", stripLength);
    }

    // Generate instructions for cutting final strip (usually this will be smaller than m_bladeDiameter, so we use remainder value)
    if (loopCount % 2 == 0) {
        std::cout << "TR90" << std::endl;
        //m_instructions.push_back("TL90");

        addAFew("TR", 90);
        addConditionally(remainder, "MB", stripWidth, remainder);
        // TODO: make into a helper function to be used in both even and odd loops

        //replaced with helper function
        /*if (remainder == 0) {
            std::cout << "MF" << stripWidth << std::endl;
            m_instructions.push_back("MF"+to_string(stripWidth));
        } else {
            std::cout << "MF" << remainder << std::endl;
            m_instructions.push_back("MF"+to_string(remainder));
        }*/

        // addConditionally(remainder, "MF", stripWidth, remainder);
        /*
        std::cout << "TL90" << std::endl;
        m_instructions.push_back("TL90");

        std::cout << "MF" << stripLength << std::endl;
        m_instructions.push_back("MF"+std::to_string(stripLength));

        // If we cut an even number of strips, we need to add instructions to return to starting position
        std::cout << "TR180" << std::endl;
        m_instructions.push_back("TR180");

        std::cout << "MF" << secondMoveDistance << std::endl;
        m_instructions.push_back("MF"+std::to_string(secondMoveDistance));
        */

        addAFew("TR", 100, "MF", stripLength, "TL", 180, "MF", secondMoveDistance);

        addAFew("TR", 90, "MB", m_carDiameter * 2);
    } else {
        std::cout << "TL110" << std::endl;
        //m_instructions.push_back("TR90");

        addAFew("TL", 110);
        addConditionally(remainder, "MB", stripWidth, remainder);
        // TODO: make into a helper function to be used in both even and odd loops

        //replaced with helper function
        /*if (remainder == 0) {
            std::cout << "MF" << stripWidth << std::endl;
            m_instructions.push_back("MF"+std::to_string(stripWidth));
        } else {
            std::cout << "MF" << remainder << std::endl;
            m_instructions.push_back("MF"+std::to_string(remainder));
        }*/

        // addConditionally(remainder, "MF", stripWidth, remainder);

        //replace with helper
        /*
        std::cout << "TR90" << std::endl;
        m_instructions.push_back("TR90");

        std::cout << "MF" << secondMoveDistance << std::endl;
        m_instructions.push_back("TR"+std:: to_string(secondMoveDistance));
        */
        std::cout << "TL100" << std::endl;
        std::cout << "MF" << secondMoveDistance << std::endl;
        std::cout << "TR100" << std::endl;
        std::cout << "MB" << m_carDiameter << std::endl;

        addAFew("TL", 100, "MF", secondMoveDistance);

        addAFew("TR", 100, "MB", m_carDiameter);
    }


    /*
    std::cout << "TR90" << std::endl;
    m_instructions.push_back("TR90");
    */
    // addAFew("TR", 90, "MB", m_carDiameter);

    std::cout << "-------------------from deque-------------------" << std::endl;

    // while (m_instructions.size() > 0){
    //     std::cout << m_instructions.front().action<< m_instructions.front().value<<std::endl;
    //     m_instructions.pop_front();
    // }

    return 0;
}

double Path::calculateRemainder(double numer, double denom) {
    while (numer >= denom) {
        numer -= denom;
    }

    return numer;
}


// helper function that add a few instructions in a row
void Path::addAFew(std::string firstMove, double firstDis, std::string secMove, double secDis, std::string thirdMove, double thirdDis, std::string fourthMove , double fourthDis){
    //std::string firstDisStr = std::to_string (firstDis);
    //firstDisStr.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    //firstDisStr.erase ( str.find_last_not_of('.') + 1, std::string::npos );
   // m_instructions.push_back(firstMove+firstDisStr);

    m_instructions.push_back(Instruction{firstMove, firstDis});
    if(secMove != ""){
        //std::string secDisStr = std::to_string (secDis);
        //secDisStr.erase ( str.find_last_not_of('0') + 1, std::string::npos );
        //secDisStr.erase ( str.find_last_not_of('.') + 1, std::string::npos );
        //m_instructions.push_back(secMove+secDisStr);

        m_instructions.push_back(Instruction{secMove, secDis});
    }

    if(thirdMove != ""){
        //std::string thirdDisStr = std::to_string (thirdDis);
        //thirdDisStr.erase ( str.find_last_not_of('0') + 1, std::string::npos );
        //thirdDisStr.erase ( str.find_last_not_of('.') + 1, std::string::npos );
        //m_instructions.push_back(thirdMove+thirdDisStr);

        m_instructions.push_back(Instruction{thirdMove, thirdDis});
    }

    if(fourthMove != ""){
        //std::string fourthDisStr = std::to_string (fourthDis);
        //fourthDisStr.erase ( str.find_last_not_of('0') + 1, std::string::npos );
        //fourthDisStr.erase ( str.find_last_not_of('.') + 1, std::string::npos );
        //m_instructions.push_back(thirdMove+fourthDisStr);

        m_instructions.push_back(Instruction{fourthMove, fourthDis});
    }

}


// helper function that add instructions based on a condition
void Path:: addConditionally(double condition, std::string move, double firstDis, double secDis){
    if (condition == 0) {


        //std::string str = std::to_string (firstDis);
        //str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
        //str.erase ( str.find_last_not_of('.') + 1, std::string::npos );

        std::cout << move << firstDis << std::endl;

        m_instructions.push_back(Instruction{move, firstDis});
    } else {

        //std::string str = std::to_string (secDis);
        //str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
        //str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
        std::cout << move << secDis << std::endl;
        m_instructions.push_back(Instruction{move, secDis});
    }
}
