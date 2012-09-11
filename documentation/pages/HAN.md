Hidden Automatic Navigator (HAN)    {#han}
==========================

\tableofcontents

HAN can be seen as a gateway for the HTTP data flow between the browser und the WWW-Server, substituting parts of the HTML pages, i.e. every link points to HAN. In this way the HAN-Server can automatically authenticate by the providers of e-journals or online-databases, navigating the way to the destination page and skip unimportant pages.

\section han_technical Technical information

The HAN-Server is not a Proxy-Server, so that it doesn't have to be authenticated as a proxy by the browsers. Instead the HAN-Server provides a persistent URL for each e-journal/every online database that you can simply address in your Intranet www-server, for example.

Before a user can access a HAN-PURL and thereby the online sites, it is recommendable the users have already been authenticated. For this purpose HAN provides a variety of authentication services:

  - IP/DNS-address checker
  - NT-registration for a particular domain
  - Registration over a LDAP-Interface (Microsoft ADS, Netscape iPlanet)
  - Microsoft Active Directory
  - NetMan Registration
  - PICA (CBS und LBS)
  - SISIS

\subsection han_functional_overview Functional Overview

  - Authentication by the HAN-Server using the HTTP or HTML-Form
  - Automatic navigation in the Internet services
  - Automatic authentication for Internet services liable to charges
  - Access control for Internet services
  - License for the Internet services
  - Metering of the chargeable Internet-services with statistical evaluation
  - Interface to the Electronic Journal Library in Regensburg (HAN Interface to EJL)

\subsection han_system_requirements System requirements

  - Apache Server for Windows-Platforms Version 2.x (Version 2.046 or higher)
  - Windows Server 2003
  - Windows 2000 (Service Pack 2 or higher)
  - Windows NT 4 Server/Terminal server (Service Pack 6a or higher)

\section han_references References

  - [www.hh-han.com](http://www.hh-han.com)
  - [HAN Product Information](http://www.hh-software.com/hh2003/index.cfm/ly/0/0/HAN100/0/50,HAN100/0$.cfm)
