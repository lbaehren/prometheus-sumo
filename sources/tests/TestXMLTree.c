/*!
  \file TestXMLTree.c

  \brief Navigates the tree of a \ref xml document to print element names
  \author Dodji Seketeli
  \copyright see Copyright for the status of this software.
  
  \b Purpose: Parse a file to a tree, use \c xmlDocGetRootElement() to get the
  root element, then walk the document and print all the element name in document
  order.

  \b Usage
  \verbatim
  tree1 filename_or_URL
  \endverbatim
 */
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#ifdef LIBXML_TREE_ENABLED

int nofNodes = 0;

//_______________________________________________________________________________
//                                                            print_element_names

/*!
  \brief Prints the names of the all the xml elements

  \param a_node - the initial xml node to consider.

  Prints the names of the all the xml elements that are siblings or children of
  a given xml node.
*/
static void
print_element_names(xmlNode * a_node)
{
  xmlNode *currentNode = NULL;

  nofNodes++;
  
  for (currentNode = a_node; currentNode; currentNode = currentNode->next) {
    if (currentNode->type == XML_ELEMENT_NODE) {
      printf("node type: Element, name: %s\n", currentNode->name);
    }
    
    print_element_names(currentNode->children);
  }
}

// === Program main function ====================================================

/*!
  Simple example to parse a file called "file.xml", walk down the DOM, and
  print the name of the xml elements nodes.
*/
int
main(int argc, char **argv)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    if (argc != 2)
        return(1);

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
    }

    /* Get the root element node */
    root_element = xmlDocGetRootElement(doc);
    printf("Name of the root node = %s\n", root_element->name);

    print_element_names(root_element);

    /* free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    printf ("Finished parsing of %i nodes.", nofNodes);

    return 0;
}
#else
int main(void) {
    fprintf(stderr, "Tree support not compiled in\n");
    exit(1);
}
#endif
