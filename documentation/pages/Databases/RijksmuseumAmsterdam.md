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

\subsection rijksmuseum_api_terms Terms and conditions

All object descriptions available via this API are covered by a Creative Commons
0 licence. The images are in the Public Domain, according to which the data and
the images are free of rights and may be copied, changed, distributed or exported
without the Rijksmuseum’s permission.

The Rijksmuseum uses other standards and larger formats if a digital image is used for a publication or other printing forms. Our ordinary terms and conditions of use also apply to the digital image on our website which is not part of this set.
Objections

As far as we have been able to determine, all objects and images in the API are free of rights. While we have done our very best to ascertain whether all of the works are free of rights, it is possible that some are copyright protected. Please send an e-mail to api@rijksmuseum.nl.

If you believe that we have breached the copyright that applies to a particular image, we will remove the image concerned from the API set as quickly as possible.
Fair Use

In addition to the CC0 licence, the Rijksmuseum also applies a Fair Use policy regarding the reuse of our metadata and our images. This involves the following:

 - The metadata and images must be used as far as possible in the spirit of the creator and in keeping with his/her intentions;
 - Our object descriptions must not be used in an obscene or offensive manner;
 - Apps and web applications developed using our API must be registered with the Rijksmuseum. We will report interesting and relevant apps on our website;
 - The information regarding the collection will be updated. We request that you update the app or web application on a regular basis.

\section rijksmuseum_api The Rijksmuseum API

The data sets are provided via a simple \ref xml web service which is based on
the OAI/PMH protocol. In short, the system works as follows:
Every request must be accompanied by the API key provided in the api key parameter.

    http://www.rijksmuseum.nl/api/oai/[YOURKEY]/

The verb parameter can be used to ‘ask’ the API to retrieve the data. The following
verbs can be used to retrieve all the data.

\subsection rijksmuseum_images Images

The Rijksmuseum images are available in JPEG format. The images have been saved at 300 dpi and the size of the files (on average) is between 2 MB and 5 MB. The images were recorded in controlled conditions and show the actual colours.

Images can be downloaded, but we advise you instead (if possible) to create a link to the images on our webserver so that you always access the best and most up-to-date images. The Rijksmuseum uses other quality standards and file formats for publications and other printing forms. Please fill out the form on the Photoservice page if you would like to use our images for such applications.

The metadata includes the url for the image of the object. This url is always for the largest image size (2500x2500 pixels). A parameter can be included with this url so that the user can change the scale and reduce the size of the image to 100x100 or 200x200.

 - Full image of The Night Watch: http://www.rijksmuseum.nl/media/assets/SK-C-5
 - The Night Watch at 100 x 100: http://www.rijksmuseum.nl/media/assets/SK-C-5?100x100
 - The Night Watch at 200 x 200: http://www.rijksmuseum.nl/media/assets/SK-C-5?200x200

If you want a different size, we advise you to change the scale of the image yourself.

\section rijksmuseum_references References

- [Instructions for use](https://www.rijksmuseum.nl/en/api/instructions-for-use)
- [Terms and conditions for using the Rijksmuseum API](https://www.rijksmuseum.nl/en/api/terms-and-conditions-of-use)
- Example projects using the API
  - [PHP classes to access the Rijksmuseum API](https://github.com/hay/rijksmuseumapi)
  - [Rijksmuseum Wallpaper](https://github.com/tacoe/rijksmuseum-wallpaper)
  - [Rijksmuseum app inside the Spotify](https://github.com/floreskul/rijksmuseum-spotify)