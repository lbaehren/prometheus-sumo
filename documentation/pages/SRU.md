SRU (Search and Retrieve URL)    {#sru}
=============================

\tableofcontents

\section sru_overview Overview

SRU is a standard \ref xml -focused search protocol for Internet search queries,
utilizing CQL (Contextual Query Language), a standard syntax for representing queries.

The SRU Initiative recognizes the importance of Z39.50 (as currently defined and
deployed) for business communication. While SRU focuses on getting information
to the user, building on Z39.50 semantics enables the creation of gateways to
existing Z39.50 systems.

SRU combines several Z39.50 features, most notably, the Search, Present, Sort
and Scan Services. Additional features/services may be added later or defined
later as new web services.

\section sru_openurl OpenURL and SRU

SRU is sometimes compared with OpenURL. People ask "why isn't OpenURL used for searching, rather than SRU?"

OpenURL packages metadata, about a desired resource, along with additional context information, into a URL. SRU packages query parameters, which similarly are often metadata about a desired resource, along with protocol information, into a URL. So there are similarities between OpenURL and SRU.

But the comparison is superficial. It's useful to look more closely at the OpenURL model. OpenURL links a user to an appropriate resource. It does this in part by including bibliographic information about the resource. As that information might lead to several resources, context information is also included in the URL, to help select the most appropriate from among those several resources.

In a typical OpenURL scenario  a user (requester) accesses a server (referrer) on which there is an article (referring entity) which cites a reference (referent). The reference looks like it might be a normal link that the user can click, but it's really an OpenURL -- an  HTTP URL, not a URL for a specific resource, but instead, metadata about these context entities (requester, referrer, refering entity, referent). And the base url (i.e. where the url is being sent) isn't the location of the desired resource, instead it is what's known as a resolver -- a server designed to take all this information and determine what resource the user really wants (or is "most appropriate"). 

> **Note:** There may be an additional step: when the user clicks on the link it might first get a menu of services:  full text, abstract, table of contents, reviews, etc.  The user selects one and this desired  service type is also included in the URL.

So SRU and OpenURL serve very different purposes. One selects records based on search criteria, the other selects a single resource, the one deemed  "most appropriate", from among a number of potential resources, based on context information.

Note also that  OpenURL intends to locate a single resource, while SRU finds all resources that meet specified criteria.  OpenURL generally returns full text of the resource (or if not full text of the resource, text for some desired service). With SRU, the request can specify the format of the response records, and the response might not include any record, but instead indicate a result count (and the user may subsequently retrieve records from the result set).

Thus SRU is an information retrieval protocol. OpenURL is not. On the other hand, OpenURL, clearly, addresses functions that SRU doesn't contemplate.

\section sry_examples Examples

1. **Start with an Explain request.**
~~~~
http://z3950.loc.gov:7090/voyager
~~~~
The Explain record for an SRU server is an XML document that explains features, defaults, etc. It may be used by a client to self-configure and allow it to fully interoperate with the server. As an example, for the above server (z3950.loc.gov:7090) you can see that "title" is a supported index. Advanced clients may make use Explain information in more sophisticated ways, but this is not strictly necessary. Most clients don't rely on Explain.
2. **Next, a simple search for the term "dinosaur".**
~~~~
http://z3950.loc.gov:7090/voyager?version=1.1& operation=searchRetrieve&query=dinosaur
~~~~
For this SRU request, no records are requested in the response. The response shows that there are 1634 records containing the term "dinosaur". (This is subject to change since this is a production database, but there were 1634 such records when this page was created.)
3. **Now the user wants to see the first of the 1634 records.**
~~~~
http://z3950.loc.gov:7090/voyager?version=1.1&operation=searchRetrieve&query=dinosaur&maximumRecords=1
~~~~
The response includes a single record -- a marcxml record.  Note that the request does not specify a particular schema for the record-to-be-retrieved, and so the default, marcxml, is used.
4. **Retrieve the same record, different schema -- DC.**
~~~~
http://z3950.loc.gov:7090/voyager?version=1.1&operation=searchRetrieve&query=dinosaur&maximumRecords=1&recordSchema=dc
~~~~
Again the response includes a single record -- this time a DC record.  Note that DC is one of the supported-schemas listed in the Explain record.
5. **Retrieve the next five records:**
~~~~
http://z3950.loc.gov:7090/voyager?version=1.1&operation=searchRetrieve&query=dinosaur&startRecord=2&maximumRecords=5&recordSchema=dc
~~~~
The response includes five records, each wrapped with a `<recordPostition>`, two through six.
6. **Search for "dinosaur" in the title.**
~~~~
http://z3950.loc.gov:7090/voyager?version=1.1&operation=searchRetrieve&query=title=dinosaur
~~~~
This query turned up 1238 records. (Similarly, as in step 2, this is subject to change since this is a production database, but there were 1238 such records when this page was created.)

\section sru_references References

* [Standards at the Library of Congress](http://www.loc.gov/standards/sru/index.html)
* [Software and Tools](http://www.loc.gov/standards/sru/resources/tools.html)