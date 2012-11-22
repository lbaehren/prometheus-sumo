Rijksmuseum Amsterdam    {#rijksmuseum}
=====================

\tableofcontents

\section rijksmuseum_api_collection The API collection

The [Rijksmuseum API](https://www.rijksmuseum.nl/en/api) Collection is a set of
more than 110,000 descriptions of objects (metadata) and digital images from the
Rijksmuseum collection. The works of art and implements in the set date from
ancient times through to the late 19th century and provide an excellent overview
of the richness, diversity and beauty of the Dutch and international heritage.
Unfortunately, copyright restrictions mean that we are not yet able to include
any works from the 20th or 21st centuries.

The set includes paintings and prints (ranging from the great masters of the
Golden Age through to anonymous biblical paintings and other painted objects
from the Middle Ages), 19th-century photographs, ceramics, furniture, silverware,
doll’s houses, miniatures, etc. Digital photographs were taken of all of the
objects in this set. Of course, the Night Watch is included!

\subsection rijksmuseum_api_key Register for an API key

Register for an API key, for access to the API collection. Access to our general
data set is available to all. We can also provide customised data sets. There is
space on the registration form to indicate your interests. If permitted by our
collection registration system and if copyrights allow, your API key can grant
access to specific data sets.

With questions or comments regarding the general data set or specific data sets,
please e-mail api@rijksmuseum.nl.

\section rijksmuseum_api The Rijksmuseum API

The data sets are provided via a simple \ref xml web service which is based on
the OAI/PMH protocol. In short, the system works as follows:
Every request must be accompanied by the API key provided in the api key parameter.

    http://www.rijksmuseum.nl/api/oai/[YOURKEY]/

The verb parameter can be used to ‘ask’ the API to retrieve the data. The following
verbs can be used to retrieve all the data.

\section rijksmuseum_references References

- [Instructions for use](https://www.rijksmuseum.nl/en/api/instructions-for-use)
