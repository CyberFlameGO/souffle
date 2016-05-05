/*
 * Copyright (c) 2015, Oracle and/or its affiliates. All Rights reserved
 * 
 * The Universal Permissive License (UPL), Version 1.0
 * 
 * Subject to the condition set forth below, permission is hereby granted to any person obtaining a copy of this software,
 * associated documentation and/or data (collectively the "Software"), free of charge and under any and all copyright rights in the 
 * Software, and any and all patent rights owned or freely licensable by each licensor hereunder covering either (i) the unmodified 
 * Software as contributed to or provided by such licensor, or (ii) the Larger Works (as defined below), to deal in both
 * 
 * (a) the Software, and
 * (b) any piece of software and/or hardware listed in the lrgrwrks.txt file if one is included with the Software (each a "Larger
 * Work" to which the Software is contributed by such licensors),
 * 
 * without restriction, including without limitation the rights to copy, create derivative works of, display, perform, and 
 * distribute the Software and make, use, sell, offer for sale, import, export, have made, and have sold the Software and the 
 * Larger Work(s), and to sublicense the foregoing rights on either these or other terms.
 * 
 * This license is subject to the following condition:
 * The above copyright notice and either this complete permission notice or at a minimum a reference to the UPL must be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/************************************************************************
 *
 * @file driver.cpp 
 *
 * Driver program for invoking a Souffle program using the OO-interface
 *
 ***********************************************************************/

#include "souffle/SouffleInterface.h"

using namespace souffle; 

/**
 * Declare static vars for program factory 
 */
ProgramFactory *ProgramFactory::base = nullptr;

/**
 * Error handler
 */ 
void error(std::string txt) 
{
   std::cerr << "error: " << txt << "\n"; 
   exit(1); 
} 

/**
 * Main program
 */
int main(int argc, char **argv)
{
   // create an instance of program "insert_print"
   if(Program *prog = ProgramFactory::newInstance("insert_print")) {
      // get input relation "edge" 
      if(Relation *edge = prog->getRelation("edge")) {
         std::vector<std::array<std::string,2>> myData={
            {"A","B"}, 
            {"B","C"}, 
            {"C","D"}, 
            {"D","E"},
            {"E","F"},
            {"F","A"}
         }; 
         for(auto input : myData) { 
            tuple t(edge);
            t << input[0] << input[1];
            edge->insert(t); 
         }

         // run program 
         prog->run(); 

         // print all relations to CSV files in current directory
         // NB: Defaul is current directory
         prog->printAll();

         // free program analysis
         delete prog; 

      } else {
         error("cannot find relation edge");        
      }
   } else {
      error("cannot find program insert_print");        
   }
}
